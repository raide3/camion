set terminal png
set datafile separator ";"
set style fill solid
set boxwidth 0.5  


unset ytics

set y2tics
set y2label "valeurs"
set output './images/histogram_l.png'

plot "./temp/sample_l.dat"  using 2:xtic(1) with boxes axes x1y2 title "courbe l"