#  file: eigen_tridiagonal.plt 
#
#  Gnuplot plot file for eigen_tridiagonal output
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
set title 'Error in Ground State Energy for N-by-N Matrix Diagonalization'
set xlabel 'log10(N)'
set ylabel 'log10(error)'

# move the legend to a free space
set key left

# set the x and y axis scales (already logs)
set xrange [0:4]
set yrange [-6:0]

f1(x) = a1*x + b1
fit [0.5:3.5] f1(x) "eigen_tridiagonal_error.dat" using ($1):($2) via a1,b1 
fit_title1 = sprintf("%-+4.1f*x %-+4.1f",a1,b1)

#f2(x) = a2*x + b2
#fit [1:3] f2(x) "eigen_tridiagonal_error2.dat" using ($1):($2) via a2,b2
#fit_title2 = sprintf("%-+4.1f*x %-+4.1f",a2,b2)

# set the terminal type to be the screen (which is x11 here)
set term x11

# plot the data as well as the fit, with appropriate titles 
plot "eigen_tridiagonal_error.dat" using ($1):($2) title 'Rmax = 6.5', \
     a1*x + b1 title fit_title1, \
"eigen_tridiagonal_error2.dat" using ($1):($2) title 'Rmax = 4'#, \
#     a2*x + b2 title fit_title2

# output the plot to the file derivative_test_plt.ps   
set out "eigen_tridiagonal_error.ps"
set term postscript color enhanced
replot
