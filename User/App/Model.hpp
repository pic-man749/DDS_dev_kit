/*
 * ModelData.hpp
 *
 *  Created on: Feb 8, 2025
 *      Author: picman
 */

#ifndef APP_MODEL_HPP_
#define APP_MODEL_HPP_

#include <stdint.h>
#include <memory>
#include "Driver/ST7032i/ST7032i.hpp"
#include "Driver/AD9833/AD9833.hpp"

namespace App {

  enum class Waveform {
      Sin,
      Triangle,
      Square
  };

  class LCD : public ST7032i_Driver::ST7032i {

    public:
      static LCD* Instance(void);

    private:
      LCD();
      LCD(const LCD&) = delete;
      LCD& operator=(const LCD&) = delete;
      LCD(LCD &&) = delete;
      LCD& operator=(LCD &&) = delete;

  };

  class AnalogOut : private AD9833_Driver::AD9833 {

    public:
      static AnalogOut* Instance(void);

      void SetFreqx10(uint32_t fx10);

      uint32_t GetFreqx10(void);

      Waveform GetWaveform(void);

      void SetOutput(bool f);

      void SetWaveform(Waveform wf);

    private:
      AnalogOut();
      AnalogOut(const AnalogOut&) = delete;
      AnalogOut& operator=(const AnalogOut&) = delete;
      AnalogOut(AnalogOut &&) = delete;
      AnalogOut& operator=(AnalogOut &&) = delete;

      const uint32_t MAX_FREQ_X10 = 99999999;
      uint32_t _freqx10;
      Waveform _waveform;

  };

}

#endif /* APP_MODEL_HPP_ */
