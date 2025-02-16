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

    // init screen
    _screen = std::move(startScreen);
    auto ret = _screen->StartScreen();
    if(ret != nullptr){
      MoveScreen(std::move(ret));
    }
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
    static auto oldButtonType = Button::ButtonType::NONE;
    auto buttonType = _button->GetPushedButton();

    if(buttonType != oldButtonType){

      switch(buttonType){
        case Button::ButtonType::LEFT:
          ret = _screen->LeftButtonPushed();
          break;

        case Button::ButtonType::BOTTOM:
          ret = _screen->BottomButtonPushed();
          break;

        case Button::ButtonType::TOP:
          ret = _screen->TopButtonPushed();
          break;

        case Button::ButtonType::RIGHT:
          ret = _screen->RightButtonPushed();
          break;

        case Button::ButtonType::CENTER:
          ret = _screen->CenterButtonPushed();
          break;

        case Button::ButtonType::NONE:
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
