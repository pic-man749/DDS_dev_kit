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

  ST7032i::ST7032i(I2C_HandleTypeDef* hi2c){
    _hi2c = hi2c;
  }

  void ST7032i::Init(){
    // wait for boot
    HAL_Delay(40);
    // init
    WriteCommand(0x38);
    HAL_Delay(1);
    WriteCommand(0x39);
    HAL_Delay(1);
    WriteCommand(0x14);
    HAL_Delay(1);
    WriteCommand(0x73);
    HAL_Delay(1);
    WriteCommand(0x56);
    HAL_Delay(1);
    WriteCommand(0x6C);
    HAL_Delay(200);
    WriteCommand(0x38);
    HAL_Delay(1);
    WriteCommand(0x01);
    HAL_Delay(1);
    WriteCommand(0x0C);
    HAL_Delay(1);

  }

  bool ST7032i::SetCursor(uint8_t row, uint8_t col){
    if(row <= 2 && col <= 16){
      // LCD char address
      uint8_t cmd = 0x80 + col -1;
      if(row == 2 ) cmd += 0x40;

      WriteCommand(cmd);
      HAL_Delay(1);
      return true;
    } else {
      return false;
    }
  }

//  void ST7032i::SetContrast(uint8_t val){
//    // set IS = 1
//    WriteCommand(0x39);
//    HAL_Delay(1);
//
//    // validation
//    val = val & 0b00111111;
//
//    // send contrast value(lower)
//    WriteCommand(0b01110000 | (0b00001111 & val));
//    // upper
//    WriteCommand(0b0101 | (val >> 4));
//
//    // set IS = 0
//    WriteCommand(0x38);
//    HAL_Delay(1);
//  }

  void ST7032i::Clear(){
    ST7032i::WriteCommand(0x01);
    SetCursor(1, 1);
  }

  bool ST7032i::sputs(const char *str){
    size_t size = strlen(str);
    if(strlen(str) > LCD_BUFFER_SIZE){
      return false;
    }

    WriteData((uint8_t *)str, size);

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
    WriteData((uint8_t *)tmp, cnt);

    return cnt;
  }

  bool ST7032i::WriteCommand(const uint8_t cmd){

    uint8_t buffer[2] = { COMMAND_BYTE, cmd};

    HAL_StatusTypeDef res = HAL_I2C_Master_Transmit(_hi2c, WRITE_ADDR, buffer, sizeof(buffer), 100);

    return (res == HAL_OK);

  }

  bool ST7032i::WriteData(const uint8_t* data, size_t size){

    uint8_t buffer[sizeof(DATA_BYTE) + size];

    buffer[0] = DATA_BYTE;

    for(size_t i = 0; i < size; ++i ){
      buffer[i + 1] = data[i];
    }

    HAL_StatusTypeDef res = HAL_I2C_Master_Transmit(_hi2c, WRITE_ADDR, buffer, sizeof(buffer), 100);

    return (res == HAL_OK);

  }



}
