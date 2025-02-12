/*
 * IScreen.cpp
 *
 *  Created on: Feb 11, 2025
 *      Author: picman
 */
#include "IScreen.hpp"

namespace App {

  IScreen::IScreen(void) {
    ;
  }

  IScreen::~IScreen(void) {
    ;
  }

  std::unique_ptr<IScreen> IScreen::StartScreen(void) {
    return nullptr;
  }

  std::unique_ptr<IScreen> IScreen::LeftButtonPushed(void) {
    return nullptr;
  }

  std::unique_ptr<IScreen> IScreen::BottomButtonPushed(void) {
    return nullptr;
  }

  std::unique_ptr<IScreen> IScreen::TopButtonPushed(void) {
    return nullptr;
  }

  std::unique_ptr<IScreen> IScreen::RightButtonPushed(void) {
    return nullptr;
  }

  std::unique_ptr<IScreen> IScreen::CenterButtonPushed(void) {
    return nullptr;
  }

  std::unique_ptr<IScreen> IScreen::EncoderTurned(int step) {
    return nullptr;
  }

  void IScreen::EndScreen(void) {
    ;
  }

}
