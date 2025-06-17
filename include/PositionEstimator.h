#ifndef POSITION_ESTIMATOR_H
#define POSITION_ESTIMATOR_H
#include "Types.h"

class PositionEstimator {
public:
  PositionEstimator();
  void begin();
  float getPositionPercent();
private:
  float calibrationTime;
};

#endif