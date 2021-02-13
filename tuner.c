#include "stm32l1xx.h"
#include "stm32l1xx_ll_gpio.h"
#include "stm32l1xx_ll_pwr.h"
#include "stm32l1xx_ll_rcc.h"
#include "stm32l1xx_ll_bus.h"
#include "stm32l1xx_ll_utils.h"
#include "stm32l1xx_ll_system.h"
#include "stm32l1xx_ll_tim.h"
#include "stdio.h"
#include "string.h"
#include "math.h"
#include "stdlib.h"

//------------------------ Music Sheet FN -----------------------//
#define C_0	  (uint16_t)16
#define CS_0	(uint16_t)17
#define D_0	  (uint16_t)18
#define DS_0	(uint16_t)19
#define E_0	  (uint16_t)20
#define F_0   (uint16_t)21
#define FS_0	(uint16_t)23
#define G_0	  (uint16_t)24
#define GS_0	(uint16_t)25
#define A_0	  (uint16_t)27
#define AS_0	(uint16_t)29
#define B_0	  (uint16_t)30

#define C_01	(uint16_t)32
#define CS_01	(uint16_t)34
#define D_01	(uint16_t)36
#define DS_01	(uint16_t)38
#define E_01	(uint16_t)41
#define F_01  (uint16_t)43
#define FS_01	(uint16_t)46
#define G_01	(uint16_t)49
#define GS_01	(uint16_t)51
#define A_01	(uint16_t)55
#define AS_01	(uint16_t)58
#define B_01	(uint16_t)61

#define C_02	(uint16_t)65
#define CS_02	(uint16_t)69
#define D_02	(uint16_t)73
#define DS_02	(uint16_t)77
#define E_02	(uint16_t)82
#define F_02  (uint16_t)87
#define FS_02	(uint16_t)92
#define G_02	(uint16_t)98
#define GS_02	(uint16_t)103
#define A_02	(uint16_t)110
#define AS_02	(uint16_t)116
#define B_02  (uint16_t)123

#define C_03	(uint16_t)130
#define CS_03	(uint16_t)138
#define D_03	(uint16_t)146
#define DS_03	(uint16_t)155
#define E_03	(uint16_t)164
#define F_03  (uint16_t)174
#define FS_03	(uint16_t)185
#define G_03	(uint16_t)196
#define GS_03	(uint16_t)207
#define A_03	(uint16_t)220
#define AS_03	(uint16_t)223
#define B_03	(uint16_t)246

#define C_04	(uint16_t)261
#define CS_04	(uint16_t)277
#define D_04	(uint16_t)293
#define DS_04	(uint16_t)311
#define E_04	(uint16_t)329
#define F_04  (uint16_t)349
#define FS_04	(uint16_t)369
#define G_04	(uint16_t)392
#define GS_04	(uint16_t)415
#define A_04	(uint16_t)440
#define AS_04	(uint16_t)446
#define B_04	(uint16_t)493

#define C_05	(uint16_t)523
#define CS_05	(uint16_t)554
#define D_05	(uint16_t)587
#define DS_05	(uint16_t)622
#define E_05	(uint16_t)659
#define F_05  (uint16_t)698
#define FS_05	(uint16_t)739
#define G_05	(uint16_t)783
#define GS_05	(uint16_t)830
#define A_05	(uint16_t)880
#define AS_05	(uint16_t)932
#define B_05	(uint16_t)987

#define C_06	(uint16_t)1046
#define CS_06	(uint16_t)1108
#define D_06	(uint16_t)1174
#define DS_06	(uint16_t)1244
#define E_06	(uint16_t)1318
#define F_06  (uint16_t)1396
#define FS_06	(uint16_t)1479
#define G_06	(uint16_t)1567
#define GS_06	(uint16_t)1661
#define A_06	(uint16_t)1760
#define AS_06	(uint16_t)1864
#define B_06	(uint16_t)1975

#define C_07	(uint16_t)2093
#define CS_07	(uint16_t)2217
#define D_07	(uint16_t)2349
#define DS_07	(uint16_t)2489
#define E_07	(uint16_t)2637
#define F_07  (uint16_t)2793
#define FS_07	(uint16_t)2959
#define G_07  (uint16_t)3135
#define GS_07	(uint16_t)3322
#define A_07	(uint16_t)3520
#define AS_07	(uint16_t)3729
#define B_07	(uint16_t)3951

#define C_08	(uint16_t)4186
#define CS_08	(uint16_t)4434
#define D_08	(uint16_t)4698
#define DS_08	(uint16_t)4978
#define E_08	(uint16_t)5274
#define F_08  (uint16_t)5587
#define FS_08	(uint16_t)5919
#define G_08	(uint16_t)6271
#define GS_08	(uint16_t)6644
#define A_08	(uint16_t)7040
#define AS_08	(uint16_t)7458
#define B_08	(uint16_t)7902

int RD,CS,Position,F_final;
char Note_final[10];

int Round_Decimal (double d);
int compare_sheet (int s);
int compare_num (int sheet_num ,int w[9][12],int num);
int findSmallestElement(int arr[], int n);
void compare_main(void);

int Sheet [9] [12] = {
    {C_0,  CS_0,  D_0,  DS_0,  E_0,  F_0,  FS_0,  G_0,  GS_0,  A_0,  AS_0,  B_0},
    {C_01, CS_01, D_01, DS_01, E_01, F_01, FS_01, G_01, GS_01, A_01, AS_01, B_01},
    {C_02, CS_02, D_02, DS_02, E_02, F_02, FS_02, G_02, GS_02, A_02, AS_02, B_02},
    {C_03, CS_03, D_03, DS_03, E_03, F_03, FS_03, G_03, GS_03, A_03, AS_03, B_03},
    {C_04, CS_04, D_04, DS_04, E_04, F_04, FS_04, G_04, GS_04, A_04, AS_04, B_04},
    {C_05, CS_05, D_05, DS_05, E_05, F_05, FS_05, G_05, GS_05, A_05, AS_05, B_05},
    {C_06, CS_06, D_06, DS_06, E_06, F_06, FS_06, G_06, GS_06, A_06, AS_06, B_06},
    {C_07, CS_07, D_07, DS_07, E_07, F_07, FS_07, G_07, GS_07, A_07, AS_07, B_07},
    {C_08, CS_08, D_08, DS_08, E_08, F_08, FS_08, G_08, GS_08, A_08, AS_08, B_08}
};

char *Sheet_note [9] [12] = {
    {"C_00", "CS00", "D_00", "DS00", "E_00", "F_00", "FS00", "G_00", "GS00", "A_00", "AS00", "B_00"},
    {"C_01", "CS01", "D_01", "DS01", "E_01", "F_01", "FS01", "G_01", "GS01", "A_01", "AS01", "B_01"},
    {"C_02", "CS02", "D_02", "DS02", "E_02", "F_02", "FS02", "G_02", "GS02", "A_02", "AS02", "B_02"},
    {"C_03", "CS03", "D_03", "DS03", "E_03", "F_03", "FS03", "G_03", "GS03", "A_03", "AS03", "B_03"},
    {"C_04", "CS04", "D_04", "DS04", "E_04", "F_04", "FS04", "G_04", "GS04", "A_04", "AS04", "B_04"},
    {"C_05", "CS05", "D_05", "DS05", "E_05", "F_05", "FS05", "G_05", "GS05", "A_05", "AS05", "B_05"},
    {"C_06", "CS06", "D_06", "DS06", "E_06", "F_06", "FS06", "G_06", "GS06", "A_06", "AS06", "B_06"},
    {"C_07", "CS07", "D_07", "DS07", "E_07", "F_07", "FS07", "G_07", "GS07", "A_07", "AS07", "B_07"},
    {"C_08", "CS08", "D_08", "DS08", "E_08", "F_08", "FS08", "G_08", "GS08", "A_08", "AS08", "B_08"}
};

//--------------------- Seven segment FN -----------------------//

uint32_t num_to_seg[19] = {
				LL_GPIO_PIN_2 	| LL_GPIO_PIN_10 | LL_GPIO_PIN_11 | LL_GPIO_PIN_12 | LL_GPIO_PIN_13 | LL_GPIO_PIN_14,													//0
				LL_GPIO_PIN_10 	| LL_GPIO_PIN_11,																																															//1
				LL_GPIO_PIN_2 	| LL_GPIO_PIN_10 | LL_GPIO_PIN_12 | LL_GPIO_PIN_13 | LL_GPIO_PIN_15,																					//2
				LL_GPIO_PIN_2 	| LL_GPIO_PIN_10 | LL_GPIO_PIN_11 | LL_GPIO_PIN_12 | LL_GPIO_PIN_15,																					//3
				LL_GPIO_PIN_10 	| LL_GPIO_PIN_11 | LL_GPIO_PIN_14 | LL_GPIO_PIN_15,																														//4
				LL_GPIO_PIN_2 	| LL_GPIO_PIN_11 | LL_GPIO_PIN_12 | LL_GPIO_PIN_14 | LL_GPIO_PIN_15,																					//5
				LL_GPIO_PIN_2 	| LL_GPIO_PIN_11 | LL_GPIO_PIN_12 | LL_GPIO_PIN_13 | LL_GPIO_PIN_14 | LL_GPIO_PIN_15, 												//6
				LL_GPIO_PIN_2 	| LL_GPIO_PIN_10 | LL_GPIO_PIN_11,																																						//7
				LL_GPIO_PIN_2 	| LL_GPIO_PIN_10 | LL_GPIO_PIN_11 | LL_GPIO_PIN_12 | LL_GPIO_PIN_13 | LL_GPIO_PIN_14 | LL_GPIO_PIN_15, 				//8
				LL_GPIO_PIN_2 	| LL_GPIO_PIN_10 | LL_GPIO_PIN_11 | LL_GPIO_PIN_12 | LL_GPIO_PIN_14 | LL_GPIO_PIN_15,													//9
			/*C*/ LL_GPIO_PIN_2	|	LL_GPIO_PIN_12	|	LL_GPIO_PIN_13	|	LL_GPIO_PIN_14,
			/*D*/ LL_GPIO_PIN_2	|	LL_GPIO_PIN_10	|	LL_GPIO_PIN_11	|	LL_GPIO_PIN_12	|	LL_GPIO_PIN_13	|	LL_GPIO_PIN_14,
			/*E*/ LL_GPIO_PIN_2	|	LL_GPIO_PIN_12	|	LL_GPIO_PIN_13	|	LL_GPIO_PIN_14	|	LL_GPIO_PIN_15,
			/*F*/ LL_GPIO_PIN_2	|	LL_GPIO_PIN_13	|	LL_GPIO_PIN_14	|	LL_GPIO_PIN_15,
			/*G*/ LL_GPIO_PIN_2	|	LL_GPIO_PIN_11	|	LL_GPIO_PIN_12	|	LL_GPIO_PIN_13	|	LL_GPIO_PIN_14	|	LL_GPIO_PIN_15,
			/*A*/ LL_GPIO_PIN_2	|	LL_GPIO_PIN_10	|	LL_GPIO_PIN_11	|	LL_GPIO_PIN_13	|	LL_GPIO_PIN_14	|	LL_GPIO_PIN_15,
			/*B*/ LL_GPIO_PIN_2	|	LL_GPIO_PIN_10	|	LL_GPIO_PIN_11	|	LL_GPIO_PIN_12	|	LL_GPIO_PIN_13	|	LL_GPIO_PIN_14|LL_GPIO_PIN_15,
			/*S*/ LL_GPIO_PIN_2	|	LL_GPIO_PIN_11	|	LL_GPIO_PIN_12	|	LL_GPIO_PIN_14	|	LL_GPIO_PIN_15,
			/*_*/ LL_GPIO_PIN_12};


uint32_t digit[4] = {LL_GPIO_PIN_0, LL_GPIO_PIN_1, LL_GPIO_PIN_2, LL_GPIO_PIN_3};

void display_segment(void);
int encodechar(char s);
void GPIO_Config(void);

//--------------------- Sample Frequency FN --------------------//
uint16_t uwIC1 = 0;
uint16_t uwIC2 = 0;
uint16_t uwIC3 = 0;

uint16_t uwDiff_Pos = 0;
uint16_t uwDiff_Neg = 0;
uint32_t uwDiff = 0;

uint16_t ovRound_Pos = 0;
uint16_t ovRound_Neg = 0;

uint16_t uhICIndex = 0;
uint16_t counterval = 0;
uint16_t ICIcount1 = 0;
uint16_t ICIcount2 = 0;
uint8_t state = 0;

float period = 0;
float frequency = 0;
uint32_t TIM2CLK;
uint32_t PSC;
uint32_t IC1PSC;
long int x = 0;

void SystemClock_Config(void);
void TIMx_IC_Config(void);
void Overflow_Check(void);
float Calculate_Frequency(void);
//-------------------------------------------------------------//

int main()
{
    SystemClock_Config();
		GPIO_Config();
    TIMx_IC_Config();
	
    while(1)
    {

		Overflow_Check();
		compare_main();
		display_segment();
    
		}
}

void display_segment(){
	int i; 
	
	for(i = 0; i < 4; ++i){
		LL_GPIO_ResetOutputPin(GPIOC, LL_GPIO_PIN_0 | LL_GPIO_PIN_1  | LL_GPIO_PIN_2  | LL_GPIO_PIN_3);
		LL_GPIO_ResetOutputPin(GPIOB, LL_GPIO_PIN_2 | LL_GPIO_PIN_10 | LL_GPIO_PIN_11 | LL_GPIO_PIN_12 | LL_GPIO_PIN_13 | LL_GPIO_PIN_14 | LL_GPIO_PIN_15);

			int b = encodechar(Note_final[i]);
			LL_GPIO_SetOutputPin(GPIOB, num_to_seg[b]);
			LL_GPIO_SetOutputPin(GPIOC, digit[i]);


		if(i < 4)
			LL_mDelay(1);
	
	}
}

int encodechar(char s){
	switch(s){
		case '0' 	: return 0;
		case '1' 	: return 1;
		case '2'	: return 2;
		case '3'	: return 3;
		case '4'	: return 4;
		case '5'	: return 5;
		case '6'	: return 6;
		case '7'	: return 7;
		case '8'	: return 8;
		case '9'  : return 9;
		case 'C' 	: return 10;
		case 'D' 	: return 11;
		case 'E'	: return 12;
		case 'F'	: return 13;
		case 'G'	: return 14;
		case 'A'	: return 15;
		case 'B'	: return 16;
		case 'S'	: return 17;
		case '_'	: return 18;
		
	}
}

void compare_main(void){
	
		RD = Round_Decimal(frequency);
    CS = compare_sheet(RD);
    Position = compare_num(CS,Sheet,RD);
    F_final = Sheet[CS][Position];
		strcpy(Note_final, Sheet_note[CS][Position] );

}

int Round_Decimal (double d)
{
    int com;
    double ans;
    com = d;
    ans = d - com;
    if(ans > 0.5)
    {
        return(com += 1);
    }
    else
    {
        return(com);
    }

}

int compare_sheet (int s)
{
    int Answer;
    if(s <= 31)
    {
        Answer = 0;
    }
    else if(s >= 32 && s <= 63)
    {
        Answer = 1;
    }
    else if(s >= 64 && s <= 126)
    {
        Answer = 2;
    }
    else if(s >= 127 && s <= 253)
    {
        Answer = 3;
    }
    else if(s >= 254 && s <= 508)
    {
        Answer = 4;
    }
    else if(s >= 509 && s <= 1016)
    {
        Answer = 5;
    }
    else if(s >= 1017 && s <= 2034)
    {
        Answer = 6;
    }
    else if(s >= 2035 && s <= 4068)
    {
        Answer = 7;
    }
    else if(s >= 4069)
    {
        Answer = 8;
    }
    return Answer;
}

int compare_num (int sheet_num ,int w[9][12],int num)
{
    int i;
    int com[12];
    for(i = 0;i < 12;i++)
    {
        com[i] = abs(w[sheet_num][i] - num);
    }
    return findSmallestElement(com,12);
}

int findSmallestElement(int arr[], int n)
{
   int temp = arr[0];
   int p = 0;
   for(int i=0; i<n; i++)
   {
      if(temp>arr[i])
      {
         temp=arr[i];
         p = i;
      }
   }
   return p;
}

void Overflow_Check(void){
	
				// Overflow 65535 on Positive
				counterval = LL_TIM_GetCounter(TIM2);
				if(counterval > 65534 == SET && uhICIndex == 1  && uhICIndex < 2)
				{
						ovRound_Pos++;
				}
				// Overflow 65535 on Negative
				else if(counterval > 65534 == SET && uhICIndex == 2  && uhICIndex < 3)
				{
						ovRound_Neg++;
				} 
				Calculate_Frequency();
}

float Calculate_Frequency(void){
	
				if(uhICIndex == 3)
				{
						PSC = LL_TIM_GetPrescaler(TIM2) + 1;
						TIM2CLK = SystemCoreClock / PSC;
						IC1PSC = __LL_TIM_GET_ICPSC_RATIO(LL_TIM_IC_GetPrescaler(TIM2, LL_TIM_CHANNEL_CH1));
						x = (uwDiff_Pos+ (ovRound_Pos*65535) ) + (uwDiff_Neg + (ovRound_Neg*65535));
						period = ( x *(PSC) * 1.0) / (TIM2CLK *IC1PSC * 1.0); //calculate uptime period
						frequency = 1/period;
						ovRound_Pos = 0;
						ovRound_Neg = 0;
						uhICIndex = 0;
						return frequency;
				}

}

void TIM2_IRQHandler(void)
{	 

	if(LL_TIM_IsActiveFlag_CC2(TIM2) == SET){
		if(uhICIndex == 0){
		uwIC1 = LL_TIM_IC_GetCaptureCH2(TIM2);
		uhICIndex = 1;
		}
		LL_TIM_ClearFlag_CC2(TIM2);						
	}
		
	if(LL_TIM_IsActiveFlag_CC3(TIM2) == SET){
			if(uhICIndex == 2){
			uwIC3 = LL_TIM_IC_GetCaptureCH3(TIM2);
								
			if(uwIC3 > uwIC2)
			{	
				uwDiff_Neg = uwIC3 - uwIC2;
			}
			
			else if(uwIC3 < uwIC2)
			{
				uwDiff_Neg = ((LL_TIM_GetAutoReload(TIM2) - uwIC2) + uwIC3) + 1;
			}
			uhICIndex = 3;

		}
		LL_TIM_ClearFlag_CC3(TIM2);							
	}

	if(LL_TIM_IsActiveFlag_CC4(TIM2) == SET)
	{
		//Find Falling edge 
		if(uhICIndex == 1){
		uwIC2 = LL_TIM_IC_GetCaptureCH4(TIM2);
								
			if(uwIC2 > uwIC1)
			{	
				uwDiff_Pos = uwIC2 - uwIC1;
			}
			
			else if(uwIC2 < uwIC1)
			{
				uwDiff_Pos = ((LL_TIM_GetAutoReload(TIM2) - uwIC1) + uwIC2) + 1;
			}
			uhICIndex = 2;
		}
		LL_TIM_ClearFlag_CC4(TIM2);
	}
		
				
}
		
void GPIO_Config(void)
{

    LL_GPIO_InitTypeDef x;
    LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_GPIOB);
    LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_GPIOC);

    x.Mode = LL_GPIO_MODE_OUTPUT;
    x.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
    x.Pull = LL_GPIO_PULL_NO;
    x.Speed = LL_GPIO_SPEED_FREQ_VERY_HIGH;
    x.Pin = LL_GPIO_PIN_2 | LL_GPIO_PIN_10 | LL_GPIO_PIN_11 | LL_GPIO_PIN_12 | LL_GPIO_PIN_13 | LL_GPIO_PIN_14 | LL_GPIO_PIN_15;

    LL_GPIO_Init(GPIOB, &x);

    x.Pin = LL_GPIO_PIN_0 | LL_GPIO_PIN_1 | LL_GPIO_PIN_2 | LL_GPIO_PIN_3;
    LL_GPIO_Init(GPIOC, &x);

}

void TIMx_IC_Config(void)
{
		LL_GPIO_InitTypeDef timic_gpio;
		LL_TIM_InitTypeDef timbase;
		LL_TIM_IC_InitTypeDef timic;
		
		LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_GPIOA);
		
		timic_gpio.Mode 			= LL_GPIO_MODE_ALTERNATE;
		timic_gpio.Pull 			= LL_GPIO_PULL_DOWN;
		timic_gpio.Pin 				= LL_GPIO_PIN_1 | LL_GPIO_PIN_2 | LL_GPIO_PIN_3;
		timic_gpio.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
		timic_gpio.Speed 			= LL_GPIO_SPEED_FREQ_VERY_HIGH;
		timic_gpio.Alternate 	= LL_GPIO_AF_1;
		LL_GPIO_Init(GPIOA, &timic_gpio);
		
		LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_TIM2);
		
		//TIM_IC Configure CH2
		timic.ICActiveInput 	= LL_TIM_ACTIVEINPUT_DIRECTTI;
		timic.ICFilter 				= LL_TIM_IC_FILTER_FDIV1;
		timic.ICPolarity 			= LL_TIM_IC_POLARITY_RISING;
		timic.ICPrescaler 		= LL_TIM_ICPSC_DIV1;
		LL_TIM_IC_Init(TIM2, LL_TIM_CHANNEL_CH2, &timic);
		//TIM_IC Configure CH3
		LL_TIM_IC_Init(TIM2, LL_TIM_CHANNEL_CH3, &timic);
		
		//TIM_IC Configure CH4
		timic.ICPolarity = LL_TIM_IC_POLARITY_FALLING;
		LL_TIM_IC_Init(TIM2, LL_TIM_CHANNEL_CH4, &timic);
		
		NVIC_SetPriority(TIM2_IRQn, 0);
		NVIC_EnableIRQ(TIM2_IRQn);
		
		LL_TIM_EnableIT_CC2(TIM2);
		LL_TIM_EnableIT_CC4(TIM2);
		
		LL_TIM_CC_EnableChannel(TIM2, LL_TIM_CHANNEL_CH2);
		LL_TIM_CC_EnableChannel(TIM2, LL_TIM_CHANNEL_CH4);
		
		LL_TIM_EnableCounter(TIM2);
}

void SystemClock_Config(void)
{
  /* Enable ACC64 access and set FLASH latency */ 
  LL_FLASH_Enable64bitAccess();; 
  LL_FLASH_SetLatency(LL_FLASH_LATENCY_1);

  /* Set Voltage scale1 as MCU will run at 32MHz */
  LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_PWR);
  LL_PWR_SetRegulVoltageScaling(LL_PWR_REGU_VOLTAGE_SCALE1);
  
  /* Poll VOSF bit of in PWR_CSR. Wait until it is reset to 0 */
  while (LL_PWR_IsActiveFlag_VOSF() != 0)
  {
  };
  
  /* Enable HSI if not already activated*/
  if (LL_RCC_HSI_IsReady() == 0)
  {
    /* HSI configuration and activation */
    LL_RCC_HSI_Enable();
    while(LL_RCC_HSI_IsReady() != 1)
    {
    };
  }
  
	
  /* Main PLL configuration and activation */
  LL_RCC_PLL_ConfigDomain_SYS(LL_RCC_PLLSOURCE_HSI, LL_RCC_PLL_MUL_6, LL_RCC_PLL_DIV_3);

  LL_RCC_PLL_Enable();
  while(LL_RCC_PLL_IsReady() != 1)
  {
  };
  
  /* Sysclk activation on the main PLL */
  LL_RCC_SetAHBPrescaler(LL_RCC_SYSCLK_DIV_1);
  LL_RCC_SetSysClkSource(LL_RCC_SYS_CLKSOURCE_PLL);
  while(LL_RCC_GetSysClkSource() != LL_RCC_SYS_CLKSOURCE_STATUS_PLL)
  {
  };
  
  /* Set APB1 & APB2 prescaler*/
  LL_RCC_SetAPB1Prescaler(LL_RCC_APB1_DIV_1);
  LL_RCC_SetAPB2Prescaler(LL_RCC_APB2_DIV_1);

  /* Set systick to 1ms in using frequency set to 32MHz                             */
  /* This frequency can be calculated through LL RCC macro                          */
  /* ex: __LL_RCC_CALC_PLLCLK_FREQ (HSI_VALUE, LL_RCC_PLL_MUL_6, LL_RCC_PLL_DIV_3); */
  LL_Init1msTick(32000000);
  
  /* Update CMSIS variable (which can be updated also through SystemCoreClockUpdate function) */
  LL_SetSystemCoreClock(32000000);
}