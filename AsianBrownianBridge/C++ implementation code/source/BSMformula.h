//
//  BSMformula.hpp
//  HW1
//
//  Created by Hang Miao on 2/8/18.
//  Copyright © 2018 Hang Miao. All rights reserved.
//

#ifndef BSMformula_h
#define BSMformula_h
#include <vector>
using namespace std;

vector<double> BSMformula(double Expiry,
                          double Strike,
                          double Spot,
                          double Vol,
                          double r,
                          double d);



#endif /* BSMformula_h */
