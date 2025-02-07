/*
 * IScreen.hpp
 *
 *  Created on: Feb 8, 2025
 *      Author: picman
 */

#ifndef APP_ISCREEN_HPP_
#define APP_ISCREEN_HPP_

#include "ModelData.hpp"

#include <memory>

namespace App{

  class IScreen {

    public:
      IScreen(){};

      virtual ~IScreen();

      virtual void StartScreen(ModelData& modelData);

      virtual std::unique_ptr<IScreen> LeftButtonPushed(ModelData& modelData);

      virtual std::unique_ptr<IScreen> BottomButtonPushed(ModelData& modelData);

      virtual std::unique_ptr<IScreen> TopButtonPushed(ModelData& modelData);

      virtual std::unique_ptr<IScreen> RightButtonPushed(ModelData& modelData);

      virtual std::unique_ptr<IScreen> CenterButtonPushed(ModelData& modelData);

      virtual std::unique_ptr<IScreen> EncoderTurned(ModelData& modelData, int step);

      virtual std::unique_ptr<IScreen> EndScreen(ModelData& modelData);

  };

}

#endif /* APP_ISCREEN_HPP_ */
