//
//  BSM_GeometricAsianFormula.cpp
//  CF4_AsianBrownianBridge
//
//  Created by Hang Miao on 3/8/20.
//  Copyright © 2020 Hang Miao. All rights reserved.
//

#include "BSM_GeometricAsianFormula.hpp"
#include <cmath>
#include "Normals.h"
#include <vector>

vector<double> GAsian_Cont(double Expiry,
                           double Strike,
                           double Spot,
                           double Vol,
                           double r,
                           double d)
{
    double discountfactor = exp(-r*Expiry);
    double sd = Vol*sqrt(Expiry/3);
    double drift = Expiry/2*(r-d-0.5*Vol*Vol);
    
    double F = Spot*exp(drift + sd*sd/2);
    double d2 = -(log(Strike/Spot) - drift)/sd;
    double d1 = d2 +sd;
    
    double GAsian_Cont_Call = discountfactor * (F*CumulativeNormal(d1) - Strike*CumulativeNormal(d2));
    double GAsian_Cont_Put = discountfactor * (Strike*CumulativeNormal(-d2) - F*CumulativeNormal(-d1));
    
    vector<double> result(2);
    result[0] = GAsian_Cont_Call;
    result[1] = GAsian_Cont_Put;
    return result;
}

vector<double> GAsian_Disc(double Expiry,
                           double Strike,
                           double Spot,
                           double Vol,
                           double r,
                           double d,
                           double D)
{
    double discountfactor = exp(-r*Expiry);
    double h = Expiry/D;
    double sd = Vol*sqrt( h *(D+1)*(2*D+1)/(6*D) );
    double drift = h*(1+D)/2*(r-d-0.5*Vol*Vol);
    
    double F = Spot*exp(drift + sd*sd/2);
    double d2 = - (log(Strike/Spot) - drift)/sd;
    double d1 = d2 +sd;
    
    double GAsian_Cont_Call = discountfactor * (F*CumulativeNormal(d1) - Strike*CumulativeNormal(d2));
    double GAsian_Cont_Put = discountfactor * (Strike*CumulativeNormal(-d2) - F*CumulativeNormal(-d1));
    
    vector<double> result(2);
    result[0] = GAsian_Cont_Call;
    result[1] = GAsian_Cont_Put;
    return result;
}





