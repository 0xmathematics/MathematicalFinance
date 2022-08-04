//
//  MilsteinSchemeMC.hpp
//  HW1
//
//  Created by Hang Miao on 2/9/18.
//  Copyright © 2018 Hang Miao. All rights reserved.
//

#ifndef MilsteinSchemeMC_h
#define MilsteinSchemeMC_h


#include <vector>
using namespace std;
#include <stdio.h>
double MilsteinScheme(double Expiry,
                   double Strike,
                   double Spot,
                   double Vol,
                   double r,
                   double d,
                   unsigned long steps);

vector<double> MilsteinSchemeMC(double Expiry,
                             double Strike,
                             double Spot,
                             double Vol,
                             double r,
                             double d,
                             unsigned long NumberOfPaths,
                             unsigned long steps );


#endif /* MilsteinSchemeMC_hpp */
