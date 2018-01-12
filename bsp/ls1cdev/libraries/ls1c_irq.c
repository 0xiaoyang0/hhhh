/*************************************************************************
 *
 * �ж���صĺ���
 * ��о1c���ж���һ�����͵��쳣��
 * �������Ϊcpu���м����쳣�����ж�������һ���쳣�����һ��������
 * ��о1c���쳣��Ϊ�ļ�
 * ��һ��: ����������쳣�����������
 * �ڶ���: �����쳣����ڣ�����ExcCode=0���쳣Ϊ�����жϵ������
 * ������: �����жϵ�ÿ��������(��о1c�����������Ϊ����)
 * ���ļ�: ÿ�������жϵ����
 *
 *************************************************************************/

#include <stdio.h>
#include <string.h>
#include "ls1c_clock.h"
#include "ls1c_gpio.h"



// ÿ���쳣��0x80�ֽڵĿռ�
#define EXCEPTION_HANDER_MAX_SIZE               (0x80)

// ��������ʱ���쳣����ڻ���ַ
// ��������ʱ��STATUS�Ĵ�����BEV=0��cpu����RAM�ռ���쳣���
// 0x80000000��ַ������TLBӳ�䣬������
#define EXCEPTION_RAM_EBASE                     (0x80000000)

// �쳣��������
#define EXCEPTION_MAX_NUM                       (32)

#define LS1C_INTREG_BASE 0xbfd01040


struct ls1c_intc_regs
{
	volatile unsigned int int_isr;
	volatile unsigned int int_en;
	volatile unsigned int int_set;
	volatile unsigned int int_clr;		/* offset 0x10*/
	volatile unsigned int int_pol;
   	volatile unsigned int int_edge;		/* offset 0 */
}; 


unsigned long exception_handlers[EXCEPTION_MAX_NUM];



// ���ʵ�ֵĺ���
extern void irq_disable(void);
extern void irq_enable(void);
extern void general_exception(void);
extern void handle_int(void);
extern void handle_reserved(void);


// ���������쳣�����Ĵ�����
// @offset �쳣��������ڵ�ƫ��
// @src_addr �쳣��������ڴ��������׵�ַ
void irq_set_exception_vector_handler(unsigned long offset, void *src_addr, unsigned long size)
{
    unsigned long dst_addr;   // �쳣���

    dst_addr = EXCEPTION_RAM_EBASE+offset;
    memcpy((void *)dst_addr, src_addr, size);

    // �Ȼ�дdcache��������icache
    // memcpy֮�������쳣��������ڵ�ָ��λ��dcache�У���Ҫ��д���ڴ棬
    // ��������Ӧicache�����Ϻ����жϷ���ʱ���Ż���ڴ����¼����´��뵽icache�������´������Ч��
    dcache_writeback_invalidate_range(dst_addr, dst_addr + size);
    icache_invalidate_range(dst_addr, dst_addr + size);

    return ;
}



// ����һ���쳣�Ĵ�����
// @n Э������0��cause�Ĵ�����[2,6]λ����ExcCode
// @addr �쳣���������׵�ַ
void irq_set_one_exception_handler(int n, void *addr)
{
    unsigned long handler = (unsigned long)addr;
    exception_handlers[n] = handler;

    return ;
}


// ��ʼ���ж�
void irq_init(void)
{
    int i;
    
    // ��ֹ�ж�
    irq_disable();

    // ��ʼ�����ٻ���
    cache_init();
    
    // ���������쳣�����Ĵ�����
    irq_set_exception_vector_handler(0x180, &general_exception, EXCEPTION_HANDER_MAX_SIZE);
    irq_set_exception_vector_handler(0x200, &general_exception, EXCEPTION_HANDER_MAX_SIZE);

    // ���ø����쳣�Ĵ�����
    for (i=0; i<EXCEPTION_MAX_NUM; i++)
    {
        irq_set_one_exception_handler(i, handle_reserved);
    }
    irq_set_one_exception_handler(0, handle_int);

    // �Ȼ�д����dcache������������icache
    dcache_writeback_invalidate_all();
    icache_invalidate_all();

    // ʹ���ж�
    irq_enable();

    return ;
}


// �жϷַ�����
void irq_dispatch(void)
{
/*
    unsigned int pending;

    pending = read_c0_cause() & read_c0_status() & ST0_IM;

    if (pending & CAUSEF_IP7)
    {
        sys_tick_handler();
    }
    else if (pending & CAUSEF_IP2)
    {
    }
    else if (pending & CAUSEF_IP3)
    {
    }
    else if (pending & CAUSEF_IP4)
    {
    }
    else if (pending & CAUSEF_IP5)
    {
    }
    else if (pending & CAUSEF_IP6)
    {
    }
    else
    {
        // �������������
    }
*/

    gpio_set(32, gpio_level_high);

    return ;
}



