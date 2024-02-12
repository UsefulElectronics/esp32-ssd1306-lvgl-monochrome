SET(SOURCES screens/ui_mainScreen.c
    ui.c
    components/ui_comp_hook.c
    ui_helpers.c
    ui_events.c
    fonts/ui_font_S52.c
    fonts/ui_font_SS52.c)

add_library(ui ${SOURCES})
