paste -d, TRC02.CSV TRC01.CSV | awk -F, 'NR>1&&$1>-0.001 && $1<0.006{

	vin = $2
	vt = $4

	vr = vin - vt

	i = vr / 10

	print vt,i,$1*1000
}' > tmp.txt 

gnuplot <<FOO
set terminal postscript enhanced color 30
set output "a.ps"
set xlabel 'Voltage'
set ylabel 'Current (A)'
set cblabel 'Time (ms)'
set style line 1 lw 4 pt 0 lc palette
plot [:][0:0.7] 'tmp.txt' using 1:2:3 with line ls 1 title ''
FOO

#| plot -ps="enhanced color 30"  -xl 'Vt' -yl 'I'  -x 'set  style line 1 linecolor rgb "#0080ff" lw 4 pt 0' - --1,"" > a.ps 


pstopnm -stdout -xborder=0 -yborder=0 -portrait -xsize 8192 a.ps | pnmscale -r 8  | pnmflip -r270 | pnmtopng > a.png

