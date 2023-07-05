/**
*********************************************************************
*********
* @project_name :templateDevelopment
* @file : LED.cpp
* @author : zen3
* @brief : None
* @attention : None
* @date : 2023/4/27 
*********************************************************************
*********
*/
//

#include "LED.h"

void LED::LED_Flip() {
    HAL_GPIO_TogglePin(GPIOF,GPIO_PIN_9);
    HAL_GPIO_TogglePin(GPIOF,GPIO_PIN_10);
}