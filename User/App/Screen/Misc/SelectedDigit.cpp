/*
 * SelectedDigit.cpp
 *
 *  Created on: Feb 15, 2025
 *      Author: picman
 */
#include "SelectedDigit.hpp"

SelectedDigit::SelectedDigit(uint8_t max, uint8_t initialPos) {
  _max = max;
  if(initialPos < _max){
    _now = initialPos;
  } else {
    _now = 0;
  }
}

uint8_t SelectedDigit::GetNowPos(void) {
  return _now;
}

uint8_t SelectedDigit::MoveLeft(void) {
  if(_now >= _max -1) {
    _now = 0;
  } else {
    _now += 1;
  }
  return _now;
}

uint8_t SelectedDigit::MoveRight(void) {
  if(_now == 0) {
    _now = _max -1;
  } else {
    _now -= 1;
  }
  return _now;
}
