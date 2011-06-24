set terminal postscript portrait enhanced lw 2 "Helvetica" 14

set size 1.0, 0.66

set output "res.eps"

set xrange [0:1000]

set yrange [0:1.0]

set xlabel "Pause Times (s)"

set ylabel "Packet Delivery Ratio (PDR)"

set grid

plot 'res.dat' using 1:2 title 'DSDV 10 nodes' with linespoints, 'res2.dat' using 1:2 title 'BATMAN 10 nodes' with linespoint

