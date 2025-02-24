/*
 * Context.cpp
 *
 *  Created on: Feb 7, 2025
 *      Author: picman
 */
#include "Context.hpp"
#include "tim.h"
#include "Model.hpp"

namespace App {

  Context::Context(std::unique_ptr<IScreen> startScreen) {
    // init inputs
    _encoder = std::make_unique<Encoder_Driver::Encoder>(&htim2);
    _encoder->Start();
    _button = std::make_unique<Button_Driver::Button>();

    // init screen
    _screen = std::move(startScreen);
    auto ret = _screen->StartScreen();
    if(ret != nullptr){
      MoveScreen(std::move(ret));
    }

    // init analogOut
    auto ao = AnalogOut::Instance();
    ao->SetOutput(false);
    ao->SetWaveform(ao->GetWaveform());
    ao->SetFreqx10(ao->GetFreqx10());
  }

  void Context::LoopAction(){

    // next
    std::unique_ptr<IScreen> ret = nullptr;

    // encoder turned
    static int oldStep = 0;
    auto step = _encoder->GetValue();
    int diff = step - oldStep;
    if(diff != 0){
      ret = _screen->EncoderTurned(diff);
      oldStep = step;
    }

    if(ret){
      MoveScreen(std::move(ret));
      return;
    }

    // button pushed
    static auto oldButtonType = Button_Driver::ButtonType::NONE;
    auto buttonType = _button->GetPushedButton();

    if(buttonType != oldButtonType){

      switch(buttonType){
        case Button_Driver::ButtonType::LEFT:
          ret = _screen->LeftButtonPushed();
          break;

        case Button_Driver::ButtonType::BOTTOM:
          ret = _screen->BottomButtonPushed();
          break;

        case Button_Driver::ButtonType::TOP:
          ret = _screen->TopButtonPushed();
          break;

        case Button_Driver::ButtonType::RIGHT:
          ret = _screen->RightButtonPushed();
          break;

        case Button_Driver::ButtonType::CENTER:
          ret = _screen->CenterButtonPushed();
          break;

        case Button_Driver::ButtonType::NONE:
          ;
          break;
      }

      oldButtonType = buttonType;

      if(ret){
        MoveScreen(std::move(ret));
        return;
      }
    }
  }

  void Context::MoveScreen(std::unique_ptr<IScreen> nextScreen){
    _screen->EndScreen();
    _screen = std::move(nextScreen);
    _screen->StartScreen();
  }

  Context::~Context(){
    _encoder->Stop();
  }

}
