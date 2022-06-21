//
//  BarrierFormula.cpp
//
//
//  Created by Hang Miao on 2/8/20.
//  Copyright © 2020 Hang Miao. All rights reserved.
//

#include "BarrierFormula.hpp"
#include <cmath>
#include "Normals.h"
#include <vector>
using namespace std;
vector<double> BarrierFormula(double Expiry,
                              double Strike,
                              double Spot,
                              double Vol,
                              double r,
                              double d,
                              double Barrier)
{
    
    double Intgral_r = (r-d)*Expiry;
    double discountfactor = exp(-r*Expiry);
    double Variance = Vol*Vol*Expiry;
    double itoCorrection = -0.5*Variance;
    double rootVariance = sqrt(Variance);
    double rootVariance_inverse = 1/rootVariance;
    double xK = Spot/Strike;
    double xB = Spot/Barrier;
    double B2xK = Barrier*Barrier/(Strike*Spot);
    double Bx = Barrier/Spot;
  /*//Easy to read code
    double dpxK = (1/rootVariance)* (log(xK) + (r+0.5*Vol*Vol)*Expiry);
    double dpxB = (1/rootVariance)* (log(xB) + (r+0.5*Vol*Vol)*Expiry);
    double dnxK = (1/rootVariance)* (log(xK) + (r-0.5*Vol*Vol)*Expiry);
    double dnxB = (1/rootVariance)* (log(xB) + (r-0.5*Vol*Vol)*Expiry);
    
    double dpB2xK = (1/rootVariance)* (log(B2xK) + (r+0.5*Vol*Vol)*Expiry);
    double dpBx = (1/rootVariance)* (log(Bx) + (r+0.5*Vol*Vol)*Expiry);
    double dnB2xK = (1/rootVariance)* (log(B2xK) + (r-0.5*Vol*Vol)*Expiry);
    double dnBx = (1/rootVariance)* (log(Bx) + (r-0.5*Vol*Vol)*Expiry);
*/
    
    
    // the following are efficient code
    double dpxK = rootVariance_inverse* (log(xK) + (Intgral_r -itoCorrection));
    double dpxB = rootVariance_inverse* (log(xB) + (Intgral_r-itoCorrection));
    double dnxK = rootVariance_inverse* (log(xK) + (Intgral_r+itoCorrection));
    double dnxB = rootVariance_inverse* (log(xB) + (Intgral_r+itoCorrection));
    
    double dpB2xK = rootVariance_inverse* (log(B2xK) + (Intgral_r-itoCorrection));
    double dpBx = rootVariance_inverse* (log(Bx) + (Intgral_r-itoCorrection));
    double dnB2xK = rootVariance_inverse* (log(B2xK) + (Intgral_r+itoCorrection));
    double dnBx = rootVariance_inverse* (log(Bx) + (Intgral_r+itoCorrection));
    /**/
    double UpOutcall = exp(-d*Expiry)*Spot*(CumulativeNormal(dpxK)-CumulativeNormal(dpxB)) - discountfactor*Strike*(CumulativeNormal(dnxK) - CumulativeNormal(dnxB)) -exp(-d*Expiry)* Barrier* pow (xB, -2*(r-d)/(Vol*Vol))*(CumulativeNormal(dpB2xK) -CumulativeNormal(dpBx)) + discountfactor*Strike*pow(xB, -2*(r-d)/(Vol*Vol)+1)*(CumulativeNormal(dnB2xK) -CumulativeNormal(dnBx));
    

    vector<double> result(1);
    result[0] = UpOutcall;
   // result[1] = BSMput;
    return result;
}

