file(GLOB_RECURSE DISPLAY_SOURCES display/*.c)
file(GLOB_RECURSE HARDWARE_SOURCES hardware/*.c)

idf_component_register(SRCS "main.c" "esp_interrupt.c"
					   ${DISPLAY_SOURCES}
					   ${HARDWARE_SOURCES
                       INCLUDE_DIRS ".")