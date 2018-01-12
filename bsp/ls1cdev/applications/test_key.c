/*
 * File      : test_key.c
����key�ӿ���finsh������
1. test_key   
���ȳ�ʼ���򿪰����жϣ������̲߳��ϼ���־λ��
�������£������жϷ��������λ��־λ��
�̼߳�⵽��־λ���������һ�¡�
 */
#include <rtthread.h>  

#include "ls1c.h"  
#include "ls1c_timer.h"  
#include "ls1c_public.h"  
#include "ls1c_gpio.h"  
#include "mipsregs.h"  

// �����õ��߳�    
#define THREAD_TEST_PRIORITY                    (25)    
#define THREAD_TEST_STACK_SIZE                  (4*1024)        // 4k    
#define THREAD_TEST_TIMESLICE                   (10)    

#define led_gpio 52
#define key_gpio 85

    
struct rt_thread thread_test;    
ALIGN(8)  
rt_uint8_t thread_test_stack[THREAD_TEST_STACK_SIZE];    
  
  
volatile rt_int32_t key_irq_flag = 0;  
  
void ls1c_test_key_irqhandler(int irq, void *param)  
{  
    key_irq_flag = 1;  
}  
    
// �����õ��̵߳����    
void thread_test_entry(void *parameter)    
{  
    int key_irq = LS1C_GPIO_TO_IRQ(key_gpio);  
  
    // ��ʼ�������ж�  
    gpio_set_irq_type(key_gpio, IRQ_TYPE_EDGE_FALLING);  
    rt_hw_interrupt_install(key_irq, ls1c_test_key_irqhandler, RT_NULL, "Key1");  
    rt_hw_interrupt_umask(key_irq);  
    gpio_init(key_gpio, gpio_mode_input);  
  
    // ��ʼ��led  
    gpio_init(led_gpio, gpio_mode_output);
    gpio_set(led_gpio, gpio_level_high);       // ָʾ��Ĭ��Ϩ��
      
    while (1)    
    {    
        if (1 == key_irq_flag)  
        {  
            // �ӳ�10ms������  
            rt_thread_delay(RT_TICK_PER_SECOND/10);  
            key_irq_flag = 0;  
		if (0 == (gpio_get(led_gpio)))
			 gpio_set(led_gpio, gpio_level_high); 
		else
			 gpio_set(led_gpio, gpio_level_low); 

            rt_kprintf("[%s] Key1 press\n", __FUNCTION__);  
        }  
        rt_thread_delay(RT_TICK_PER_SECOND);    
    }    
}    
  
  

int test_key(void)  
{  
    rt_thread_t tid;  
    rt_err_t result;  
  
 
  
    
    // ��ʼ�������õ��߳�    
    result = rt_thread_init(&thread_test,     
                            "thread_test",    
                            thread_test_entry,    
                            RT_NULL,    
                            &thread_test_stack[0],    
                            sizeof(thread_test_stack),    
                            THREAD_TEST_PRIORITY,    
                            THREAD_TEST_TIMESLICE);    
    if (RT_EOK == result)    
    {    
        rt_thread_startup(&thread_test);    
    }    
    else    
    {    
        return -1;    
    }    
  
    return 0;  
}  
 #include  <finsh.h> 
FINSH_FUNCTION_EXPORT(test_key, test_key  e.g.test_key());

