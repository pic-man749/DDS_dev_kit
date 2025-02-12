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

  std::unique_ptr<IScreen> ScreenFreq::StartScreen(){

    PrintLabelLine1();
    PrintLabelLine2();
    PrintFreq();

    return nullptr;
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
    const int MAX_FREQ_NUM_OF_DIGITS = 8;

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

}
