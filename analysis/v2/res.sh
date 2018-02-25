
paste -d, TRC05.CSV TRC04.CSV TRC02.CSV | awk -F, 'NR>1&&$1>-0.001 && $1<0.006{

	vin=$6
	vt=$2
	vt2=$4

	vr = vin-vt

	vb = vt-vt2

	i=vr/10

	print vb*1000, i, $1*1000 
}' > tmp.txt



gnuplot <<FOO
set terminal postscript enhanced color 30
set output "b.ps"
set xlabel 'Voltage (mV)'
set ylabel 'Current (A)'
set xtics -50,50,150
set mxtics 10
set cblabel 'Time (ms)'
set style line 1 lw 4 pt 0 lc palette
plot  'tmp.txt' using 1:2:3 with line ls 1 title ''
FOO



pstopnm -stdout -xborder=0 -yborder=0 -portrait -xsize 8192 b.ps | pnmscale -r 8  | pnmflip -r270 | pnmtopng > b.png

