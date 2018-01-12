/*
 * File      : test_gpio.c
����gpio�ӿ���finsh������
1. test_output()
2. test_delay_1us()
3. test_delay_1s()
4. print_clk()  ����ǰ�ķ�Ƶ������ʱ�Ӷ���ӡ����
5. test_rtdelay_1s ����RT_TICK_PER_SECONDʵ��1s ��ʱ����
6. mem_read(***) ��ȡ***�Ĵ�����32λ���ݲ���ӡ
 */


#include <rtthread.h>
#include "../libraries/ls1c_public.h"
#include "../libraries/ls1c_gpio.h"
#include "../libraries/ls1c_delay.h"
#define led_gpio 52
#define key_gpio 85


/*
 * ���Կ���gpio��Ϊ���ʱ����ؽӿ�
 * led��˸10��
 */
void test_output(void)
{
    int i;

    // ��ʼ��
    rt_kprintf("Init gpio! \n");
    gpio_init(led_gpio, gpio_mode_output);
    gpio_set(led_gpio, gpio_level_high);       // ָʾ��Ĭ��Ϩ��

    // ���10�����β������gpio50����led������Կ���led��˸10��
    for (i=0; i<10; i++)
    {
        gpio_set(led_gpio, gpio_level_low);
        delay_ms(500);
        gpio_set(led_gpio, gpio_level_high);
        delay_ms(500);
	rt_kprintf("current time: %d \n", i);
    }
    
    return ;
}



/*
 * ���Կ���gpio��Ϊ����ʱ����ؽӿ�
 * ��������ʱ��ָʾ�Ƶ���������Ϩ��
 */
void test_input(void)
{

    // ��ʼ��
    gpio_init(led_gpio, gpio_mode_output);
    gpio_init(key_gpio, gpio_mode_input);
    gpio_set(led_gpio, gpio_level_high);        // ָʾ��Ĭ��Ϩ��

    while (1)
    {
        if (gpio_level_low != gpio_get(key_gpio))
            continue;       // ����û�а���

        // ��ʱ(�������)���ٴ�ȷ�ϰ����Ƿ���
        delay_ms(10);
        if (gpio_level_low != gpio_get(key_gpio))
            continue;       // ����û�а���

        // ����ָʾ��
        gpio_set(led_gpio, gpio_level_low);

        // �ȴ��ͷŰ���
        while (gpio_level_high != gpio_get(key_gpio))
            ;
        delay_ms(10);

        // Ϩ��ָʾ��
        gpio_set(led_gpio, gpio_level_high);
    }
}

 #include  <finsh.h> 
FINSH_FUNCTION_EXPORT(test_output, test_output  e.g.test_output());
FINSH_FUNCTION_EXPORT(test_input, test_input  e.g.test_input());




