/*
 * ScreenWaveform.cpp
 *
 *  Created on: Feb 23, 2025
 *      Author: picman
 */
#include "ScreenWaveform.hpp"
#include "ScreenFreq.hpp"

namespace App {

  std::unique_ptr<IScreen> ScreenWaveform::StartScreen(){

    _waveform = AnalogOut::Instance()->GetWaveform();
    PrintLabelLine1();
    PrintWaveform();
    App::PutsOutputStatus();

    return nullptr;
  }

  std::unique_ptr<IScreen> ScreenWaveform::LeftButtonPushed(void) {
    // -1

    auto ao = AnalogOut::Instance();
    uint8_t nowWF = static_cast<uint8_t>(_waveform);

    if(nowWF == 0){
      _waveform = static_cast<App::Waveform>(WAVEFORM_ITEM_NUM - 1);
      ao->SetWaveform(_waveform);
    } else {
      _waveform = static_cast<App::Waveform>(nowWF - 1);
      ao->SetWaveform(_waveform);
    }

    return nullptr;
  }

  std::unique_ptr<IScreen> ScreenWaveform::BottomButtonPushed(void) {
    return std::make_unique<ScreenFreq>();
  }

  std::unique_ptr<IScreen> ScreenWaveform::TopButtonPushed(void) {
    return std::make_unique<ScreenFreq>();
  }

  std::unique_ptr<IScreen> ScreenWaveform::RightButtonPushed(void) {
    // +1

    auto ao = AnalogOut::Instance();
    uint8_t nowWF = static_cast<uint8_t>(_waveform);

    if(nowWF +1 >= App::WAVEFORM_ITEM_NUM){
      _waveform = static_cast<App::Waveform>(0);
      ao->SetWaveform(_waveform);
    } else {
      _waveform = static_cast<App::Waveform>(nowWF + 1);
      ao->SetWaveform(_waveform);
    }

    return nullptr;
  }

  std::unique_ptr<IScreen> ScreenWaveform::CenterButtonPushed(void) {
    // get now output status and toggle status, then puts status
    auto ao = AnalogOut::Instance();
    bool f = ao->GetOutputStatus();
    ao->SetOutput(!f);
    App::PutsOutputStatus();

    return nullptr;
  }

  void ScreenWaveform::EndScreen(void) {
    auto lcd = LCD::Instance();
    lcd->ClearDisp();
  }

  void ScreenWaveform::PrintLabelLine1(void){

    static const char* STR_LINE_1 = "waveform:";

    auto lcd = LCD::Instance();

    lcd->SetCursorPos(1, 1);
    lcd->sputs(STR_LINE_1);

  }

  void ScreenWaveform::PrintWaveform(void) {
    auto wf = AnalogOut::Instance()->GetWaveform();

    static const char* STR_SIN = "SIN";
    static const char* STR_TRI = "TRIANGLE";
    static const char* STR_SQ = "SQUARE";
    static const char* STR_NONE = "NONE";

    auto lcd = LCD::Instance();

    lcd->SetCursorPos(2, 2);

    switch(wf) {
      case Waveform::Sin :
        lcd->sputs(STR_SIN);
        break;
      case Waveform::Triangle :
        lcd->sputs(STR_TRI);
        break;
      case Waveform::Square :
        lcd->sputs(STR_SQ);
        break;
      default:
        lcd->sputs(STR_NONE);
        break;
    }

  }

}
