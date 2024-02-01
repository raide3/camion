#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

// Structure pour représenter un nœud dans un arbre AVL
typedef struct AVLNode {
    char *key; // Nom de la ville
    int passThroughCount; // Nombre total de trajets passant par cette ville
    int departureCount; // Nombre de trajets partant de cette ville
    struct AVLNode *left;
    struct AVLNode *right;
    int height;
} AVLNode;

// Fonction pour obtenir la hauteur d'un nœud
int getHeight(AVLNode *node) {
    if (node == NULL) {
        return 0;
    }
    return node->height;
}

// Fonction pour obtenir le facteur d'équilibre d'un nœud
int getBalanceFactor(AVLNode *node) {
    if (node == NULL) {
        return 0;
    }
    return getHeight(node->left) - getHeight(node->right);
}

// Rotation gauche
AVLNode *rotateLeft(AVLNode *node) {
    AVLNode *rightChild = node->right;
    AVLNode *temp = rightChild->left;

    rightChild->left = node;
    node->right = temp;

    node->height = fmax(getHeight(node->left), getHeight(node->right)) + 1;
    rightChild->height = fmax(getHeight(rightChild->left), getHeight(rightChild->right)) + 1;

    return rightChild;
}

// Rotation droite
AVLNode *rotateRight(AVLNode *node) {
    AVLNode *leftChild = node->left;
    AVLNode *temp = leftChild->right;

    leftChild->right = node;
    node->left = temp;

    node->height = fmax(getHeight(node->left), getHeight(node->right)) + 1;
    leftChild->height = fmax(getHeight(leftChild->left), getHeight(leftChild->right)) + 1;

    return leftChild;
}

// Insertion d'un nœud dans l'arbre AVL
AVLNode *AVLInsert(AVLNode *root, char *key, int passThroughCount, int departureCount) {
    if (root == NULL) {
        AVLNode *newNode = (AVLNode *)malloc(sizeof(AVLNode));
        if (newNode == NULL) {
            fprintf(stderr, "Erreur : échec d'allocation de mémoire.\n");
            exit(EXIT_FAILURE);
        }
        newNode->key = strdup(key);
        newNode->passThroughCount = passThroughCount;
        newNode->departureCount = departureCount;
        newNode->left = NULL;
        newNode->right = NULL;
        newNode->height = 1;
        return newNode;
    }

    // Insertion récursive dans l'arbre
    if (strcmp(key, root->key) < 0) {
        root->left = AVLInsert(root->left, key, passThroughCount, departureCount);
    } else if (strcmp(key, root->key) > 0) {
        root->right = AVLInsert(root->right, key, passThroughCount, departureCount);
    } else {
        // La ville existe déjà, mettre à jour les compteurs
        root->passThroughCount += passThroughCount;
        root->departureCount += departureCount;
        return root;
    }

    // Mettre à jour la hauteur du nœud actuel
    root->height = fmax(getHeight(root->left), getHeight(root->right)) + 1;

    // Rééquilibrer l'arbre
    int balanceFactor = getBalanceFactor(root);
    if (balanceFactor > 1 && strcmp(key, root->left->key) < 0) {
        return rotateRight(root);
    }
    if (balanceFactor < -1 && strcmp(key, root->right->key) > 0) {
        return rotateLeft(root);
    }
    if (balanceFactor > 1 && strcmp(key, root->left->key) > 0) {
        root->left = rotateLeft(root->left);
        return rotateRight(root);
    }
    if (balanceFactor < -1 && strcmp(key, root->right->key) < 0) {
        root->right = rotateRight(root->right);
        return rotateLeft(root);
    }

    return root;
}

// Fonction pour rechercher une ville dans l'arbre AVL
AVLNode *searchCity(AVLNode *root, char *key) {
    if (root == NULL || strcmp(root->key, key) == 0) {
        return root;
    }
    if (strcmp(key, root->key) < 0) {
        return searchCity(root->left, key);
    } else {
        return searchCity(root->right, key);
    }
}

// Fonction pour mettre à jour les compteurs de ville
void updateCityCounts(AVLNode *root, char *city, int isDeparture) {
    AVLNode *cityNode = searchCity(root, city);
    if (cityNode) {
        cityNode->passThroughCount++;
        if (isDeparture) {
            cityNode->departureCount++;
        }
    } else {
        // Ajouter une nouvelle ville dans l'arbre
        root = AVLInsert(root, city, 1, isDeparture ? 1 : 0);
    }
}

// Fonction de parcours infixé pour écrire les statistiques des villes dans un fichier
void inorderTraversal(AVLNode *root, FILE *output_fp) {
    if (root == NULL) {
        return;
    }
    inorderTraversal(root->left, output_fp);
    fprintf(output_fp, "%s,%d,%d\n", root->key, root->passThroughCount, root->departureCount);
    inorderTraversal(root->right, output_fp);
}

// Fonction pour obtenir les 10 premières villes avec le plus de trajets
void top10Cities(AVLNode *root, FILE *output_fp) {
    AVLNode *stack[100];
    int top = -1;
    AVLNode *current = root;

    while (current || top != -1) {
        while (current) {
            stack[++top] = current;
            current = current->left;
        }
        current = stack[top--];
        // Only write top 10 cities
        if (top < 9) {
            inorderTraversal(current, output_fp);
        }
        current = current->right;
    }
}

// Fonction pour traiter l'option -t
void process_t(FILE *input_fp, FILE *output_fp) {
    char line[1024];
    char *departureCity, *arrivalCity;

    AVLNode *root = NULL; // Initialiser l'arbre AVL pour les villes

    while (fgets(line, sizeof(line), input_fp)) {
        departureCity = strtok(line, ";");
        arrivalCity = strtok(NULL, ";");

        updateCityCounts(root, departureCity, 1);
        updateCityCounts(root, arrivalCity, 0);
    }

    fprintf(output_fp, "City,Total Trips,Departure Trips\n");
    inorderTraversal(root, output_fp);
}

    // Fonction pour libérer la mémoire allouée pour l'arbre AVL
void freeAVLTree(AVLNode *node) {
    if (node == NULL) return;

    // Parcourir récursivement l'arbre et libérer chaque nœud
    freeAVLTree(node->left);
    freeAVLTree(node->right);

    // Libérer le nœud actuel
    free(node);
}


int main(int argc, char *argv[]) {
    if (argc < 4) {
        fprintf(stderr, "Usage: %s <option> <input_file> <output_file>\n", argv[0]);
        return EXIT_FAILURE;
    }

    char *option = argv[1];
    char *input_file = argv[2];
    char *output_file = argv[3];

    FILE *input_fp = fopen(input_file, "r");
    FILE *output_fp = fopen(output_file, "w");

    if (input_fp == NULL || output_fp == NULL) {
        fprintf(stderr, "Erreur : Impossible d'ouvrir les fichiers d'entrée/sortie.\n");
        return EXIT_FAILURE;
    }

    if (strcmp(option, "-t") == 0) {
        process_t(input_fp, output_fp);
    } else if (strcmp(option, "-s") == 0) {
        // ... À implémenter pour l'option -s ...
    } else {
        fprintf(stderr, "Erreur : Option non valide.\n");
        return EXIT_FAILURE;
    }

    fclose(input_fp);
    fclose(output_fp);

    // Libérer la mémoire allouée pour l'arbre AVL
    freeAVLTree(root);

    return 0;
}


