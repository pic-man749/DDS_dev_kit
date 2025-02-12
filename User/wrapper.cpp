/*
 * wrapper.cpp
 *
 *  Created on: Dec 1, 2024
 *      Author: picman
 */

#include "wrapper.hpp"

#include <memory>
#include "App/Context.hpp"
#include "App/Screen/ScreenStartp.hpp"

namespace {
  std::unique_ptr<App::Context> context;
}

void setup(void){
  context =std::make_unique<App::Context>(std::make_unique<App::ScreenStartup>());
}

void loop(void){
  context->LoopAction();
}
