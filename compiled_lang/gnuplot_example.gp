#######################################################
# Gnuplot commands
# run script with
# gnuplot -e "load 'gnuplot_example.gp'"
# or launch interactive Gnuplot shell by
# typing gnuplot in command line
# and then copy/paste these commands
######################################################

# The input data to be plotted
# can be a matrix that is space delimited
# You will find the input.dat and Purples.plt files
# for the plotting example here
# For more color palettes, check out Gnuplot Colorbrewer

# load the palette file
load 'Purples.plt'
set border lw 3

# unset the legend
unset key

# unset the x, y axes
unset xtics
unset ytics

# set the aspect ratio to be 1
set size square

# set the range of the color bar
set cbrange [0:3]

# plot the matrix as an image
plot 'input.dat' matrix with image
