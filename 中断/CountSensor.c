#include "stm32f10x.h"                  // Device header
#include "Delay.h"
uint16_t CountSensor_Count;				//全局变量，用于计数

/**
  * 函    数：计数传感器初始化
  * 参    数：无
  * 返 回 值：无
  */
void CountSensor_Init(void)
{
	/*开启时钟*/
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);		//开启GPIOB的时钟
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);		//开启AFIO的时钟，外部中断必须开启AFIO的时钟	
	
	/*GPIO初始化*/
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_14|GPIO_Pin_1;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructure);						//将PB14引脚初始化为上拉输入
	
	/*AFIO选择中断引脚*/
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOB, GPIO_PinSource14);//将外部中断的14号线映射到GPIOB，即选择PB14为外部中断引脚
	
	/*EXTI初始化*/
	EXTI_InitTypeDef EXTI_InitStructure;						//定义结构体变量
	EXTI_InitStructure.EXTI_Line = EXTI_Line14;					//选择配置外部中断的14号线，选择那条线就用那条Line
	EXTI_InitStructure.EXTI_LineCmd = ENABLE;					//指定外部中断线使能
	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;//事件模式为	EXTI_Mode_Event		//指定外部中断线为中断模式
	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;		//指定外部中断线为下降沿触发
	EXTI_Init(&EXTI_InitStructure);								//将结构体变量交给EXTI_Init，配置EXTI外设
	/*EXTI_Trigger_Falling 下降沿触发
	  EXTI_Trigger_Rising 上升沿触发
	  EXTI_Trigger_Rising_Falling 都触发

	*/




	
	/*NVIC中断分组*/
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);				//配置NVIC为分组2,即为
	/*
	#define NVIC_PriorityGroup_0 ((uint32_t)0x700)	抢占优先级使用 0 位，子优先级使用 4 位
	#define NVIC_PriorityGroup_1 ((uint32_t)0x600)	抢占优先级使用 1 位，子优先级使用 3 位
	#define NVIC_PriorityGroup_2 ((uint32_t)0x500)	抢占优先级使用 2 位，子优先级使用 2 位
	#define NVIC_PriorityGroup_3 ((uint32_t)0x400)	抢占优先级使用 3 位，子优先级使用 1 位
	#define NVIC_PriorityGroup_4 ((uint32_t)0x300)	抢占优先级使用 4 位，子优先级使用 0 位			
	
	*/															//即抢占优先级范围：0~3，响应优先级范围：0~3
																//此分组配置在整个工程中仅需调用一次
																//若有多个中断，可以把此代码放在main函数内，while循环之前
																//若调用多次配置分组的代码，则后执行的配置会覆盖先执行的配置
	
	/*NVIC配置*/
	NVIC_InitTypeDef NVIC_InitStructure;						//定义结构体变量
	NVIC_InitStructure.NVIC_IRQChannel = EXTI15_10_IRQn;		//选择配置NVIC的EXTI15_10线，10~15，用其他的需配置其他的线路
	//EXTI0_IRQn                  = 6,      /*!< EXTI Line0 Interrupt                                 */
    //EXTI1_IRQn                  = 7,      /*!< EXTI Line1 Interrupt                                 */
 	// EXTI2_IRQn                  = 8,      /*!< EXTI Line2 Interrupt                                 */
	//EXTI3_IRQn                  = 9,      /*!< EXTI Line3 Interrupt                                 */
	// EXTI4_IRQn                  = 10,     /*!< EXTI Line4 Interrupt
	//EXTI9_5_IRQn
	// EXTI15_10_IRQn
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;				//指定NVIC线路使能
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;	//指定NVIC线路的抢占优先级为1
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;			//指定NVIC线路的响应优先级为1
	NVIC_Init(&NVIC_InitStructure);								//将结构体变量交给NVIC_Init，配置NVIC外设
	/*
	
	
	 */
}



/**
  * 函    数：获取计数传感器的计数值
  * 参    数：无
  * 返 回 值：计数值，范围：0~65535
  */
uint16_t CountSensor_Get(void)
{
	if (GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_1) == 0)			//读PB1输入寄存器的状态，如果为0，则代表按键1按下
	{
		Delay_ms(20);											//延时消抖
		while (GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_1) == 0);	//等待按键松手
		Delay_ms(20);					//延时消抖
		CountSensor_Count =0;											//置键码为1
	} //读取GPIOB在Pin_1的值，格式为uint8_t
	return CountSensor_Count;
}

/**
  * 函    数：EXTI15_10外部中断函数
  * 参    数：无
  * 返 回 值：无
  * 注意事项：此函数为中断函数，无需调用，中断触发后自动执行
  *           函数名为预留的指定名称，可以从启动文件复制
  *           请确保函数名正确，不能有任何差异，否则中断函数将不能进入
  */
void EXTI15_10_IRQHandler(void)
{//EXTI0_IRQHandler
 //EXTI1_IRQHandler
 //EXTI2_IRQHandler
 //EXTI3_IRQHandler
 //EXTI4_IRQHandler
 //EXTI9_5_IRQHandler
 //EXTI15_10_IRQHandler
	if (EXTI_GetITStatus(EXTI_Line14) == SET)		//判断是否是外部中断14号线触发的中断
	{
		/*如果出现数据乱跳的现象，可再次判断引脚电平，以避免抖动*/
		if (GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_14) == 0)
		{
			CountSensor_Count ++;					//计数值自增一次
		}
		EXTI_ClearITPendingBit(EXTI_Line14);		//清除外部中断14号线的中断标志位
													//中断标志位必须清除
													//否则中断将连续不断地触发，导致主程序卡死
	}
}
