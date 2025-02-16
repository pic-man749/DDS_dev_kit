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

  namespace {
    constexpr uint32_t AD9833_OSC_FREQ = 25000000;
    constexpr uint32_t AD9833_INITIAL_FREQ = 1000;

    constexpr uint8_t OUTPUT_STATUS_ROW = 1;
    constexpr uint8_t OUTPUT_STATUS_COL = 14;
  }

  void PutsOutputStatus(void) {
    auto lcd = LCD::Instance();
    auto ao = AnalogOut::Instance();

    lcd->SetCursorPos(OUTPUT_STATUS_ROW, OUTPUT_STATUS_COL);

    if(ao->GetOutputStatus()){
      lcd->sputs("ON ");
    } else {
      lcd->sputs("OFF");
    }

  }

  LCD::LCD() : ST7032i(&hi2c1) {
    this->Init();
  }

  LCD* LCD::Instance(void) {
    static LCD* lcd = new LCD();
    return lcd;
  }

  AnalogOut::AnalogOut(void) :
      AD9833(AD9833_OSC_FREQ, &hspi1, AD9833_FSYNC_GPIO_Port, AD9833_FSYNC_Pin) {
    // init model data
    _freqx10 = AD9833_INITIAL_FREQ * 10;
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
    _isOutput = f;
    this->setOutputStatus(f);
  }

  void AnalogOut::SetWaveform(Waveform wf) {
    _waveform = wf;

    switch(wf){
      case Waveform::Sin:
        this->setVoutType(AD9833_Driver::VoutType::SIN);
        break;
      case Waveform::Square:
        this->setVoutType(AD9833_Driver::VoutType::SIN);
        break;
      case Waveform::Triangle:
        this->setVoutType(AD9833_Driver::VoutType::SIN);
        break;
    }
  }

  bool AnalogOut::GetOutputStatus(void) {
    return _isOutput;
  }

}
