/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * File Name          : freertos.c
  * Description        : Code for freertos applications
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2022 STMicroelectronics.
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
#include "FreeRTOS.h"
#include "task.h"
#include "main.h"
#include "cmsis_os.h"

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
/* USER CODE BEGIN Variables */

/* USER CODE END Variables */
osThreadId defaultTaskHandle;
osThreadId BlinkHandle;
osThreadId COMHandle;
osThreadId TM1638Handle;
osThreadId DebugHandle;

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN FunctionPrototypes */

/* USER CODE END FunctionPrototypes */

void StartDefaultTask(void const * argument);
void Start_Blink(void const * argument);
void Start_COM(void const * argument);
void Start_TM1638(void const * argument);
void Start_Debug(void const * argument);

void MX_FREERTOS_Init(void); /* (MISRA C 2004 rule 8.1) */

/* GetIdleTaskMemory prototype (linked to static allocation support) */
void vApplicationGetIdleTaskMemory( StaticTask_t **ppxIdleTaskTCBBuffer, StackType_t **ppxIdleTaskStackBuffer, uint32_t *pulIdleTaskStackSize );

/* USER CODE BEGIN GET_IDLE_TASK_MEMORY */
static StaticTask_t xIdleTaskTCBBuffer;
static StackType_t xIdleStack[configMINIMAL_STACK_SIZE];

void vApplicationGetIdleTaskMemory( StaticTask_t **ppxIdleTaskTCBBuffer, StackType_t **ppxIdleTaskStackBuffer, uint32_t *pulIdleTaskStackSize )
{
  *ppxIdleTaskTCBBuffer = &xIdleTaskTCBBuffer;
  *ppxIdleTaskStackBuffer = &xIdleStack[0];
  *pulIdleTaskStackSize = configMINIMAL_STACK_SIZE;
  /* place for user code */
}
/* USER CODE END GET_IDLE_TASK_MEMORY */

/**
  * @brief  FreeRTOS initialization
  * @param  None
  * @retval None
  */
void MX_FREERTOS_Init(void) {
  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* USER CODE BEGIN RTOS_MUTEX */
  /* add mutexes, ... */
  /* USER CODE END RTOS_MUTEX */

  /* USER CODE BEGIN RTOS_SEMAPHORES */
  /* add semaphores, ... */
  /* USER CODE END RTOS_SEMAPHORES */

  /* USER CODE BEGIN RTOS_TIMERS */
  /* start timers, add new ones, ... */
  /* USER CODE END RTOS_TIMERS */

  /* USER CODE BEGIN RTOS_QUEUES */
  /* add queues, ... */
  /* USER CODE END RTOS_QUEUES */

  /* Create the thread(s) */
  /* definition and creation of defaultTask */
  osThreadDef(defaultTask, StartDefaultTask, osPriorityNormal, 0, 128);
  defaultTaskHandle = osThreadCreate(osThread(defaultTask), NULL);

  /* definition and creation of Blink */
  osThreadDef(Blink, Start_Blink, osPriorityNormal, 0, 128);
  BlinkHandle = osThreadCreate(osThread(Blink), NULL);

  /* definition and creation of COM */
  osThreadDef(COM, Start_COM, osPriorityNormal, 0, 128);
  COMHandle = osThreadCreate(osThread(COM), NULL);

  /* definition and creation of TM1638 */
  osThreadDef(TM1638, Start_TM1638, osPriorityNormal, 0, 128);
  TM1638Handle = osThreadCreate(osThread(TM1638), NULL);

  /* definition and creation of Debug */
  osThreadDef(Debug, Start_Debug, osPriorityHigh, 0, 128);
  DebugHandle = osThreadCreate(osThread(Debug), NULL);

  /* USER CODE BEGIN RTOS_THREADS */
  /* add threads, ... */
  /* USER CODE END RTOS_THREADS */

}

/* USER CODE BEGIN Header_StartDefaultTask */
/**
  * @brief  Function implementing the defaultTask thread.
  * @param  argument: Not used
  * @retval None
  */
/* USER CODE END Header_StartDefaultTask */
void StartDefaultTask(void const * argument)
{
  /* USER CODE BEGIN StartDefaultTask */
  F103_BEEP(ON);
  osDelay(200);
  F103_BEEP(OFF);
  /* Infinite loop */
  for(;;)
  {
    osDelay(1);
  }
  /* USER CODE END StartDefaultTask */
}

/* USER CODE BEGIN Header_Start_Blink */
/**
* @brief Function implementing the Blink thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_Start_Blink */
void Start_Blink(void const * argument)
{
  /* USER CODE BEGIN Start_Blink */
  osDelay(1000);
  /* Infinite loop */
  for(;;)
  {
    F103_LED(LED_COLOR_GREEN, ON);
    osDelay(150);
    F103_LED(LED_COLOR_GREEN, OFF);
    osDelay(850);
  }
  /* USER CODE END Start_Blink */
}

/* USER CODE BEGIN Header_Start_COM */
/**
* @brief Function implementing the COM thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_Start_COM */
void Start_COM(void const * argument)
{
  /* USER CODE BEGIN Start_COM */
  osDelay(1000);
  uint32_t nCount = 0;
  /* Infinite loop */
  for(;;)
  {
    //用于测试微秒级延时函数
    printf("Hanris: %d\r\n", nCount++);
    osDelay(1000);
    printf("Hanris: %d\r\n", nCount++);
    for(int n=0; n!=1000; n++)
      Delay_us(1000);
  }
  /* USER CODE END Start_COM */
}

/* USER CODE BEGIN Header_Start_TM1638 */
/**
* @brief Function implementing the TM1638 thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_Start_TM1638 */
void Start_TM1638(void const * argument)
{
  /* USER CODE BEGIN Start_TM1638 */
  osDelay(500);
  TM1638_Init();
  /* Infinite loop */
  for(;;)
  {
    osDelay(1);
  }
  /* USER CODE END Start_TM1638 */
}

/* USER CODE BEGIN Header_Start_Debug */
/**
* @brief Function implementing the Debug thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_Start_Debug */
void Start_Debug(void const * argument)
{
  /* USER CODE BEGIN Start_Debug */
  osDelay(1000);
  /* Infinite loop */
  for(;;)
  {
    YMX_Flowmeter = {0};  //初始化
    Flow_UI_Setting(0);   //
    osDelay(1);
  }
  /* USER CODE END Start_Debug */
}

/* Private application code --------------------------------------------------*/
/* USER CODE BEGIN Application */

/* USER CODE END Application */

