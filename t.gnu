reset
set terminal pngcairo enhanced font "arial,13" fontscale 1.0 size 1400,1000
set output 'image/t.png'
set title "Option -t : Nb routes = f(Towns)"
set datafile separator ";"
set xlabel 'TOWN NAMES'
set xtics rotate by 45 right scale 0
set ylabel 'NB ROUTES'
set yrange [0:4000]
set boxwidth 1.7
set style data histogram
set style fill solid 1.0
set multiplot layout 1,1
plot "temp/tempt.txt" u 2:xtic(1) lc rgb "red" title "total routes", "temp/tempt.txt"  u 3:xtic(1) lc rgb "green" title "first town"
unset multiplot
