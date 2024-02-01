set terminal png
set datafile separator ";"
set style fill solid
set boxwidth 0.5  
set xtic rotate

unset ytics
set y2tic rotate
set y2tics
set y2label "valeurs"
set output './temp/picture_d2.png'

plot "./temp/sample2.dat"  using 2:xtic(1) with boxes axes x1y2 title "courbe d1"