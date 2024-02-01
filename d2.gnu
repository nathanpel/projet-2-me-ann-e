reset
set terminal pngcairo enhanced font "arial,13" fontscale 1.0 size 1000,1200
set output 'image/d22.png'
set  ylabel "Option -d2 : Distance =f(Driver)" center rotate by 90
set datafile separator ";"
set xlabel 'DRIVER NAMES' center rotate by 180
set y2label 'DISTANCE(km)'
set yrange [0:160000]
set xtic rotate out scale 0
unset ytic
set y2tic rotate out
set boxwidth 0.8
set style fill solid
plot "temp/temp2.txt" u 1:xtic(2) w boxes lc rgb "green" notitle
