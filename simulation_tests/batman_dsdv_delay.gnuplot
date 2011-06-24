set terminal postscript portrait enhanced lw 2 "Helvetica" 14

set size 1.0, 0.66

set output "batman_dsdv_delay.eps"

set xrange [0:900]

set yrange [0:3.0]

set xlabel "Pause Times (s)"

set ylabel "Packet Delay (ms)"

set grid

plot 'dsdv_delay.dat' using 1:2 title 'DSDV 10 nodes' with linespoints, 'batman_delay.dat' using 1:2 title 'BATMAN 10 nodes' with linespoint

