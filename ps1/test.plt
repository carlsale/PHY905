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
set title 'Bessel Function for Various Methods Versus x'
set xlabel 'log10(x)'
set ylabel 'log10(error)'

# move the legend to a free space
set key right bottom inside

# set the x and y axis scales (already logs)
set xrange [0:100]
set yrange [-0.2:0.2]

# fit the curve
#f1(x) = a1*x + b1
#fit [0.1:1] f1(x) "bessel.dat" using ($5):($6) via a1,b1 
#fit_title1 = sprintf("%-+4.1f*x %-+4.1f",a1,b1)

#f2(x) = a2*x + b2
#fit [1.5:1.6] f2(x) "bessel.dat" using ($5):($6) via a2,b2
#fit_title2 = sprintf("%-+4.1f*x %-+4.1f",a2,b2)

# set the terminal type to be the screen (which is x11 here)
set term x11

# plot the data as well as the fit, with appropriate titles 
plot "bessel.dat" using ($1):($7) title 'gsl', \
	"bessel.dat" using ($1):($2) title 'down recursion', \
	"bessel.dat" using ($1):($3) title 'up recursion'
#     a1*x + b1 title fit_title1, \
#     a2*x + b2 title fit_title2

# output the plot to the file derivative_test_plt.ps   
set out "bessel_function.ps"
set term postscript color enhanced
replot
