file(GLOB_RECURSE DISPLAY_SOURCES display/*.c)

idf_component_register(SRCS "main.c" 
					   ${DISPLAY_SOURCES}
                       INCLUDE_DIRS ".")