# Generated Cmake Pico project file

cmake_minimum_required(VERSION 3.12)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

# initalize pico_sdk from installed location
# (note this can come from environment, CMake cache etc)
set(PICO_SDK_PATH "/home/pi/pico_atlast/pico-sdk")

# Pull in Pico SDK (must be before project)
include(pico_sdk_import.cmake)

project(atlast C CXX)

# Initialise the Pico SDK
pico_sdk_init()

# Add executable. Default name is the project name, version 0.1

add_executable(atlast atlast.c )

pico_set_program_name(atlast "atlast")
pico_set_program_version(atlast "0.1")

pico_enable_stdio_uart(atlast 0)
pico_enable_stdio_usb(atlast 1)

# Add the standard library to the build
target_link_libraries(atlast pico_stdlib)

# Add any user requested libraries
target_link_libraries(atlast
        hardware_spi
        hardware_adc
	hardware_watchdog
	pico_multicore 
#        hardware_i2c
#        hardware_pio
        )

pico_add_extra_outputs(atlast)

