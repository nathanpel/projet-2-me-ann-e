reset
set terminal pngcairo enhanced font "arial,13" fontscale 1.0 size 1000,1200
set output 'image/d11.png'
set ylabel "Option -d1 : Nb routes =f(Driver)" center rotate by 90
set datafile separator ";"
set xlabel 'DRIVER NAMES' center rotate by 180
set y2label 'NB ROUTES'
set yrange [0:250]
set xtic rotate out scale 0
unset ytic
unset x2tic
set y2tic rotate out
set boxwidth 0.8
set style fill solid
plot "temp/d1.csv" u 1:xtic(2) w boxes lc rgb "red" notitle
