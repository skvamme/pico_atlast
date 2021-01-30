#define ATLAST "( Blink morse code p i c o ) \
: setup 25 gpioinit 25 1 gpiosetdir ; \
: sl longsleep ; \
: sp 100 sl ; \
: sh 25 1 gpioput sp 25 0 gpioput sp ; \
: lo 25 1 gpioput sp sp sp 25 0 gpioput sp ; \
: p sh lo lo sh ; \
: i sh sh ; \
: c lo sh lo sh ;  \
: o lo lo lo ; \
: blink begin p sp sp i sp sp c sp sp o sp sp sp sp sp sp again ; \
setup blink"
