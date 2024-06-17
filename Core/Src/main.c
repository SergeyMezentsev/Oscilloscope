/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2024 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "spi.h"
#include "tim.h"
#include "usart.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

//#include "IRQ_Handlers.h"
#include <stdio.h>
#include <string.h>
#include "graphic.h"
// #include "ADC.h"

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */

volatile uint8_t flag = 0u;
volatile uint8_t flag_menu = 0u;
volatile uint8_t flag_btn_encoder = 0u;

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_SPI1_Init();
  MX_TIM1_Init();
  MX_USART6_UART_Init();
  MX_TIM10_Init();
  MX_TIM9_Init();
  /* USER CODE BEGIN 2 */
	
	
	
	//----------------------------------------------------------------------------------------------------------------------------------------------------------
	/*
	ST7735_initR(INITR_BLACKTAB, &hspi1); // Initialize the LCD
  setRotation(1);
  createFramebuf(); // Create the framebuffer for the LCD
  clearDisplay();
  //splash(); // Splash screen
	
	//drawBitmap(0, 0, 160, 128, (uint16_t*)logo);
	drawRect(20, 20, 50, 50, ST7735_RED);
  setTextColor(ST7735_BLACK, ST7735_WHITE);

  printString(" FW compiled: ");
  //printString(__DATE__);
  flushDisplay();
	drawFastVLine(50, 50, 77, ST7735_RED);
  HAL_Delay(2500);
	*/




  
	HAL_TIM_IC_Start_IT(&htim1, TIM_CHANNEL_1);
	HAL_TIM_Encoder_Start(&htim1, TIM_CHANNEL_1);
  HAL_TIM_Base_Start_IT(&htim9);

  scopeInit();

  

	//----------------------------------------------------------------------------------------------------------------------------------------------------------
	
	uint8_t str[10];
	uint8_t str1[] = "Pushed\r\n\0";
  uint8_t str2[] = "Released\r\n\0";
	
	
	//createADCArray();
  //createPointArrays();
  //getNewADCMeasures();
  
  //updateScales();

  // uint16_t len = 200;
  // uint16_t* mas  = (uint16_t*)malloc(len * sizeof(uint16_t));
  
	// for (uint16_t i = 0U; i < len; ++i) {
  //   mas[i] = i;
  // }
	
	
	

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
		
		//HAL_GPIO_TogglePin(GPIOC, GPIO_PIN_13);
		//HAL_Delay(100);
		
		

		//clearDisplay();
		
		// if (flag) {
		// drawRect(20, 20, 100, 100, ST7735_RED);
		// flag = 0u;
		
		// } else {
		// 	drawRect(20, 20, 100, 100, ST7735_BLUE);
		// 	flag = 1u;
			
		// }
		// //flushDisplay();
		// HAL_Delay(200);
		






		
		
    scopeLoop();

    sprintf((char*)str, "%d\n\r", pixelScaleMV);
    HAL_UART_Transmit(&huart6, str, strlen((char*)str), 30);
    // if (updateScreenShot == 1U) {
    //   HAL_UART_Transmit(&huart6, str1, 8, 30);
    //   updateScreenShot = 0U;
    // }
    
    // if (measures != NULL) {
    //   for (uint16_t i = 0U; i < LENGTH; ++i) {
    //     sprintf((char*)str, "%d\n\r", measures[i]);
    //     //sprintf((char*)str, "---\n\r");
    //     HAL_UART_Transmit(&huart6, str, strlen((char*)str), 30);
    //     HAL_Delay(100);
    //   }
    // } else {
    //   HAL_UART_Transmit(&huart6, str1, strlen((char*)str1), 30);
    //   HAL_Delay(100);
    // }
		
    
    // sprintf((char*)str, "%d\n\r", trigLevelMV);
		// HAL_UART_Transmit(&huart6, str, strlen(str), 30);
    // HAL_Delay(10);
    











		






    // if (menuButtonPushed == 1U) {
		//   HAL_UART_Transmit(&huart6, str1, 8, 30);		  
    // } else {
    //   HAL_UART_Transmit(&huart6, str2, 10, 30);
    // }

    // HAL_Delay(50);






    // Test the INTERRUPTS
    /*
		if (flag != 0u) {
			cnt = TIM1->CNT;
			sprintf(str, "%d\r\n", cnt);
			HAL_UART_Transmit(&huart6, (uint8_t*)str, strlen((char*)str), 50);
			//HAL_Delay(500);
			flag = 0u;
		}
		
		if ( flag_menu != 0u) {
			HAL_UART_Transmit(&huart6, (uint8_t*)"menu\r\n", 6, 50);
			flag_menu = 0u;
		}
		
		if ( flag_btn_encoder != 0u) {
			HAL_UART_Transmit(&huart6, (uint8_t*)"btn_enc\r\n", 9, 50);
			flag_btn_encoder = 0u;
		}
    */
		
		
  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Configure the main internal regulator output voltage
  */
  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE2);

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLM = 16;
  RCC_OscInitStruct.PLL.PLLN = 192;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV4;
  RCC_OscInitStruct.PLL.PLLQ = 4;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
  {
    Error_Handler();
  }
}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
