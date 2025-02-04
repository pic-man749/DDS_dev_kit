/*
 * ST7032i.hpp
 *
 *  Created on: Feb 2, 2025
 *      Author: picman
 */

#ifndef DRIVER_ST7032I_ST7032I_HPP_
#define DRIVER_ST7032I_ST7032I_HPP_

#include "stm32l4xx_hal.h"

namespace ST7032i {

  constexpr uint8_t DEVICE_ADDR = 0x3E;
  constexpr uint8_t WRITE_ADDR = ( DEVICE_ADDR << 1 ) | 0x00;

  constexpr uint8_t COMMAND_BYTE = 0x00;
  constexpr uint8_t DATA_BYTE = 0x40;

  constexpr size_t LCD_BUFFER_SIZE = 16 * 2;

  class ST7032i {

    public:
      ST7032i(I2C_HandleTypeDef* hi2c);

      void Init();

      bool SetCursor(uint8_t row, uint8_t col);

      // bool SetContrast(uint8_t val);

      void Clear();

      bool sputs(const char *str);

      int sputsf(const char format_str[], ...);

    private:

      I2C_HandleTypeDef* _hi2c;

      bool WriteCommand(uint8_t cmd);

      bool WriteData(const uint8_t* data, size_t size);

  };

}


#endif /* DRIVER_ST7032I_ST7032I_HPP_ */
