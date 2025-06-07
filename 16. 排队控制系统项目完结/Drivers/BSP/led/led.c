#include "led.h"
#include "sys.h"

//��ʼ��GPIO����
void led_init(void)
{
    GPIO_InitTypeDef gpio_initstruct;
    //��ʱ��
    __HAL_RCC_GPIOB_CLK_ENABLE();                           // ʹ��GPIOBʱ��
    
    //����GPIO��ʼ������
    gpio_initstruct.Pin = GPIO_PIN_8 | GPIO_PIN_9;          // ����LED��Ӧ������
    gpio_initstruct.Mode = GPIO_MODE_OUTPUT_PP;             // �������
    gpio_initstruct.Pull = GPIO_PULLUP;                     // ����
    gpio_initstruct.Speed = GPIO_SPEED_FREQ_HIGH;           // ����
    HAL_GPIO_Init(GPIOB, &gpio_initstruct);
    //�ر�LED
    led1_off();
    led2_off();
}

//����LED1�ĺ���
void led1_on(void)
{
    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_8, GPIO_PIN_RESET);   // ����LED1���ţ�����LED1
}

//Ϩ��LED1�ĺ���
void led1_off(void)
{
    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_8, GPIO_PIN_SET);     // ����LED1���ţ�Ϩ��LED1
}

//��תLED1״̬�ĺ���
void led1_toggle(void)
{
    HAL_GPIO_TogglePin(GPIOB, GPIO_PIN_8);
}

//����LED2�ĺ���
void led2_on(void)
{
    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_9, GPIO_PIN_RESET);   // ����LED2���ţ�����LED2
}

//Ϩ��LED2�ĺ���
void led2_off(void)
{
    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_9, GPIO_PIN_SET);     // ����LED2���ţ�Ϩ��LED2
}

//��תLED2״̬�ĺ���
void led2_toggle(void)
{
    HAL_GPIO_TogglePin(GPIOB, GPIO_PIN_9);
}
