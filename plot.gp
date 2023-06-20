reset
set terminal png
set title 'performance'
set xlabel 'number of data'
set ylabel 'time(us)'
set output 'perform_compare.png'

plot \
"ttest.txt" using 1:2 with line title 'heap sort' , \
'' using 1:3 with line title 'intro sort'