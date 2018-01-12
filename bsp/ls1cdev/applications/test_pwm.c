/*
 * File      : test_pwm.c   
����Ӳ��pwm�� ��finsh������
1. test_pwm_normal()    ����������pwm����
2. test_pwm_pulse()  ����Ӳ��pwm
3. test_pwm_gpio04_gpio06()  ����gpio04����Ϊpwm,gpio06��Ϊ��ͨgpioʹ��
4. test_pwm_max_period() ����pwm�������
 */

#include "../libraries/ls1c_public.h"
#include "../libraries/ls1c_gpio.h"
#include "../libraries/ls1c_delay.h"
#include "../libraries/ls1c_pwm.h"


// ����Ӳ��pwm����������pwm����
void test_pwm_normal(void)
{
    pwm_info_t pwm_info;

    pwm_info.gpio = LS1C_PWM0_GPIO06;               // pwm����λgpio06
    pwm_info.mode = PWM_MODE_NORMAL;                // ����ģʽ--�������pwm����
    pwm_info.duty = 0.85;                           // pwmռ�ձ�
    pwm_info.period_ns = 5*1000*1000;               // pwm����5ms

    // pwm��ʼ������ʼ������������pwm����
    pwm_init(&pwm_info);

    while (1)
    {
        // ��ʱ100ms
        delay_ms(100);

        // ��ֹpwm
        pwm_disable(&pwm_info);

        // ��ʱ100ms
        delay_ms(100);

        // ʹ��pwm
        pwm_enable(&pwm_info);
    }

    return ;
}


// ����Ӳ��pwm����pwm����
void test_pwm_pulse(void)
{
    int i;
    pwm_info_t pwm_info;

    pwm_info.gpio = LS1C_PWM0_GPIO06;               // ���pwm���ε�����
    pwm_info.mode = PWM_MODE_PULSE;                 // ������ģʽ��ÿ�ε���ֻ����һ�����壬���ü���������pwm����
    pwm_info.duty = 0.25;                           // pwmռ�ձ�
    pwm_info.period_ns = 1*1000*1000;               // pwm����1ms

    // Ϊ�˱�����ʾ�����۲죬����ѡ��ÿ��1s�ͷ���10������
    while (1)
    {
        // ����10������
        for (i=0; i<10; i++)
        {
            pwm_init(&pwm_info);
            delay_ms(2);
        }

        // ��ʱ10ms
        delay_ms(10);
    }

    return ;
}


/*
 * ����gpio04����Ϊpwm,gpio06��Ϊ��ͨgpioʹ��
 * PWM0��Ĭ������λGPIO06����Ҳ���Ը���ΪGPIO04
 * ��gpio06���Ǳ���Ĭ��Ϊpwmʱ������gpio04Ϊpwm0����ô��ͬʱ���������������ͬ��pwm����
 * ������ּ��֤��������gpio04����Ϊpwm0ʱ�������Խ�(Ĭ����Ϊpwm0��)gpio06��Ϊ��ͨgpioʹ��
 */
void test_pwm_gpio04_gpio06(void)
{
    pwm_info_t pwm_info;
    unsigned int gpio = 6;

    // ��gpio04�������pwm����
    pwm_info.gpio = LS1C_PWM0_GPIO04;           // gpio04������Ϊpwmʹ��
    pwm_info.mode = PWM_MODE_NORMAL;            // ���������pwm����
    pwm_info.duty = 0.25;                       // ռ�ձ�0.25
    pwm_info.period_ns = 1*1000*1000;           // pwm����1ms
    pwm_init(&pwm_info);

    // gpio06������Ϊ��ͨgpioʹ��
    gpio_init(gpio, gpio_mode_output);
    gpio_set(gpio, gpio_level_low);

    while (1)
        ;

    return ;
}


// ����pwm�������
void test_pwm_max_period(void)
{
    pwm_info_t pwm_info;

    // ��gpio04�������pwm����
    pwm_info.gpio = LS1C_PWM0_GPIO06;           // gpio06������Ϊpwmʹ��
    pwm_info.mode = PWM_MODE_NORMAL;            // ���������pwm����
    pwm_info.duty = 0.25;                       // ռ�ձ�0.25
    pwm_info.period_ns = 130*1000*1000;         // pwm����130ms

    // pwm���ڳ������ֵʱ����ָ����쳣���ݲ�֪��Ϊʲô
//    pwm_info.period_ns = 134*1000*1000;         // pwm����134ms�����������ֵ���ᱻ�Զ���Ϊ���ֵ

    pwm_init(&pwm_info);

    while (1)
        ;
}

 #include  <finsh.h> 
FINSH_FUNCTION_EXPORT(test_pwm_normal, test_pwm_normal e.g.test_pwm_normal());
FINSH_FUNCTION_EXPORT(test_pwm_pulse, test_pwm_pulse e.g.test_pwm_pulse());
FINSH_FUNCTION_EXPORT(test_pwm_gpio04_gpio06, test_pwm_gpio04_gpio06 e.g.test_pwm_gpio04_gpio06());
FINSH_FUNCTION_EXPORT(test_pwm_max_period, test_pwm_max_period e.g.test_pwm_max_period());




