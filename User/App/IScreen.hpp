/*
 * IScreen.hpp
 *
 *  Created on: Feb 8, 2025
 *      Author: picman
 */

#ifndef APP_ISCREEN_HPP_
#define APP_ISCREEN_HPP_

#include "Model.hpp"

#include <memory>

namespace App{

  class IScreen {

    public:
      IScreen();

      virtual ~IScreen();

      virtual std::unique_ptr<IScreen> StartScreen();

      virtual std::unique_ptr<IScreen> LeftButtonPushed();

      virtual std::unique_ptr<IScreen> BottomButtonPushed();

      virtual std::unique_ptr<IScreen> TopButtonPushed();

      virtual std::unique_ptr<IScreen> RightButtonPushed();

      virtual std::unique_ptr<IScreen> CenterButtonPushed();

      virtual std::unique_ptr<IScreen> EncoderTurned(int step);

      virtual void EndScreen();

  };

}

#endif /* APP_ISCREEN_HPP_ */
