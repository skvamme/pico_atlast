char FORTH[5000] = " ( ATLAST forth ) \n\
( Draw sixel graphics in a terminal emulator, Xterm -fn 6x12 ) \n\
 \n\
8 string num \n\
variable row \n\
500 1 1 ARRAY data \n\
 \n\
: color \"#0;2;50;50;50#1;2;100;0;0#2;2;0;100;00#3;2;0;0;100\" type ; \n\
: start 27 emit \"Pq\" type ; \n\
: end 27 emit 92 emit ; \n\
: cr_ \"$\" type ; \n\
: crlf  \"-\" type ; \n\
: up 27 emit 91 emit \"%d\" num strform num type \"A\" type ; ( n -- ) \n\
 \n\
 \n\
: filldata  450 1 do i float  3.14 f* 180.0 f/ sin 50.0 f* fix 130 + 2 / i data c! loop ; \n\
 \n\
: plot  6 * row !  \n\
		\"#1!35?\" type \n\
	    450 1 do  \n\
		row @ 0 + i data c@ = if \"@\" type ( 1 ) \n\
		else \n\
		row @ 1 + i data c@ = if \"A\" type ( 2 ) \n\
		else \n\
		row @ 2 + i data c@ = if \"C\" type ( 4 ) \n\
		else \n\
		row @ 3 + i data c@ = if \"G\" type ( 8 ) \n\
		else \n\
		row @ 4 + i data c@ = if \"O\" type ( 16 ) \n\
		else \n\
		row @ 5 + i data c@ = if \"_\" type ( 32 ) \n\
		else  \n\
		\"?\" type then then then then then then loop cr_ ; \n\
 \n\
: y_arrow \"#0------!33?~~\" type crlf \"!32?~~~\" type crlf \"!31?!4~\" type crlf \"!30?!5~\" type  \n\
	crlf \"!34?~\" type crlf \"!34?~\" type crlf ; \n\
: yaxis \"#0!29?!5@~\" type crlf ; \n\
: hor_line \"#0!24?!10@\" type 65 1 do \"~!6@\" type loop \"!4~!4^!4N!4F!4B!4@\" type crlf ; \n\
: hor_ticks  \"#0!34?\" type 14 1 do \"N!34?\" type loop crlf ; \n\
: hor_num \"     0     1     2     3     4     5     6     7     8     9   10    11    12\" type ; \n\
: ver_num \"400 -\" type cr cr \"300 -\" type cr cr \"200 -\" type cr cr \"100 -\" type cr cr \"  0\" type ; \n\
 \n\
 \n\
: run filldata start color y_arrow 20 1 do i plot yaxis loop hor_line hor_ticks end cr cr cr cr \n\
	ver_num cr cr hor_num cr ; \n\
go\n";
