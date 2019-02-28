set terminal x11 # terminal type (try: help set terminal)
set title 'Numerical Derivatives Test'
set xlabel 'Log_{10}(N)'
set ylabel 'Log_{10}(relative error)'
set xrange [0:3.5]
set pointsize 1.5 # set the size of the plotted points
set key top left # move the key away from the lines
set timestamp # turn on a date/time indicator
f(x) = a*x+b
g(x) = c*x+d
fit [1:2.5] f(x) 'integ.dat' using 1:2 via a,b
fit [1:2.5] g(x) 'integ.dat' using 1:3 via c,d
plot "integ.dat" using 1:2 title 'Simpsons', f(x) title 'slope = -6.07842',\
"integ.dat" using 1:3 title 'Milnes', g(x) title 'slope = -6.1277'
set out "integ_test.ps"
replot # plot to the file
