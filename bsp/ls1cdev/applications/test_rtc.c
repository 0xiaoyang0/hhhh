/*
file: test_rtc.c
����rtc������ ��finsh ������
1. test_rtc(0)   ����ʱ��Ϊ2018.1.1 01:01:01
2. test_rtc(1)   ��ʾ��ǰʱ��
 */

#include <rtthread.h>
#include <stdlib.h>  
#include "ls1c_regs.h"
#include "ls1c_rtc.h"

void test_rtc(int flag)  
{
	rt_device_t rtc_device;//rtc�豸

	time_t timestamp;
	struct tm *p_tm;
	/* ����ʱ��Ϊ2018.1.1 01:01:01*/
	struct tm tm_new ;
	tm_new.tm_year = 118;
	tm_new.tm_mon = 1 - 1;
	tm_new.tm_mday= 1;
	tm_new.tm_hour= 1;
	tm_new.tm_min= 1;
	tm_new.tm_sec= 1;
	timestamp = mktime(&tm_new); 
	
  	rtc_device = rt_device_find("rtc");
  
	if (rtc_device != RT_NULL)    
	{
	rt_device_init(rtc_device);	
	if(!flag)
		{

			rt_device_control(rtc_device,RT_DEVICE_CTRL_RTC_SET_TIME,  &timestamp);
		}
	else
		{
			rt_device_control(rtc_device,RT_DEVICE_CTRL_RTC_GET_TIME, &timestamp);
			p_tm = localtime(&timestamp);
				rt_kprintf("\r\nrtc time is %d.%d.%d - %d:%d:%d",p_tm->tm_year+1900, p_tm->tm_mon+1, p_tm->tm_mday, p_tm->tm_hour, p_tm->tm_min, p_tm->tm_sec);		
		}
	}
}  

void test_rtc_msh(int flag)  
{
	rt_device_t rtc_device;//rtc�豸

	time_t timestamp;
	struct tm *p_tm;
	/* ����ʱ��Ϊ2018.1.1 01:01:01*/
	struct tm tm_new ;
	tm_new.tm_year = 118;
	tm_new.tm_mon = 1 - 1;
	tm_new.tm_mday= 1;
	tm_new.tm_hour= 1;
	tm_new.tm_min= 1;
	tm_new.tm_sec= 1;
	timestamp = mktime(&tm_new); 
	
  	rtc_device = rt_device_find("rtc");
  
	if (rtc_device != RT_NULL)    
	{
	rt_device_init(rtc_device);	
	if(!flag)
		{

			rt_device_control(rtc_device,RT_DEVICE_CTRL_RTC_SET_TIME,  &timestamp);
		}
	else
		{
			rt_device_control(rtc_device,RT_DEVICE_CTRL_RTC_GET_TIME, &timestamp);
			p_tm = localtime(&timestamp);
				rt_kprintf("\r\nrtc time is %d.%d.%d - %d:%d:%d",p_tm->tm_year+1900, p_tm->tm_mon+1, p_tm->tm_mday, p_tm->tm_hour, p_tm->tm_min, p_tm->tm_sec);		
		}
	}
} 

FINSH_FUNCTION_EXPORT(test_rtc , test_rtc  e.g.test_rtc(1));

void test_mphaldelay(void)

{
  rt_kprintf("\r\nstart");
   mp_hal_delay_ms(1000);
  rt_kprintf("\r\nend");
}
 #include  <finsh.h> 
FINSH_FUNCTION_EXPORT(test_mphaldelay , test_mphaldelay  e.g.test_mphaldelay());
/* ������ msh �����б��� */
MSH_CMD_EXPORT(test_mphaldelay, test_mphaldelay);

