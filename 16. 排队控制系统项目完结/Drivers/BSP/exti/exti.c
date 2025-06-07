#include "exti.h"
#include "sys.h"
#include "delay.h"
#include "led.h"

uint8_t ia_flag = FALSE;                               // ��⵽�𶯱�־λ

void exti_init(void)
{
    GPIO_InitTypeDef gpio_initstruct;
    //��ʱ��
    __HAL_RCC_GPIOB_CLK_ENABLE();                           // ʹ��GPIOAʱ��
    
    //����GPIO��ʼ������
    gpio_initstruct.Pin = GPIO_PIN_4;                       // �𶯴�������Ӧ������
    gpio_initstruct.Mode = GPIO_MODE_IT_FALLING;            // �½��ش���
    gpio_initstruct.Pull = GPIO_PULLUP;                     // ����
    HAL_GPIO_Init(GPIOB, &gpio_initstruct);
    
    HAL_NVIC_SetPriority(EXTI4_IRQn, 2, 0);                 // ����EXTI0�ж��ߵ����ȼ�
    HAL_NVIC_EnableIRQ(EXTI4_IRQn);                         // ʹ���ж�
}

void EXTI4_IRQHandler(void)
{
    HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_4);
}

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
    delay_ms(20);
    if (GPIO_Pin == GPIO_PIN_4)
    {
        if(HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_4) == GPIO_PIN_RESET)
            //led1_toggle();
            ia_flag = TRUE;
    }
}

uint8_t ia_flag_get(void)
{
    uint8_t temp = ia_flag;
    ia_flag = FALSE;
    return temp;
    
}

void ia_flag_set(uint8_t value)
{
    ia_flag = value;
}
