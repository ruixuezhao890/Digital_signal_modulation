/**
*********************************************************************
*********
* @project_name :templateDevelopment
* @file : MyKey.cpp
* @author : zen3
* @brief : None
* @attention : None
* @date : 2023/5/4 
*********************************************************************
*********
*/
//

#include "MyKey.h"
/***
 * 仅针对stm32f407
 * KeyLeft是PE2
 * KeyRight是PE4
 * KeyDown是PE3
 * KeyUp是PA0下拉
*/
MyKey::KEYS MyKey::ScanPressedKey(uint32_t timeout) {
    MyKey::KEYS keys = MyKey::KEY_NONE;
    uint32_t tickStart = HAL_GetTick();
    const uint32_t btnDelay = 20;
    GPIO_PinState keyState;
    while (1) {
#ifdef KeyUp_Pin
        keyState = HAL_GPIO_ReadPin(KeyUp_GPIO_Port, KeyUp_Pin);
            if (keyState == GPIO_PIN_SET) {
                HAL_Delay(btnDelay);
                keyState = HAL_GPIO_ReadPin(KeyUp_GPIO_Port, KeyUp_Pin);
                if (keyState == GPIO_PIN_SET) {
                    return KEY_UP;
                }
            }
#endif

#ifdef KeyRight_Pin
        keyState = HAL_GPIO_ReadPin(KeyRight_GPIO_Port, KeyRight_Pin);
        if (keyState == GPIO_PIN_RESET) {
            HAL_Delay(btnDelay);
            keyState = HAL_GPIO_ReadPin(KeyRight_GPIO_Port, KeyRight_Pin);
            if (keyState == GPIO_PIN_RESET) {
                return KEY_RIGHT;
            }
        }
#endif
#ifdef KeyDown_Pin
        keyState = HAL_GPIO_ReadPin(KeyDown_GPIO_Port, KeyDown_Pin);
        if (keyState == GPIO_PIN_RESET) {
            HAL_Delay(btnDelay);
            keyState = HAL_GPIO_ReadPin(KeyDown_GPIO_Port, KeyDown_Pin);
            if (keyState == GPIO_PIN_RESET) {
                return KEY_DOWN;
            }
        }
#endif
#ifdef KeyLeft_Pin
        keyState = HAL_GPIO_ReadPin(KeyLeft_GPIO_Port, KeyLeft_Pin);
        if (keyState == GPIO_PIN_RESET) {
            HAL_Delay(btnDelay);
            keyState = HAL_GPIO_ReadPin(KeyLeft_GPIO_Port, KeyLeft_Pin);
            if (keyState == GPIO_PIN_RESET) {
                return KEY_LEFT;
            }
        }
#endif
        if (timeout!=KEY_WAIT_ALWAYS){
            if ((HAL_GetTick()-tickStart)>timeout)
                break;

        }
    }
    return keys;
}
//传入等待时间
void  MyKey::KeyScan(uint32_t timeOut)
{
    MyUsart myUsart(&huart1);
    MyKey::KEYS curKey= ScanPressedKey(timeOut);
    switch (curKey) {
        case  MyKey::KEY_LEFT://填入对应所需要的数据

           myUsart.SendString("Left",4);
            break;
        case  MyKey::KEY_RIGHT:

            myUsart.SendString("right",4);
            break;
        case  MyKey::KEY_UP:
            this->flage++;
            myUsart.SendOneInt(flage);
            myUsart.SendString("up",4);
            break;
        case  MyKey::KEY_DOWN:
            this->flage--;
            myUsart.SendOneInt(flage);
            myUsart.SendString("down",4);
            break;
    }
    HAL_Delay(200);
}