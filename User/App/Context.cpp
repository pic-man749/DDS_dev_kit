/*
 * Context.cpp
 *
 *  Created on: Feb 7, 2025
 *      Author: picman
 */
#include "Context.hpp"
#include "tim.h"

namespace App {

  Context::Context(std::unique_ptr<IScreen> startScreen) {
    // init inputs
    _encoder = std::make_unique<Encoder::Encoder>(&htim2);
    _encoder->Start();
    _button = std::make_unique<Button::Button>();

    // init model data
    _modelData.freqx10 = 1000 * 10;
    _modelData.waveform = Waveform::Sin;

    // init screen
    _screen = std::move(startScreen);
    _screen->StartScreen(_modelData);
  }

  void Context::LoopAction(){

    // next
    std::unique_ptr<IScreen> ret = nullptr;

    // encoder turned
    auto step = _encoder->GetValue();
    if(step != 0){
      ret = _screen->EncoderTurned(_modelData, step);
    }

    if(ret){
      MoveScreen(std::move(ret));
      return;
    }

    // button pushed
    static auto oldButtonType = _button->GetPushedButton();
    auto buttonType = _button->GetPushedButton();

    if(buttonType != oldButtonType){

      switch(buttonType){
        case Button::ButtonType::LEFT:
          ret = _screen->LeftButtonPushed(_modelData);
          break;

        case Button::ButtonType::BOTTOM:
          ret = _screen->BottomButtonPushed(_modelData);
          break;

        case Button::ButtonType::TOP:
          ret = _screen->TopButtonPushed(_modelData);
          break;

        case Button::ButtonType::RIGHT:
          ret = _screen->RightButtonPushed(_modelData);
          break;

        case Button::ButtonType::CENTER:
          ret = _screen->CenterButtonPushed(_modelData);
          break;

        case Button::ButtonType::NONE:
          ;
          break;
      }

      if(ret){
        MoveScreen(std::move(ret));
        return;
      }
    }
  }

  void Context::MoveScreen(std::unique_ptr<IScreen> nextScreen){
    _screen->EndScreen(_modelData);
    _screen = std::move(nextScreen);
    _screen->StartScreen(_modelData);
  }

  Context::~Context(){
    _encoder->Stop();
  }

}
