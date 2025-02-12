/*
 * ST7032i.cpp
 *
 *  Created on: Feb 2, 2025
 *      Author: picman
 */

#include "ST7032i.hpp"
#include <string.h>
#include <stdio.h>
#include <stdarg.h>

namespace ST7032i{

  /*
   * public
   */

  ST7032i::ST7032i(I2C_HandleTypeDef* hi2c){
    _hi2c = hi2c;
  }

  void ST7032i::Init(){
    // wait for boot
    HAL_Delay(40);

    // init register and send command
    _reg.functionSet = REG_FUNCTION_SET | BM_IF_DATABIT_84_BIT | BM_NUM_OF_LINE_21_BIT;
    _WriteCommand(_reg.functionSet);
    HAL_Delay(1);

    _SetInstractionTable1();

    _reg.instructionTable1.internalOSCFrequency = REG_INTERNAL_OSC_FREQ | 0b00000100;
    _WriteCommand(_reg.instructionTable1.internalOSCFrequency);
    HAL_Delay(1);

    _reg.instructionTable1.contrastSet = REG_CONTRAST_SET;
    _WriteCommand(_reg.instructionTable1.contrastSet);
    HAL_Delay(1);

    _reg.instructionTable1.powerICONControlContrastSet = REG_P_I_C_control | BM_BON_BIT;
    _reg.instructionTable1.powerICONControlContrastSet |= 0b00000010;  //  C5C4
    _WriteCommand(_reg.instructionTable1.powerICONControlContrastSet);
    HAL_Delay(1);

    _reg.instructionTable1.followerControl = REG_FOLLOWER_CONTROL;
    _reg.instructionTable1.followerControl |= BM_FON | 0b00000100;
    _WriteCommand(_reg.instructionTable1.followerControl);
    HAL_Delay(200);

    _SetInstractionTable0();

    // clear Display
    ClearDisp();

    _reg.displayOnOff = REG_DISPLAY_ONOFF;
    _reg.displayOnOff |= BM_ENTIRE_DISPLAY_BIT;
    _WriteCommand(_reg.displayOnOff);
    HAL_Delay(1);
  }

  bool ST7032i::SetCursorPos(uint8_t row, uint8_t col){
    if(row <= 2 && col <= 16){
      // LCD char address
      uint8_t cmd = 0x80 + col -1;
      if(row == 2 ) cmd += 0x40;

      _WriteCommand(cmd);
      HAL_Delay(1);
      return true;
    } else {
      return false;
    }
  }

  void ST7032i::SetContrast(uint8_t val){
    // set IS = 1
    _SetInstractionTable1();

    // validation
    if(val > MAX_CONTRAST){
      val = MAX_CONTRAST;
    }

    // send contrast value(lower)
    _reg.instructionTable1.contrastSet = REG_CONTRAST_SET | (BM_REG_CONTRAST_SET_DATA & val);
    _WriteCommand(_reg.instructionTable1.contrastSet);
    // upper
    _reg.instructionTable1.powerICONControlContrastSet &= ~BM_C5C4_DATA;
    _reg.instructionTable1.powerICONControlContrastSet |= (val >> 4);
    _WriteCommand(_reg.instructionTable1.powerICONControlContrastSet);

    // set IS = 0
    _SetInstractionTable0();
  }

  void ST7032i::SetCursorDisp(bool flg){
    if(flg){
      _reg.displayOnOff |= BM_CURSOR_ON_BIT;
    } else {
      _reg.displayOnOff &= ~BM_CURSOR_ON_BIT;
    }
    _WriteCommand(_reg.displayOnOff);
  }

  void ST7032i::SetCursorBlink(bool flg){
    if(flg){
      _reg.displayOnOff |= BM_CURSOR_BLINK_BIT;
    } else {
      _reg.displayOnOff &= ~BM_CURSOR_BLINK_BIT;
    }
    _WriteCommand(_reg.displayOnOff);
  }

  void ST7032i::SetDoubleHeightFont(bool flg){
    if(flg){
      _reg.functionSet |= BM_DOUBLE_HEIGHT_FONT;
      _reg.functionSet &= ~BM_NUM_OF_LINE_21_BIT;
    } else {
      _reg.functionSet &= ~BM_DOUBLE_HEIGHT_FONT;
      _reg.functionSet |= BM_NUM_OF_LINE_21_BIT;
    }
    _WriteCommand(_reg.functionSet);
  }

  void ST7032i::ClearDisp(){
    ST7032i::_WriteCommand(_reg.clearDisplay);
    SetCursorPos(1, 1);
  }

  bool ST7032i::sputs(const char *str){
    size_t size = strlen(str);
    if(strlen(str) > LCD_BUFFER_SIZE){
      return false;
    }

    _WriteData((uint8_t *)str, size);

    return true;
  }

  int ST7032i::sputsf(const char format_str[], ...){
    char tmp[LCD_BUFFER_SIZE + 1];  // +1 = \0

    va_list args;
    va_start( args, format_str );

    if(strlen(format_str) > LCD_BUFFER_SIZE){
      va_end(args);
      return -1;
    }

    int cnt = vsnprintf(tmp, sizeof(tmp), format_str, args);
    _WriteData((uint8_t *)tmp, cnt);

    return cnt;
  }

  /*
   * private
   */

  bool ST7032i::_SetInstractionTable1(){
    _reg.functionSet |= BM_INSTRUCTION_TABLE_BIT;
    bool res = _WriteCommand(_reg.functionSet);
    HAL_Delay(1);
    return res;
  }

  bool ST7032i::_SetInstractionTable0(){
    _reg.functionSet &= ~BM_INSTRUCTION_TABLE_BIT;
    bool res = _WriteCommand(_reg.functionSet);
    HAL_Delay(1);
    return res;
  }

  bool ST7032i::_WriteCommand(const uint8_t cmd){

    uint8_t buffer[2] = { COMMAND_BYTE, cmd};

    HAL_StatusTypeDef res = HAL_I2C_Master_Transmit(_hi2c, WRITE_ADDR, buffer, sizeof(buffer), 100);

    return (res == HAL_OK);

  }

  bool ST7032i::_WriteData(const uint8_t* data, size_t size){

    uint8_t buffer[sizeof(DATA_BYTE) + size];

    buffer[0] = DATA_BYTE;

    for(size_t i = 0; i < size; ++i ){
      buffer[i + 1] = data[i];
    }

    HAL_StatusTypeDef res = HAL_I2C_Master_Transmit(_hi2c, WRITE_ADDR, buffer, sizeof(buffer), 100);

    return (res == HAL_OK);

  }

}
