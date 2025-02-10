/*
 * IScreen.cpp
 *
 *  Created on: Feb 11, 2025
 *      Author: picman
 */
#include "IScreen.hpp"

namespace App {

  IScreen::IScreen() {
    ;
  }

  IScreen::~IScreen() {
    ;
  }

  std::unique_ptr<IScreen> IScreen::StartScreen() {
    return nullptr;
  }

  std::unique_ptr<IScreen> IScreen::LeftButtonPushed() {
    return nullptr;
  }

  std::unique_ptr<IScreen> IScreen::BottomButtonPushed() {
    return nullptr;
  }

  std::unique_ptr<IScreen> IScreen::TopButtonPushed() {
    return nullptr;
  }

  std::unique_ptr<IScreen> IScreen::RightButtonPushed() {
    return nullptr;
  }

  std::unique_ptr<IScreen> IScreen::CenterButtonPushed() {
    return nullptr;
  }

  std::unique_ptr<IScreen> IScreen::EncoderTurned(int step) {
    return nullptr;
  }

  void IScreen::EndScreen() {
    ;
  }

}
