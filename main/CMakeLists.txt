file(GLOB_RECURSE DISPLAY_SOURCES display/*.c)
file(GLOB_RECURSE HARDWARE_SOURCES hardware/*.c)
file(GLOB_RECURSE PERIPHERALS_SOURCES peripherals/*.c)

idf_component_register(SRCS "main.c" "esp_interrupt.c" "display/logo_small.c" 
					   ${DISPLAY_SOURCES}
					   ${HARDWARE_SOURCES}
					   ${PERIPHERALS_SOURCES}
                       INCLUDE_DIRS ".")