/**
 ******************************************************************************
 *							USEFUL ELECTRONICS
 ******************************************************************************/
/**
 ******************************************************************************
 * @file    :  main.h
 * @author  :  WARD ALMASARANI
 * @version :  v.1.0
 * @date    :  Feb 6, 2024
 * @link    :  https://www.youtube.com/@usefulelectronics
 *			   Hold Ctrl button and click on the link to be directed to
			   Useful Electronics YouTube channel	
 ******************************************************************************/

#ifndef MAIN_H_
#define MAIN_H_


/* INCLUDES ------------------------------------------------------------------*/
#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/queue.h"
#include "freertos/semphr.h"
#include "esp_timer.h"
#include "driver/gpio.h"


/* MACROS --------------------------------------------------------------------*/
#define MAIN_LEFT_BUTTON 		1
#define MAIN_RIGHT_BUTTON 		3

#define SYS_TICK()				xTaskGetTickCount() * portTICK_PERIOD_MS
/* ENUMORATIONS --------------------------------------------------------------*/

/* STRUCTURES & TYPEDEFS -----------------------------------------------------*/

/* VARIABLES -----------------------------------------------------------------*/
extern TaskHandle_t hMain_eventTask;
/* FUNCTIONS DECLARATION -----------------------------------------------------*/



#endif /* MAIN_MAIN_H_ */

/*************************************** USEFUL ELECTRONICS*****END OF FILE****/
