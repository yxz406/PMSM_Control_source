#ifndef APPLICATION_USER_WRAPPER_HPP_
#define APPLICATION_USER_WRAPPER_HPP_


#ifdef __cplusplus
extern "C" {
#endif
//Init
void ADC_Init(void);

//Do
void cppwrapper(void);
void HighFreqTask(void);
void BtnAct(void);
void BtnActOFF(void);
void BtnActON(void);
void MotorPWMTask(void);

void DebugTask(float pIu, float pIv, float pIw, float pArg);

#ifdef __cplusplus
};
#endif


#endif /* APPLICATION_USER_WRAPPER_HPP_ */
