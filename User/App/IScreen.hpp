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

  /// @class IScreen
  /// @brief Interface of Screen class.
  /// @brief All screens inherit and implement this interface.
  ///
  class IScreen {

    public:
      IScreen(void);

      virtual ~IScreen(void);

      /// @fn std::unique_ptr<IScreen> StartScreen(void)
      /// @brief Callback of screen start.
      ///
      /// @return nullptr continue now screen
      /// @return other next screen
      virtual std::unique_ptr<IScreen> StartScreen(void);

      /// @fn std::unique_ptr<IScreen> LeftButtonPushed(void)
      /// @brief Callback of left button pushed.
      ///
      /// @return nullptr continue now screen
      /// @return other next screen
      virtual std::unique_ptr<IScreen> LeftButtonPushed(void);

      /// @fn std::unique_ptr<IScreen> BottomButtonPushed(void)
      /// @brief Callback of bottom button pushed.
      ///
      /// @return nullptr continue now screen
      /// @return other next screen
      virtual std::unique_ptr<IScreen> BottomButtonPushed(void);

      /// @fn std::unique_ptr<IScreen> TopButtonPushed(void)
      /// @brief Callback of top button pushed.
      ///
      /// @return nullptr continue now screen
      /// @return other next screen
      virtual std::unique_ptr<IScreen> TopButtonPushed(void);

      /// @fn std::unique_ptr<IScreen> RightButtonPushed(void)
      /// @brief Callback of right button pushed.
      ///
      /// @return nullptr continue now screen
      /// @return other next screen
      virtual std::unique_ptr<IScreen> RightButtonPushed(void);

      /// @fn std::unique_ptr<IScreen> CenterButtonPushed(void)
      /// @brief Callback of center button pushed.
      ///
      /// @return nullptr continue now screen
      /// @return other next screen
      virtual std::unique_ptr<IScreen> CenterButtonPushed(void);

      /// @fn std::unique_ptr<IScreen> EncoderTurned(int)
      /// @brief Callback of encoder turned.
      ///
      /// @param step turned amount, +:CW, -:CCW
      /// @return nullptr continue now screen
      /// @return other next screen
      virtual std::unique_ptr<IScreen> EncoderTurned(int step);

      /// @fn void EndScreen(void)
      /// @brief Interface of Screen class that called screen end.
      ///
      virtual void EndScreen(void);

  };

}

#endif /* APP_ISCREEN_HPP_ */
