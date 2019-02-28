# plot file for diffeq_test_exp_back
set timestamp

set xlabel 't'
set ylabel 'Relative Error'

set title 'Comparing Errors of Differential Equation Algorithms'

set xrange [0:0.5]

plot \
  "diffeq_test.dat" using (log10($1)):(log10(abs((($2)-($4)))/($4))) title 'Euler, h = 0.1', \
  "diffeq_test.dat" using (log10($1)):(log10(abs((($3)-($4)))/($4))) title '4th order Runge-Kutta, h = 0.1', \
  "diffeq_test2.dat" using (log10($1)):(log10(abs((($2)-($4)))/($4))) title 'Euler, h = 0.01', \
  "diffeq_test2.dat" using (log10($1)):(log10(abs((($3)-($4)))/($4))) title '4th order Runge-Kutta, h = 0.01'

# output the plot to the file derivative_test_plt.ps   
set out "diffeq_test.ps"
set term postscript color enhanced
replot
