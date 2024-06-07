#include "stm32f10x.h"                  // Device header

//默认引脚A设定为推挽输出，引脚B为上拉输入，可根据需求自行更改

void InitGPIOA(void)
{
	/*开启时钟*/
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);	//开启GPIOA的时钟
	/*另外两个时钟是RCC_APB1,RCC_AHB*/			/*DISABLE 禁用*/			//使用各个外设前必须开启时钟，否则对外设的操作无效
	
	/*GPIO初始化*/
	GPIO_InitTypeDef GPIO_InitStructure;					//定义结构体变量
	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;		//GPIO模式，赋值为推挽输出模式
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_All;				//GPIO引脚，赋值为所有引脚
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		//GPIO速度，赋值为50MHz
	
	GPIO_Init(GPIOA, &GPIO_InitStructure);					//将赋值后的构体变量传递给GPIO_Init函数
															//函数内部会自动根据结构体的参数配置相应寄存器
															//实现GPIOA的初始化
	
}
/*设定电平的函数：
		GPIO_ResetBits(GPIOA, GPIO_Pin_0);					//将PA0引脚设置为低电平	
		GPIO_SetBits(GPIOA, GPIO_Pin_0);					//将PA0引脚设置为高电平


*/
/* GPIO输入模式
GPIO_Mode_AIN = 0x0 模拟输入
         _IN_FLOATING = 0x04 浮空输入
		 _IPD = 0x28 下拉输入
         _IPU = 上拉输入
*/
/*GPIO输出模式
GPIO_Mode_Out_OD = 0x14 开漏
	     _Out_PP = 0x10 推挽
		 _AF_OD = 0x1C 复用开漏
		 _AF_PP = 0x18 复用推挽
*/
void InitGPIOB(void)
{
	/*开启时钟*/
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);		//开启GPIOB的时钟
	
	/*GPIO初始化*/
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_All;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructure);						//将所有引脚初始化为上拉输入
}
