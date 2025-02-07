/*
 * ModelData.hpp
 *
 *  Created on: Feb 8, 2025
 *      Author: picman
 */

#ifndef APP_MODELDATA_HPP_
#define APP_MODELDATA_HPP_

namespace App {

  enum class Waveform{
      Sin,
      Triangle,
      Square
  };

  struct ModelData {
      uint32_t freqx10;
      Waveform waveform;
  };

}

#endif /* APP_MODELDATA_HPP_ */
