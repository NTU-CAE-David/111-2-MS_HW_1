//
//  ANGLE.h
//  HW_1
//
//  Created by 陳啟瑋 on 2023/3/10.
//

#ifndef ANGLE_h
#define ANGLE_h

#include <iostream>
#include <cmath>
#include "ATOM.h"

using namespace std;

class ANGLE{
public:
    ANGLE(){
        k0=theta0=eng=theta=pe=f=0;
    }
    double k0;      // Force constant in kcal/mol
    double theta0;  // Equilibrium angle in degrees
    double eng;     // angle energy in kcal/mol
    double theta;   // Initi angle in degrees
    double pe;      // potential_energy
    double f;       // force
    double angle(const ATOM& a1, const ATOM& a2, const ATOM& a3);
    double energy(double theta);
    double potential_energy(double theta);
    double force(double theta);
    
};

double ANGLE::angle(const ATOM& a1, const ATOM& a2, const ATOM& a3) {
    // Calculate two vectors
    double v1[3], v2[3];
    for (int i = 0; i < 3; ++i) {
        v2[i] = a2.x[i] - a1.x[i];  // vector from a1 to a2
        v1[i] = a3.x[i] - a1.x[i];  // vector from a1 to a3
    }

    // Calculate the inner product of the two vectors
    double inner_product = 0.0;
    for (int i = 0; i < 3; ++i) {
        inner_product += v1[i] * v2[i];
    }

    // Calculate the magnitude of the two vectors
    double magnitude_v1 = 0.0, magnitude_v2 = 0.0;
    for (int i = 0; i < 3; ++i) {
        magnitude_v1 += v1[i] * v1[i];
        magnitude_v2 += v2[i] * v2[i];
    }
    magnitude_v1 = sqrt(magnitude_v1);
    magnitude_v2 = sqrt(magnitude_v2);

    // Calculate the cosine of the angle between the two vectors
    double cosine = inner_product / (magnitude_v1 * magnitude_v2);

    // Calculate the angle in radians
    double radians = acos(cosine);

    // Convert the angle from radians to degrees
    theta = radians * 180.0 / M_PI;

    return theta;
}


double ANGLE::energy(double theta) {
    double rad_theta = theta * M_PI / 180.0;
    double rad_theta0 = theta0 * M_PI / 180.0;
    double cos_sin_delta = cos(rad_theta) - cos(rad_theta0) / sin(theta0);
    eng = 0.5 * k0 * cos_sin_delta * cos_sin_delta;
    return eng;
}

double ANGLE::potential_energy(double theta){
    double delta_theta = theta - theta0;
    pe = 0.5 * k0 * delta_theta * delta_theta;
    return pe;
}

double ANGLE::force(double theta){
    double delta_theta = theta - theta0;
    f = -k0 * delta_theta;
    return f;
}

#endif /* ANGLE_h */
