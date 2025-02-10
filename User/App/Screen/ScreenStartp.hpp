/*
 * ScreenStartp.hpp
 *
 *  Created on: Feb 8, 2025
 *      Author: picman
 */

#ifndef APP_SCREEN_SCREENSTARTP_HPP_
#define APP_SCREEN_SCREENSTARTP_HPP_

#include "App/IScreen.hpp"
namespace App {

  class ScreenStartup : public IScreen {

    public:
      ScreenStartup(){};
      ~ScreenStartup(){};

      std::unique_ptr<IScreen> StartScreen() override;

  };

}

#endif /* APP_SCREEN_SCREENSTARTP_HPP_ */
