//
//  BarrierFormula.hpp
//  HW2
//
//  Created by Hang Miao on 2/8/20.
//  Copyright © 2020 Hang Miao. All rights reserved.
//

#ifndef BarrierFormula_hpp
#define BarrierFormula_hpp
#include <vector>
#include <stdio.h>
using namespace std;



vector<double> BarrierFormula(double Expiry,
                          double Strike,
                          double Spot,
                          double Vol,
                          double r,
                           double d,
                        double Barrier);


#endif /* BarrierFormula_hpp */
