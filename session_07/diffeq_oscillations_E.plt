# plot file for diffeq_oscillations
set timestamp

set title 'Oscillations'

# simple plot versus time
pi = 3.141592653589793
k = (2.*pi)**2
m = 1
omega = sqrt(k/m)
set xlabel 't'
set ylabel 'E'
plot "diffeq_oscillations.dat" using ($1):($6) title 'h=0.001' with lines
#plot "diffeq_oscillations.dat" using ($1):($2) title 'p=?' with lines # , \
#  (1/omega)*sin(omega*x)

