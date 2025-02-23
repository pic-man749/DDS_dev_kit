/*
 * ST7032i.hpp
 *
 *  Created on: Feb 2, 2025
 *      Author: picman
 */

#ifndef DRIVER_ST7032I_ST7032I_HPP_
#define DRIVER_ST7032I_ST7032I_HPP_

#include "stm32l4xx_hal.h"

namespace ST7032i_Driver {

  constexpr uint8_t DEVICE_ADDR = 0x3E;
  constexpr uint8_t WRITE_ADDR = ( DEVICE_ADDR << 1 ) | 0x00;

  constexpr uint8_t COMMAND_BYTE = 0x00;
  constexpr uint8_t DATA_BYTE = 0x40;

  constexpr size_t LCD_BUFFER_SIZE = 16 * 2;

  /***** Instruction REGISTER *****/
  // Clear Display
  const uint8_t REG_CLEAR_DISPLAY_SET     = 0b00000001;

  // Return Home
  const uint8_t REG_RETURN_HOME           = 0b00000010;

  // Entry Mode Set
  const uint8_t REG_ENTRY_MODE            = 0b00000100;

  // Display ON/OFF
  const uint8_t REG_DISPLAY_ONOFF         = 0b00001000;
  const uint8_t BM_ENTIRE_DISPLAY_BIT     = 0b00000100;
  const uint8_t BM_CURSOR_ON_BIT          = 0b00000010;
  const uint8_t BM_CURSOR_BLINK_BIT       = 0b00000001;

  // Function Set
  const uint8_t REG_FUNCTION_SET          = 0b00100000;
  const uint8_t BM_IF_DATABIT_84_BIT      = 0b00010000;
  const uint8_t BM_NUM_OF_LINE_21_BIT     = 0b00001000;
  const uint8_t BM_DOUBLE_HEIGHT_FONT     = 0b00000100;
  const uint8_t BM_INSTRUCTION_TABLE_BIT  = 0b00000001;

  // Set DDRAM address
  const uint8_t REG_SET_DDRAM_ADDRESS     = 0b10000000;
  const uint8_t BM_DDRAM_ADDR_DATA        = 0b01111111;

  /* Instruction table 0 */
  // Cursor or Display Shift
  const uint8_t REG_CURSOR_OR_DISP_SHIFT  = 0b00010000;
  const uint8_t BM_SC_BIT                 = 0b00001000;
  const uint8_t BM_RL_BIT                 = 0b00000100;

  // Set CGRAM
  const uint8_t REG_SET_CGRAM             = 0b01000000;
  const uint8_t BM_CGRAM_ADDR             = 0b00111111;

  /* Instruction table 1 */
  // Internal OSC frequency
  const uint8_t REG_INTERNAL_OSC_FREQ     = 0b00010000;

  // Set ICON address
  const uint8_t REG_SET_ICON_ADDRESS      = 0b00010000;
  const uint8_t BM_BS                     = 0b00001000;
  const uint8_t BM_ADJUST_OSC_DATA        = 0b00000111;

  // Power/ICON control/Contrast set
  const uint8_t REG_P_I_C_control         = 0b01010000;
  const uint8_t BM_ION_BIT                = 0b00001000;
  const uint8_t BM_BON_BIT                = 0b00000100;
  const uint8_t BM_C5C4_DATA              = 0b00000011;

  // Follower control
  const uint8_t REG_FOLLOWER_CONTROL      = 0b01100000;
  const uint8_t BM_FON                    = 0b00001000;
  const uint8_t BM_RAB_DATA               = 0b00000111;

  // Contrast set
  const uint8_t REG_CONTRAST_SET          = 0b01110000;
  const uint8_t BM_REG_CONTRAST_SET_DATA  = 0b00001111;
  const uint8_t MAX_CONTRAST              = 0b00111111;

  class ST7032i {

    public:
      ST7032i(I2C_HandleTypeDef* hi2c);

      void Init();

      bool SetCursorPos(uint8_t row, uint8_t col);

      void SetContrast(uint8_t val);

      void SetCursorDisp(bool flg);

      void SetCursorBlink(bool flg);

      void SetDoubleHeightFont(bool flg);

      void ClearDisp();

      bool sputs(const char *str);

      int sputsf(const char format_str[], ...);

    private:

      I2C_HandleTypeDef* _hi2c;

      bool _SetInstractionTable1();

      bool _SetInstractionTable0();

      bool _WriteCommand(uint8_t cmd);

      bool _WriteData(const uint8_t* data, size_t size);

      struct InstructionTable0 {
          uint8_t cursorOrDisplayShift  = REG_CURSOR_OR_DISP_SHIFT;
          uint8_t setCGRAM              = REG_SET_CGRAM;
      };
      struct InstructionTable1 {
          uint8_t internalOSCFrequency        = REG_INTERNAL_OSC_FREQ;
          uint8_t setICONAddress              = REG_SET_ICON_ADDRESS;
          uint8_t powerICONControlContrastSet = REG_P_I_C_control;
          uint8_t followerControl             = REG_FOLLOWER_CONTROL;
          uint8_t contrastSet                 = REG_CONTRAST_SET;
      };
      struct RegisterST7032i{
          const uint8_t clearDisplay  = REG_CLEAR_DISPLAY_SET;
          uint8_t returnHome          = REG_RETURN_HOME;
          uint8_t entryModeSet        = REG_ENTRY_MODE;
          uint8_t displayOnOff        = REG_DISPLAY_ONOFF;
          uint8_t functionSet         = REG_FUNCTION_SET;
          uint8_t setDDRAMAddress     = REG_SET_DDRAM_ADDRESS;
          InstructionTable0 instructionTable0;
          InstructionTable1 instructionTable1;
      };

      RegisterST7032i _reg;
  };

}


#endif /* DRIVER_ST7032I_ST7032I_HPP_ */
