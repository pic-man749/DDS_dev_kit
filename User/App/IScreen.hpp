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
#include <optional>

namespace App{

  class IScreen {

    public:
      IScreen(void);

      virtual ~IScreen(void);

      virtual std::unique_ptr<IScreen> StartScreen(void);

      virtual std::unique_ptr<IScreen> LeftButtonPushed(void);

      virtual std::unique_ptr<IScreen> BottomButtonPushed(void);

      virtual std::unique_ptr<IScreen> TopButtonPushed(void);

      virtual std::unique_ptr<IScreen> RightButtonPushed(void);

      virtual std::unique_ptr<IScreen> CenterButtonPushed(void);

      virtual std::unique_ptr<IScreen> EncoderTurned(int step);

      virtual void EndScreen(void);

  };

}

#endif /* APP_ISCREEN_HPP_ */
