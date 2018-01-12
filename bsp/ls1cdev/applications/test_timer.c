/*
 * File      : test_timer.c
 ����Ӳ����ʱ���� ��finsh ������ 
1.test_timer_poll_time_out()  ����Ӳ����ʱ���Ķ�ʱ����(��ȡ�ж�״̬λ�ķ�ʽ�ж��Ƿ�ʱ)
2.test_timer_get_time ()
* ��Ӳ����ʱ����ʱ
 * ��Ӳ����ʱ�������������ͷHX1838�����Ĳ����иߵ͵�ƽ��ʱ����
 * ��ʶ�����ң�ذ������Ǹ����������£�ѡ��NEC���뷽ʽ�ĺ���ң����
 */


#include "../libraries/ls1c_timer.h"
#include "../libraries/ls1c_gpio.h"
#include "../libraries/ls1c_delay.h"


// һ����������ĳ���
#define IR_MAX_BYTE_NUM                 (4)                             // һ�������������4�ֽ�����
#define IR_MAX_BIT_NUM                  (1 + IR_MAX_BYTE_NUM * 8)       // 1bit����ʼ�źź�4���ֽ�

// ����������һ��bit���ݵ����ʱ��
#define IR_ONE_BIT_MAX_TIME             (20*1000*1000)


// ����������һ��bit����Ϣ
typedef struct
{
    unsigned long low_time_ns;          // �͵�ƽʱ������λns
    unsigned long high_time_ns;         // �ߵ�ƽʱ������λns
    unsigned int bit;                   // ����ֵ��0��1
}ir_one_bit_t;


// ����Ӳ����ʱ���Ķ�ʱ����(��ȡ�ж�״̬λ�ķ�ʽ�ж��Ƿ�ʱ)
void test_timer_poll_time_out(void)
{
    unsigned int gpio = 6;
    timer_info_t timer_info = {0};

    gpio_init(gpio, gpio_mode_output);
    gpio_set(gpio,  gpio_level_high);

    while (1)
    {
        // ��ʱ10us
        timer_info.timer    = TIMER_PWM0;
        timer_info.time_ns  = 10*1000;
        timer_init(&timer_info);
        while (! timer_is_time_out(&timer_info))    // �ȴ���ֱ����ʱ
            ;
//        timer_print_regs(&timer_info);            // ����ʱ����ӡ�Ĵ�����Ϣ
//        timer_print_regs(&timer_info);
//        timer_print_regs(&timer_info);
        gpio_set(gpio, gpio_level_low);

        // ��ʱ10ms
        timer_info.time_ns  = 10*1000*1000;
        timer_init(&timer_info);
        while (! timer_is_time_out(&timer_info))
            ;
        gpio_set(gpio, gpio_level_high);
    }
}



/*
 * ��Ӳ����ʱ����ʱ
 * ��Ӳ����ʱ�������������ͷHX1838�����Ĳ����иߵ͵�ƽ��ʱ����
 * ��ʶ�����ң�ذ������Ǹ����������£�ѡ��NEC���뷽ʽ�ĺ���ң����
 */
void test_timer_get_time(void)
{
    unsigned int ir_gpio = 47;          // �������ͷ����������
    timer_info_t timer_info = {0};      // Ӳ����ʱ����Ϣ
    ir_one_bit_t ir_bits[IR_MAX_BIT_NUM];
    unsigned char ir_bytes[IR_MAX_BYTE_NUM];
    int tmp, i, j;
    unsigned long time_ns = 0;
    gpio_init(ir_gpio, gpio_mode_input);
    
    timer_info.timer = TIMER_PWM0;              // PWM0����Ӳ����ʱ��
    timer_info.time_ns = IR_ONE_BIT_MAX_TIME;   // 20ms

    // �ȴ���ֱ���͵�ƽ(��ʼ�ź�)����
    while (gpio_get(ir_gpio))
        ;

    // ����һ�������ĺ�������
    for (tmp=0; tmp<IR_MAX_BIT_NUM; tmp++)
    {
        // ��ʼ��ʱ
        timer_init(&timer_info);                    // ��ʼ��ʱ

        // �ȴ���ֱ���ߵ�ƽ��ʱ����ʱΪֹ
        while ((!gpio_get(ir_gpio)) && (!timer_is_time_out(&timer_info)))
            ;

        // ��ȡʱ�䣬�����¿�ʼ��ʱ
        time_ns = timer_get_time_ns(&timer_info);
        timer_init(&timer_info);
        if (IR_ONE_BIT_MAX_TIME == time_ns)     // �ж��Ƿ�ʱ����ʱ��ζ��һ����������������
            break;
        ir_bits[tmp].low_time_ns = time_ns;

        // �ȴ���ֱ���͵�ƽ��ʱ����ʱΪֹ
        while ((gpio_get(ir_gpio)) && (!timer_is_time_out(&timer_info)))
            ;

        // ��ȡʱ�䣬�����¼�ʱ
        time_ns = timer_get_time_ns(&timer_info);
        timer_init(&timer_info);
        if (IR_ONE_BIT_MAX_TIME == time_ns)     // �ж��Ƿ�ʱ
            break;
        ir_bits[tmp].high_time_ns = time_ns;
    }

    // ���ߵ͵�ƽ��Ϣת��Ϊbitֵ
    for (tmp=0; tmp<IR_MAX_BIT_NUM; tmp++)
    {
        // ����ÿ��bit�ĸߵ�ƽʱ�����жϸ�bit��0������1
        if (1*1000*1000 < ir_bits[tmp].high_time_ns)        // >1msΪ1
        {
            ir_bits[tmp].bit = 1;
        }
        else                                                // <1msΪ0
        {
            ir_bits[tmp].bit = 0;
        }
    }

    // ��ӡ��ϸ�ĺ���������Ϣ
    myprintf("\n----------------one ir cmd---------------\n");
    for (tmp=0; tmp<IR_MAX_BIT_NUM; tmp++)
    {
        myprintf("low_time_ns=%d, high_time_ns=%d, bit=%d\n",
                  ir_bits[tmp].low_time_ns,
                  ir_bits[tmp].high_time_ns,
                  ir_bits[tmp].bit);
    }

    // ��bitֵ��ϳɺ�������
    for (i=0; i<IR_MAX_BYTE_NUM; i++)
    {
        tmp = 0;
        for (j=0; j<8; j++)
        {
            tmp = tmp + (ir_bits[1+i*8+j].bit << j);
        }
        ir_bytes[i] = tmp;
    }

    // ��������Ƿ���ȷ����ȷ���ӡ��������
    if ((ir_bytes[0] == (unsigned char)(~ir_bytes[1])) 
        && (ir_bytes[2] == (unsigned char)(~ir_bytes[3])))
    {
        myprintf("[%s] ir cmd=0x%02x%02x\n", __FUNCTION__, ir_bytes[0], ir_bytes[2]);
    }
    else
    {
        myprintf("[%s] ir cmd err. cmd=0x%x, 0x%x, 0x%x, 0x%x\n",
                  __FUNCTION__, ir_bytes[0], ir_bytes[1], ir_bytes[2], ir_bytes[3]);
    }

    return ;
}

