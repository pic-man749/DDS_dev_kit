/*
 * ScreenFreq.hpp
 *
 *  Created on: Feb 8, 2025
 *      Author: picman
 */

#ifndef APP_SCREEN_SCREENFREQ_HPP_
#define APP_SCREEN_SCREENFREQ_HPP_

#include "App/IScreen.hpp"
#include "App/Screen/Misc/SelectedDigit.hpp"

#include <memory>

namespace App {

  namespace {
    // freq = X,XXX,XXX.X
    static const uint8_t MAX_FREQ_NUM_OF_DIGITS = 8;

    static const uint8_t START_POS = 4;

    // line 2: _X,XXX,XXX.X[Hz]
    //         ||||||||||||||||
    //         123456789ABC...
    static const uint8_t Digit2Pos[] = {12, 10, 9, 8, 6, 5, 4, 2};
  }

  class ScreenFreq : public IScreen {

    public:
      ScreenFreq(void);
      ~ScreenFreq(void){};

      std::unique_ptr<IScreen> StartScreen(void) override;

      std::unique_ptr<IScreen> LeftButtonPushed(void);

//      std::unique_ptr<IScreen> BottomButtonPushed(void);

//      std::unique_ptr<IScreen> TopButtonPushed(void);

      std::unique_ptr<IScreen> RightButtonPushed(void);

      std::unique_ptr<IScreen> CenterButtonPushed(void);

      std::unique_ptr<IScreen> EncoderTurned(int step);

      void EndScreen(void);

    private:

      enum class Direction {
        LEFT,
        RIGHT
      };

      void PrintLabelLine1(void);

      void PrintLabelLine2(void);

      bool PrintFreq(void);

      void SetCursorPos(Direction cd);

      SelectedDigit _selectedDigit = SelectedDigit(MAX_FREQ_NUM_OF_DIGITS, START_POS);
  };
}


#endif /* APP_SCREEN_SCREENFREQ_HPP_ */
