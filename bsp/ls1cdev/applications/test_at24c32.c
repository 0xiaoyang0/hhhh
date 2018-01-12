/*
 * File      : test_at24c32.c
����Ӳ��i2c2������ ��finsh ������ test_at24c32()
1. ÿ����һ��,������ַ1������,��ӡ AT24c32_I2C_BUS_NAME������ʹ�õ�i2c����
2. ������+1 ����д���ַ1�ļĴ���
 */

#include <rtthread.h>
#include <drivers/i2c.h>
#include "../drivers/drv_i2c.h"


#define AT24c32_I2C_BUS_NAME                ("i2c2")        // ע����i2c bus��ʼ�������е�bus name����һ��
struct rt_i2c_bus_device *at24c32_i2c_bus = RT_NULL;
int at24c32_addr = 0xA0 >> 1;               // ��ַǰ7λ


/*
 * ��ָ����ַ����һ���ֽ�
 * @read_addr ��ַ
 */
unsigned char at24c32_read_byte(unsigned char read_addr)
{
    struct rt_i2c_msg msgs[2];
    unsigned char data;
    unsigned char reg_addr[2];
	
	reg_addr[0] = 0;
	reg_addr[1] = read_addr;
	
    msgs[0].addr    = at24c32_addr;
    msgs[0].flags   = RT_I2C_WR;
    msgs[0].buf     = reg_addr;
    msgs[0].len     = 2;

    msgs[1].addr    = at24c32_addr;
    msgs[1].flags   = RT_I2C_RD;
    msgs[1].buf     = &data;
    msgs[1].len     = 1;
    rt_i2c_transfer(at24c32_i2c_bus, msgs, 2);

    return data;
}


/*
 * ��ָ����ַд��һ���ֽڵ�����
 * @write_addr ��ַ
 * @data ��д�������
 */
void at24c32_write_byte(unsigned char write_addr, unsigned char data)
{
    struct rt_i2c_msg msg[1] = {0};
    unsigned char buf[3] = {0};
    unsigned char reg_addr[2];
	
	buf[0] = 0;
	buf[1] = write_addr;
    buf[2] = data;
    
    msg[0].addr    = at24c32_addr;
    msg[0].flags   = RT_I2C_WR;
    msg[0].buf     = buf;
    msg[0].len     = 3;
    rt_i2c_transfer(at24c32_i2c_bus, msg, 1);

    return ;
}


// �����õ��̵߳����  
void test_at24c32(void )  
{
    unsigned char read_addr = 1;    // ��ַ
    unsigned char count = 0;        // ���ڼ����ı���

    // find�豸
    at24c32_i2c_bus = (struct rt_i2c_bus_device *)rt_device_find(AT24c32_I2C_BUS_NAME);
    if (RT_NULL == at24c32_i2c_bus)
    {
        rt_kprintf("[%s] no i2c device -- am2320!\n", __FUNCTION__);
        return ;
    }

    // ��
    count = at24c32_read_byte(read_addr);
    rt_kprintf("[%s] last's count=%u\n", __FUNCTION__, count);

    // ��һ��Ȼ��д
    count++;
    at24c32_write_byte(read_addr, count);
    rt_thread_delay(6);     // һ��Ҫ��ʱ5ms����

    // ��
    count = at24c32_read_byte(read_addr);
    rt_kprintf("[%s] current count=%d\n", __FUNCTION__, count);
    

}  

 #include  <finsh.h>
 FINSH_FUNCTION_EXPORT(test_at24c32, test_at24c32  e.g.test_at24c32());
