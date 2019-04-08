# plot file for diffeq_test_exp_back
set timestamp

set xlabel 't'
set ylabel '{/Symbol q}'

set title '{/Symbol q} vs t'

set xrange [0:50]

plot "diffeq_pendulum.dat" using ($1):($2)

# output the plot to the file derivative_test_plt.ps   
#set out "diffeq_test.ps"
#set term postscript color enhanced
#replot
