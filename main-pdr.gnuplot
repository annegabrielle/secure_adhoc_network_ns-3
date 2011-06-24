set terminal postscript portrait enhanced lw 2 "Helvetica" 14

set size 1.0, 0.66

set output "dsdv_pdr.eps"

set xrange [0:900]

set yrange [0:1.0]

set xlabel "Pause Times (s)"

set ylabel "Packet Delivery Ratio (PDR)"

set grid

plot 'dsdv.data' using 1:2 title 'DSDV 10 nodes' with linespoints, 'olsr.data' using 1:2 title 'OLSR 10 nodes' with linespoint, 'batman.data' using 1:2 title 'BATMAN 10 nodes' with linespoint

