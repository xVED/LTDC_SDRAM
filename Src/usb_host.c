/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file            : usb_host.c
  * @version         : v1.0_Cube
  * @brief           : This file implements the USB Host
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2020 STMicroelectronics.
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

#include "usb_host.h"
#include "usbh_core.h"
#include "usbh_video.h"
/* USB Host Core handle declaration */
USBH_HandleTypeDef hUsbHostFS;
ApplicationTypeDef Appli_state = APPLICATION_IDLE;

/**
* -- Insert your variables declaration here --
*/
/* USER CODE BEGIN 0 */
void USB_HOST_fast_class_call(void)
{
  if (hUsbHostFS.gState == HOST_CLASS)
  {
    USBH_VIDEO_Process(&hUsbHostFS);
  }
}
/* USER CODE END 0 */

/*
* user callbak declaration
*/
static void USBH_UserProcess  (USBH_HandleTypeDef *phost, uint8_t id);

/**
* -- Insert your external function declaration here --
*/
/* USER CODE BEGIN 1 */

/* USER CODE END 1 */

/* init function */
void MX_USB_HOST_Init(void)
{
  /* Init Host Library,Add Supported Class and Start the library*/
  USBH_Init(&hUsbHostFS, USBH_UserProcess, HOST_FS);

  USBH_RegisterClass(&hUsbHostFS, USBH_VIDEO_CLASS);

  USBH_Start(&hUsbHostFS);
}

/*
 * Background task
*/
void MX_USB_HOST_Process(void)
{
  /* USB Host Background task */
    USBH_Process(&hUsbHostFS);
}
/*
 * user callbak definition
*/
static void USBH_UserProcess  (USBH_HandleTypeDef *phost, uint8_t id)
{

  /* USER CODE BEGIN 2 */
  switch(id)
  {

  case HOST_USER_CLASS_SELECTED:
    {
      USBH_StatusTypeDef status;
      status = USBH_VS_SetCur(phost, VS_PROBE_CONTROL << 8);
      status = USBH_VS_GetCur(phost, VS_PROBE_CONTROL << 8);
      if (status == USBH_OK)
      {
        USBH_VS_SetCur(phost, VS_COMMIT_CONTROL << 8);
        //USBH_VS_GetCur(phost, VS_COMMIT_CONTROL << 8);// not necessary
      }
    }
    break;

  case HOST_USER_SELECT_CONFIGURATION:
    break;

  case HOST_USER_DISCONNECTION:
    Appli_state = APPLICATION_DISCONNECT;
    break;

  case HOST_USER_CLASS_ACTIVE:
    Appli_state = APPLICATION_READY;
    break;

  case HOST_USER_CONNECTION:
    Appli_state = APPLICATION_START;
    break;

  default:
    break;
  }
  /* USER CODE END 2 */
}

/**
  * @}
  */

/**
  * @}
  */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
