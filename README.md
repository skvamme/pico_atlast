# pico_atlast 

Compiles out of the box, no C-programming knowledge required to use the ATLAST forth console. Get full access to the Raspberry Pi Pico C API in atlast.c and use forth as a quick yet powerful scripting engine. 

Documentation: http://www.fourmilab.ch/atlast/ and https://www.forth.com/starting-forth/ and https://www.dnd.utwente.nl/~tim/colorforth/Leo-Brodie/thinking-forth.pdf

ATLAST Forth for Raspberry Pi Pico is a boilerplate C application with a built in forth scripting environment. 

1. Put your forth code in a file,  "anyname.atl". Make sure to keep source line width below max column 132.

2. Run "./atl2h.sh anyname.atl" to create the file forth.h. 

3. Compile atlast.c with make in the build directory, see https://github.com/raspberrypi/pico-sdk 

If forth is the main entry point, the forth code must contain a word "GO" with an infinite loop, e.g. begin ... again to keep the application running. Otherwise, you will get an interactive console where you can use all the standard forth words, your own word definitions from forth.h and even define new words. New word definitions will last until power off.

Use e.g. minicom, picocom, putty to get access to the ATLAST forth console on the pico from your raspberry pi or other computer: 
picocom /dev/ttyACM0 -b 115200 -l

Take a look at https://github.com/skvamme/atlast for some example forth code, coded for the pigpio library. API names and functions are very similar to the pico C API.

Read the PICO documentation for the C/C++ API for a detailed description of each function.

Defined words:

SLEEP_MS

Stack before: integer number of milliseconds to sleep
	
This word leaves nothing at the stack
	
This can be illustrated in this way: ( millisec -- )

SLEEP_MS
	( millisec -- )

SLEEP_US
	( msb lsb -- )  64 bit microsec value. A 64 bit integer is represented by two 32 bit integers on the stack.

TIME_US
	(  --  msb lsb ) This 2x32 bit value is microseconds since power up. A 64 bit unsigned int. It never wraps.
	
TIME_DIFF
	( msb1 lsb1 msb2 lsb2 -- msb lsb ) Diff between two 64 bit timestamps.  Returns a 64 bit unsigned int.

ADD_ALARM_IN_US
	( msb lsb bool "NAME" -- result ) 2x32 bit value is microseconds to alarm. bool is 0 or 1. NAME is the word to execute.
	
U64.
	( msb lsb -- ) Print unsigned 64 bit integer

U.
	( integer -- ) Print unsigned 32 bit integer.
	
GPIO_INIT
	( gpiopin --  )

GPIO_SET_DIR
	( gpiopin type  --  ) type can be 1 for output and 0 for input

GPIO_PUT
	( gpiopin state --  ) state is 1 for high and 0 for low

GPIO_GET
	( gpiopin -- result )

GPIO_GET_ALL
	(  -- value ) value is a bit encoded integer

GPIO_SET_PULLS
	( gpiopin up down --  ) up and down are booleans 1=true 0=false

GPIO_PULL_UP
	( gpiopin --  )

GPIO_PULL_DOWN
	( gpiopin --  )

GPIO_SET_FUNCTION
	( gpiopin function --  ) function is an integer, look it up in pico C API doc
	
GPIO_SET_IRQ_ENABLED_WITH_CALLBACK
	( gpiopin events bool word -- ) word is the compile address, use ['] word to get it
	events is a bitmapped integer, see C API document
	
******************SPI*******************

SPI_WRITE_READ_BLOCKING
	( spi inbuf outbuf len --  )

SPI_INIT
	( spi baud --  ) baud in Hz

SPI_DEINIT
	( spi --  )

SPI_IS_READABLE
	( spi -- bool ) bool is non-zero if a read is possible

SPI_IS_WRITABLE
	( spi -- bool ) bool is non-zero if a write is possible

SPI_WRITE_BLOCKING
	( spi outbuf len -- )

SPI_READ_BLOCKING
	( spi dummy_byte inbuf len -- result )

******************ADC*******************

ADC_SELECT_INPUT
	( input --  ) input can be 0-3

ADC_INIT
	(  --  )

ADC_GPIO_INIT
	( gpiopin --  )

ADC_SET_ROUND_ROBIN
	( inputmask --  )

ADC_SET_TEMP_SENSOR_ENABLED
	( bool -- ) bool is 1 for enabled and 0 for disabled

ADC_READ
	(  -- result ) result is a float, print it with f.

ADC_RUN
	( bool --  )

ADC_FIFO_DRAIN
	(  --  )

ADC_FIFO_GET
	(  -- result )

ADC_FIFO_GET_BLOCKING
	(  -- result )

ADC_FIFO_GET_LEVEL
	(  -- result )

ADC_FIFO_IS_EMPTY
	( -- bool )

ADC_FIFO_SETUP
	( bool bool number bool bool --  )

ADC_IRQ_SET_ENABLED
	( bool --  )

ADC_SET_CLKDIV
	( number -- )

ADC_TEMP
	(  -- temp ) temp is a float, print it with f.

ADC_CONVERSION_FACTOR
	( volt -- result ) float volt is the adc reference voltage
	
**************MULTICORE*******************
	
MULTICORE_LAUNCH_CORE1
	( word -- ) word is a compile address, get it with [']

MULTICORE_FIFO_POP_BLOCKING
	( -- result )

MULTICORE_FIFO_PUSH_BLOCKING
	( value -- )

**************WATCHDOG*******************

WATCHDOG_ENABLE
	( millisec bool -- )
	
WATCHDOG_UPDATE
	(  --  )
	
**************QUEUE*******************

QUEUE_INIT_WITH_SPINLOCK
	( que size count spinlock --  )
	
QUEUE_INIT
	( que size count -- )
	
QUEUE_FREE
	( que -- )
	
QUEUE_GET_LEVEL_UNSAFE
	( que -- result )
	
QUEUE_GET_LEVEL
	( que -- result )
	
QUEUE_IS_EMPTY
	( que -- bool )
	
QUEUE_IS_FULL
	( que -- bool )
	
QUEUE_TRY_ADD
	( que data -- bool )
	
QUEUE_TRY_REMOVE
	( que data -- bool )
	
QUEUE_TRY_PEEK
	( que data -- bool )
	
QUEUE_ADD_BLOCKING
	( que data -- )
	
QUEUE_REMOVE_BLOCKING
	( que data -- )
	
QUEUE_PEEK_BLOCKING
	( que data -- )

