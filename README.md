# pico_atlast
ATLAST Forth for Raspberry Pi Pico is a C application with a built in forth scripting environment. Compiles out of the box, no C-programming knowledge required to use the ATLAST forth console. Get full access to the Raspberry Pi Pico C API in atlast.c and use forth as a quick yet powerful scripting engine. 

<b>Documentation:</b> http://www.fourmilab.ch/atlast/ and https://www.forth.com/starting-forth/ and https://www.dnd.utwente.nl/~tim/colorforth/Leo-Brodie/thinking-forth.pdf

Charles Moore, the inventor of forth gave an interview here http://www.ultratechnology.com/1xforth.htm and a presentation here https://www.youtube.com/watch?v=0PclgBd6_Zs 

Here is a nice tutorial from Shropshire LUG - Oct 2020 https://www.youtube.com/watch?v=EADDOnRtFrI 

J.V Noble wrote this https://galileo.phys.virginia.edu/classes/551.jvn.fall01/primer.htm and this http://galileo.phys.virginia.edu/classes/551.jvn.fall01/Fth_rev1.pdf

<B> Latest Commit:</b> Support for Neopixel LED and LEDstrips.

<B>Previous commit:</b> Run headless by commenting-out #MEMMESSAGE in atlast.c line 65. Code in BLOCK 50 is autoloaded and run.

<B>Previous commit:</b> [PICOW] Added an example how to get a file from a web server. get_from_server.atl The result from the GET is in a string variable BODY that you can TYPE or, if it is forth source code, EVALUATE to compile.

The input buffer is a round robin. If the end of the file overwrites the begining, the file is too big.

Added an example how to push data to a web sever picow_send_data.atl using GET and data encoded in the path.

<B>Previous commit:</b> Added support for PICOW. PICOW words are ARCH_POLL, WIFI_INIT, WIFI_DEINIT, HTTPC_GET_FILE, WIFI_CONNECT, TCPIP_LINK_STATUS.

<b>Previous commit:</b> Use FORTH blocks to store source code and data in FLASH. New words are LIST, LOAD, BLOCK, EMPTYBUFFER, SAVEBUFFER. See atlast.html. Try 63 0 LIST and you will get a text result from Factory Production Test. 

<b>To store a file</b> in a flash block. Max line width 130 characters. Run the shell script atl2blk.sh yourfilename.whatever The result is a file blk.atl Connect to your pico, and in cu type ~ (wait for a prompt) type > (enter) and type the name of the file to import BLK.ATL. Result is each file line as a separate string on the stack. Copy paste the text in the file blockzero.atl and run the word STACKSTRINGS It will put all the strings on the stack into one string buffer. Type 64 EMPTYBUFFER and BUFFER 64 SAVEBUFFER (64 is just an example, there is more than 400 blocks to use). Now you can type 64 0 list or 64 load if it was forth code. Any code that you put in block 50 will autorun when the pico is started headless by commenting out #MEMMESSAGE in atlast.c line 65. 

<b>Note:</b> If you want to read from memory outside the HEAP, define #NOMEMCHECK at line 72 of atlast c. It will also give a considerable speed improvment. But beware, you can read and write everywhere.

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

To exit cu, type ~ (wait for a prompt) and type  .

There is a nice feature in cu, type ~ (wait for the prompt) and type > and give a file name you want to download to the pico. Use the forth word FORGET to erase words you don't want. 

Note: The last character in your forth files should be a new line. Alternatively, reconfigure cu to put in a nl/cr instead of the default EOF. Press enter when "File transfer complete" to clear kb buffer.

The other way around is also possible, type ~ (wait for the prompt) and type < and give a file name you want to use for saving data from pico. Type it as both infile and outfile, and then type a forth word that prints the data e.g. 1 0 list to get the contents of flash block 1.

The following terminal emulators can do sixel graphics: XTerm (360 or later), MLterm (3.8.4), Contour (0.1.1), WezTerm (20210502), Mintty (3.5.0), RLogin (2.25.3), XQuartz, MacTerm and Reflection Desktop (16.2.0).

