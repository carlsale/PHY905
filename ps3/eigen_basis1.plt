#  file: eigen_basis.plt 
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
set title 'G.S. Radial Wavefunctions for Various Parameters'
set xlabel 'r'
set ylabel 'u_{n}(r)'

# move the legend to a free space
set key left

# set the x and y axis scales (already logs)
set xrange [0:10]
#set yrange [-16:0]

# set the terminal type to be the screen (which is x11 here)
set term x11

# plot the data as well as the fit, with appropriate titles 
plot "eig_b1.2_N_1.out" using ($1):($2) title 'b=1.2,N=1', \
"eig_b1.2_N_5.out" using ($1):(-($2)) title 'b=1.2,N=5', \
"eig_b1.2_N_10.out" using ($1):(-($2)) title 'b=1.2,N=10', \
"eig_b1.2_N_20.out" using ($1):($2) title 'b=1.2,N=20', \
"eig_b0.5_N_1.out" using ($1):($2) title 'b=0.5,N=1', \
"eig_b0.5_N_5.out" using ($1):($2) title 'b=0.5,N=5', \
"eig_b0.5_N_10.out" using ($1):($2) title 'b=0.5,N=10', \
"eig_b0.5_N_20.out" using ($1):($2) title 'b=0.5,N=20'

# output the plot to the file derivative_test_plt.ps   
set out "eigen_basis_b_0.5and1.2.ps"
set term postscript color enhanced
replot
