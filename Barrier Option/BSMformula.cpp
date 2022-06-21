//
//  BSMformula.cpp
//  HW1
//
//  Created by Hang Miao on 2/8/18.
//  Copyright © 2018 Hang Miao. All rights reserved.
//

#include "BSMformula.h"
#include <cmath>
#include "Normals.h"
#include <vector>
using namespace std;
vector<double> BSMformula(double Expiry,
                          double Strike,
                          double Spot,
                          double Vol,
                          double r,
                          double d)
{
    
    double F = Spot*exp((r-d)*Expiry);
    double discountfactor = exp(-r*Expiry);
    double rootVariance = Vol*sqrt(Expiry);
    double d1 = (1/rootVariance)* (log(Spot/Strike) + (r-d+0.5*Vol*Vol)*Expiry);
    double d2= d1 - rootVariance;
    
    double BSMcall = discountfactor * (F*CumulativeNormal(d1) - Strike*CumulativeNormal(d2));
    
    double BSMput = discountfactor * (Strike*CumulativeNormal(-d2) - F*CumulativeNormal(-d1));
    vector<double> result(2);
    result[0] = BSMcall;
    result[1] = BSMput;
    return result;
}
