#include "lcd1602.h"
#include "string.h"
#include <stdarg.h>
#include "delay.h"

// RS���Ŷ���
#define RS_GPIO_Port GPIOB
#define RS_GPIO_PIN GPIO_PIN_1
#define RS_HIGH     HAL_GPIO_WritePin(RS_GPIO_Port, RS_GPIO_PIN, GPIO_PIN_SET)
#define RS_LOW      HAL_GPIO_WritePin(RS_GPIO_Port, RS_GPIO_PIN, GPIO_PIN_RESET)

// RW���Ŷ���
#define RW_GPIO_Port GPIOB
#define RW_GPIO_PIN GPIO_PIN_2
#define RW_HIGH     HAL_GPIO_WritePin(RW_GPIO_Port, RW_GPIO_PIN, GPIO_PIN_SET)
#define RW_LOW      HAL_GPIO_WritePin(RW_GPIO_Port, RW_GPIO_PIN, GPIO_PIN_RESET)

// EN���Ŷ���
#define EN_GPIO_Port GPIOB
#define EN_GPIO_PIN GPIO_PIN_10
#define EN_HIGH     HAL_GPIO_WritePin(EN_GPIO_Port, EN_GPIO_PIN, GPIO_PIN_SET)
#define EN_LOW      HAL_GPIO_WritePin(EN_GPIO_Port, EN_GPIO_PIN, GPIO_PIN_RESET)

/**
 * @brief       LCD1602 GPIO��ʼ��
 * @param       ��
 * @retval      ��
 */
void lcd1602_gpio_init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};

  /* GPIO Ports Clock Enable */
  //__HAL_RCC_GPIOD_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

//  /*Configure GPIO pin Output Level */
//  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3
//                          |GPIO_PIN_4|GPIO_PIN_5|GPIO_PIN_6|GPIO_PIN_7, GPIO_PIN_SET);

//  /*Configure GPIO pin Output Level */
//  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_10, GPIO_PIN_SET);

  /*Configure GPIO pins : PA0 PA1 PA2 PA3
                           PA4 PA5 PA6 PA7 */
  GPIO_InitStruct.Pin = GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3
                          |GPIO_PIN_4|GPIO_PIN_5|GPIO_PIN_6|GPIO_PIN_7;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pins : PB1 PB2 PB10 */
  GPIO_InitStruct.Pin = GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_10;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);
}

/**
 * @brief       lcd��ʼ����
 * @param       ��
 * @retval      ��
 */
void lcd1602_start(void)
{
//��1����ʱ 15ms
    delay_ms(15);
//��2��дָ�� 38H(�����æ�ź�) 
    lcd1602_write_cmd(0x38);
//��3����ʱ 5ms
    delay_ms(5);
//��4�����æ�ź�(ʡ��)
//��5��дָ�� 38H����ʾģʽ����
    lcd1602_write_cmd(0x38);
//��6��дָ�� 08H����ʾ�ر�
    lcd1602_write_cmd(0x08);
//��7��дָ�� 01H����ʾ����
    lcd1602_write_cmd(0x01);
//��8��дָ�� 06H����ʾ����ƶ�����
    lcd1602_write_cmd(0x06);
//��9��дָ�� 0CH����ʾ�����������
    lcd1602_write_cmd(0x0c);
}

/**
 * @brief       LCD1602��ʼ��
 * @param       ��
 * @retval      ��
 */
void lcd1602_init(void)
{
    lcd1602_gpio_init();
    lcd1602_start();
}

/**
 * @brief       дָ��
* @param        cmd��ָ��
 * @retval      ��
 */
void lcd1602_write_cmd(char cmd)
{
    RS_LOW;
    RW_LOW;
    EN_LOW;
    GPIOA->ODR = cmd;       //��һ�ֽ����ݷ���GPIOA 8������
    delay_ms(5);
    EN_HIGH;
    delay_ms(5);
    EN_LOW;
}

/**
 * @brief       д����
 * @param       dataShow����ʾ���ַ�
 * @retval      ��
 */
void lcd1602_write_data(char dataShow)
{
    RS_HIGH;
    RW_LOW;
    EN_LOW;
    GPIOA->ODR = dataShow;   //��һ�ֽ����ݷ���GPIOA 8������
    delay_ms(5);
    EN_HIGH;
    delay_ms(5);
    EN_LOW;
}

/**
 * @brief       ��������
 * @param       ��
 * @retval      ��
 */
void lcd1602_right_move(void)
{
    for(int i=0;i < 16;i++){
        delay_ms(1000);
        lcd1602_write_cmd(0x18);            //��������һλ 0x18
    }
}

/**
 * @brief       ��ʾ�ַ�
 * @param       row: ��ʾ�У�col�� ��ʾ��ʼ�У�string����ʾ�ַ�
 * @retval      ��
 */
void lcd1602_show_line(char row, char col, char *string)
{
    switch(row){
    case 1:
        lcd1602_write_cmd(0x80+col);        //���λ D7 Ϊ�ߵ�ƽ
        while(*string){
            lcd1602_write_data(*string);
            string++;
        }
        break;
    
    case 2:
        lcd1602_write_cmd(0x80+0x40+col);
        while(*string){
            lcd1602_write_data(*string);
            string++;
        }
        break;
    }
}
