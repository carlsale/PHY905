#  file: derivative_test.plt 
#
#  Gnuplot plot file for derivative_test output
#  
#  Programmer:  Dick Furnstahl  furnstahl.1@osu.edu
# 
#  Revision history
#   2004-01-24  original version for 780.20 session 5
#   2004-01-16  added postscript enhanced and comments for session 4
#

# record the time and date the graph was generated
set timestamp

# titles and labels
set title 'Nonlinear Least Squares Fitting with GSL Routines'
set xlabel 't'
set ylabel 'y(t)'

# move the legend to a free space
set key left

# set the x and y axis scales (already logs)
set xrange [-1:40]
set yrange [0:7]


# set the terminal type to be the screen (which is x11 here)
set term x11

f(x) = 5.04536*exp(-0.10405*x)+1.01925

# plot the data as well as the fit, with appropriate titles 
plot "multifit_test.dat" using ($1):($2):($3) title 'real data' with yerrorbars, \
     f(x) title 'fit curve: 5.04536*exp(-0.10405*x)+1.01925'

# output the plot to the file derivative_test_plt.ps   
set out "multifit_test.ps"
set term postscript color enhanced
replot
