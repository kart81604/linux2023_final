# compare number of comparisons with average case
reset
set terminal png
set title 'comparison number'
set xlabel 'number of data'
set ylabel 'comparison'
set output 'cmp.png'

base(x) = x * log10(x) / log10(2) + 0.37 * x

plot \
"data.txt" using 1:2 with line linewidth 4 title 'heap sort' , \
base(x) with line linewidth 4 title 'average cmp'