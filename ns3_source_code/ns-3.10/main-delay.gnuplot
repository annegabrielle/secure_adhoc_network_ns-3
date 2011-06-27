set terminal postscript portrait enhanced lw 2 "Helvetica" 14

set size 1.0, 0.66

set output "dsdv_delay.eps"

set xrange [0:900]

set yrange [0:0.002]

set xlabel "Pause Times (s)"

set ylabel "Packet Delay (s)"

set grid

plot 'annestest_v2.data' using 1:2 title 'DSDV 10 nodes' with linespoints

