/*
 * Encoder.cpp
 *
 *  Created on: Feb 2, 2025
 *      Author: picman
 */
#include "Encoder.hpp"

namespace Encoder{

  Encoder::Encoder(TIM_HandleTypeDef *htim){
    _htim = htim;
    _lastCounterValue = __HAL_TIM_GET_COUNTER(_htim);
  }

  bool Encoder::Start(void){
    return ( HAL_TIM_Encoder_Start(_htim, TIM_CHANNEL_ALL) == HAL_OK );
  }

  bool Encoder::Stop(void){
    return ( HAL_TIM_Encoder_Stop(_htim, TIM_CHANNEL_ALL) == HAL_OK );
  }

  int Encoder::GetValue(void){
    return (int32_t)__HAL_TIM_GET_COUNTER(_htim) / 2;
  }

}
