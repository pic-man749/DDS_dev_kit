/*
 * ScreenWaveform.hpp
 *
 *  Created on: Feb 23, 2025
 *      Author: picman
 */

#ifndef APP_SCREEN_SCREENWAVEFORM_HPP_
#define APP_SCREEN_SCREENWAVEFORM_HPP_

#include "App/IScreen.hpp"
#include "App/Model.hpp"

#include <memory>

namespace App {

  /// @class ScreenWaveform
  /// @brief This screen controls the output waveform.
  ///
  class ScreenWaveform : public IScreen {

    public:
      ScreenWaveform(void);
      ~ScreenWaveform(void){};

      std::unique_ptr<IScreen> StartScreen(void) override;

      std::unique_ptr<IScreen> LeftButtonPushed(void) override;

      std::unique_ptr<IScreen> BottomButtonPushed(void) override;

      std::unique_ptr<IScreen> TopButtonPushed(void) override;

      std::unique_ptr<IScreen> RightButtonPushed(void) override;

      std::unique_ptr<IScreen> CenterButtonPushed(void) override;

//      std::unique_ptr<IScreen> EncoderTurned(int step) override;

      void EndScreen(void) override;

    private:

      void PrintLabelLine1(void);

      void PrintWaveform(void);

      App::Waveform _waveform;

  };

}

#endif /* APP_SCREEN_SCREENWAVEFORM_HPP_ */
