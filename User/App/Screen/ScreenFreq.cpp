/*
 * ScreenFreq.cpp
 *
 *  Created on: Feb 12, 2025
 *      Author: picman
 */
#include "ScreenFreq.hpp"
#include "App/Model.hpp"

#include <stdio.h>

namespace App {

  namespace {

    int intpow(int base, uint32_t exp) {
      int ret = 0;
      if(exp == 0){
        ret = 1;
      } else {
        ret = base;
        for(uint32_t i = 1; i < exp; ++i){
          ret *= base;
        }
      }
      return ret;
    }

  }

  ScreenFreq::ScreenFreq(void) {
    ;
  }

  std::unique_ptr<IScreen> ScreenFreq::StartScreen(){

    PrintLabelLine1();
    PrintLabelLine2();
    PrintFreq();

    auto lcd = LCD::Instance();
    lcd->SetCursorPos(2, Digit2Pos[_selectedDigit.GetNowPos()]);
    lcd->SetCursorDisp(true);

    return nullptr;
  }

  std::unique_ptr<IScreen> ScreenFreq::LeftButtonPushed(void) {
    uint8_t digit = _selectedDigit.MoveLeft();
    auto lcd = LCD::Instance();
    lcd->SetCursorPos(2, Digit2Pos[digit]);
    return nullptr;
  }

  std::unique_ptr<IScreen> ScreenFreq::RightButtonPushed(void) {
    uint8_t digit = _selectedDigit.MoveRight();
    auto lcd = LCD::Instance();
    lcd->SetCursorPos(2, Digit2Pos[digit]);
    return nullptr;
  }

  std::unique_ptr<IScreen> ScreenFreq::CenterButtonPushed(void) {
    return nullptr;
  }

  std::unique_ptr<IScreen> ScreenFreq::EncoderTurned(int step) {
    auto ao = AnalogOut::Instance();
    auto lcd = LCD::Instance();

    int diff = step * intpow(10, _selectedDigit.GetNowPos());

    uint32_t nowFreq = ao->GetFreqx10();
    uint32_t newFreq = 0;
    if((int)nowFreq + diff > 0) {
      newFreq = (uint32_t)((int)nowFreq + diff);
    }

    ao->SetFreqx10(newFreq);

    PrintFreq();

    uint8_t digit = _selectedDigit.GetNowPos();
    lcd->SetCursorPos(2, Digit2Pos[digit]);

    return nullptr;
  }

  void ScreenFreq::EndScreen(void) {
    auto lcd = LCD::Instance();
    lcd->SetCursorDisp(false);
    lcd->ClearDisp();
  }

  void ScreenFreq::PrintLabelLine1(void){

    static const char* STR_LINE_1 = "freq:";

    auto lcd = LCD::Instance();

    lcd->SetCursorPos(1, 1);
    lcd->sputs(STR_LINE_1);

  }

  void ScreenFreq::PrintLabelLine2(void){

    static const char* STR_LINE_2 = "[Hz]";

    auto lcd = LCD::Instance();

    lcd->SetCursorPos(2, 13);
    lcd->sputs(STR_LINE_2);
  }

  bool ScreenFreq::PrintFreq(void){

    const int BUFFER_SIZE = 16;

    auto lcd = LCD::Instance();
    auto ao = AnalogOut::Instance();

    uint32_t freq = ao->GetFreqx10();

    char buffer[BUFFER_SIZE] = {0};
    int size = snprintf(buffer, BUFFER_SIZE, "%08u", (int)freq);

    // too big freq value
    if(size != MAX_FREQ_NUM_OF_DIGITS){
      return false;
    }

    // copy and add "," and "."
    char lcdBuffer[BUFFER_SIZE] = {0};
    int lidx = 0;
    int idx = 0;
    lcdBuffer[lidx++] = ' ';
    lcdBuffer[lidx++] = buffer[idx++];
    lcdBuffer[lidx++] = ',';
    lcdBuffer[lidx++] = buffer[idx++];
    lcdBuffer[lidx++] = buffer[idx++];
    lcdBuffer[lidx++] = buffer[idx++];
    lcdBuffer[lidx++] = ',';
    lcdBuffer[lidx++] = buffer[idx++];
    lcdBuffer[lidx++] = buffer[idx++];
    lcdBuffer[lidx++] = buffer[idx++];
    lcdBuffer[lidx++] = '.';
    lcdBuffer[lidx++] = buffer[idx++];
    lcdBuffer[lidx++] = '\0';

    lcd->SetCursorPos(2,  1);
    lcd->sputs(lcdBuffer);

    return true;
  }

  void ScreenFreq::SetCursorPos(Direction d) {
    uint8_t digit = _selectedDigit.GetNowPos();
    switch (d) {
      case Direction::LEFT:
        digit = _selectedDigit.MoveLeft();
        break;
      case Direction::RIGHT:
        digit = _selectedDigit.MoveRight();
        break;
      default:
        ;
        break;
    }

    LCD::Instance()->SetCursorPos(2, Digit2Pos[digit]);

  }

}
