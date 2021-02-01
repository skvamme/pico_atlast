#define ATLAST "( Blink morse code pico ) \n\
: setup 25 gpio_init 25 1 gpio_set_dir ; \n\
: sp 100 sleep_ms ; \n\
: sh 25 1 gpio_put sp 25 0 gpio_put sp ; \n\
: lo 25 1 gpio_put sp sp sp 25 0 gpio_put sp ; \n\
: p sh lo lo sh ; \n\
: ii sh sh ; \n\
: c lo sh lo sh ;  \n\
: o lo lo lo ; \n\
: blink begin p sp sp ii sp sp c sp sp o sp sp sp sp sp sp again ; \n\
setup blink\n"
