/**
 ******************************************************************************
 *							USEFUL ELECTRONICS
 ******************************************************************************/
/**
 ******************************************************************************
 * @file    :  lvgl_ui.h
 * @author  :  WARD ALMASARANI
 * @version :  v.1.0
 * @date    :  Feb 6, 2024
 * @link    :  https://www.youtube.com/@usefulelectronics
 *			   Hold Ctrl button and click on the link to be directed to
			   Useful Electronics YouTube channel	
 ******************************************************************************/

#ifndef LVGL_UI_H_
#define LVGL_UI_H_


/* INCLUDES ------------------------------------------------------------------*/
#include "lvgl.h"

/* MACROS --------------------------------------------------------------------*/

/* ENUMORATIONS --------------------------------------------------------------*/
typedef enum
{
	LVGL_TIMER_STOP = 0,
	LVGL_TIMER_CREAT,
	LVGL_TIMER_RESUME,
	LVGL_TIMER_PAUSE,
	LVGL_TIMER_RESET
}lvgl_timer_status_t;

/* STRUCTURES & TYPEDEFS -----------------------------------------------------*/

/* VARIABLES -----------------------------------------------------------------*/

/* FUNCTIONS DECLARATION -----------------------------------------------------*/
void lvgl_ui_start(lv_disp_t *disp);

void lvgl_ui_timer_function(lvgl_timer_status_t timer_state);

bool lvgl_ui_pause_timer_check();

bool lvgl_ui_running_timer_check(void);


#endif /* MAIN_LVGL_UI_H_ */

/*************************************** USEFUL ELECTRONICS*****END OF FILE****/
