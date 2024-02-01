set terminal png size 1024, 768 enhanced font 'Verdana,10';
set output 'images/stage_graph.png';
set title 'Stage Statistics - Top 50';
set xlabel 'Trip Identifier';
set ylabel 'Distance (km)';
set yrange [0:1000];
set ytics 100;
set xtics rotate by 270;
set key outside;
set style data lines;
plot 'temp/stage_stats.txt' using 2:xticlabels(1) title 'Min', \
     '' using 3:xticlabels(1) title 'Average', \
     '' using 4:xticlabels(1) title 'Max';" 