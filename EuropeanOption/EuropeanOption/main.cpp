//
//  main.cpp
//  Pricing European Option
//  Black-Scholes Formula, Monte Carlo Method, Euler and Milstein Scheme for Numerical Solution of SDE 
//
//  Created by Hang Miao on 2/6/18.
//  Copyright © 2018 Hang Miao. All rights reserved.
//

//
//


#include "Random1.h"
#include <iostream>
#include <cmath>
#include "Normals.h"
#include <vector>
#include "BSMformula.h"
#include "simpleMonteCarlo.h"
#include "EulerSchemeMC.h"
#include "MilsteinSchemeMC.h"
#include "logEulerSchemeMC.h"
#include "MilsteinSchemeMC.h"

using namespace std;


int main()
{
    

    
    const double Expiry = 1;
    const double Strike = 110;
    const double Spot = 100;
    const double Vol = 0.3;
    const double r = 0.05;
    const double d = 0.02;
    const unsigned long NumberOfPaths = 100000;
    const unsigned long steps = 252;
    
    vector<double> formularesult = BSMformula(Expiry,
                                              Strike,
                                              Spot,
                                              Vol,
                                              r,
                                              d);
    
    vector<double> mresult = SimpleMonteCarlo1(Expiry,
                                      Strike,
                                      Spot,
                                      Vol,
                                      r,
                                      d,
                                      NumberOfPaths);

    vector<double> EulerResult = EulerSchemeMC(Expiry,
                                            Strike,
                                            Spot,
                                            Vol,
                                            r,
                                            d,
                                            NumberOfPaths,
                                            steps);
    vector<double> logEulerResult =logEulerSchemeMC(Expiry,
                                    Strike,
                                    Spot,
                                    Vol,
                                    r,
                                    d,
                                    NumberOfPaths,
                                    steps);
    
    vector<double> MilsteinSchemeResult = MilsteinSchemeMC(Expiry,
                                                    Strike,
                                                    Spot,
                                                    Vol,
                                                    r,
                                                    d,
                                                    NumberOfPaths,
                                                    steps);


    
    

    cout <<"European Call Option Price using Closed-form formula = " << formularesult[0] << "\n";
    cout <<"European Put Option Price using Closed-form formula = " << formularesult[1] << "\n";
    cout << endl;
    
    cout <<"European Call Option price using single-step exact SDE solution = "<< mresult[0] << "\n";
    cout <<"European Put Option price using single-step exact SDE solution = " << mresult[1] << "\n";
    cout << endl;
    
    cout <<"European Call Option price using Euler numerical solution of SDE for spot = "<< EulerResult[0] << "\n";
    cout <<"European Put Option price using Euler numerical solution of SDE for spot = " << EulerResult[1] << "\n";
    cout << endl;
        
    cout <<"European Call Option price using Euler numerical solution of SDE for log spot = "<< logEulerResult[0] << "\n";
    cout <<"European Put Option price using Euler numerical solution of SDE for log spot = "<< logEulerResult[1] << "\n";
    cout << endl;
    
    
     cout <<"European Call Option price using Milstein numerical solution of SDE for spot = "<< MilsteinSchemeResult[0] << "\n";
     cout <<"European Put Option price using Milstein numerical solution of SDE for spot = " << MilsteinSchemeResult[1] << "\n";
     cout << endl;
    
     /*
     cout <<"European Call Option price using Euler numerical solution of SDE for spot = "<< mresult[0] << "\n";
     cout <<"European Put Option price using Euler numerical solution of SDE for spot = " << mresult[1] << "\n";
     cout << endl;
     
     
     */
    
    
    return 0;
}
