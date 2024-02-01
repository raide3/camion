source verif.sh

option_d1=""
option_d2=""
option_l=""
option_t=""
option_s=""
csv_file="$1"

# Fonction pour afficher l'aide
afficher_aide() {
    echo "Utilisation : $0 [options]"
    echo "Options :"
    echo "  -h      Afficher le message d'aide"
    echo "  -d1     Conducteurs avec le plus de trajets"
    echo "  -d2     Conducteurs et la plus grande distance"
    echo "  -l      10 plus longs trajets"
    echo "  -t      10 villes les plus traversées"
    echo "  -s      Statistiques sur les étapes"
}

# Vérifier l'option d'aide
if [ "$1" == "-h" ]; then
    afficher_aide
    exit 0
fi

# Traitement des arguments
while [[ $# -gt 1 ]]; do
  case "$2" in
    -d1)
      option_d1="true"
      ;;
    -d2)
      option_d2="true"
      ;;
    -l)
      option_l="true"
      ;;
    -t)
      option_t="true"
      ;;
    -s)
      option_s="true"
      ;;
    *)
      echo "Argument inconnu: $2"
      exit 1
      ;;
  esac
  shift
done


# Utilisation des options
if [ ! -z "$option_d1" ]; then
  time {    
  echo "Option -d1 détectée. Exécution des commandes..."
  cut "$csv_file" -d';' -f1,6 | awk -F';' '!seen[$1,$2]++ {tab[$2] += 1} END {for (i in tab) {print i";"tab[i]} }' | sort -t';' -nr -k2 | head -n +10 > ./temp/sample.dat
  }
gnuplot ./images/template.gnu
convert -rotate 90 "./temp/picture_d1.png" "./images/histogram1.png"
#display "./images/picture_d1.png"


fi

if [ ! -z "$option_d2" ]; then
  time {
  echo "Option -d2 détectée. Exécution des commandes ..."
  tail -n +2 "$csv_file" | cut -d';' -f5,6 | awk -F';' '{distances[$2] += $1} END {for (driver in distances) {printf "%s;%.4f\n", driver, distances[driver]}}' | sort -t';' -nr -k2 | head -n +10 > ./temp/sample2.dat
  }
gnuplot ./images/template_d2.gnu
convert -rotate 90 "./temp/picture_d2.png" "./images/histogram2.png"
#display "./images/picture_d2.png"

fi

if [ ! -z "$option_l" ]; then
  time {
  echo "Option -l détectée. Exécution des commandes..."
  tail -n +2 "$csv_file" | cut -d';' -f1,5 | awk -F';' '{distance[$1] += $2} END {for (trip in distance) {printf "%s;%.4f\n", trip, distance[trip]}}' | sort -t';' -nr -k2 | head -n +10 | sort -t';' -n -k1> ./temp/sample_l.dat
  }
  gnuplot ./images/template_l.gnu
#display "./images/picture_l.png"
fi


if [ ! -z "$option_t" ]; then
  time {
  echo "Option -t détectée. Exécution des commandes..."
  gcc -o city_stats progc/city_stats.c
  ./city_stats data.csv > ./temp/city_stats_output.dat
  }
  gnuplot ./images/template_t.gnu
  #display "./images/picture_t.png"
fi

if [ ! -z "$option_s" ]; then
  time {
  echo "Option -s détectée. Exécution des commandes..."
  gcc -o process_s progc/process_s.c
  ./process_s data.csv > ./temp/process_s_output.dat
  }
  gnuplot ./images/template_s.gnu
  #display "./images/picture_s.png"
fi