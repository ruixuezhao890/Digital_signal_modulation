/**
*********************************************************************
*********
* @project_name :templateDevelopment
* @file : MyFFT.h
* @author : zen3
* @brief : None
* @attention : None
* @date : 2023/4/29 
*********************************************************************
*********
*/
//

#ifndef TEMPLATEDEVELOPMENT_MYFFT_H
#define TEMPLATEDEVELOPMENT_MYFFT_H
#ifdef __cplusplus
#define FFT_LENGTH 1024
extern "C"
{
#endif
#include "Myapplication.h"
/*______________________类的声明在这下面________________:*/
class MyFFT{
public:
    void FFTInit(uint16_t * adcNum);
    void FFTProcess();
    uint32_t Getmax_Index();
    float32_t GetPhase();
    float GetFmax();
    float * GetOutputbuf();
    float * GetIutputbuf();
    void PhaProcess();
    void FindMax();
    void DrawFFTWave();
    void FindFre();

    float32_t PhaProcess(MyFFT* myFFT1);
private:
    float32_t phase_diff;
    uint32_t max_Index;
    float Fmax;
    float fft_Inputbuf1[FFT_LENGTH * 2];
    float fft_Outputbuf1[FFT_LENGTH];
};
#ifdef __cplusplus
}
#endif
#endif //TEMPLATEDEVELOPMENT_MYFFT_H
