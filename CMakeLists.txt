# Generated Cmake Pico project file

cmake_minimum_required(VERSION 3.12)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)


# initalize pico_sdk from installed location
# (note this can come from environment, CMake cache etc)
set(PICO_SDK_PATH "/home/pi/pico/pico-sdk")
set(PICO_EXTRAS_PATH "/home/pi/pico/pico-extras")

# Pull in Pico SDK (must be before project)
include(pico_sdk_import.cmake)
include(${PICO_EXTRAS_PATH}/external/pico_extras_import.cmake)

project(atlast C CXX)

# Initialise the Pico SDK
pico_sdk_init()

# Add executable. Default name is the project name, version 0.1

add_executable(atlast atlast.c )

pico_set_program_name(atlast "atlast")
pico_set_program_version(atlast "0.1")

pico_enable_stdio_uart(atlast 0)
pico_enable_stdio_usb(atlast 1)

# Run in RAM (NOT FOR PICOW )
#set(SET_COPY_TO_RAM 1)
#pico_set_binary_type(atlast copy_to_ram)

# Add the standard library to the build
target_link_libraries(atlast pico_stdlib)

# Add any user requested libraries
target_link_libraries(atlast
	hardware_spi
	hardware_adc
	hardware_watchdog
	pico_multicore 
    hardware_i2c
    hardware_pio
	pico_cyw43_arch_lwip_threadsafe_background
#	pico_cyw43_arch_lwip_poll
	pico_lwip_http
)

pico_add_extra_outputs(atlast)

include_directories( /home/pi/pico/atlast )

# Make malloc return 0 and not panic
target_compile_definitions(atlast PRIVATE PICO_MALLOC_PANIC=0)

