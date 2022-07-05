//
//  simpleMonteCarlo.hpp
//  HW1
//
//  Created by Hang Miao on 2/8/18.
//  Copyright © 2018 Hang Miao. All rights reserved.
//

#ifndef simpleMonteCarlo_h
#define simpleMonteCarlo_h
#include <vector>
using namespace std;
#include <stdio.h>
vector<double> SimpleMonteCarlo1(double Expiry,
                                 double Strike,
                                 double Spot,
                                 double Vol,
                                 double r,
                                 double d,
                                 unsigned long NumberOfPaths);


#endif /* simpleMonteCarlo_hpp */
