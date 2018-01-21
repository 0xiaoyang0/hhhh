/*
 * File      : ls1c_can.c
 * This file is part of RT-Thread RTOS
 * COPYRIGHT (C) 2006 - 2018, RT-Thread Development Team
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License along
 *  with this program; if not, write to the Free Software Foundation, Inc.,
 *  51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 *
 * Change Logs:
 * Date           Author       Notes
 * 2018-01-06     sundm75       first version
 */

#include "ls1c.h"
#include "ls1c_public.h"
#include "ls1c_can.h"

static unsigned char  set_reset_mode(CAN_TypeDef* CANx)
{
  unsigned char status;
  int i;

  /*��鸴λ��־*/
  status = CANx->MOD;

  /* �ر��ж� */
  CANx->IER = 0x00;
  
  for (i = 0; i < 100; i++)
  {
    if((status & CAN_Mode_RM) == CAN_Mode_RM)
        return 1;
  
    /* ���ø�λ*/
    CANx->MOD |=  ((unsigned char)CAN_Mode_RM);
  
    /*��ʱ*/
    delay_us(10);

    /*��鸴λ��־*/
    status = CANx->MOD;
  }
  rt_kprintf("\r\nSetting SJA1000 into reset mode failed!\r\n");
  return 0;  
}

static unsigned char  set_normal_mode(CAN_TypeDef* CANx)
{
  unsigned char status;
  int i;

  /*��鸴λ��־*/
  status = CANx->MOD;
  
  for (i = 0; i < 100; i++)
  {
    if((status & CAN_Mode_RM) != CAN_Mode_RM)
    {
      /*�������ж� �����ߴ����жϲ�����*/
      CANx->IER |= (~(unsigned char)CAN_IR_BEI);	
      return 1;
    }
    /* ������������ģʽ*/
    CANx->MOD &= (~(unsigned char) CAN_Mode_RM); 
    /*��ʱ*/
    delay_us(10); 
    status = CANx->MOD;	
  }
  rt_kprintf("\r\nSetting SJA1000 into normal mode failed!\r\n");
  return 0;
}

static unsigned char  set_start(CAN_TypeDef* CANx)
{
  /*��λTX���������*/
  CANx->TXERR = 0;
  /*��λRX���������*/
  CANx->RXERR = 0;
  /*ʱ�ӷ�Ƶ�Ĵ���: PeliCANģʽ; CBP=1,��ֹ����Ƚ���, RX0����*/
  CANx->CDR = 0xC0;	
 
  return  set_normal_mode(CANx);  
}

 unsigned char CAN_Init(CAN_TypeDef* CANx, CAN_InitTypeDef* CAN_InitStruct)
{
  unsigned char InitStatus = CAN_InitStatus_Failed;
  unsigned long wait_ack = 0x00000000;
  unsigned char status;

  status = CANx->MOD;
  if( status == 0xFF)
  {
    rt_kprintf("\n Probe can0 failed \r\n");  	   
    return CAN_InitStatus_Failed;
  }

   /* ���븴λģʽ */
  InitStatus = set_reset_mode(CANx);
  
  if((CAN_InitStruct->CAN_Mode & CAN_Mode_SM) == CAN_Mode_SM) 
  {
    /* ˯��ģʽ 1: ˯�� 0: ����*/
    CANx->MOD|= (unsigned char)CAN_Mode_SM;    
  }
  else if((CAN_InitStruct->CAN_Mode & CAN_Mode_LOM) == CAN_Mode_LOM) 
  {
    /*ֻ��ģʽ 1:ֻ��  0:���� */
    CANx->MOD|= (unsigned char)CAN_Mode_LOM;    
  }
  else if((CAN_InitStruct->CAN_Mode & CAN_Mode_AFM) == CAN_Mode_AFM) 
  {
    /*���˲�ģʽ 1:�� 0: ˫*/
    CANx->MOD |= (unsigned char)CAN_Mode_AFM;    
  }
  else if((CAN_InitStruct->CAN_Mode & CAN_Mode_STM) == CAN_Mode_STM) 
  {
    /*�Լ��ģʽ 1:�Լ��  0:����  */
    CANx->MOD |= (unsigned char)CAN_Mode_STM;    
  }
  
  /* ����ʱ��Ƶ�� */
  CANx->BTR0 = (( unsigned char )( unsigned char )CAN_InitStruct->CAN_Prescaler -1) | \
               (unsigned char)CAN_InitStruct->CAN_SJW << 6;
  
  CANx->BTR1 = ((unsigned char)CAN_InitStruct->CAN_BS1) | \
               ((unsigned char)CAN_InitStruct->CAN_BS2 << 4) | \
               ((unsigned char)CAN_InitStruct->CAN_SJW<<7);

   /* ���빤��ģʽ */
  set_start(CANx);    
  
  /* ���س�ʼ����� */
  return InitStatus;
}

 void CAN_FilterInit(CAN_TypeDef* CANx,  CAN_FilterInitTypeDef* CAN_FilterInitStruct)
{
   /* ���븴λģʽ */
    set_reset_mode(CANx);

    CANx->IDE_RTR_DLC = CAN_FilterInitStruct->CAN_FilterId0;
    CANx->ID[0] = CAN_FilterInitStruct->CAN_FilterId1;
    CANx->ID[1] = CAN_FilterInitStruct->CAN_FilterId2;
    CANx->ID[2] = CAN_FilterInitStruct->CAN_FilterId3;
    CANx->ID[3] = CAN_FilterInitStruct->CAN_FilterMaskId0;
    CANx->BUF[0]= CAN_FilterInitStruct->CAN_FilterMaskId1;
    CANx->BUF[1]= CAN_FilterInitStruct->CAN_FilterMaskId2;
    CANx->BUF[2]= CAN_FilterInitStruct->CAN_FilterMaskId3;

   /* ���빤��ģʽ */
    set_start(CANx);
}

unsigned char  CAN_Transmit(CAN_TypeDef* CANx, CanTxMsg* TxMessage)
{
    int i;
    if (TxMessage->IDE == CAN_Id_Extended)
    {
        CANx->ID[0]= TxMessage ->ExtId>> 21;
        CANx->ID[1]= TxMessage ->ExtId>> 13;
        CANx->ID[2]= TxMessage ->ExtId>> 5;
        CANx->ID[3]= TxMessage ->ExtId<<3;
        CANx->IDE_RTR_DLC= (TxMessage ->IDE & 0x01) << 7 |\
            (TxMessage ->RTR & 0x01) << 6 |\
            (TxMessage ->DLC & 0x0F);
        for( i=0;i<TxMessage ->DLC; i++)
        {
           CANx->BUF[i]= TxMessage->Data[i];
        }
    }
    else if (TxMessage->IDE ==CAN_Id_Standard)
    {
        CANx->ID[0]= TxMessage ->StdId>> 3;
        CANx->ID[1]= TxMessage ->StdId<< 5;
        CANx->IDE_RTR_DLC= (TxMessage ->IDE & 0x01) << 7 |\
            (TxMessage ->RTR & 0x01) << 6 |\
            (TxMessage ->DLC & 0x0F);
        CANx->ID[2]= TxMessage ->Data[0];
        CANx->ID[3]= TxMessage ->Data[1];
        for( i=0;i<TxMessage ->DLC-2; i++)
        {
           CANx->BUF[i]= TxMessage->Data[i+2];
        }
    }
    CANx->CMR = CAN_CMR_TR ;
}

void CAN_Receive(CAN_TypeDef* CANx,  CanRxMsg* RxMessage)
{
  /* ��ȡ IDE */
  RxMessage->IDE = (CANx->IDE_RTR_DLC  & 0x80)>>7;
  /* ��ȡ RTR */
  RxMessage->RTR = (CANx->IDE_RTR_DLC  & 0x40)>>4;
  /* ��ȡ DLC */
  RxMessage->DLC= (CANx->IDE_RTR_DLC  & 0x0F);
  if (RxMessage->IDE == CAN_Id_Standard)
  {
    RxMessage->StdId = CANx->ID[0]<<3 |CANx->ID[1]>>5 ;
    /* ��ȡ���� */
    RxMessage->Data[0] = (unsigned char)CANx->ID[2];
    RxMessage->Data[1] = (unsigned char)CANx->ID[3];
    RxMessage->Data[2] = (unsigned char)CANx->BUF[0];
    RxMessage->Data[3] = (unsigned char)CANx->BUF[1];
    RxMessage->Data[4] = (unsigned char)CANx->BUF[2];
    RxMessage->Data[5] = (unsigned char)CANx->BUF[3];
    RxMessage->Data[6] = (unsigned char)CANx->BUF[4];
    RxMessage->Data[7] = (unsigned char)CANx->BUF[5];
  }
  else  if (RxMessage->IDE == CAN_Id_Extended)
  {
    RxMessage->ExtId= CANx->ID[0]<<21 |CANx->ID[1]<<13|CANx->ID[2]<<5|CANx->ID[3]>>3 ;
    /* ��ȡ���� */
    RxMessage->Data[0] = (unsigned char)CANx->BUF[0];
    RxMessage->Data[1] = (unsigned char)CANx->BUF[1];
    RxMessage->Data[2] = (unsigned char)CANx->BUF[2];
    RxMessage->Data[3] = (unsigned char)CANx->BUF[3];
    RxMessage->Data[4] = (unsigned char)CANx->BUF[4];
    RxMessage->Data[5] = (unsigned char)CANx->BUF[5];
    RxMessage->Data[6] = (unsigned char)CANx->BUF[6];
    RxMessage->Data[7] = (unsigned char)CANx->BUF[7];
  }  
}


