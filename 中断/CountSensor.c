#include "stm32f10x.h"                  // Device header
#include "Delay.h"
uint16_t CountSensor_Count;				//ȫ�ֱ��������ڼ���

/**
  * ��    ����������������ʼ��
  * ��    ������
  * �� �� ֵ����
  */
void CountSensor_Init(void)
{
	/*����ʱ��*/
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);		//����GPIOB��ʱ��
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);		//����AFIO��ʱ�ӣ��ⲿ�жϱ��뿪��AFIO��ʱ��	
	
	/*GPIO��ʼ��*/
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_14|GPIO_Pin_1;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructure);						//��PB14���ų�ʼ��Ϊ��������
	
	/*AFIOѡ���ж�����*/
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOB, GPIO_PinSource14);//���ⲿ�жϵ�14����ӳ�䵽GPIOB����ѡ��PB14Ϊ�ⲿ�ж�����
	
	/*EXTI��ʼ��*/
	EXTI_InitTypeDef EXTI_InitStructure;						//����ṹ�����
	EXTI_InitStructure.EXTI_Line = EXTI_Line14;					//ѡ�������ⲿ�жϵ�14���ߣ�ѡ�������߾�������Line
	EXTI_InitStructure.EXTI_LineCmd = ENABLE;					//ָ���ⲿ�ж���ʹ��
	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;//�¼�ģʽΪ	EXTI_Mode_Event		//ָ���ⲿ�ж���Ϊ�ж�ģʽ
	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;		//ָ���ⲿ�ж���Ϊ�½��ش���
	EXTI_Init(&EXTI_InitStructure);								//���ṹ���������EXTI_Init������EXTI����
	/*EXTI_Trigger_Falling �½��ش���
	  EXTI_Trigger_Rising �����ش���
	  EXTI_Trigger_Rising_Falling ������

	*/




	
	/*NVIC�жϷ���*/
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);				//����NVICΪ����2,��Ϊ
	/*
	#define NVIC_PriorityGroup_0 ((uint32_t)0x700)	��ռ���ȼ�ʹ�� 0 λ�������ȼ�ʹ�� 4 λ
	#define NVIC_PriorityGroup_1 ((uint32_t)0x600)	��ռ���ȼ�ʹ�� 1 λ�������ȼ�ʹ�� 3 λ
	#define NVIC_PriorityGroup_2 ((uint32_t)0x500)	��ռ���ȼ�ʹ�� 2 λ�������ȼ�ʹ�� 2 λ
	#define NVIC_PriorityGroup_3 ((uint32_t)0x400)	��ռ���ȼ�ʹ�� 3 λ�������ȼ�ʹ�� 1 λ
	#define NVIC_PriorityGroup_4 ((uint32_t)0x300)	��ռ���ȼ�ʹ�� 4 λ�������ȼ�ʹ�� 0 λ			
	
	*/															//����ռ���ȼ���Χ��0~3����Ӧ���ȼ���Χ��0~3
																//�˷������������������н������һ��
																//���ж���жϣ����԰Ѵ˴������main�����ڣ�whileѭ��֮ǰ
																//�����ö�����÷���Ĵ��룬���ִ�е����ûḲ����ִ�е�����
	
	/*NVIC����*/
	NVIC_InitTypeDef NVIC_InitStructure;						//����ṹ�����
	NVIC_InitStructure.NVIC_IRQChannel = EXTI15_10_IRQn;		//ѡ������NVIC��EXTI15_10�ߣ�10~15������������������������·
	//EXTI0_IRQn                  = 6,      /*!< EXTI Line0 Interrupt                                 */
    //EXTI1_IRQn                  = 7,      /*!< EXTI Line1 Interrupt                                 */
 	// EXTI2_IRQn                  = 8,      /*!< EXTI Line2 Interrupt                                 */
	//EXTI3_IRQn                  = 9,      /*!< EXTI Line3 Interrupt                                 */
	// EXTI4_IRQn                  = 10,     /*!< EXTI Line4 Interrupt
	//EXTI9_5_IRQn
	// EXTI15_10_IRQn
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;				//ָ��NVIC��·ʹ��
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;	//ָ��NVIC��·����ռ���ȼ�Ϊ1
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;			//ָ��NVIC��·����Ӧ���ȼ�Ϊ1
	NVIC_Init(&NVIC_InitStructure);								//���ṹ���������NVIC_Init������NVIC����
	/*
	
	
	 */
}



/**
  * ��    ������ȡ�����������ļ���ֵ
  * ��    ������
  * �� �� ֵ������ֵ����Χ��0~65535
  */
uint16_t CountSensor_Get(void)
{
	if (GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_1) == 0)			//��PB1����Ĵ�����״̬�����Ϊ0���������1����
	{
		Delay_ms(20);											//��ʱ����
		while (GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_1) == 0);	//�ȴ���������
		Delay_ms(20);					//��ʱ����
		CountSensor_Count =0;											//�ü���Ϊ1
	} //��ȡGPIOB��Pin_1��ֵ����ʽΪuint8_t
	return CountSensor_Count;
}

/**
  * ��    ����EXTI15_10�ⲿ�жϺ���
  * ��    ������
  * �� �� ֵ����
  * ע������˺���Ϊ�жϺ�����������ã��жϴ������Զ�ִ��
  *           ������ΪԤ����ָ�����ƣ����Դ������ļ�����
  *           ��ȷ����������ȷ���������κβ��죬�����жϺ��������ܽ���
  */
void EXTI15_10_IRQHandler(void)
{//EXTI0_IRQHandler
 //EXTI1_IRQHandler
 //EXTI2_IRQHandler
 //EXTI3_IRQHandler
 //EXTI4_IRQHandler
 //EXTI9_5_IRQHandler
 //EXTI15_10_IRQHandler
	if (EXTI_GetITStatus(EXTI_Line14) == SET)		//�ж��Ƿ����ⲿ�ж�14���ߴ������ж�
	{
		/*��������������������󣬿��ٴ��ж����ŵ�ƽ���Ա��ⶶ��*/
		if (GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_14) == 0)
		{
			CountSensor_Count ++;					//����ֵ����һ��
		}
		EXTI_ClearITPendingBit(EXTI_Line14);		//����ⲿ�ж�14���ߵ��жϱ�־λ
													//�жϱ�־λ�������
													//�����жϽ��������ϵش�����������������
	}
}
