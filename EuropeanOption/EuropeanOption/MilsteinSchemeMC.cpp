//
//  MilsteinSchemeMC.cpp
//  HW1
//
//  Created by Hang Miao on 2/9/18.
//  Copyright © 2018 Hang Miao. All rights reserved.
//

#include "MilsteinSchemeMC.h"
#include "Random1.h"
#include <iostream>
#include <cmath>
#include <vector>
using namespace std;

double MilsteinScheme(double Expiry,
                   double Strike,
                   double Spot,
                   double Vol,
                   double r,
                   double d,
                   unsigned long steps){
    const double h = Expiry/steps;
    const double drift = (r-d)*h;
    const double diffution = sqrt(h)*Vol;
    const double diffutionCorrect = 0.5*Vol*Vol*h;
    
    vector<double> stockprice(steps+1);
    stockprice[0] = Spot;
    
    for (int i=1; i<= steps; i++) {
        double W = GetOneGaussianByBoxMuller();
        stockprice[i] = stockprice[i-1] + drift*stockprice[i-1] + diffution*stockprice[i-1]*W +diffutionCorrect*(W*W-1);
    }
    
    return stockprice[steps];
}




vector<double> MilsteinSchemeMC(double Expiry,
                             double Strike,
                             double Spot,
                             double Vol,
                             double r,
                             double d,
                             unsigned long NumberOfPaths,
                             unsigned long steps)
{
    double thisSpot;
    
    double callrunningSum=0;
    double putrunningSum=0;
    for (unsigned long i=0; i < NumberOfPaths; i++)
    {
        
        thisSpot = MilsteinScheme(Expiry, Strike,Spot,Vol,r,d, steps);
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
