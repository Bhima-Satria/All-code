#pragma once
#include <cstdarg>
namespace Eloquent {
namespace ML {
namespace Port {
class DecisionTree {
  public:
    /**
      Predict class for features vector
    */
    int predict(float *x) {
      if (x[2] <= 681.0) {
        if (x[0] <= 26.5) {
          if (x[1] <= 76.5) {
            return 0;
          }

          else {
            return 1;
          }
        }

        else {
          return 1;
        }
      }

      else {
        return 1;
      }
    }

  protected:
};
}
}
}
