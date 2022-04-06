# pico_atlast
ATLAST Forth for Raspberry Pi Pico is a boilerplate C application with a built in forth scripting environment. Compiles out of the box, no C-programming knowledge required to use the ATLAST forth console. Get full access to the Raspberry Pi Pico C API in atlast.c and use forth as a quick yet powerful scripting engine. 

Documentation: http://www.fourmilab.ch/atlast/ and https://www.forth.com/starting-forth/ and https://www.dnd.utwente.nl/~tim/colorforth/Leo-Brodie/thinking-forth.pdf

Here is one way to install this on a raspberry pi 4. If you are on another computer, here is a HOWTO https://datasheets.raspberrypi.com/pico/getting-started-with-pico.pdf

Download the shellscript pico_setup.sh and make it executable. Run it from your home directory.
<pre>wget https://raw.githubusercontent.com/raspberrypi/pico-setup/master/pico_setup.sh
chmod 744 pico_setup.sh
./pico_setup.sh</pre>

Clone pico-project-generator in your home directory 
<pre>sudo apt install git
git clone https://github.com/raspberrypi/pico-project-generator
sudo apt install python3-tk
cd pico-project-generator
./pico_project.py --gui</pre>

Type project name atlast and place it in the pico directory. Check all Library Options. Check "console over usb" and uncheck "console over UART". Press OK. 

Clone this pico_atlast git repository in your home directory and copy the files to the atlast directory in ~/pico The reason I do it this way is that I don't want a git repository in the toolchain.
<pre>
git clone https://github.com/skvamme/pico_atlast
cd pico_atlast
cp *.* ~/pico/atlast
</pre>

Go to ~/pico/atlast and open the file CMakeLists.txt and add a line to the list of User requested libraries down at the end of the file. Put it right after hardware_spi. These two are actually needed, comment out the other ones if you like.
<pre>hardware_spi
hardware_adc
</pre>

Compile pico_atlast
<pre>cd ~/pico/atlast/build
make
</pre>

Hold the BOOTSEL button down while connecting the pico to the raspberry pi USB port. The pico mounts as an external drive. Drag and drop the file atlast.uf2 from ~/pico/atlast/build to the pico external drive. It will now disconnect.

From now on you can use the forth word BOOTSEL to reboot the pico as an external drive; drag and drop a new uf2-file without the need to unplug and hold button.

Upgrade your Xterm to the latest version. 
<pre>sudo apt install xterm</pre>

And install cu
<pre>sudo apt install cu</pre>

Add a file .Xresources to your home directory with the following line 
<pre>vi .Xresources
i
xterm*decTerminalID: vt340
ESC :wq

xrdb -merge .Xresources</pre>
Note: The "i" and"ESC :wq" are vi-commands. Use your favourite editor.

Start xterm
<pre>xterm -fn 6x12</pre>

Connect to the pico with 
<pre>cu --nostop -l /dev/ttyACM0 -s 115200</pre>

Now, you have the forth interpreter and compiler up and running. If you didn't make your own forth.h, turn off sixel scrolling in xterm with ctrl-middlemousebutton, and then type the forth word RUN

To exit cu, type ~ (wait for a prompt) and type  .

There is a nice feature in cu, type ~ (wait for the prompt) and type > and give a file name you want to download to the pico.
You can try different versions of your atlast forth files before creating the .h file with atl2h.sh Use the forth word FORGET to erase words you don't want. Note: The last character in your forth files should be a new line. Alternatively, reconfigure cu to put in a nl/cr instead of the default EOF. Press enter when "File transfer complete" to clear kb buffer.

The other way around is also possible, type ~ (wait for the prompt) and type < and give a file name you want to use for saving data from pico. Type it as both infile and outfile, and then type a forth word that prints the data.

The following terminal emulators can do sixel graphics: XTerm (360 or later), MLterm (3.8.4), Contour (0.1.1), WezTerm (20210502), Mintty (3.5.0), RLogin (2.25.3), XQuartz and Reflection Desktop (16.2.0).
*******************************************************************************************

If you want to make your forth code remain after power off, use the shell script atl2h.sh.

1. Put your forth code in a file,  "anyname.atl". Make sure to keep source line width below max column 132.

2. Run "./atl2h.sh anyname.atl" to create the file forth.h. 

3. Compile atlast.c with make in the build directory.

If forth is the main entry point, the forth code must contain a word "GO" with an infinite loop, e.g. begin ... again to keep the application running. Otherwise, you will get an interactive console where you can use all the standard forth words, your own word definitions from forth.h and even define new words. New word definitions will last until power off. Use the construct "kbhit? if exit then" to be able to break out from a begin ... again loop.

******************************************************************************************
Read the PICO documentation for the C/C++ API for a detailed description of each function. https://datasheets.raspberrypi.com/pico/raspberry-pi-pico-c-sdk.pdf

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

HOUR_US
	( hours minutes -- msb lsb ) Convert hours and minutes to 2x32 bit microseconds.
	
ADD_ALARM_IN_US
	( msb lsb bool "NAME" -- result ) 2x32 bit value is microseconds to alarm. bool is 0 or 1. NAME is the word to execute.
	
U64.
	( msb lsb -- ) Print unsigned 64 bit integer

U.
	( integer -- ) Print unsigned 32 bit integer.
	
EMIT
	( integer -- ) Print ASCII integer as a char
	
BOOTSEL
	( -- ) Re-boot pico in external drive mode.
	
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

