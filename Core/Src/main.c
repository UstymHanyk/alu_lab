/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2022 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under Ultimate Liberty license
  * SLA0044, the "License"; You may not use this file except in compliance with
  * the License. You may obtain a copy of the License at:
  *                             www.st.com/SLA0044
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "i2c.h"
#include "i2s.h"
#include "spi.h"
#include "usb_host.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

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

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
void MX_USB_HOST_Process(void);

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
  MX_I2C1_Init();
  MX_I2S2_Init();
  MX_I2S3_Init();
  MX_SPI1_Init();
  MX_USB_HOST_Init();
  /* USER CODE BEGIN 2 */
//    uint16_t testPins[8] = {a1_Pin, a2_Pin, b1_Pin, b2_Pin,  op_Pin, r1_Pin, r2_Pin, Cout_Pin};
//    GPIO_TypeDef *testPorts[8] = {a1_GPIO_Port,a2_GPIO_Port,b1_GPIO_Port,b2_GPIO_Port,op_GPIO_Port, r1_GPIO_Port,r2_GPIO_Port, Cout_GPIO_Port};
      uint16_t testPins[8] = {a2_Pin, a1_Pin, b2_Pin, b1_Pin,  op_Pin, r2_Pin, r1_Pin, Cout_Pin};
      GPIO_TypeDef *testPorts[8] = {a2_GPIO_Port,a1_GPIO_Port,b2_GPIO_Port,b1_GPIO_Port,op_GPIO_Port, r2_GPIO_Port,r1_GPIO_Port, Cout_GPIO_Port};

    int tests[][9]={
    		// substraction
    		// a1_a2 - b1_b2 = r1_r1 cout: cout
    		{0,0,0,0,0,0,0,1},
    		{0,0,0,1,0,1,1,0},
    		{0,0,1,0,0,1,0,0},
    		{0,0,1,1,0,0,1,0},

    		{0,1,0,0,0,0,1,1},
    		{0,1,0,1,0,0,0,1},
    		{0,1,1,0,0,1,1,0},
    		{0,1,1,1,0,1,0,0},

    		{1,0,0,0,0,1,0,1},
    		{1,0,0,1,0,0,1,1},
    		{1,0,1,0,0,0,0,1},
    		{1,0,1,1,0,1,1,0},

    		{1,1,0,0,0,1,1,1},
    		{1,1,0,1,0,1,0,1},
    		{1,1,1,0,0,0,1,1},
    		{1,1,1,1,0,0,0,1},

//			// xor
			{0,0,0,0,1,0,0,1},
			{0,0,0,1,1,0,1,0},
			{0,0,1,0,1,1,0,0},
			{0,0,1,1,1,1,1,0},

			{0,1,0,0,1,0,1,1},
			{0,1,0,1,1,0,0,1},
			{0,1,1,0,1,1,1,0},
			{0,1,1,1,1,1,0,0},

			{1,0,0,0,1,1,0,1},
			{1,0,0,1,1,1,1,1},
			{1,0,1,0,1,0,0,1},
			{1,0,1,1,1,0,1,0},

			{1,1,0,0,1,1,1,1},
			{1,1,0,1,1,1,0,1},
			{1,1,1,0,1,0,1,1},
			{1,1,1,1,1,0,0,1},



    };

  	int failure =0;

    void setSuccessSign(){
    	HAL_GPIO_WritePin(LD3_GPIO_Port, LD3_Pin, 1);
    	HAL_GPIO_WritePin(LD6_GPIO_Port, LD6_Pin, 0);
    }
    void setFailureSign(){
    	HAL_GPIO_WritePin(LD3_GPIO_Port, LD3_Pin, 0);
    	HAL_GPIO_WritePin(LD6_GPIO_Port, LD6_Pin, 1);
//    	HAL_GPIO_TogglePin(LD6_GPIO_Port, LD6_Pin);

    }
    void Blink(){
    	HAL_GPIO_TogglePin(LD5_GPIO_Port, LD5_Pin);
    	HAL_Delay(80);
    	HAL_GPIO_TogglePin(LD5_GPIO_Port, LD5_Pin);
    }


    void checkIfEqual(int outputVal, int inputVal){
    	if(outputVal!= inputVal){
    		setFailureSign();
    		failure++;
    	}
    }


  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
	  failure=0;

	  	  for(int i=0; i <32;i++){
	  		  HAL_GPIO_WritePin(Cin_GPIO_Port, Cin_Pin, 1);  // carry-in always 1


	  		  for(int j=0;j<5;j++){
	  			  HAL_GPIO_WritePin(testPorts[j], testPins[j], tests[i][j]);
	  		  }
	  		  HAL_Delay(25);

	  		  for(int j=5; j<8;j++){
	  			  checkIfEqual(HAL_GPIO_ReadPin(testPorts[j],testPins[j]), tests[i][j]);
	  		  }

	  	  }
	  	  if (failure==0){
	  	  		  	setSuccessSign();
	  	  		}
	  	  Blink();
	  	 HAL_Delay(100);
    /* USER CODE END WHILE */
    MX_USB_HOST_Process();

    /* USER CODE BEGIN 3 */
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
  RCC_PeriphCLKInitTypeDef PeriphClkInitStruct = {0};

  /** Configure the main internal regulator output voltage
  */
  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);
  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLM = 4;
  RCC_OscInitStruct.PLL.PLLN = 192;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV4;
  RCC_OscInitStruct.PLL.PLLQ = 8;
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
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_3) != HAL_OK)
  {
    Error_Handler();
  }
  PeriphClkInitStruct.PeriphClockSelection = RCC_PERIPHCLK_I2S;
  PeriphClkInitStruct.PLLI2S.PLLI2SN = 200;
  PeriphClkInitStruct.PLLI2S.PLLI2SM = 5;
  PeriphClkInitStruct.PLLI2S.PLLI2SR = 2;
  if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInitStruct) != HAL_OK)
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

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
