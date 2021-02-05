# pico_atlast 

Get full access to the Raspberry Pi Pico C API in atlast.c and use forth as a quick yet powerful scripting engine in forth.h

Documentation: http://www.fourmilab.ch/atlast/ and https://www.forth.com/starting-forth/ and https://www.dnd.utwente.nl/~tim/colorforth/Leo-Brodie/thinking-forth.pdf

Atlast Forth for Raspberry Pi Pico is a boilerplate C application with a built in forth scripting environment. Put the forth code in the file forth.h and compile atlast.c with cmake and make, see https://github.com/raspberrypi/pico-sdk 

If forth is the main entry point, the forth code must contain an infinite loop, e.g. begin ... again to keep the application running. Otherwise, put the infinite loop in the main function in atlast.c An application on the pico should never return.

Use the Makefile included in this repo to compile atlast.c to run on a Raspberry Pi or other host to be able to test your forth code before flashing to the pico. Make sure to comment out #define PICO prior to compilation. Take a look at https://github.com/skvamme/atlast for some example forth code, coded for the pigpio library. API names and functions are very similar to the pico C API.

Read the PICO documentation for the C/C++ API for a detailed description of each function.

Defined words:

SLEEP_US

Stack before: integer number of microseconds to sleep
	
This word leaves nothing at the stack
	
This can be illustrated in this way: ( microsec -- )

SLEEP_MS
	( millisec -- )

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

GPIO_SET_IRQ_ENABLED_WITH_CALLBACK
	( gpiopin events bool word --  ) events is a bimapped integer

GPIO_SET_FUNCTION
	( gpiopin function --  ) function is an integer, look it up in pico C API doc
	
GPIO_SET_IRQ_ENABLED_WITH_CALLBACK
	( pin events bool word -- ) word is the compile address, use ['] word to get it
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
	
TODO: MULTICORE_LAUNCH_CORE1
	( word -- ) word is a compile address, get it with ['] It should never return

TODO: MULTICORE_FIFO_POP_BLOCKING
	( -- result )

TODO: MULTICORE_FIFO_PUSH_BLOCKING
	( value -- )


