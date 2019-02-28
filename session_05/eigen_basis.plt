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
set title 'Accuracy of Ground State Energy vs Basis Size'
set xlabel 'Dimension'
set ylabel 'Rel. Error in Ground State Energy'

# move the legend to a free space
set key left

# set the x and y axis scales (already logs)
set xrange [0:2]
set yrange [-5:0]

# set the terminal type to be the screen (which is x11 here)
set term x11

f1(x) = a1*x + b1
fit [0.25:1.7] f1(x) "eigen_basis_b.dat" using ($1):($2) via a1,b1 
fit_title1 = sprintf("%-+4.1f*x %-+4.1f",a1,b1)

# plot the data as well as the fit, with appropriate titles 
plot "eigen_basis_b.dat" using ($1):($2) title 'b = 0.3', \
     a1*x + b1 title fit_title1,\
"eigen_basis_2b.dat" using ($1):($2) title 'b = 0.6',\
"eigen_basis_4b.dat" using ($1):($2) title 'b = 1.2'
#"eigen_basis_35.dat" using ($1):($2) title 'Dimension = 35'

# output the plot to the file derivative_test_plt.ps   
set out "eigen_basis_b.ps"
set term postscript color enhanced
replot
