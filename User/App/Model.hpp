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

  /// @enum Waveform
  /// @brief waveform enum for Model layer.
  ///
  enum class Waveform : uint8_t {
      Sin = 0, ///< Sin
      Triangle,///< Triangle
      Square   ///< Square
  };
  const uint8_t WAVEFORM_ITEM_NUM = 3;

  /// @fn void ShowOutputStatus(void)
  /// @brief show analogOut output state on LCD
  ///
  void PutsOutputStatus(void);

  /// @class LCD
  /// @brief LCD class for Model layer.
  ///
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

  /// @class AnalogOut
  /// @brief Analog output for Model layer.
  ///
  class AnalogOut : private AD9833_Driver::AD9833 {

    public:
      /// @fn AnalogOut Instance*(void)
      /// @brief Get AnalogOut instance(singleton)
      ///
      /// @return instance of AnalogOut
      static AnalogOut* Instance(void);

      /// @fn void SetFreqx10(uint32_t)
      /// @brief Set output frequency.
      ///
      /// @param fx10 frequency * 10
      void SetFreqx10(uint32_t fx10);

      /// @fn uint32_t GetFreqx10(void)
      /// @brief Get now frequency.
      ///
      /// @return freq * 10
      uint32_t GetFreqx10(void);

      /// @fn Waveform GetWaveform(void)
      /// @brief Get now waveform.
      ///
      /// @return now waveform
      Waveform GetWaveform(void);

      /// @fn void SetOutput(bool)
      /// @brief Set output status
      ///
      /// @param f true enable
      /// @param f true disable
      void SetOutput(bool f);

      /// @fn void SetWaveform(Waveform)
      /// @brief Set waveform
      ///
      /// @param wf waveform
      void SetWaveform(Waveform wf);

      /// @fn bool GetOutputStatus(void)
      /// @brief Get now output status.
      ///
      /// @return true output enabled
      /// @return true output disabled
      bool GetOutputStatus(void);

    private:
      AnalogOut();
      AnalogOut(const AnalogOut&) = delete;
      AnalogOut& operator=(const AnalogOut&) = delete;
      AnalogOut(AnalogOut &&) = delete;
      AnalogOut& operator=(AnalogOut &&) = delete;

      const uint32_t MAX_FREQ_X10 = 99999999;
      uint32_t _freqx10;
      Waveform _waveform;
      bool _isOutput = false;

  };

}

#endif /* APP_MODEL_HPP_ */
