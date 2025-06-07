#include "sys.h"
#include "delay.h"
#include "led.h"
#include "tasks.h"
#include "gate.h"
#include "beep.h"
#include "exti.h"
#include "lcd1602.h"

int main(void)
{
    HAL_Init();                         /* ��ʼ��HAL�� */
    stm32_clock_init(RCC_PLL_MUL9);     /* ����ʱ��, 72Mhz */
    led_init();                         /* ��ʼ��LED�� */
    gate_init();                        /* ��ʼ���̵��� */
    beep_init();                        /* ��ʼ�������� */
    exti_init();                        /* ��ʼ�����⴫���� */
    lcd1602_init();                     /* ��ʼ��LCD1602 */
    
    lcd1602_show_line(1, 1, "PASS...");

    while(1)
    { 
        led1_task();
        led2_task();
        sensor_task();
//        if(ia_flag_get() == TRUE)
//        {
//            led1_on();
//            delay_ms(2000);
//            led1_off();
//        }
//        beep_on();
//        delay_ms(500);
//        beep_off();
//        delay_ms(500);
//        task1();
//        task2();
    }
}

