//
//  main_errorAnalysis.cpp
//  Pricing European Option
//  Black-Scholes Formula, Monte Carlo Method, Euler and Milstein Scheme for Numerical Solution of SDE 
//
//  Created by Hang Miao on 6/16/22.
//  Copyright © 2018 Hang Miao. All rights reserved.
//

//
//

//
//
//
//  Created by Hang Miao on 2/12/20.
//  Copyright © 2020 Hang Miao. All rights reserved.

//  Barrier Option Project
/*
    uses source files
    AntiThetic.cpp
    Arrays.cpp,
    ConvergenceTable.cpp,  //ConvergenceTable.cpp is used only for testing
    ExoticBSEngine.cpp
    ExoticEngine
    MCStatistics.cpp
    Normals.cpp
    Parameters.cpp,
    ParkMiller.cpp,
    PathDependent.cpp
    PayOff3.cpp,
    PayOffBridge.cpp,
    Random2.cpp,
  */
#include "ParkMiller.h"
#include <iostream>
#include <iomanip> // for setw
#include <time.h>  // for counting the excution time
#include <valarray>
#include <numeric> // for accumulate summation min max
#include <vector>

#include "MCStatistics.h"
#include "ConvergenceTable.h"
#include "AntiThetic.h"
#include "ExoticBSEngine.h"
#include "BarrierFormula.hpp"
#include "PathDependentBarrier.hpp"
#include "MCSamples.hpp"
#include "ExoticBSEngineCtrl.hpp"
#include "Statistics.hpp" // for sample mean, sample variance, sample sd
#include "BSMformula.h" // for Black-Scholes formula used in Vanila Control Variates
#include "dataOutput.h"
// #include "../dataOutput.h"



int main()
{
   


    clock_t t1, t2;

    const double Expiry = 1;
    const double Strike = 20;
    const double Spot = 100;
    const double Vol = 0.3;
    const double r = 0.05;
    const double d = 0.02;
    const double Barrier = 120;
    const unsigned long NumberOfPaths = 100000;
    const unsigned long NumberOfDates = 252;
    /**/
     //******************************************************
     // Barrier Option Closed Form Formula
     //******************************************************

    t1 = clock();
    vector<double> barrierF = BarrierFormula(Expiry,
        Strike,
        Spot,
        Vol,
        r,
        d,
        Barrier);
    t2 = clock();
    float diff((float)t2 - (float)t1);
    float seconds = diff / CLOCKS_PER_SEC;

    cout << endl;
    cout << " Closed form barrier option price = " << barrierF[0] << ", run time = " << seconds << " seconds" << endl;

    //******************************************************
    // Vanilla Option Closed Form Formula
    //******************************************************

    t1 = clock();
    vector<double> BSoption = BSMformula(Expiry,
        Strike,
        Spot,
        Vol,
        r,
        d);
    t2 = clock();
    diff = (float)t2 - (float)t1;
    seconds = diff / CLOCKS_PER_SEC;

    cout << endl;
    cout << " Closed form Black-Scholes option price = " << BSoption[0] << ", run time = " << seconds << " seconds" << endl;

    //******************************************************
    //Barrier Option Monte Carlo Simulation Initialization
    //******************************************************
    PayOffCall thePayOff(Strike);
    MJArray times(NumberOfDates);

    for (unsigned long i = 0; i < NumberOfDates; i++)
        times[i] = (i + 1.0) * Expiry / NumberOfDates;

    ParametersConstant VolParam(Vol);
    ParametersConstant rParam(r);
    ParametersConstant dParam(d);
    PathDependentBarrier theOption(times, Expiry, thePayOff, Barrier);


    RandomParkMiller generator(NumberOfDates);
    AntiThetic GenTwo(generator);

    //************************************************************************
    //Barrier Option Monte Carlo Simulation using Park Miller Random Generator
    //************************************************************************
    MCSamples Sample_Getherer(NumberOfPaths);
    vector<double>  results;
    double SampleMean;
    //-----------------------------------------------------------------------------------
    t1 = clock();  //clock start
    ExoticBSEngine theEngine(theOption, rParam, dParam, VolParam, generator, Spot);
    theEngine.DoSimulation(Sample_Getherer, NumberOfPaths);
    // sample mean
    results = Sample_Getherer.GetResultsSoFar()[0];
    SampleMean = Sample_Mean(results);
    t2 = clock();  //clock ends
    writeCSV(results, "MC_sample.csv");
    //-----------------------------------------------------------------------------------
    // total amount of time
    diff = (float)t2 - (float)t1;
    seconds = diff / CLOCKS_PER_SEC;
    
    // output the results
    cout << endl;
    cout << " Monte Carlo barrier option price = " << SampleMean << ", std error = " << sd_Sample_Mean(results) << ", run time = " << seconds << " seconds" << endl;

    //*********************************************************************************************
    //Barrier Option Monte Carlo Simulation using Antithetic Park Miller Random Generator
    //*********************************************************************************************
    // set samplepath = 0
    Sample_Getherer.ResetMCSamples();
    //-----------------------------------------------------------------------------------
    t1 = clock();  //clock start
    ExoticBSEngine Antithetic_Engine(theOption, rParam, dParam, VolParam, GenTwo, Spot);
    Antithetic_Engine.DoSimulation(Sample_Getherer, NumberOfPaths);
    // sample mean
    results = Sample_Getherer.GetResultsSoFar()[0];
    SampleMean = Sample_Mean(results);
    t2 = clock();  //clock ends
    writeCSV(results, "AV_sample.csv");
    //-----------------------------------------------------------------------------------
    // total amount of time
    diff = (float)t2 - (float)t1;
    seconds = diff / CLOCKS_PER_SEC;

    cout << endl;
    cout << " Antithetic variates barrier option price = " << SampleMean << ", std error = " << sd_Sample_Mean(results) << ", run time = " << seconds << " seconds" << endl;


    //*********************************************************************************************
    //Barrier Option Monte Carlo Simulation using Vanila as Control Variates
    //*********************************************************************************************
    // Declaration of the Sample Gatherer(during MC) and the vectors for storing the MC result
    const double CtrlStrike = Strike;
    PayOffCall CtrlPayOff(CtrlStrike);
    vector<double>  Y;
    vector<double>  X;
    //-----------------------------------------------------------------------------------
    t1 = clock();  //clock start
    //Monte Carlo Process
    ExoticBSEngineCtrl ControlEngine(theOption, rParam, dParam, VolParam, generator, Spot, CtrlPayOff);
    int J1 = 0.1 * NumberOfPaths;
    int J2 = 0.9 * NumberOfPaths;
    MCSamples Sample_GethererY_b(J1);
    MCSamples Sample_GethererX_b(J1);

    ControlEngine.DoCtrlSimulation(Sample_GethererY_b, Sample_GethererX_b, J1);
    // Retrieve the data from Getherer
    Y = Sample_GethererY_b.GetResultsSoFar()[0];
    X = Sample_GethererX_b.GetResultsSoFar()[0];
    // Estimate the b_hat which minize the Variance of the Control Variates Estimator
    double b_hat = CrossProductSUM(X, Y) / TSS(X);

    MCSamples Sample_GethererY(J2);
    MCSamples Sample_GethererX(J2);
    ControlEngine.DoCtrlSimulation(Sample_GethererY, Sample_GethererX, J2);
    // Retrieve the data from Getherer
    Y = Sample_GethererY.GetResultsSoFar()[0];
    X = Sample_GethererX.GetResultsSoFar()[0];
    // Expectation of X, which is same as the Black-Scholes Call option
    double E_X = BSMformula(Expiry, CtrlStrike, Spot, Vol, r, d)[0];
    // Adjust Each simulated Barrier Option Price by the Vanila Control Variate
    vector<double> Y_b(Y.size());
    for (int i = 0; i < Y.size(); i++) {
        Y_b[i] = Y[i] - b_hat * (X[i] - E_X);
        //cout<< Y_b[i]<<endl;
    }
    // Barrier with Vanila Control Variates Estimator
    SampleMean = Sample_Mean(Y_b);
    t2 = clock();  //clock ends
    writeCSV(Y_b, "CV_sample.csv");
    //-----------------------------------------------------------------------------------
    // total amount of time
    diff = (float)t2 - (float)t1;
    seconds = diff / CLOCKS_PER_SEC;



    // results output
    cout << endl;
    //cout<<"size of Y "<<Y.size()<<endl;
    cout << " Control variates barrier option price = " << SampleMean << ", std error = " << sd_Sample_Mean(Y_b) << ", run time = " << seconds << " seconds" << endl;
    cout << endl;
    cout << "b_hat = " << b_hat << endl;
    double rho = Sample_Corr(X, Y);
    cout << "Corr = " << rho << endl;

    cout << endl;
    cout << "Control variates MC Barrier Sample Mean Y = " << Sample_Mean(Y) << ", std error = " << sd_Sample_Mean(Y) << endl;
    cout << "Control variates MC Vanila Sample Mean X = " << Sample_Mean(X) << ", std error = " << sd_Sample_Mean(X) << endl;
    cout << "`Control variates Vanila Population Mean X = " << E_X << endl;

    //test
    /*
    double sd_Ymean = sd_Sample_Mean(Y);
    double sdmeanYb = sd_Ymean*sd_Ymean*(1-rho*rho);
    cout<< sqrt(sdmeanYb)<<endl;
    cout<< sd_Sample_Mean(Y_b)<<endl;
    cout<< "corr= "<<rho<<endl;
 */

 /**/
    double tmp;
    cin >> tmp;

    return 0;

}

