/**
*********************************************************************
*********
* @project_name :templateDevelopment
* @file : MyLCD.cpp
* @author : zen3
* @brief : None
* @attention : None
* @date : 2023/4/28 
*********************************************************************
*********
*/
//

#include "MyLCD.h"
#include "Myapplication.h"
#include "MyUsart.h"
#include "string"


MyUsart myUsart(&huart1);


void MyLCD::MyLCDInit() {

    lcd_init();
    tp_dev.init();
    lcd_display_dir(1);


}
void MyLCD::MyLCDDrawCoorDinat() {
    lcd_draw_line(287, 0, 287, 230, RED);
    lcd_draw_line(287, 230, 800, 230, RED);
//    lcd_draw_line(5, 470, 800, 470, RED);
//    lcd_draw_line(5, 460, 5, 280, RED);

}
void MyLCD::MyLDshowLable() {

    lcd_show_string(5, 8, 200, 16, 16, "My_project:", GREEN);
    lcd_show_string(5, 28, 200, 16, 16, "div/(mv)", GRAY);
    lcd_show_string(5, 48, 200, 16, 16, "max(mv):", GRAY);
    lcd_show_string(5, 68, 200, 16, 16, "min(mv):", GRAY);
    lcd_show_string(5, 88, 200, 16, 16, "vpp(mv):", GRAY);
    lcd_show_string(5, 108, 200, 16, 16, "f(Hz):", GRAY);
    lcd_show_string(5, 128, 200, 16, 16, "WAVE:", GRAY);  //采样率
    lcd_show_string(5, 148, 200, 16, 16, "Hz:", GRAY);
    lcd_show_string(5,168,200,16,16,"Pha",GRAY);
    lcd_show_string(100, 13, 200, 16, 16, "IN:PA6", BRRED);
    lcd_show_string(5, 230, 200, 16, 16, "0V", RED);
    //lcd_show_xnum(5, 28, 12345, 5, 16, 1, BLUE);



}

void MyLCD::MyLCDLoadKeyBoard() {
    //lcd_clear(WHITE);
    uint16_t ADD=20;
    lcd_show_xnum(30+ADD,480+ADD,1,1,24,0,BLACK);
    lcd_show_xnum(150+ADD,480+ADD,2,1,24,0,BLACK);
    lcd_show_xnum(270+ADD,480+ADD,3,1,24,0,BLACK);
    lcd_show_string(390+ADD,480+ADD,200,24,24,"RET",RED);//清空
    lcd_show_xnum(30+ADD,560+ADD,4,1,24,0,BLACK);
    lcd_show_xnum(150+ADD,560+ADD,5,1,24,0,BLACK);
    lcd_show_xnum(270+ADD,560+ADD,6,1,24,0,BLACK);
    lcd_show_xnum(30+ADD,640+ADD,7,1,24,0,BLACK);
    lcd_show_xnum(150+ADD,640+ADD,8,1,24,0,BLACK);
    lcd_show_xnum(270+ADD,640+ADD,9,1,24,0,BLACK);
    lcd_show_string(380+ADD,640+ADD,200,24,24,"Enter",RED);//确认
    lcd_show_string(390+ADD,720+ADD,200,24,24,"DEL",RED);//退格
    lcd_show_string(390+ADD,560+ADD,1,24,24,".",RED);
    lcd_show_xnum(150+ADD,720+ADD,0,1,24,0,BLACK);
    lcd_show_string(30+ADD,720+ADD,1,24,24,"-",RED);
    lcd_show_string(270+ADD,720+ADD,1,24,24,"+",RED);
    lcd_draw_rectangle(100,360,400,420,RED);
    //化线
    lcd_draw_line(0,480,480,480,RED);
    lcd_draw_line(0,560,480,560,RED);
    lcd_draw_line(0,640,480,640,RED);
    lcd_draw_line(0,720,480,720,RED);
    //lcd_draw_line(0,480,400,480,RED);
    lcd_draw_line(120,480,120,800,RED);
    lcd_draw_line(240,480,240,800,RED);
    lcd_draw_line(360,480,360,800,RED);
}

/*void MyLCD::MyLCDMonitorScreen() {

    tp_dev.scan(0); //扫描触摸屏.0,屏幕扫描;1,物理坐标;

    if (tp_dev.sta & TP_PRES_DOWN)         //触摸屏被按下
    {
        //myUsart.SendString("hello",5);
        if (tp_dev.x[0] < lcddev.width && tp_dev.y[0] < lcddev.height) {
//            myUsart.SendString("x",1);
//            myUsart.SendOneInt(tp_dev.x[0]);
//            myUsart.SendString("y",1);
//            myUsart.SendOneInt(tp_dev.y[0]);
            if (tp_dev.x[0] > 0 && tp_dev.x[0] < 100) {
                if (tp_dev.y[0] > 480 && tp_dev.y[0] < 560) {
                    DisplayValue+= '1';

                } else if (tp_dev.x[0] > 560 && tp_dev.x[0] < 640) {
                    DisplayValue += '4';
                } else if (tp_dev.x[0] > 640 && tp_dev.x[0] < 720) {
                    DisplayValue += '7';
                }
                //else if(tp_dev.y[0]>280&&tp_dev.y[0]<320){}
            } else if (tp_dev.x[0] > 100 && tp_dev.x[0] < 200) {
                if (tp_dev.y[0] > 480 && tp_dev.y[0] < 560) {
                    DisplayValue += '2';
                } else if (tp_dev.y[0] > 560 && tp_dev.y[0] < 640) {
                    DisplayValue += '5';
                } else if (tp_dev.y[0] > 640 && tp_dev.y[0] < 720) {
                    DisplayValue += '8';
                } else if (tp_dev.y[0] > 720 && tp_dev.y[0] < 800) {
                    DisplayValue += '0';
                }
            } else if (tp_dev.x[0] > 200 && tp_dev.x[0] < 300) {
                if (tp_dev.y[0] > 480 && tp_dev.y[0] < 560) {
                    DisplayValue += '3';
                } else if (tp_dev.y[0] > 560 && tp_dev.y[0] < 640) {
                    DisplayValue += '6';
                } else if (tp_dev.y[0] > 640 && tp_dev.y[0] < 720) {
                    DisplayValue += '9';
                }
                //else if(tp_dev.y[0]>280&&tp_dev.y[0]<320){}
            } else if (tp_dev.x[0] > 300 && tp_dev.x[0] < 400) {
//                if(tp_dev.y[0]>160&&tp_dev.y[0]<200){      digital=11;
//                }else if(tp_dev.y[0]>200&&tp_dev.y[0]<240){digital=12;
//                }else if(tp_dev.y[0]>240&&tp_dev.y[0]<280){digital=13;
//                }else if(tp_dev.y[0]>280&&tp_dev.y[0]<320){digital=14;
//                }
            }
        }
        const char* cstr=DisplayValue.c_str();

        myUsart.SendString(cstr,20);
    }
}*/
/*void MyLCD::MyLCDLoadKeyBoard()
{
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            int x=j*GRID_SIZE+(j+1)*INTERVAL;
            int y=i*GRID_SIZE+(i+1)*INTERVAL;
            lcd_draw_rectangle(x,y+SHOWINIT,x+GRID_SIZE,y+SHOWINIT+GRID_SIZE,RED);
            lcd_show_string(x,y+SHOWINIT,120,24,24,ShowMap[i][j],BLACK);
        }
    }
}*/
/*void MyLCD:: py_key_staset(u16 x,u16 y,u8 keyx,u8 sta)
{
    u16 i=keyx/4,j=keyx%4;
    if(keyx>16)return;
    if(sta)lcd_fill(x+j*120,y+i*80,x+j*120+120,y+i*80+80,GREEN);
    else lcd_fill(x+j*120,y+i*80,x+j*120+120,y+i*80+80,WHITE);
    //POINT_COLOR=BLACK;
//	Show_Str(x+51,y+38,lcddev.width,lcddev.height,"灯:",24,0);
//	//LCD_ShowString(x+51,y+38,lcddev.width,lcddev.height,24,"LED1");
//	LCD_ShowString(x+201,y+38,lcddev.width,lcddev.height,24,"LED2");
//	LCD_ShowString(x+39,y+138,lcddev.width,lcddev.height,24,"LED_ON");
//	LCD_ShowString(x+183,y+138,lcddev.width,lcddev.height,24,"LED_OFF");
}*/
/*u16 MyLCD::py_get_keynum(u16 x,u16 y)
{

    u16 i,j;
    static u8 key_x=0;//0,没有任何按键按下；1~4，1~4号按键按下
    u16 key=0;
    tp_dev.scan(0);
    if(tp_dev.sta&TP_PRES_DOWN)			//触摸屏被按下
    {
        for(i=0;i<4;i++)
        {
            for(j=0;j<4;j++)
            {
                if(tp_dev.x[0]<(x+j*120+120)&&tp_dev.x[0]>(x+j*120)&&tp_dev.y[0]<(y+i*80+80)&&tp_dev.y[0]>(y+i*80))
                {
                    key=i*4+j+1;
                    break;
                }
            }
            if(key)
            {
                if(key_x==key)key=0;
                else
                {
                    py_key_staset(x,y,key_x-1,0);
                    key_x=key;
                    py_key_staset(x,y,key_x-1,1);
                    this->MyLCDLoadKeyBoard();
                    myUsart.SendOneInt(key);
                }
                break;
            }
        }
    }
    //如果要记录按下后的状态 这句话需要被注释掉
	else if(key_x)
	{
		py_key_staset(x,y,key_x-1,0);
		key_x=0;
        this->MyLCDLoadKeyBoard();
	}
    return key;
}*/

void MyLCD::MyLCDTouchInit() {
    lcd_init();
    tp_dev.init();
}

int y=380;
char * MyLCD::MyLCDMonitorScreen(uint32_t timeout) {
    DisplayValue[0] = ' ';
    uint32_t tickStart = HAL_GetTick();
    while (1) {
        tp_dev.scan(0);

        if ((tp_dev.sta) & (1 << t)) {
            if (tp_dev.x[t] < lcddev.width && tp_dev.y[t] < lcddev.height) {
                if (lastpos[t][0] == 0XFFFF) {
                    lastpos[t][0] = tp_dev.x[t];
                    lastpos[t][1] = tp_dev.y[t];
                }
//					lcd_draw_bline(lastpos[t][0],lastpos[t][1],tp_dev.x[t],tp_dev.y[t],2,POINT_COLOR_TBL[t]);//画线
                lastpos[t][0] = tp_dev.x[t];
                lastpos[t][1] = tp_dev.y[t];

                //键盘扫描部分
                if (tp_dev.x[t] > (lcddev.width - 120) && tp_dev.y[t] > 480 && tp_dev.y[t] < 560)  //如果右上角RST被按下，清除
                {
                    biaozhi = 1;
                    for (i = 0; i < 20; i++) {
                        DisplayValue[i] = ' ';
                    }
                    n = 1;
                    DisplayValue[0] = ' ';
                    lcd_fill(105,365,300,400,WHITE);
                    lcd_show_string(100, y, 240, 24, 24, DisplayValue, RED);
                }
                if (tp_dev.x[t] > 0 && tp_dev.x[t] < 120 && tp_dev.y[t] > 480 && tp_dev.y[t] < 560)  //如果按下1
                {
                    while (tp_dev.x[t] > 0 && tp_dev.x[t] < 120 && tp_dev.y[t] > 480 && tp_dev.y[t] < 560) {
                        tp_dev.scan(0);
                    }
                    DisplayValue[n] = '1';
                    n++;
                    lcd_show_string(100, y, 240, 24, 24, DisplayValue, RED);
                    myUsart.SendOneInt(n);
                    myUsart.SendString(DisplayValue, 20);
                }
                if (tp_dev.x[t] > 120 && tp_dev.x[t] < 240 && tp_dev.y[t] > 480 && tp_dev.y[t] < 560)  //如果按下2
                {
                    while (tp_dev.x[t] > 120 && tp_dev.x[t] < 240 && tp_dev.y[t] > 480 && tp_dev.y[t] < 560) {
                        tp_dev.scan(0);
                    }
                    DisplayValue[n] = '2';
                    n++;
                    lcd_show_string(100, y, 240, 24, 24, DisplayValue, RED);
                    myUsart.SendOneInt(n);
                    myUsart.SendString(DisplayValue, 20);
                }
                if (tp_dev.x[t] > 240 && tp_dev.x[t] < 360 && tp_dev.y[t] > 480 && tp_dev.y[t] < 560)  //如果按下3
                {
                    while (tp_dev.x[t] > 240 && tp_dev.x[t] < 360 && tp_dev.y[t] > 480 && tp_dev.y[t] < 560) {
                        tp_dev.scan(0);
                    }
                    DisplayValue[n] = '3';
                    n++;
                    lcd_show_string(100, y, 240, 24, 24, DisplayValue, RED);
                    myUsart.SendOneInt(n);
                    myUsart.SendString(DisplayValue, 20);
                }
                if (tp_dev.x[t] > 0 && tp_dev.x[t] < 120 && tp_dev.y[t] > 560 && tp_dev.y[t] < 640)  //如果按下4
                {
                    while (tp_dev.x[t] > 0 && tp_dev.x[t] < 120 && tp_dev.y[t] > 560 && tp_dev.y[t] < 640) {
                        tp_dev.scan(0);
                    }
                    DisplayValue[n] = '4';
                    n++;
                    lcd_show_string(100, y, 240, 24, 24, DisplayValue, RED);
                    myUsart.SendOneInt(n);
                    myUsart.SendString(DisplayValue, 20);
                }
                if (tp_dev.x[t] > 120 && tp_dev.x[t] < 240 && tp_dev.y[t] > 560 && tp_dev.y[t] < 640)  //如果按下5
                {
                    while (tp_dev.x[t] > 120 && tp_dev.x[t] < 240 && tp_dev.y[t] > 560 && tp_dev.y[t] < 640) {
                        tp_dev.scan(0);
                    }
                    DisplayValue[n] = '5';
                    n++;
                    lcd_show_string(100, y, 240, 24, 24, DisplayValue, RED);
                }
                if (tp_dev.x[t] > 240 && tp_dev.x[t] < 360 && tp_dev.y[t] > 560 && tp_dev.y[t] < 640)  //如果按下6
                {
                    while (tp_dev.x[t] > 240 && tp_dev.x[t] < 360 && tp_dev.y[t] > 560 && tp_dev.y[t] < 640) {
                        tp_dev.scan(0);
                    }
                    DisplayValue[n] = '6';
                    n++;
                    lcd_show_string(100, y, 240, 24, 24, DisplayValue, RED);
                }
                if (tp_dev.x[t] > 0 && tp_dev.x[t] < 120 && tp_dev.y[t] > 640 && tp_dev.y[t] < 720)  //如果按下7
                {
                    while (tp_dev.x[t] > 0 && tp_dev.x[t] < 120 && tp_dev.y[t] > 640 && tp_dev.y[t] < 720) {
                        tp_dev.scan(0);
                    }
                    DisplayValue[n] = '7';
                    n++;
                    lcd_show_string(100, y, 240, 24, 24, DisplayValue, RED);
                }
                if (tp_dev.x[t] > 120 && tp_dev.x[t] < 240 && tp_dev.y[t] > 640 && tp_dev.y[t] < 720)  //如果按下8
                {
                    while (tp_dev.x[t] > 120 && tp_dev.x[t] < 240 && tp_dev.y[t] > 640 && tp_dev.y[t] < 720) {
                        tp_dev.scan(0);
                    }
                    DisplayValue[n] = '8';
                    n++;
                    lcd_show_string(100, y, 240, 24, 24, DisplayValue, RED);
                }
                if (tp_dev.x[t] > 240 && tp_dev.x[t] < 360 && tp_dev.y[t] > 640 && tp_dev.y[t] < 720)  //如果按下9
                {
                    while (tp_dev.x[t] > 240 && tp_dev.x[t] < 360 && tp_dev.y[t] > 640 && tp_dev.y[t] < 720) {
                        tp_dev.scan(0);
                    }
                    DisplayValue[n] = '9';
                    n++;
                    lcd_show_string(100, y, 240, 24, 24, DisplayValue, RED);
                }
                if (tp_dev.x[t] > 120 && tp_dev.x[t] < 240 && tp_dev.y[t] > 720 && tp_dev.y[t] < 800)  //如果按下0
                {
                    while (tp_dev.x[t] > 120 && tp_dev.x[t] < 240 && tp_dev.y[t] > 720 && tp_dev.y[t] < 800) {
                        tp_dev.scan(0);
                    }
                    DisplayValue[n] = '0';
                    n++;
                    lcd_show_string(100, y, 240, 24, 24, DisplayValue, RED);
                }
                if (tp_dev.x[t] > 360 && tp_dev.x[t] < 480 && tp_dev.y[t] > 560 && tp_dev.y[t] < 640) //如果按下.
                {
                    while (tp_dev.x[t] > 360 && tp_dev.x[t] < 480 && tp_dev.y[t] > 560 && tp_dev.y[t] < 640) {
                        tp_dev.scan(0);
                    }
                    if (biaozhi == 1)               //小数点防重复程序
                    {
                        DisplayValue[n] = '.';
                        n++;
                        biaozhi++;
                    }
                    lcd_show_string(100, y, 240, 24, 24, DisplayValue, RED);
                }
                if (tp_dev.x[t] > 240 && tp_dev.x[t] < 360 && tp_dev.y[t] > 720 && tp_dev.y[t] < 800)//+
                {
                    while (tp_dev.x[t] > 240 && tp_dev.x[t] < 360 && tp_dev.y[t] > 720 && tp_dev.y[t] < 800) {
                        tp_dev.scan(0);
                    }
                    DisplayValue[2] = '+';
                    for (int j = 0; j < 20; ++j) {
                        temp[j]=DisplayValue[j];
                    }
                    for (i = 0; i < 20; i++)        //清空数组
                    {
                        DisplayValue[i] = ' ';
                        n = 1;
                        biaozhi = 1;
                    }
                    lcd_fill(105,365,300,400,WHITE);
                    lcd_show_string(100, y, 240, 24, 24, temp, RED);
                    return temp;
                }
                if (tp_dev.x[t] > 0 && tp_dev.x[t] < 120 && tp_dev.y[t] > 720 && tp_dev.y[t] < 800)//-
                {
                    while (tp_dev.x[t] > 0 && tp_dev.x[t] < 120 && tp_dev.y[t] > 720 && tp_dev.y[t] < 800) {
                        tp_dev.scan(0);
                    }
                    DisplayValue[1] = '-';
                    for (int j = 0; j < 20; ++j) {
                        temp[j]=DisplayValue[j];
                    }
                    for (i = 0; i < 20; i++)        //清空数组
                    {
                        DisplayValue[i] = ' ';
                        n = 1;
                        biaozhi = 1;
                    }
                    lcd_fill(105,365,300,400,WHITE);
                    lcd_show_string(100, y, 240, 24, 24, temp, RED);
                    return temp;
                }
                if (tp_dev.x[t] > (lcddev.width - 120) && tp_dev.y[t] > 640 && tp_dev.y[t] < 720)  //如果按下OK
                {
                    while (tp_dev.x[t] > (lcddev.width - 120) && tp_dev.y[t] > 640 && tp_dev.y[t] < 720) {
                        tp_dev.scan(0);
                    }
                    // this->flag = 0;

                    for (int j = 0; j < 20; ++j) {
                        temp[j]=DisplayValue[j];
                    }
                    for (i = 0; i < 20; i++)        //清空数组
                    {
                        DisplayValue[i] = ' ';
                        n = 1;
                        biaozhi = 1;
                    }
                    myUsart.SendString(temp, 20);
                    //myUsart.SendString(GetChar, 20);
                    lcd_fill(105,365,300,400,WHITE);
                    lcd_show_string(100, y, 240, 24, 24, DisplayValue, RED);
                    return temp;
//                UART_Send_Str(DisplayValue);      //发送数据到串口上
//                printf("\r\n\r");            //换行

                }
                if (tp_dev.x[t] > 360 && tp_dev.x[t] < 480 && tp_dev.y[t] > 720 &&
                    tp_dev.y[t] < 800)  //如果按下NO  删除部分
                {
                    while (tp_dev.x[t] > 360 && tp_dev.x[t] < 480 && tp_dev.y[t] > 720 && tp_dev.y[t] < 800) {
                        tp_dev.scan(0);
                    }
                    if (DisplayValue[n - 1] == '.')      //小数点删除特殊情况，还原标志位
                    { biaozhi = 1; }
                    DisplayValue[n - 1] = ' ';
                    n--;
                    if (n == 0)
                        n = 1;

                    lcd_fill(105,365,300,400,WHITE);
                    lcd_show_string(100, y, 240, 24, 24, DisplayValue, RED);
                }

//如果输入超过长度程序部分
                if (n >= 20) {
                    for (i = 0; i < 20; i++)        //清空数组
                    {
                        DisplayValue[i] = ' ';
                        n = 1;
                    }
                    lcd_fill(100,360,400,420, WHITE);
                    lcd_draw_rectangle(100,360,400,420,RED);
                    lcd_show_string(100, y, 240, 24, 24, DisplayValue, RED);
                    lcd_show_string(100, y, 240, 24, 24, "Exceed the limit length", RED);
                    HAL_Delay(1000);
                    lcd_fill(105,365,300,400,WHITE);
                    //size3=101;
//                for(i=10;i<22;i++)      //显示汉字超过有效长度，请重新输入
//                {
//                    //Show_Chinese32(size3,500,i,24,RED,BLUE,1);
//                    size3+=25;
//                    HAL_Delay(100);
//                }
                    //lcd_fill(95, 500, 400, 525, WHITE);    //清屏部分，防止乱码
                }

//串口发送到lcd上面显示

//显示部分
//            lcd_fill(95,500,400,525,WHITE);
//            lcd_show_string(100,500,240,24,24,DisplayValue,RED);
                //myUsart.SendString(DisplayValue, 20);
            }


        }
        if (timeout!=0){
            if ((HAL_GetTick()-tickStart)>timeout)
                break;

        }
    }
    return NULL;
}


/*
char * MyLCD::dealKeynum(u16 *deal) {
//    double num=0;
    if (*deal>0) {


        if (*deal == 1) {

            DisplayValue[n] = '1';
            n++;
        }
        if (*deal == 2) {
            DisplayValue[n] = '2';
            n++;
        }
        if (*deal == 3) {
            DisplayValue[n] = '3';
            n++;
        }
        if (*deal == 4) {
            biaozhi = 1;
            n = 1;
            for (i = 1; i < 20; i++) {
                DisplayValue[i] = ' ';
            }

            //DisplayValue[0] = ' ';
            return DisplayValue;
        }
        if (*deal == 5) {
            DisplayValue[n] = '4';
            n++;
        }
        if (*deal == 6) {
            DisplayValue[n] = '5';
            n++;
        }
        if (*deal == 7) {
            DisplayValue[n] = '6';
            n++;
        }
        if (*deal == 9) {
            DisplayValue[n] = '7';
            n++;
        }
        if (*deal == 10) {
            DisplayValue[n] = '8';
            n++;
        }
        if (*deal == 11) {
            DisplayValue[n] = '9';
            n++;
        }
        if (*deal == 12) {
            myUsart.SendString(DisplayValue, 20);
            return DisplayValue;
        }

        if (*deal == 14) {


            DisplayValue[n] = '0';
            n++;
        }
        if (*deal == 15) {
            if (biaozhi == 1)               //小数点防重复程序
            {
                DisplayValue[n] = '.';
                n++;
                biaozhi++;
            }
        }
        if (*deal == 16) {
            if (DisplayValue[n - 1] == '.')      //小数点删除特殊情况，还原标志位
            { biaozhi = 1; }
            DisplayValue[n - 1] = ' ';
            n--;
            if (n == 0)
                n = 1;
        }

        if (n > 20) {
            for (i = 1; i < 20; i++)        //清空数组
            {
                n = 1;
                DisplayValue[i] = ' ';

            }

        }

        lcd_show_string(100, 200, 240, 24, 24, DisplayValue, BLACK);



        //lcd_show_string(380,580,120,32,32,&temp,BLACK);
//        myUsart.SendOneFloat(num);
//       // myUsart.SendString(cstr, 20);
        *deal = 0;

    }
}*/
