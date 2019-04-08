# plot file for diffeq_oscillations
set timestamp

set title 'Van der Pol Oscillations'

# phase space plot
set xlabel 'x(t)'
set ylabel 'v(t)'
plot "gsl_spline_test_class.dat" using ($1):($2) title 'Exact Results' with lines, \
     "gsl_spline_test_class.dat" using ($1):($3) title 'Cubic Interpolation', \
     "gsl_spline_test_class.dat" using ($1):($4) title 'Linear Interpolation', \
     "gsl_spline_test_class.dat" using ($1):($5) title 'Polynomial Interpolation'
