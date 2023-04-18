/* USER CODE BEGIN Header */
/**
 ******************************************************************************
 * @file           : main.c
 * @brief          : Main program body
 ******************************************************************************
 * @attention
 *
 * Copyright (c) 2023 STMicroelectronics.
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

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "string.h"
#include <stdlib.h>
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
TIM_HandleTypeDef htim2;

UART_HandleTypeDef huart1;

/* USER CODE BEGIN PV */
char input = '0';
int percent = 0;
int entered = 0;
int sentenceTurn = 0;
char str1[1000];
char str2[1000];
int fiveSec = 0;
int wordEnterd = 0;
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_TIM2_Init(void);
static void MX_USART1_UART_Init(void);
/* USER CODE BEGIN PFP */
void decode(int num, int BCD[4]);
int compare(char *str1, char *str2);
/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/**
 * @brief  The application entry point.
 * @retval int
 */
int main(void) {
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
	MX_TIM2_Init();
	MX_USART1_UART_Init();
	/* USER CODE BEGIN 2 */
	HAL_TIM_Base_Start_IT(&htim2);
	HAL_UART_Receive_IT(&huart1, &input, sizeof(input));
	/* USER CODE END 2 */

	/* Infinite loop */
	/* USER CODE BEGIN WHILE */
	while (1) {
		/* USER CODE END WHILE */

		/* USER CODE BEGIN 3 */
	}
	/* USER CODE END 3 */
}

/**
 * @brief System Clock Configuration
 * @retval None
 */
void SystemClock_Config(void) {
	RCC_OscInitTypeDef RCC_OscInitStruct = { 0 };
	RCC_ClkInitTypeDef RCC_ClkInitStruct = { 0 };

	/** Initializes the RCC Oscillators according to the specified parameters
	 * in the RCC_OscInitTypeDef structure.
	 */
	RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
	RCC_OscInitStruct.HSIState = RCC_HSI_ON;
	RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
	RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
	RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI_DIV2;
	RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL12;
	if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK) {
		Error_Handler();
	}

	/** Initializes the CPU, AHB and APB buses clocks
	 */
	RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_SYSCLK
			| RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2;
	RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
	RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
	RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
	RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

	if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_1) != HAL_OK) {
		Error_Handler();
	}
}

/**
 * @brief TIM2 Initialization Function
 * @param None
 * @retval None
 */
static void MX_TIM2_Init(void) {

	/* USER CODE BEGIN TIM2_Init 0 */

	/* USER CODE END TIM2_Init 0 */

	TIM_ClockConfigTypeDef sClockSourceConfig = { 0 };
	TIM_MasterConfigTypeDef sMasterConfig = { 0 };

	/* USER CODE BEGIN TIM2_Init 1 */

	/* USER CODE END TIM2_Init 1 */
	htim2.Instance = TIM2;
	htim2.Init.Prescaler = 0;
	htim2.Init.CounterMode = TIM_COUNTERMODE_UP;
	htim2.Init.Period = 47999;
	htim2.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
	htim2.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
	if (HAL_TIM_Base_Init(&htim2) != HAL_OK) {
		Error_Handler();
	}
	sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
	if (HAL_TIM_ConfigClockSource(&htim2, &sClockSourceConfig) != HAL_OK) {
		Error_Handler();
	}
	sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
	sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
	if (HAL_TIMEx_MasterConfigSynchronization(&htim2, &sMasterConfig)
			!= HAL_OK) {
		Error_Handler();
	}
	/* USER CODE BEGIN TIM2_Init 2 */

	/* USER CODE END TIM2_Init 2 */

}

/**
 * @brief USART1 Initialization Function
 * @param None
 * @retval None
 */
static void MX_USART1_UART_Init(void) {

	/* USER CODE BEGIN USART1_Init 0 */

	/* USER CODE END USART1_Init 0 */

	/* USER CODE BEGIN USART1_Init 1 */

	/* USER CODE END USART1_Init 1 */
	huart1.Instance = USART1;
	huart1.Init.BaudRate = 9600;
	huart1.Init.WordLength = UART_WORDLENGTH_8B;
	huart1.Init.StopBits = UART_STOPBITS_1;
	huart1.Init.Parity = UART_PARITY_NONE;
	huart1.Init.Mode = UART_MODE_TX_RX;
	huart1.Init.HwFlowCtl = UART_HWCONTROL_NONE;
	huart1.Init.OverSampling = UART_OVERSAMPLING_16;
	if (HAL_UART_Init(&huart1) != HAL_OK) {
		Error_Handler();
	}
	/* USER CODE BEGIN USART1_Init 2 */

	/* USER CODE END USART1_Init 2 */

}

/**
 * @brief GPIO Initialization Function
 * @param None
 * @retval None
 */
static void MX_GPIO_Init(void) {
	GPIO_InitTypeDef GPIO_InitStruct = { 0 };

	/* GPIO Ports Clock Enable */
	__HAL_RCC_GPIOA_CLK_ENABLE();
	__HAL_RCC_GPIOB_CLK_ENABLE();

	/*Configure GPIO pin Output Level */
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_2,
			GPIO_PIN_RESET);

	/*Configure GPIO pin Output Level */
	HAL_GPIO_WritePin(GPIOB,
			GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_10 | GPIO_PIN_11 | GPIO_PIN_12
					| GPIO_PIN_13, GPIO_PIN_RESET);

	/*Configure GPIO pins : PA0 PA1 PA2 */
	GPIO_InitStruct.Pin = GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_2;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

	/*Configure GPIO pins : PB0 PB1 PB10 PB11
	 PB12 PB13 */
	GPIO_InitStruct.Pin = GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_10 | GPIO_PIN_11
			| GPIO_PIN_12 | GPIO_PIN_13;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

}

/* USER CODE BEGIN 4 */
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim) {
	static int counter = 0;
	static int bcd[4] = { 0 };
	//	GPIOB
	static uint16_t IC[4] = { GPIO_PIN_0, GPIO_PIN_1, GPIO_PIN_10, GPIO_PIN_11 };

	static int state = 0;

	static int fiveSecond = 5000;
	static int oneSec = 1000;

	static exLedFreq = 100;
	if (htim->Instance == TIM2) {
		if (counter == 100) {
			counter = 0;
			if (entered == 0) {
				HAL_GPIO_TogglePin(GPIOB, GPIO_PIN_12 | GPIO_PIN_13);
			}
		}

		int temp = percent;
		if (state == 0) {
			state++;
			HAL_GPIO_WritePin(GPIOA, GPIO_PIN_1 | GPIO_PIN_2, GPIO_PIN_SET);
			HAL_GPIO_WritePin(GPIOA, GPIO_PIN_0, GPIO_PIN_RESET);
			decode(percent / 100, bcd);
			for (int i = 0; i < 4; i++) {
				HAL_GPIO_WritePin(GPIOB, IC[i], bcd[i]);
			}
		} else if (state == 1) {
			state++;
			HAL_GPIO_WritePin(GPIOA, GPIO_PIN_0 | GPIO_PIN_2, GPIO_PIN_SET);
			HAL_GPIO_WritePin(GPIOA, GPIO_PIN_1, GPIO_PIN_RESET);
			decode((percent / 10) % 10, bcd);
			for (int i = 0; i < 4; i++) {
				HAL_GPIO_WritePin(GPIOB, IC[i], bcd[i]);
			}
		} else if (state == 2) {
			state = 0;
			HAL_GPIO_WritePin(GPIOA, GPIO_PIN_0 | GPIO_PIN_1, GPIO_PIN_SET);
			HAL_GPIO_WritePin(GPIOA, GPIO_PIN_2, GPIO_PIN_RESET);
			decode(percent % 10, bcd);
			for (int i = 0; i < 4; i++) {
				HAL_GPIO_WritePin(GPIOB, IC[i], bcd[i]);
			}
		}

		if (wordEnterd) {
			if (oneSec % exLedFreq == 0) {
				HAL_GPIO_TogglePin(GPIOB, GPIO_PIN_13);
			}
		} else if (fiveSec) {
			if (fiveSecond % exLedFreq == 0) {
				HAL_GPIO_TogglePin(GPIOB, GPIO_PIN_13);
			}
		} else if (entered) {
			HAL_GPIO_WritePin(GPIOB, GPIO_PIN_13, GPIO_PIN_RESET);
		}

		if (percent >= 60) {
			HAL_GPIO_WritePin(GPIOB, GPIO_PIN_12, GPIO_PIN_SET);
		} else if (entered && percent < 60) {
			HAL_GPIO_WritePin(GPIOB, GPIO_PIN_12, GPIO_PIN_RESET);
		}
		if (fiveSec) {
			fiveSecond--;
			if (fiveSecond == 0) {
				fiveSecond = 5000;
				fiveSec = 0;
			}

		} else if (wordEnterd) {
			oneSec--;
			if (oneSec == 0) {
				wordEnterd = 0;
				oneSec = 1000;
			}
		}
		counter++;

	}
}

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart) {
	static index = 0;
	static char str3[1000];
	static char str4[1000];
	if (huart->Instance == USART1) {
		if (entered == 0) {
			entered = 1;
		}
		if ((int) input == 32) {
			wordEnterd = 1;
			HAL_GPIO_WritePin(GPIOB, GPIO_PIN_13, GPIO_PIN_SET);
		}

		if ((int) input == 13) {
			sentenceTurn++;
			index = 0;
			fiveSec = 1;

		} else if (sentenceTurn == 0) {
			str1[index] = input;
			str1[index + 1] = '\0';
		} else if (sentenceTurn == 1) {
			str2[index] = input;
			str2[index + 1] = '\0';
		}

		if (sentenceTurn == 2) {
//			if (!strcmp(str1, str2)){
//				HAL_GPIO_WritePin(GPIOB, GPIO_PIN_12, GPIO_PIN_SET);
			strcpy(str3, str1);
			strcpy(str4, str2);
				percent = compare(str3, str4);
//			}
		}
		HAL_UART_Receive_IT(&huart1, &input, sizeof(input));
	}
}

void decode(int num, int BCD[4]) {
	switch (num) {
	case 0:
		BCD[3] = 0;
		BCD[2] = 0;
		BCD[1] = 0;
		BCD[0] = 0;
		break;
	case 1:
		BCD[3] = 0;
		BCD[2] = 0;
		BCD[1] = 0;
		BCD[0] = 1;
		break;
	case 2:
		BCD[3] = 0;
		BCD[2] = 0;
		BCD[1] = 1;
		BCD[0] = 0;
		break;
	case 3:
		BCD[3] = 0;
		BCD[2] = 0;
		BCD[1] = 1;
		BCD[0] = 1;
		break;
	case 4:
		BCD[3] = 0;
		BCD[2] = 1;
		BCD[1] = 0;
		BCD[0] = 0;
		break;
	case 5:
		BCD[3] = 0;
		BCD[2] = 1;
		BCD[1] = 0;
		BCD[0] = 1;
		break;
	case 6:
		BCD[3] = 0;
		BCD[2] = 1;
		BCD[1] = 1;
		BCD[0] = 0;
		break;
	case 7:
		BCD[3] = 0;
		BCD[2] = 1;
		BCD[1] = 1;
		BCD[0] = 1;
		break;
	case 8:
		BCD[3] = 1;
		BCD[2] = 0;
		BCD[1] = 0;
		BCD[0] = 0;
		break;
	case 9:
		BCD[3] = 1;
		BCD[2] = 0;
		BCD[1] = 0;
		BCD[0] = 1;
		break;
	default:
		break;
	}
}


int compare(char *str1, char *str2) {
    int str1_length = strlen(str1);
    int str2_length = strlen(str2);
    char *words1[200];
    char *words2[200];
    char *word;
    int i, j, count1 = 0, count2 = 0, similar1 = 0;
    float similar_words = 0;
    // Split string1 into words
    word = strtok(str1, " \n");
    while (word != NULL && count1 < 200) {
        words1[count1++] = word;
        word = strtok(NULL, " \n");
    }

    // Split string2 into words
    word = strtok(str2, " \n");
    while (word != NULL && count2 < 200) {
        words2[count2++] = word;
        word = strtok(NULL, " \n");
    }
    
    long int index_1 = 0;
    long int index_2 = 0;
    // Compare the words in both strings
    for (i = 0; i < count1; i++) {
        index_2 = 0;
        for (j = 0; j < count2; j++) {
            if (strcmp(words1[i], words2[j]) == 0) {
                similar_words += 1.0 - abs(index_2 - index_1) / ((str1_length + str2_length) / 2.0);
                break;
            }
            index_2 += strlen(words2[j]);
        }
        index_1 += strlen(words1[i]);
    }
    // for (i = 0; i < count1; i++){
    // 	if(strstr(str2, words1[i]) != NULL){
    // 		similar1++;
    // 	}
    // }
    // hello new world
    // world counter hi hello

    // Calculate similarity percentage
    if (count1 == 0 || count2 == 0) {
        return 0;
    } else {
        float similarity = (similar_words * 100.0) / ((count1 + count2) / 2.0);
        return (int)similarity;
    }
}

/* USER CODE END 4 */

/**
 * @brief  This function is executed in case of error occurrence.
 * @retval None
 */
void Error_Handler(void) {
	/* USER CODE BEGIN Error_Handler_Debug */
	/* User can add his own implementation to report the HAL error return state */
	__disable_irq();
	while (1) {
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
