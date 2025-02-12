/*
 * ScreenFreq.hpp
 *
 *  Created on: Feb 8, 2025
 *      Author: picman
 */

#ifndef APP_SCREEN_SCREENFREQ_HPP_
#define APP_SCREEN_SCREENFREQ_HPP_

#include "App/IScreen.hpp"

namespace App {

  class ScreenFreq : public IScreen {

    public:
      ScreenFreq(void){};
      ~ScreenFreq(void){};

      std::unique_ptr<IScreen> StartScreen(void) override;

    private:
      void PrintLabelLine1(void);
      void PrintLabelLine2(void);

      void PrintFreq(void);

  };

}


#endif /* APP_SCREEN_SCREENFREQ_HPP_ */
