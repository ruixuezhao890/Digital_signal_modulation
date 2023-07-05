/**
*********************************************************************
*********
* @project_name :templateDevelopment
* @file : MyLCD.h
* @author : zen3
* @brief : None
* @attention : None
* @date : 2023/4/28 
*********************************************************************
*********
*/
//

#ifndef TEMPLATEDEVELOPMENT_MYLCD_H
#define TEMPLATEDEVELOPMENT_MYLCD_H
#ifdef __cplusplus
extern "C"
{
#endif
#include "Myapplication.h"
#include "IncludeALL.h"
#define SHOWINIT 360
#define GRID_SIZE 90
#define INTERVAL 15
/*______________________类的声明在这下面________________:*/
class MyLCD{
public:
    void MyLCDTouchInit();
    void MyLCDInit();
    void MyLCDDrawCoorDinat();
    void MyLDshowLable();
    void MyLCDLoadKeyBoard();
    char * MyLCDMonitorScreen(uint32_t timeout);
    char temp[20];
    char DisplayValue[20];
    int flag;
private:
    u8 t=0;
    u16 lastpos[5][2];
    int biaozhi=1;
    int i;
    int n=1;
};
#ifdef __cplusplus
}

#endif
#endif //TEMPLATEDEVELOPMENT_MYLCD_H
