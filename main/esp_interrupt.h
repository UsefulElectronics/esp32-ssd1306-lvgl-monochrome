/**
 ******************************************************************************
 *							USEFUL ELECTRONICS
 ******************************************************************************/
/**
 ******************************************************************************
 * @file    :  esp_interrupt.h
 * @author  :  WARD ALMASARANI
 * @version :  v.1.0
 * @date    :  Aug 1, 2023
 * @link    :  https://www.youtube.com/@usefulelectronics
 *			   Hold Ctrl button and click on the link to be directed to
			   Useful Electronics YouTube channel	
 ******************************************************************************/

#ifndef MAIN_ESP_INTERRUPT_H_
#define MAIN_ESP_INTERRUPT_H_


/* INCLUDES ------------------------------------------------------------------*/
#include "driver/gpio.h"
#include "driver/periph_ctrl.h"
#include "esp_log.h"
#include "main.h"


/* MACROS --------------------------------------------------------------------*/

/* ENUMORATIONS --------------------------------------------------------------*/

/* STRUCTURES & TYPEDEFS -----------------------------------------------------*/
//This interrupt ID should be passed to the event task to differentiate between events
typedef enum 
{
	IDLE_INT 		  = 0,
	RIGHT_BUTTON_INT  = MAIN_RIGHT_BUTTON	,
	LEFT_BUTTON_INT	  = MAIN_LEFT_BUTTON	,
}interrupt_e;
/* VARIABLES -----------------------------------------------------------------*/
extern interrupt_e interrupt_id;
/* FUNCTIONS DECLARATION -----------------------------------------------------*/
/**
 * @brief 	GPIO interrupt service routine will be executed when the related interrupt is fired. this function will give
 * 			button_sem as semaphore and clear the related interrupt flags
 *
 * @param 	arg	:	pointer to the GPIO pin responsible for the interrupt.
 */
void  gpio_isr_handle(void *arg);


#endif /* MAIN_ESP_INTERRUPT_H_ */

/*************************************** USEFUL ELECTRONICS*****END OF FILE****/
