/*
 * Model.cpp
 *
 *  Created on: Feb 11, 2025
 *      Author: picman
 */
#include "Model.hpp"
#include "i2c.h"
#include "spi.h"

namespace App {

  LCD::LCD() : ST7032i(&hi2c1) {
    this->Init();
  }

  LCD* LCD::Instance(void) {
    static LCD* lcd = new LCD();
    return lcd;
  }

  AnalogOut::AnalogOut(void) :
      AD9833(25000000, &hspi1, AD9833_FSYNC_GPIO_Port, AD9833_FSYNC_Pin) {
    // init model data
    _freqx10 = 1000 * 10;
    _waveform = Waveform::Sin;
  }

  AnalogOut* AnalogOut::Instance(void) {
    static AnalogOut* analogOut = new AnalogOut();
    return analogOut;
  }

  void AnalogOut::SetFreqx10(uint32_t fx10) {
    if(fx10 > MAX_FREQ_X10){
      return; // do not change
    }
    this->_freqx10 = fx10;
    this->setFreq((double)fx10 / 10.0);
  }

  uint32_t AnalogOut::GetFreqx10(void) {
    return _freqx10;
  }

  Waveform AnalogOut::GetWaveform(void) {
    return _waveform;
  }

  void AnalogOut::SetOutput(bool f) {
    this->setOutputStatus(f);
  }

  void AnalogOut::SetWaveform(Waveform wf) {
    _waveform = wf;

    switch(wf){
      case Waveform::Sin:
        this->setVoutType(NS_AD9833::VoutType::SIN);
        break;
      case Waveform::Square:
        this->setVoutType(NS_AD9833::VoutType::SIN);
        break;
      case Waveform::Triangle:
        this->setVoutType(NS_AD9833::VoutType::SIN);
        break;
    }
  }

}
