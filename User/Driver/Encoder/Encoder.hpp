/*
 * Encoder.hpp
 *
 *  Created on: Feb 2, 2025
 *      Author: picman
 */

#ifndef DRIVER_ENCODER_ENCODER_HPP_
#define DRIVER_ENCODER_ENCODER_HPP_

#include "stm32l4xx_hal.h"

namespace Encoder {

  class Encoder {

    public:
      Encoder(TIM_HandleTypeDef *htim);

      bool Start(void);

      bool Stop(void);

      int GetValue(void);

    private:

      TIM_HandleTypeDef *_htim;

      int32_t _lastCounterValue;

  };
}

#endif /* DRIVER_ENCODER_ENCODER_HPP_ */
