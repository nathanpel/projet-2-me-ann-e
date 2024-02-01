reset
set terminal pngcairo enhanced font "arial,13" fontscale 1.0 size 2000,1000
set output 'image/l.png'
set title "Les 10 trajets les plus long"
set datafile separator ";"
set xlabel 'ID de trajet'
set xtics scale 0
set ylabel 'Distance(km)'
set yrange [0:3000]
set boxwidth 0.8
set style fill solid
plot "temp/templ.txt" u 2:xtic(1) w boxes lc rgb "green" notitle
