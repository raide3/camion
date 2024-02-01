
dossier_temp="temp"
dossier_images="images"

# Fonction pour vérifier et créer le dossier si nécessaire
verifier_et_creer_dossier() {
    if [ ! -d "$1" ]; then
        mkdir "$1"
    fi
}

# Vérifier et créer le dossier temp
verifier_et_creer_dossier "$dossier_temp"

# Vérifier et créer le dossier images
verifier_et_creer_dossier "$dossier_images"

# Vider le dossier temp s'il existe
if [ -d "$dossier_temp" ]; then
    rm -rf "$dossier_temp"/*
fi

if [ -d "$dossier_images" ]; then
    rm -rf "$dossier_temp"/*
fi