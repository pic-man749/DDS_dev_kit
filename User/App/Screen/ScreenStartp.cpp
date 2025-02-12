/*
 * ScreenStartp.cpp
 *
 *  Created on: Feb 8, 2025
 *      Author: picman
 */
#include "ScreenStartp.hpp"
#include "App/Model.hpp"

#include "ScreenFreq.hpp"

namespace App {

  std::unique_ptr<IScreen> ScreenStartup::StartScreen() {
    auto lcd = LCD::Instance();
    lcd->SetDoubleHeightFont(true);
    lcd->sputs("DDS dev kit");
    HAL_Delay(STARTUP_SCREEN_DURATION);
    return std::make_unique<ScreenFreq>();
  }

  void ScreenStartup::EndScreen() {
    // reset LCD
    auto lcd = LCD::Instance();
    lcd->SetDoubleHeightFont(false);
    lcd->ClearDisp();
  }

}
