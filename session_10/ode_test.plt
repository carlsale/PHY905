# plot file for diffeq_oscillations
set timestamp

set title 'Van der Pol Oscillations'

# phase space plot
set xlabel 'x(t)'
set ylabel 'v(t)'
plot "ode_test_x0_0.1_v0_0.dat" using ($2):($3) title 'x_0 = 0.1, v_0 = 0.0' with lines, \
     "ode_test_x0_1_v0_0.dat" using ($2):($3) title 'x_0 = 1.0, v_0 = 0.0' with lines, \
     "ode_test_x0_-1.5_v0_2.dat" using ($2):($3) title 'x_0 = -1.5, v_0 = 2.0' with lines
