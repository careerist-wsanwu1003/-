#include "tasks.h"
#include "led.h"
#include "beep.h"
#include "exti.h"
#include "lcd1602.h"
#include "gate.h"
#include "stdio.h"

enum
{
    PASS_STATE,
    WAIT_STATE
};

uint32_t led1_task_cnt = 0;
uint32_t led2_task_cnt = 0;
uint32_t wait_cnt = 0;
uint32_t passenger = 0;

uint8_t led1_task_flag = 0;
uint8_t led2_task_flag = 0;
uint8_t state = PASS_STATE;

char message[16] = {0};

void systick_isr(void)
{
    //�����������ͨ�е�״̬
    if(state == PASS_STATE)
    {
        //LED1��1���Ƶ����˸
        if (led1_task_cnt < 1000)
            led1_task_cnt++;
        else
        {
            led1_task_flag = 1;
            led1_task_cnt = 0;
        }
        //LED2����˸
        led2_off();
        //����������
        beep_off();
        //����
        gate_off();
    }
    //������ڲ�����ͨ�е�״̬
    else if(state == WAIT_STATE)
    {
        //LED2��200ms��Ƶ����˸
        if (led2_task_cnt < 200)
            led2_task_cnt++;
        else
        {
            led2_task_flag = 1;
            led2_task_cnt = 0;
        }
        //LED1����
        led1_off();
        //��������
        beep_on();
        //����
        gate_on();
        //��ʱ3�룬֮��
        if(wait_cnt < 3000)
            wait_cnt++;
        else
        {
            wait_cnt = 0;
            //��������ͨ��״̬
            state = PASS_STATE;
            //LCD��ʾ״̬
            lcd1602_show_line(1, 1, "PASS...");
        }
    }
}

void led1_task(void)
{
    if(led1_task_flag == 0)
        return;
    
    led1_task_flag = 0;
    
    led1_toggle();
}

void led2_task(void)
{
    if(led2_task_flag == 0)
        return;
    
    led2_task_flag = 0;
    
    led2_toggle();
}

void sensor_task(void)
{
    //�����⵽����ͨ��
    if(ia_flag_get() == TRUE && state == PASS_STATE)
    {
        //������1
        passenger++;
        //LCD��ʾ״̬
        sprintf(message, "PASS...%02d/05", passenger);
        lcd1602_show_line(1, 1, message);
        
    }

    //���ͨ������������5��
    if(passenger >= 5)
    {
        //��������
        passenger = 0;
        //���벻����ͨ��״̬
        state = WAIT_STATE;
        //LCD��ʾ״̬
        lcd1602_show_line(1, 1, "WAIT...00/05");
    }
}
