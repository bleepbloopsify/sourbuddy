#include "utils.h"

float randomFloat(float lo, float hi) {
  return lo + static_cast <float> (rand()) /( static_cast <float> (RAND_MAX/(hi-lo)));
}
