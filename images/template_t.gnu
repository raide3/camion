set datafile separator ';';
set terminal png size 800, 600 enhanced font 'Verdana,10';
set output 'images/city_histogram.png';
set title 'City Data Histogram';
set xlabel 'Cities';
set ylabel 'Counts';
set boxwidth 0.4 relative;
set style data histograms;
set style histogram clustered;
set style fill solid 1.0 border lt -1;
set xtics rotate by -45;
set grid ytics;
set key outside;

plot '$data_file' using 2:xtic(1) title 'Total Routes', \
     '' using 3:xtic(1) title 'First Town';