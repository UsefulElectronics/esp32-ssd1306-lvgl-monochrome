/**
 ******************************************************************************
 *							USEFUL ELECTRONICS
 ******************************************************************************/
/**
 ******************************************************************************
 * @file    :  main.c
 * @author  :  WARD ALMASARANI
 * @version :  v.1.0
 * @date    :  Feb 6, 2024
 * @link    :  https://www.youtube.com/@usefulelectronics
 *			   Hold Ctrl button and click on the link to be directed to
			   Useful Electronics YouTube channel	
 ******************************************************************************/


/* INCLUDES ------------------------------------------------------------------*/
#include "main.h"
#include "display/display_config.h"
#include "hardware/button.h"
#include "peripherals/gpio_config.h"
#include "esp_interrupt.h"
/* PRIVATE STRUCTRES ---------------------------------------------------------*/

/* VARIABLES -----------------------------------------------------------------*/
static const char *TAG = "main";
TaskHandle_t hMain_eventTask			= NULL;
/* DEFINITIONS ---------------------------------------------------------------*/

/* MACROS --------------------------------------------------------------------*/

/* PRIVATE FUNCTIONS DECLARATION ---------------------------------------------*/
static void event_handle_task(void* param);
static void main_system_task(void* param);
static uint32_t main_get_systick(void);
static void main_right_button_callback(button_state_t button_callback_type);
static void main_left_button_callback(button_state_t button_callback_type);
/* FUNCTION PROTOTYPES -------------------------------------------------------*/

void app_main(void)
{
	display_init();

	gpio_config_ext_interrupt(MAIN_LEFT_BUTTON,
							GPIO_PULLUP_ENABLE,
							GPIO_PULLDOWN_DISABLE,
							GPIO_INTR_NEGEDGE,
							gpio_isr_handle);

	gpio_config_ext_interrupt(MAIN_RIGHT_BUTTON,
							GPIO_PULLUP_ENABLE,
							GPIO_PULLDOWN_DISABLE,
							GPIO_INTR_NEGEDGE,
							gpio_isr_handle);

	button_init((uint32_t*)main_get_systick, gpio_get_level);

	button_add(MAIN_LEFT_BUTTON, true, 1000, main_left_button_callback);

	button_add(MAIN_RIGHT_BUTTON, true, 1000, main_right_button_callback);


	xTaskCreatePinnedToCore(event_handle_task, "event_handle_task", 10000, NULL, 4, &hMain_eventTask, 1);

	xTaskCreatePinnedToCore(main_system_task, "main_system_task", 10000, NULL, 4, NULL, 1);
}

void main_system_task(void* param)
{
	TickType_t xLastWakeTime = xTaskGetTickCount();


	while(1)
	{

		button_manager();

        vTaskDelayUntil(&xLastWakeTime, pdMS_TO_TICKS(10) );

	}
}

static void event_handle_task(void* param)
{
	while(1)
	{
		//Note: CallbackID is cleared immediately after executing this task
		if(xTaskNotifyWait(0, ULONG_MAX, &interrupt_id, portMAX_DELAY ))
		{
			button_debounce(interrupt_id);
		}
	}
}

static void main_right_button_callback(button_state_t button_callback_type)
{
	lvgl_timer_status_t timer_action = LVGL_TIMER_CREAT;

	if(lvgl_ui_running_timer_check())
	{
		timer_action = LVGL_TIMER_RESET;

		lvgl_ui_timer_function(timer_action);
	}
	else
	{
		lvgl_ui_timer_function(timer_action);
	}
	ESP_LOGI(TAG, "right button callback: %d", button_callback_type);
}

static void main_left_button_callback(button_state_t button_callback_type)
{
	lvgl_timer_status_t timer_action = LVGL_TIMER_RESUME;

	if(lvgl_ui_pause_timer_check())
	{
		lvgl_ui_timer_function(timer_action);
	}
	else
	{
		timer_action = LVGL_TIMER_PAUSE;

		lvgl_ui_timer_function(timer_action);
	}

	ESP_LOGI(TAG, "left button callback: %d", button_callback_type);
}

static uint32_t main_get_systick(void)
{
	return SYS_TICK();
}
/*************************************** USEFUL ELECTRONICS*****END OF FILE****/
