/*
 * Button.hpp
 *
 *  Created on: Feb 3, 2025
 *      Author: picman
 */

#ifndef DRIVER_BUTTON_BUTTON_HPP_
#define DRIVER_BUTTON_BUTTON_HPP_

#include "gpio.h"

namespace Button_Driver {

  enum class ButtonType{
      NONE,
      LEFT,
      BOTTOM,
      TOP,
      RIGHT,
      CENTER
  };

  class Button {

    public:
      Button();

      ButtonType GetPushedButton();

      ButtonType GetPushedButton(int32_t timeout);

    private:

  };

}

#endif /* DRIVER_BUTTON_BUTTON_HPP_ */
