#define ATLAST "( Blink temp Celsius 0 - 24 deg) \n\
: sp 100 sleep_ms ; \n\
: dot 25 1 gpio_put sp 25 0 gpio_put sp ; \n\
: dash 25 1 gpio_put sp sp sp 25 0 gpio_put sp ; \n\
\n\
: w0 dash dash dash dash dash ; \n\
: w1 dot dash dash dash dash ; \n\
: w2 dot dot dash dash dash ; \n\
: w3 dot dot dot dash dash ; \n\
: w4 dot dot dot dot dash ; \n\
: w5 dot dot dot dot dot ; \n\
: w6 dash dot dot dot dot ; \n\
: w7 dash dash dot dot dot ; \n\
: w8 dash dash dash dot dot ; \n\
: w9 dash dash dash dash dot ; \n\
: w10 w1 sp sp w0 ; \n\
: w11 w1 sp sp w1 ; \n\
: w12 w1 sp sp w2 ; \n\
: w13 w1 sp sp w3 ; \n\
: w14 w1 sp sp w4 ; \n\
: w15 w1 sp sp w5 ; \n\
: w16 w1 sp sp w6 ; \n\
: w17 w1 sp sp w7 ; \n\
: w18 w1 sp sp w8 ; \n\
: w19 w1 sp sp w9 ; \n\
: w20 w2 sp sp w0 ; \n\
: w21 w2 sp sp w1 ; \n\
: w22 w2 sp sp w2 ; \n\
: w23 w2 sp sp w3 ; \n\
: w24 w2 sp sp w4 ; \n\
\n\
: stuff ['] w24 ['] w23 ['] w22 ['] w21 ['] w20 ['] w19 ['] w18 ['] w17 ['] w16 \n\
['] w15 ['] w14 ['] w13 ['] w12 ['] w11 \n\
['] w10 ['] w9 ['] w8 ['] w7 ['] w6 ['] w5 ['] w4 ['] w3 ['] w2 ['] w1 ['] w0 ; \n\
\n\
: setup 25 gpio_init 25 1 gpio_set_dir \n\
stuff adc_init 1 adc_set_temp_sensor_enabled 4 adc_select_input ;\n\
\n\
: run begin adc_temp fix dup . cr pick execute 3000 sleep_ms again ; \n\
setup run\n"
