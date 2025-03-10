/*
 * Context.hpp
 *
 *  Created on: Feb 7, 2025
 *      Author: picman
 */

#ifndef APP_CONTEXT_HPP_
#define APP_CONTEXT_HPP_

#include <memory>
#include "IScreen.hpp"
#include "Model.hpp"
#include "Driver/Encoder/Encoder.hpp"
#include "Driver/Button/Button.hpp"

namespace App {

  class Context{

    public:
      Context(std::unique_ptr<IScreen> startScreen);
      ~Context();

      void LoopAction();

    private:
      std::unique_ptr<IScreen> _screen;

      std::unique_ptr<Encoder_Driver::Encoder> _encoder;
      std::unique_ptr<Button_Driver::Button> _button;

      void MoveScreen(std::unique_ptr<IScreen> nextScreen);

  };

}

#endif /* APP_CONTEXT_HPP_ */
