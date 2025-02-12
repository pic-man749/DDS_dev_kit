/*
 * ScreenFreq.cpp
 *
 *  Created on: Feb 12, 2025
 *      Author: picman
 */
#include "ScreenFreq.hpp"
#include "App/Model.hpp"

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

  void ScreenFreq::PrintFreq(void){

    auto lcd = LCD::Instance();
    auto ao = AnalogOut::Instance();

    double freq = ao->GetFreqx10() * 0.1f;

    lcd->SetCursorPos(2, 1);
    lcd->sputsf(" %'08.1d", freq);

  }

}
