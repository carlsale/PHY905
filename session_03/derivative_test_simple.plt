set terminal x11 # terminal type (try: help set terminal)
set title 'Numerical Derivatives Test'
set xlabel 'Log_{10}(h)'
set ylabel 'Log_{10}(relative error)'
set xrange [-10:0]
set pointsize 1.5 # set the size of the plotted points
set key top left # move the key away from the lines
set timestamp # turn on a date/time indicator
f(x) = a*x+b
g(x) = c*x+d
fit [-8:-1] f(x) 'derivative_test_simple.dat' using 1:2 via a,b
fit [-5:-1] g(x) 'derivative_test_simple.dat' using 1:3 via c,d
plot "derivative_test_simple.dat" using 1:2 title 'Forward Difference', f(x) title 'slope = 1.00188',\
"derivative_test_simple.dat" using 1:3 title 'Central Difference', g(x) title 'slope = 1.99683'
set out "quadratic_eq.pdf"
replot # plot to the file
