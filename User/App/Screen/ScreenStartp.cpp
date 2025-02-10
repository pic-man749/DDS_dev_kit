/*
 * ScreenStartp.cpp
 *
 *  Created on: Feb 8, 2025
 *      Author: picman
 */
#include "ScreenStartp.hpp"
#include "App/Model.hpp"

namespace App {

  std::unique_ptr<IScreen> ScreenStartup::StartScreen() {
    auto lcd = LCD::Instance();
    lcd->SetDoubleHeightFont(true);
    lcd->sputs("DDS dev kit");
    return nullptr;
  }


}
