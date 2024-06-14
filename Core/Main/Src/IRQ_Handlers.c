#include "stm32f4xx_hal.h"
#include "tim.h"


/*
//		If the encoder changed position ...
*/
volatile uint8_t encoderChangedPosition = 0U;
volatile int8_t encoderDir = 0;	// -1 / 1
									// 0 <--> nothing
volatile uint8_t encoderButtonPushed = 0U;
volatile uint8_t menuButtonPushed = 0U;
volatile uint8_t stopButtonPushed = 0U;
static volatile uint8_t currentEXTI = 0U;
static volatile uint16_t currentPin = 0U;



// This is the handler for the encoder
// It runs every change angle (in any direction) of the encoder
void HAL_TIM_IC_CaptureCallback(TIM_HandleTypeDef *htim)
{
	
	if (htim->Instance == TIM1) {
		
		encoderChangedPosition = 1U;

		if (TIM1->CNT > 50) {
			encoderDir = 1;
		} else if (TIM1->CNT < 50) {
			encoderDir = -1;
		}

		TIM1->CNT = (uint16_t)50U;
	}
}


// Menu button callback
// Encoder button callback
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
	
	if (GPIO_Pin == GPIO_PIN_5) {	// Menu button pushed
		
		menuButtonPushed = (menuButtonPushed == 0U) ? 1U : 0U;
		currentEXTI = EXTI9_5_IRQn;
		currentPin = GPIO_PIN_5;
		
	} else if (GPIO_Pin == GPIO_PIN_10) {	// Encoder button pushed
		
		encoderButtonPushed = (encoderButtonPushed == 0U) ? 1U : 0U;
		currentEXTI = EXTI15_10_IRQn;
		currentPin = GPIO_PIN_10;	
		
	} else if (GPIO_Pin == GPIO_PIN_1) {	// Stop button pushed
		
		stopButtonPushed = (stopButtonPushed == 0U) ? 1U : 0U;
		currentEXTI = EXTI1_IRQn;
		currentPin = GPIO_PIN_1;

	}
	
	HAL_NVIC_DisableIRQ(currentEXTI); // disable the EXTI interrupt
	HAL_TIM_Base_Start_IT(&htim10);  // start the timer (TIM10) for debounce

}


// For debounce for all buttons
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{

	if (htim->Instance == TIM10) {

		HAL_TIM_Base_Stop_IT(&htim10); 			// stop the timer interrupts 
        __HAL_GPIO_EXTI_CLEAR_IT(currentPin);  // clear bit EXTI_PR (interrupt bit)
        NVIC_ClearPendingIRQ(currentEXTI); 		// clear bit NVIC_ICPRx (queue bit)
        HAL_NVIC_EnableIRQ(currentEXTI);   		// turn on external interrupt

	}
}







