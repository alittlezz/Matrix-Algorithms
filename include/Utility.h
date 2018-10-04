#ifndef UTILITY_H
#define UTILITY_H


namespace Utility{
    const double eps = 1e-6;
    bool isEqualToZero(double x){
        return -eps <= x && x <= eps;
    }
}

#endif // UTILITY_H
