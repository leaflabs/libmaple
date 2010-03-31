void NMIException(void) {
}
void HardFaultException(void) {
  while (1) {
  }
}

void MemManageException(void) {
  while (1) {
  }
}

void BusFaultException(void) {
  while (1) {
  }
}

void UsageFaultException(void) {
  while (1) {
  }
}

#if 0
void DebugMonitor(void) {
}

void SVCHandler(void) {
}

void PendSVC(void) {
}

void WWDG_IRQHandler(void) {
}

void PVD_IRQHandler(void) {
}

void TAMPER_IRQHandler(void) {
}

void RTC_IRQHandler(void) {
}

void FLASH_IRQHandler(void) {
}

void RCC_IRQHandler(void) {
}

void DMA1_Channel1_IRQHandler(void) {
}

void DMA1_Channel2_IRQHandler(void) {
}

void DMA1_Channel3_IRQHandler(void) {
}

void DMA1_Channel4_IRQHandler(void) {
}

void DMA1_Channel5_IRQHandler(void) {
}

void DMA1_Channel6_IRQHandler(void) {
}

void DMA1_Channel7_IRQHandler(void) {
}

void ADC1_2_IRQHandler(void) {
}

void USB_HP_CAN_TX_IRQHandler(void) {
}

void USB_LP_CAN_RX0_IRQHandler(void) {
}

void CAN_RX1_IRQHandler(void) {
}

void CAN_SCE_IRQHandler(void) {
}

void TIM1_BRK_IRQHandler(void) {
}

void TIM1_UP_IRQHandler(void) {
    while(1) {
    }
}

void TIM1_TRG_COM_IRQHandler(void) {
}

void TIM1_CC_IRQHandler(void) {
    while(1)
        ;
}

void TIM2_IRQHandler(void) {
}

void TIM3_IRQHandler(void) {
}

void TIM4_IRQHandler(void) {
}

void I2C1_EV_IRQHandler(void) {
}

void I2C1_ER_IRQHandler(void) {
}

void I2C2_EV_IRQHandler(void) {
}

void I2C2_ER_IRQHandler(void) {
}

void SPI1_IRQHandler(void) {
}

void SPI2_IRQHandler(void) {
}

void USART1_IRQHandler(void) {
#if 0
  if(USART_GetITStatus(USART1, USART_IT_RXNE) != RESET)
  {
    /* Read one byte from the receive data register */
    RxBuffer[RxCounter++] = (USART_ReceiveData(USART1) & 0x7F);         

    if(RxCounter == NbrOfDataToRead)
    {
      /* Disable the USART Receive interrupt */
      USART_ITConfig(USART1, USART_IT_RXNE, DISABLE);
    }
  }

  if(USART_GetITStatus(USART1, USART_IT_TXE) != RESET)
  {   
    /* Write one byte to the transmit data register */
    USART_SendData(USART1, TxBuffer[TxCounter++]);                    

    if(TxCounter == NbrOfDataToTransfer)
    {
      /* Disable the USART1 Transmit interrupt */
      USART_ITConfig(USART1, USART_IT_TXE, DISABLE);
    }    
  }
#endif
}

void USART2_IRQHandler(void) {
#if 0
  if(USART_GetITStatus(USART2, USART_IT_RXNE) != RESET)
  {
      /* Echo the character back  */
      RxBuffer[0] = (USART_ReceiveData(USART2) & 0x7F);         
      USART_SendData(USART2, RxBuffer[0]);
  //  /* Read one byte from the receive data register */
  //  RxBuffer[RxCounter++] = (USART_ReceiveData(USART2) & 0x7F);         

  //  if(RxCounter == NbrOfDataToRead)
  //  {
  //    /* Disable the USART Receive interrupt */
  //    USART_ITConfig(USART2, USART_IT_RXNE, DISABLE);
  //  }
  }

#endif
 
#if 0
  if(USART_GetITStatus(USART2, USART_IT_TXE) != RESET)
  {   
    /* Write one byte to the transmit data register */
    USART_SendData(USART2, 'Y');                    
    TxCounter++;
//    USART_SendData(USART2, TxBuffer[TxCounter++]);                    

    if(TxCounter == NbrOfDataToTransfer) {
      /* Disable the USART1 Transmit interrupt */
      USART_ITConfig(USART2, USART_IT_TXE, DISABLE);
    }
  }
#endif
}

void USART3_IRQHandler(void) {
}

void RTCAlarm_IRQHandler(void) {
}

void USBWakeUp_IRQHandler(void) {
}

void TIM8_BRK_IRQHandler(void) {
}

void TIM8_UP_IRQHandler(void) {
}

void TIM8_TRG_COM_IRQHandler(void) {
}

void TIM8_CC_IRQHandler(void) {
}

void ADC3_IRQHandler(void) {
}

void FSMC_IRQHandler(void) {
}

void SDIO_IRQHandler(void) {
}

void TIM5_IRQHandler(void) {
}

void SPI3_IRQHandler(void) {
}

void UART4_IRQHandler(void) {
}

void UART5_IRQHandler(void) {
}

void TIM6_IRQHandler(void) {
}

void TIM7_IRQHandler(void) {
}

void DMA2_Channel1_IRQHandler(void) {
}

void DMA2_Channel2_IRQHandler(void) {
}

void DMA2_Channel3_IRQHandler(void) {
}

void DMA2_Channel4_5_IRQHandler(void) {
}
#endif
