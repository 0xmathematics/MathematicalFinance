//
//  simpleMonteCarlo.cpp
//  HW1
//
//  Created by Hang Miao on 2/8/18.
//  Copyright © 2018 Hang Miao. All rights reserved.
//

#include "simpleMonteCarlo.h"
#include "Random1.h"
#include <iostream>
#include <cmath>
#include <vector>
using namespace std;
vector<double> SimpleMonteCarlo1(double Expiry,
                                 double Strike,
                                 double Spot,
                                 double Vol,
                                 double r,
                                 double d,
                                 unsigned long NumberOfPaths)
{
    double variance = Vol*Vol*Expiry;
    double rootVariance = sqrt(variance);
    double itoCorrection = -0.5*variance;
    
    double movedSpot = Spot*exp(r*Expiry -d*Expiry +itoCorrection);
    double thisSpot;
    double callrunningSum=0;
    double putrunningSum=0;
    for (unsigned long i=0; i < NumberOfPaths; i++)
    {
        double thisGaussian = GetOneGaussianByBoxMuller();
        thisSpot = movedSpot*exp( rootVariance*thisGaussian);
        double thisPayoff = thisSpot - Strike;
        if (thisPayoff >= 0) {
            callrunningSum += thisPayoff;
            putrunningSum += 0;
        }
        else{
            putrunningSum += (-thisPayoff);
            callrunningSum += 0;
        }
        /*
         thisPayoff = thisPayoff >0 ? thisPayoff : 0;   // a ? b : c return b if a is true otherwise return c
         callrunningSum += thisPayoff;
         */
        
    }
    
    double callmean = callrunningSum / NumberOfPaths;
    callmean *= exp(-r*Expiry);
    double putmean = putrunningSum / NumberOfPaths;
    putmean *= exp(-r*Expiry);
    
    vector<double> result(2);
    result[0] = callmean;
    result[1] = putmean;
    
    return result;
}
