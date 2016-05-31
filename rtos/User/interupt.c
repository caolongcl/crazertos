#include "interupt.h"


/*-------------------------------------------------------------------------------------------*/
/* 中断初始化 */
void nvic_init(uint8_t NVIC_IRQChannel,uint8_t NVIC_IRQChannelPreemptionPriority,\
               uint8_t NVIC_IRQChannelSubPriority,FunctionalState NVIC_IRQChannelCmd)
{
  uint32_t tmppriority = 0x00, tmppre = 0x00, tmpsub = 0x0F;
    
  if (NVIC_IRQChannelCmd != DISABLE){
    /* Compute the Corresponding IRQ Priority --------------------------------*/    
    tmppriority = (0x700 - ((SCB->AIRCR) & (uint32_t)0x700))>> 0x08;
    tmppre = (0x4 - tmppriority);
    tmpsub = tmpsub >> tmppriority;

    tmppriority = (uint32_t)NVIC_IRQChannelPreemptionPriority << tmppre;
    tmppriority |=  NVIC_IRQChannelSubPriority & tmpsub;
    tmppriority = tmppriority << 0x04;
        
    NVIC->IP[NVIC_IRQChannel] = tmppriority;
    
    /* Enable the Selected IRQ Channels --------------------------------------*/
    NVIC->ISER[NVIC_IRQChannel >> 0x05] =
      (uint32_t)0x01 << (NVIC_IRQChannel & (uint8_t)0x1F);
  }
  else{
    /* Disable the Selected IRQ Channels -------------------------------------*/
    NVIC->ICER[NVIC_IRQChannel >> 0x05] =
      (uint32_t)0x01 << (NVIC_IRQChannel & (uint8_t)0x1F);
  }
}

/*------------------------------------------------------------------------------------------*/
/* 获取中断状态*/
ITStatus uart_get_it_status(USART_TypeDef* USARTx, uint16_t USART_IT)
{
  uint32_t bitpos = 0x00, itmask = 0x00, usartreg = 0x00;

  /* Get the USART register index */
  usartreg = (((uint8_t)USART_IT) >> 0x05);
  /* Get the interrupt position */
  itmask = USART_IT & IT_Mask;
  itmask = (uint32_t)0x01 << itmask;
  
  if (usartreg == 0x01){ /* The IT  is in CR1 register */
    itmask &= USARTx->CR1;
  }
  else if (usartreg == 0x02){ /* The IT  is in CR2 register */
    itmask &= USARTx->CR2;
  }
  else{ /* The IT  is in CR3 register */
    itmask &= USARTx->CR3;
  }
  
  bitpos = USART_IT >> 0x08;
  bitpos = (uint32_t)0x01 << bitpos;
  bitpos &= USARTx->SR;
  if ((itmask != (uint16_t)RESET)&&(bitpos != (uint16_t)RESET)){
    return SET;
  }
  else{
    return RESET;
  }
}

/*------------------------------------------------------------------------------------------*/
/* 中断函数 */
void USART1_IRQHandler(void)
{
    if(uart_get_it_status(USART1, USART_IT_TXE) != RESET){   
    }
    else if(uart_get_it_status(USART1, USART_IT_RXNE) != RESET){
	}
}

