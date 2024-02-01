
function somme_distances_par_conducteur() {
    local fichier="$1"
    
    # Déclaration d'un tableau associatif pour stocker la somme des distances par conducteur
    declare -A somme_distances
    
    # Lire chaque ligne du fichier
    while IFS=';' read -r Route_ID Step_ID Town_A Town_B Distance Driver_name; do
        # Ignorer la première ligne (en-têtes)
        if [[ "$Route_ID" != "Route_ID" ]]; then
            # Ajouter la distance au total pour le conducteur actuel
            somme_distances["$Driver_name"]=$(( somme_distances["$Driver_name"] + Distance ))
        fi
    done < "$fichier"
    
    # Afficher le résultat
    for Driver_name in "${!somme_distances[@]}"; do
        echo " $conducteur ${somme_distances["$Driver_name"]} "
    done
}

# Appeler la fonction avec le nom de fichier en argument
somme_distances_par_conducteur data/data.csv
