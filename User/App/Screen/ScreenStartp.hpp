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

  /// @class ScreenStartup
  /// @brief This screen show startup logo 'DDS dev kit'.
  ///
  class ScreenStartup : public IScreen {

    public:
      ScreenStartup(){};
      ~ScreenStartup(){};

      std::unique_ptr<IScreen> StartScreen() override;

      void EndScreen() override;

    private:
      const uint32_t STARTUP_SCREEN_DURATION = 2;

  };

}

#endif /* APP_SCREEN_SCREENSTARTP_HPP_ */
