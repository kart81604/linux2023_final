reset
set terminal png
set title 'performance'
set xlabel 'number of data'
set ylabel 'time(us)'
set output 'perform.png'

plot \
"data.txt" using 1:2 with line title 'heap sort'