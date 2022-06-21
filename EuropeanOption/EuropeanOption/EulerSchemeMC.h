//
//  EulerSchemeMC.hpp
//  HW1
//
//  Created by Hang Miao on 2/9/18.
//  Copyright © 2018 Hang Miao. All rights reserved.
//

#ifndef EulerSchemeMC_h
#define EulerSchemeMC_h

#include <vector>
using namespace std;
#include <stdio.h>
double EulerScheme(double Expiry,
            double Strike,
            double Spot,
            double Vol,
            double r,
            double d,
            unsigned long steps);

vector<double> EulerSchemeMC(double Expiry,
                        double Strike,
                        double Spot,
                        double Vol,
                        double r,
                        double d,
                        unsigned long NumberOfPaths,
                        unsigned long steps );


#endif /* EulerSchemeMC_hpp */
