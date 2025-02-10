/*
 * AD9833.cpp
 *
 *  Created on: Dec 1, 2024
 *      Author: picman
 */
#include "AD9833.hpp"

namespace NS_AD9833 {

  AD9833::AD9833(uint32_t osc_freq, SPI_HandleTypeDef* hspi, GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin){
    _oscFreq = osc_freq;
    _spi = hspi;
    _fsyncPort = GPIOx;
    _fsyncPortNum = GPIO_Pin;

    // reset AD9833
    _ctrlRegBuffer = 0;
    _setBitFlag(CTRLREG_RESET);
    _send(_ctrlRegBuffer);

    // ctrl register buffer initialization
    _ctrlRegBuffer = 0;
    _setBitFlag(CTRLREG_B28);

    _send(_ctrlRegBuffer);

  }

  void AD9833::setOutputStatus(bool b){
    if(b){
      // disable reset flag
      _resetBitFlag(CTRLREG_RESET);
    }else{
      // enable reset flag
      _setBitFlag(CTRLREG_RESET);
    }

    _send(_ctrlRegBuffer);

  }

  bool AD9833::setVoutType(VoutType type){
    switch(type){
      case VoutType::SIN :
        _resetBitFlag(CTRLREG_OPBITEN);
        _resetBitFlag(CTRLREG_MODE);
        break;
      case VoutType::TRIANGLE :
        _resetBitFlag(CTRLREG_OPBITEN);
        _setBitFlag(CTRLREG_MODE);
        break;
      case VoutType::DACMSB :
        _setBitFlag(CTRLREG_OPBITEN);
        _resetBitFlag(CTRLREG_MODE);
        _resetBitFlag(CTRLREG_DIV2);
        break;
      case VoutType::DACMSB_DIV2 :
        _setBitFlag(CTRLREG_OPBITEN);
        _resetBitFlag(CTRLREG_MODE);
        _setBitFlag(CTRLREG_DIV2);
        break;
    }
    _send(_ctrlRegBuffer);
    return true;
  }

  void AD9833::setFreq(double freq){
    constexpr double RESOLUTION = 268435456;  // 2^28

    // calc FREQREG value
    double tmp = RESOLUTION / (double)_oscFreq;
    uint32_t freqreg = (uint32_t)(freq * tmp);

    uint16_t freqLSB = FREQ_MASK & (freqreg);
    uint16_t freqMSB = FREQ_MASK & (freqreg >> 14);

    // send value
    _send(_ctrlRegBuffer);
    _send(FPREG_FREQ0 | freqLSB);
    _send(FPREG_FREQ0 | freqMSB);
  }

  void AD9833::setFreq(uint32_t freq){
    setFreq((double)freq);
  }


  void AD9833::setPhase(uint16_t phase){

    uint16_t phaseReg = FPREG_PHASE0 | (PHASE_MASK & phase);
    _send(phaseReg);
  }

  bool AD9833::_send(uint16_t payload){

    _setChipSelect(1);

    // prepare data
    uint8_t data[2];
    data[0] = (uint8_t)(payload>>8);
    data[1] = (uint8_t)payload;

    HAL_SPI_Transmit(_spi, data, 2, 10);

    _setChipSelect(0);

    return true;
  }

  void AD9833::_setChipSelect(bool isSet){

    HAL_GPIO_WritePin(_fsyncPort, _fsyncPortNum, (GPIO_PinState)!isSet);

  }

  void AD9833::_setBitFlag(uint16_t b){
    _ctrlRegBuffer |= b;
  }

  void AD9833::_resetBitFlag(uint16_t b){
    _ctrlRegBuffer &= ~b;
  }

}
