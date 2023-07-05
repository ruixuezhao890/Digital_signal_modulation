/**
*********************************************************************
*********
* @project_name :templateDevelopment
* @file : MyKey.h
* @author : zen3
* @brief : None
* @attention : None
* @date : 2023/5/4 
*********************************************************************
*********
*/
//

#ifndef CPROJECT_MYKEY_H
#define CPROJECT_MYKEY_H
#ifdef __cplusplus
extern "C"
{
#endif
#include "Myapplication.h"
#include "MyUsart.h"
#define  KEY_WAIT_ALWAYS 0
/*______________________类的声明在这下面________________:*/
class MyKey{

public:

    typedef enum {
        KEY_NONE=0,
        KEY_LEFT,
        KEY_RIGHT,
        KEY_UP,
        KEY_DOWN
    }KEYS;
    uint16_t flage=0;
    KEYS ScanPressedKey(uint32_t timeout);
    void  KeyScan(uint32_t timeOut);
};
#ifdef __cplusplus
}
#endif
#endif //CPROJECT_MYKEY_H
