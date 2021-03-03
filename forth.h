#define ATLAST " ( ATLAST forth ) \n\
( test 64 bit timestamp words ) \n\
: go begin time_us 500 sleep_ms time_us time_diff u64. 500 sleep_ms again ; \n\
go\n"
