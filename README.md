# pico_atlast
ATLAST Forth for Raspberry Pi Pico is a C application with a built in forth scripting environment. Compiles out of the box, no C-programming knowledge required to use the ATLAST forth console. Get full access to the Raspberry Pi Pico C API in atlast.c and use forth as a quick yet powerful scripting engine. 

<b>Documentation:</b> http://www.fourmilab.ch/atlast/ and https://www.forth.com/starting-forth/ and https://www.dnd.utwente.nl/~tim/colorforth/Leo-Brodie/thinking-forth.pdf Charles Moore, the inventor of forth gave an interview here http://www.ultratechnology.com/1xforth.htm and a presentation here https://www.youtube.com/watch?v=0PclgBd6_Zs Here is a nice tutorial from Shropshire LUG - Oct 2020 https://www.youtube.com/watch?v=EADDOnRtFrI

<B>Latest commit:</b> Added support for PICOW. Cannot run in RAM so you are not able to write blocks in flash. Reading and running is ok. PICOW words are ARCH_POLL, WIFI_INIT, WIFI_DEINIT, HTTPC_GET_FILE, WIFI_CONNECT, TCPIP_LINK_STATUS.

<b>Previous commit:</b> Use FORTH blocks to store source code and data in FLASH. New words are LIST, LOAD, BLOCK, EMPTYBUFFER, SAVEBUFFER. See atlast.html. 

ATLAST Forth now running in RAM. Try 63 0 LIST and you will get a text result from Factory Production Test. 

To store something in a flash block, write it in a file. Max line width 130 characters. Run the shell script atl2blk.sh yourfilename.whatever The result is a file blk.atl Connect to your pico, and in cu type ~ (wait for a prompt) type > (enter) and type the name of the file to import BLK.ATL. Result is each file line as a separate string on the stack. Copy paste the text in the file blockzero.atl and run the word STACKSTRINGS It will put all the strings on the stack into one string buffer. Type 5 EMPTYBUFFER and BUFFER 5 SAVEBUFFER (5 is just an example, there is more than 400 blocks to use). Now you can type 5 0 list or 5 load if it was forth code. Any code that you put in block 0 will autorun when the pico is started.

<b>Installation:</b> Here is one way to install this on a raspberry pi (Verified on a pi 4). If you are on another computer, here is a HOWTO https://datasheets.raspberrypi.com/pico/getting-started-with-pico.pdf

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

Clone this pico_atlast git repository in your home directory and copy the files to the atlast directory in ~/pico The reason I do it this way is that I don't want a git repository in the toolchain. Before copying, rename my CMakeLists.txt to something else and use it as a reference.
<pre>
git clone https://github.com/skvamme/pico_atlast
cd pico_atlast
mv CMakeLists.txt CMakeLists.original
cp *.* ~/pico/atlast
</pre>

Go to ~/pico/atlast and open the file CMakeLists.txt and add a line to the list of User requested libraries down at the end of the file. Put it right after hardware_spi. These two are actually needed, comment out the other ones if you like.
Add a line to run ATLAST in RAM. 
Add a last line to the file, make the C-function malloc return 0 if out of memory for the forth word memstat to work.
<pre>hardware_spi
hardware_adc
# Run in RAM
pico_set_binary_type(atlast copy_to_ram)
# Last line, make malloc return 0 on out of memory
target_compile_definitions(atlast PRIVATE PICO_MALLOC_PANIC=0)
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
If you are on a Mac, cu is part of the Taylor UUCP package, install with MacPorts:
<pre>sudo port install uucp</pre>

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
If you are on a Mac, the serial port is something like
<pre>sudo cu --nostop -l /dev/cu.usbmodem141201 -s 115200</pre>

Put some Forth code in block 0 (block 0 is autoloaded at startup)
<pre>".( \"Hello from buffer 0\" cr" 0 savebuffer</pre>

To exit cu, type ~ (wait for a prompt) and type  .

There is a nice feature in cu, type ~ (wait for the prompt) and type > and give a file name you want to download to the pico. Use the forth word FORGET to erase words you don't want. 

Note: The last character in your forth files should be a new line. Alternatively, reconfigure cu to put in a nl/cr instead of the default EOF. Press enter when "File transfer complete" to clear kb buffer.

The other way around is also possible, type ~ (wait for the prompt) and type < and give a file name you want to use for saving data from pico. Type it as both infile and outfile, and then type a forth word that prints the data e.g. 1 0 list to get the contents of flash block 1.

The following terminal emulators can do sixel graphics: XTerm (360 or later), MLterm (3.8.4), Contour (0.1.1), WezTerm (20210502), Mintty (3.5.0), RLogin (2.25.3), XQuartz, MacTerm and Reflection Desktop (16.2.0).
*******************************************************************************************

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

************** PICOW ****************
ARCH_POLL
	( -- )

WIFI_INIT
	( -- result )

WIFI_DEINIT
	( -- )
	
HTTPC_GET_FILE
	( int int int int int str -- )
	e.g. 127 0 0 1 8080 "/index.html" HTTPC_GET_FILE

WIFI_CONNECT
	( ssid password -- result )

TCPIP_LINK_STATUS
	( -- result )
