//
//  BSM_GeometricAsianFormula.hpp
//  CF4_AsianBrownianBridge
//
//  Created by Hang Miao on 3/8/20.
//  Copyright © 2020 Hang Miao. All rights reserved.
//

#ifndef BSM_GeometricAsianFormula_hpp
#define BSM_GeometricAsianFormula_hpp

#include <stdio.h>
#include <vector>
using namespace std;

vector<double> GAsian_Cont(double Expiry,
                          double Strike,
                          double Spot,
                          double Vol,
                          double r,
                          double d);

vector<double> GAsian_Disc(double Expiry,
                           double Strike,
                           double Spot,
                           double Vol,
                           double r,
                           double d,
                           double D);


#endif /* BSM_GeometricAsianFormula_hpp */
