#include "gate.h"
#include "sys.h"

//��ʼ��GPIO����
void gate_init(void)
{
    GPIO_InitTypeDef gpio_initstruct;
    //��ʱ��
    __HAL_RCC_GPIOB_CLK_ENABLE();                           // ʹ��GPIOBʱ��
    
    //����GPIO��ʼ������
    gpio_initstruct.Pin = GPIO_PIN_6;                       // �̵�����Ӧ������
    gpio_initstruct.Mode = GPIO_MODE_OUTPUT_PP;             // �������
    gpio_initstruct.Pull = GPIO_PULLUP;                     // ����
    gpio_initstruct.Speed = GPIO_SPEED_FREQ_HIGH;           // ����
    HAL_GPIO_Init(GPIOB, &gpio_initstruct);
    //�ر�LED
    gate_off();
}

//�պϼ̵����ĺ���
void gate_on(void)
{
    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_6, GPIO_PIN_RESET);   // ����LED1���ţ�����LED1
}

//�ɿ��̵����ĺ���
void gate_off(void)
{
    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_6, GPIO_PIN_SET);     // ����LED1���ţ�Ϩ��LED1
}

//��ȡ�̵���״̬�ĺ���
uint8_t gate_status_get(void)
{
    return (uint8_t)HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_6);
}
