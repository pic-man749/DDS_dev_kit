/*
 * AD9833.hpp
 *
 *  Created on: Dec 1, 2024
 *      Author: picman
 */

#ifndef AD9833_HPP_
#define AD9833_HPP_

#include <stdint.h>
#include "stm32l4xx_hal.h"

namespace AD9833_Driver {

  // AD9833 Control register
  constexpr uint16_t CTRLREG_B28      = 0b1<<13;
  constexpr uint16_t CTRLREG_HLB      = 0b1<<12;
  constexpr uint16_t CTRLREG_FSELECT  = 0b1<<11;
  constexpr uint16_t CTRLREG_PSELECT  = 0b1<<10;
  constexpr uint16_t CTRLREG_D9       = 0b1<<9;   // reserved, must be 0
  constexpr uint16_t CTRLREG_RESET    = 0b1<<8;
  constexpr uint16_t CTRLREG_SLEEP1   = 0b1<<7;
  constexpr uint16_t CTRLREG_SLEEP12  = 0b1<<6;
  constexpr uint16_t CTRLREG_OPBITEN  = 0b1<<5;
  constexpr uint16_t CTRLREG_D4       = 0b1<<4;   // reserved, must be 0
  constexpr uint16_t CTRLREG_DIV2     = 0b1<<3;
  constexpr uint16_t CTRLREG_D2       = 0b1<<2;   // reserved, must be 0
  constexpr uint16_t CTRLREG_MODE     = 0b1<<1;
  constexpr uint16_t CTRLREG_D0       = 0b1<<0;   // reserved, must be 0

  // Functions bitset
  constexpr uint16_t FUNC_RESET             = CTRLREG_RESET;
  constexpr uint16_t FUNC_POWERDOWN_DAC     = CTRLREG_SLEEP12;
  constexpr uint16_t FUNC_POWERDOWN_INTCLK  = CTRLREG_SLEEP12;
  constexpr uint16_t VOUT_SIN               = 0;
  constexpr uint16_t VOUT_TRIANGLE          = CTRLREG_MODE;
  constexpr uint16_t VOUT_DACMSB            = CTRLREG_OPBITEN;
  constexpr uint16_t VOUT_DACMSB_DIV2       = CTRLREG_OPBITEN | CTRLREG_DIV2;

  // AD9833 Frequency and phase register(header only)
  constexpr uint16_t FPREG_FREQ0  = 0b01<<14;
  constexpr uint16_t FPREG_FREQ1  = 0b10<<14;
  constexpr uint16_t FPREG_PHASE0 = 0b1100<<12;
  constexpr uint16_t FPREG_PHASE1 = 0b1110<<12;

  // AD9833 data bit mask
  constexpr uint16_t FREQ_MASK  = 0x3FFF;
  constexpr uint16_t PHASE_MASK = 0x0FFF;

  enum class VoutType{
    SIN,
    TRIANGLE,
    DACMSB,
    DACMSB_DIV2,
  };

  class AD9833 {

    public:
      /// @brief constructor
      ///
      /// @param osc_freq frequency of OSC
      /// @param hspi
      /// @param GPIOx
      /// @param GPIO_Pin
      AD9833(uint32_t osc_freq,       // AD9833 osc frequency
            SPI_HandleTypeDef* hspi,  // SPI port
            GPIO_TypeDef* GPIOx,      // FSYNC PORT name
            uint16_t GPIO_Pin         // FSYNC PORT num
      );

      /// @brief set output signal status
      ///
      /// @param b true output status be enabled
      /// @param b false output status be disabled
      void setOutputStatus(bool b);

      /// @brief set output signal frequency
      ///
      /// @param freq
      void setFreq(double freq);

      /// @brief set output signal frequency
      ///
      /// @param freq
      void setFreq(uint32_t freq);

      /// @brief set output signal phase
      ///
      /// @param phase
      void setPhase(uint16_t phase);

      /// @brief set output signal type
      ///
      /// @param type type of output signal waveform
      /// @return true success
      /// @return false failed
      bool setVoutType(VoutType type);

    private:
      /// AD9833 osc frequency
      uint32_t _oscFreq;

      /// SPI instance
      SPI_HandleTypeDef* _spi;

      /// SPI CS PORT
      GPIO_TypeDef* _fsyncPort;

      /// SPI CS PORT num
      uint16_t _fsyncPortNum;

      /// ctrl register buffer
      uint16_t _ctrlRegBuffer;

      /// @brief send data by SPI
      ///
      /// @param payload data
      /// @return true success
      /// @return false failed
      bool _send(uint16_t payload);

      /// @brief set chip select L/H
      ///
      /// @param isSet true = set, false = reset
      void _setChipSelect(bool isSet);

      /// @brief set _ctrlRegBuffer bit flag
      ///
      /// @param f target bit
      void _setBitFlag(uint16_t b);

      /// @brief reset _ctrlRegBuffer bit flag
      ///
      /// @param f target bit
      void _resetBitFlag(uint16_t b);
  };

}

#endif /* AD9833_HPP_ */
