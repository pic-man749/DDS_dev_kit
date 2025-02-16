/*
 * SelectedDigit.hpp
 *
 *  Created on: Feb 15, 2025
 *      Author: picman
 */

#ifndef APP_SCREEN_MISC_SELECTEDDIGIT_HPP_
#define APP_SCREEN_MISC_SELECTEDDIGIT_HPP_

#include <stdint.h>

class SelectedDigit {

  public:
    SelectedDigit(uint8_t max, uint8_t initialPos);
    ~SelectedDigit(){};

    uint8_t GetNowPos(void);

    uint8_t MoveLeft(void);

    uint8_t MoveRight(void);

  private:
    // ex) num: 0,001,000.0
    //              ‾       <- selected digit
    //     idx: 7 654 321 0

    // _now : [0, _max)
    uint8_t _max;
    uint8_t _now;

};

#endif /* APP_SCREEN_MISC_SELECTEDDIGIT_HPP_ */
