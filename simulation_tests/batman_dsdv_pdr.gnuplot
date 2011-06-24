set terminal postscript color solid portrait enhanced lw 2 "Helvetica" 14

set size 1.0, 0.66

set output "batman_dsdv_pdr.eps"

set xrange [0:900]

set yrange [0:1.0]

set xlabel "Pause Times (s)"

set ylabel "Packet Delay (ms)"

set grid

plot 'dsdv_pdr.dat' using 1:2 title 'DSDV 10 nodes' with lc rgb "blue", 'batman_pdr.dat' using 1:2 title 'BATMAN 10 nodes' with linespoint

