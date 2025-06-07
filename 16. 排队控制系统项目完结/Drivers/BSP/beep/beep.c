#include "beep.h"
#include "sys.h"

//��ʼ��GPIO����
void beep_init(void)
{
    GPIO_InitTypeDef gpio_initstruct;
    //��ʱ��
    __HAL_RCC_GPIOB_CLK_ENABLE();                           // ʹ��GPIOBʱ��
    
    //����GPIO��ʼ������
    gpio_initstruct.Pin = GPIO_PIN_5;                       // ��������Ӧ������
    gpio_initstruct.Mode = GPIO_MODE_OUTPUT_PP;             // �������
    gpio_initstruct.Pull = GPIO_PULLUP;                     // ����
    gpio_initstruct.Speed = GPIO_SPEED_FREQ_HIGH;           // ����
    HAL_GPIO_Init(GPIOB, &gpio_initstruct);
    //�رշ�����
    beep_off();
}

//�򿪷������ĺ���
void beep_on(void)
{
    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_5, GPIO_PIN_RESET);   // ���ͷ��������ţ��򿪷�����
}

//�رշ������ĺ���
void beep_off(void)
{
    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_5, GPIO_PIN_SET);     // ���߷��������ţ��رշ�����
}
