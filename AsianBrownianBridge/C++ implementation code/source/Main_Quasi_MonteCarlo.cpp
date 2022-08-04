//
//
//
//  main.cpp
//  CF_QuasiMonteCarlo
//
//  Created by Hang Miao on 2/18/20.
//  Copyright © 2020 Hang Miao. All rights reserved.

//  Quasi Monte Carlo Project
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
#include"ParkMiller.h"
#include <iostream>
#include <iomanip> // for setw
#include <time.h>  // for counting the excution time
#include <valarray>
#include <numeric> // for accumulate summation min max
#include <vector>

#include "MCStatistics.h"
//#include "ConvergenceTable.h"
#include "AntiThetic.h"
#include "ExoticBSEngine.h"

#include "PathDependentAsian.h"
#include "MCSamples.hpp"
//#include "ExoticBSEngineCtrl.hpp"
#include "Statistics.hpp" // for sample mean, sample variance, sample sd
#include "BSMformula.h" // for Black-Scholes formula used in Vanila Control Variates
#include "BSM_GeometricAsianFormula.hpp" // for Geometric Asian Option closed form formula
#include "PathDependentAsianGeometric.hpp" // Pathdependent Geometric Asian
#include "Random_Sobol.hpp" // for Sobol Sequence
#include "Random_Brownian_Bridge.hpp" // for Brownian Bridge and Stratified Sampling


using std::cout;
using std::cin;
using std::endl;
using std::setw;
using std::vector;
using namespace std;
int main()
{


    clock_t t1,t2;
    const double Expiry = 1;
    const double Strike = 110;
    const double Spot = 100;
    const double Vol = 0.3;
    const double r = 0.05;
    //const double q = 0;
    const double d = 0.02;
    //const double Barrier = 120;
    const unsigned long NumberOfPaths = 10000;
    const unsigned long NumberOfDates = 12; // q for Asian
    
    //******************************************************
    //Arithmetic Asian Option Monte Carlo Simulation Initialization
    //******************************************************
    PayOffCall thePayOff(Strike);
    MJArray times(NumberOfDates);
    
    for (unsigned long i=0; i < NumberOfDates; i++)
        times[i] = (i+1.0)*Expiry/NumberOfDates;
    
    ParametersConstant VolParam(Vol);
    ParametersConstant rParam(r);
    ParametersConstant dParam(d);
    
    //Arithmetic Asian Option
    PathDependentAsian theOption(times, Expiry, thePayOff);
    PathDependentAsianGeometric theOptionGeometricAsian(times, Expiry, thePayOff);
    
    //Random generator
    RandomParkMiller generator(NumberOfDates);
    
    //antiThetic variance reduction techniques
    AntiThetic GenTwo(generator);

    
    //*********************************************************************************************
    //Arithmetic Asian Option Monte Carlo Simulation using Park Miller Random Generator
    //*********************************************************************************************
    MCSamples Sample_Getherer(NumberOfPaths);
    vector<double> results;
    double SampleMean;
    //-----------------------------------------------------------------------------------
    t1=clock();  //clock start
    ExoticBSEngine theEngine(theOption, rParam, dParam, VolParam, generator, Spot);
    theEngine.DoSimulation(Sample_Getherer, NumberOfPaths);
    
    // sample mean
    results = Sample_Getherer.GetResultsSoFar()[0];
    SampleMean = Sample_Mean(results);
    t2=clock();  //clock ends
    //-----------------------------------------------------------------------------------
    // total amount of time
    float diff = (float)t2-(float)t1;
    float seconds = diff / CLOCKS_PER_SEC;
    
    // output the results
    cout<<endl;
    cout <<" MC Arithmetic Asian call with Park-Miller uniforms = "<< SampleMean <<", std error = " <<sd_Sample_Mean(results) <<", run time = " << seconds<< " seconds"<<endl;
    
    //*********************************************************************************************
    //Arithmetic Asian Option Quasi Monte Carlo Simulation using Sobol Sequence
    //*********************************************************************************************
    // set samplepath = 0
    Sample_Getherer.ResetMCSamples();
    Random_Sobol RandomSobolSequence(NumberOfDates);
    //-----------------------------------------------------------------------------------
    t1=clock();  //clock start
    ExoticBSEngine Asian_Sobol_Engine(theOption, rParam, dParam, VolParam, RandomSobolSequence, Spot);
    Asian_Sobol_Engine.DoSimulation(Sample_Getherer, NumberOfPaths);
    // sample mean
    results = Sample_Getherer.GetResultsSoFar()[0];
    SampleMean = Sample_Mean(results);
    t2=clock();  //clock ends
    //-----------------------------------------------------------------------------------
    // total amount of time
    diff = (float)t2-(float)t1;
    seconds = diff / CLOCKS_PER_SEC;
    
    //cout<<endl;
    cout <<" QMC Arithmetic Asian call with Sobol sequence = "<< SampleMean <<", std error = " <<sd_Sample_Mean(results) <<", run time = " << seconds<< " seconds"<<endl ;
    

    ///*

    
    
   /**/
    //******************************************************
    // Geometric Asian Option Closed Form Formula
    //******************************************************
    t1=clock();
    // Expectation of X, which is same as the Black-Scholes Call option
    double E_X1 = GAsian_Cont(Expiry,Strike,Spot,Vol,r,d)[0];
    double E_X2 = GAsian_Disc(Expiry, Strike, Spot, Vol, r, d, NumberOfDates)[0];
    t2=clock();
    diff = (float)t2-(float)t1;
    seconds = diff / CLOCKS_PER_SEC;
    
    cout<<endl;
    cout<<endl;
    cout <<" Closed-form Geometric Asian Continuous call option price = "<< E_X1<<", run time = " << seconds<< " seconds"<<endl ;
    cout <<" Closed-form Geometric Asian Discrete call option price = "<< E_X2<<", run time = " << seconds<< " seconds"<<endl ;
    
    //*********************************************************************************************
    //Geometric Asian Option Monte Carlo Simulation using Park Miller Random Generator
    //*********************************************************************************************
    Sample_Getherer.ResetMCSamples();
    //-----------------------------------------------------------------------------------
    t1=clock();  //clock start
    ExoticBSEngine GeometricAsianEngine(theOptionGeometricAsian, rParam, dParam, VolParam, generator, Spot);
    GeometricAsianEngine.DoSimulation(Sample_Getherer, NumberOfPaths);
    
    // sample mean
    results = Sample_Getherer.GetResultsSoFar()[0];
    SampleMean = Sample_Mean(results);
    t2=clock();  //clock ends
    //-----------------------------------------------------------------------------------
    // total amount of time
     diff = (float)t2-(float)t1;
     seconds = diff / CLOCKS_PER_SEC;
    
    // output the results
    cout<<endl;
    cout <<" MC Geometric Asian call with Park-Miller uniforms = "<< SampleMean <<", std error = " <<sd_Sample_Mean(results) <<", run time = " << seconds<< " seconds"<<endl;
    
    //*********************************************************************************************
    //Geometric Asian Option Quasi Monte Carlo Simulation using Sobol Sequence
    //*********************************************************************************************
    // set samplepath = 0
    Sample_Getherer.ResetMCSamples();
    //RandomSobolSequence(NumberOfDates);
    //-----------------------------------------------------------------------------------
    t1=clock();  //clock start
    ExoticBSEngine GeometricAsian_Sobol_Engine(theOptionGeometricAsian, rParam, dParam, VolParam, RandomSobolSequence, Spot);
    GeometricAsian_Sobol_Engine.DoSimulation(Sample_Getherer, NumberOfPaths);
    // sample mean
    results = Sample_Getherer.GetResultsSoFar()[0];
    SampleMean = Sample_Mean(results);
    t2=clock();  //clock ends
    //-----------------------------------------------------------------------------------
    // total amount of time
    diff = (float)t2-(float)t1;
    seconds = diff / CLOCKS_PER_SEC;
    
    //cout<<endl;
    cout <<" QMC Geometric Asian call with Sobol sequence = "<< SampleMean <<", std error = " <<sd_Sample_Mean(results) <<", run time = " << seconds<< " seconds"<<endl ;
    
    
    
    //******************************************************
    // Vanilla Option Closed Form Formula
    //******************************************************
    
    t1=clock();
    // Expectation of X, which is same as the Black-Scholes Call option
    double E_X = BSMformula(Expiry,Strike,Spot,Vol,r,d)[0];
    t2=clock();
    diff = (float)t2-(float)t1;
    seconds = diff / CLOCKS_PER_SEC;
    cout<<endl;
    cout<<endl;
    cout <<" Closed-form Vanilla call option price = "<< E_X<<", run time = " << seconds<< " seconds"<<endl ;
    
    //******************************************************
    //Vanila Option Monte Carlo Simulation Initialization
    //******************************************************
    const unsigned long NumberOfDates_Vanila = 1; // q for Vanilla
    times.resize(NumberOfDates_Vanila);
    
    for (unsigned long i=0; i < NumberOfDates_Vanila; i++)
        times[i] = (i+1.0)*Expiry/NumberOfDates_Vanila;
    
    //Vanilla Option
    PathDependentAsian VanillaOption(times, Expiry, thePayOff);
    
    RandomParkMiller ParkMiller(NumberOfDates_Vanila);
    AntiThetic ParkMillerAntiThetic(ParkMiller);
    
    //*********************************************************************************************
    //Vanila Option Monte Carlo Simulation using Park Miller Random Generator
    //*********************************************************************************************
    // set samplepath = 0
    Sample_Getherer.ResetMCSamples();
    //-----------------------------------------------------------------------------------
    t1=clock();  //clock start
    ExoticBSEngine Vanilla_Engine(VanillaOption, rParam, dParam, VolParam, ParkMiller, Spot);
    Vanilla_Engine.DoSimulation(Sample_Getherer, NumberOfPaths);
    // sample mean
    results = Sample_Getherer.GetResultsSoFar()[0];
    SampleMean = Sample_Mean(results);
    t2=clock();  //clock ends
    //-----------------------------------------------------------------------------------
    // total amount of time
    diff = (float)t2-(float)t1;
    seconds = diff / CLOCKS_PER_SEC;
    
    //cout<<endl;
    cout <<" MC Vanilla call price with Park-Miller uniforms = "<< SampleMean <<", std error = " <<sd_Sample_Mean(results) <<", run time = " << seconds<< " seconds"<<endl ;
    /*
    //*********************************************************************************************
    //Vanila Option Monte Carlo Simulation using Antithetic Park Miller Random Generator
    //*********************************************************************************************
    // set samplepath = 0
    Sample_Getherer.ResetMCSamples();
    
    //-----------------------------------------------------------------------------------
    t1=clock();  //clock start
    ExoticBSEngine Vanilla_AntiThetic_Engine(VanillaOption, rParam, dParam, VolParam, ParkMillerAntiThetic, Spot);
    Vanilla_AntiThetic_Engine.DoSimulation(Sample_Getherer, NumberOfPaths);
    // sample mean
    results = Sample_Getherer.GetResultsSoFar()[0];
    SampleMean = Sample_Mean(results);
    t2=clock();  //clock ends
    //-----------------------------------------------------------------------------------
    // total amount of time
    diff = (float)t2-(float)t1;
    seconds = diff / CLOCKS_PER_SEC;
    
    cout<<endl;
    cout <<" MC Vanilla call price with Park-Miller uniforms and antithetics = "<< SampleMean <<", std error = " <<sd_Sample_Mean(results) <<", run time = " << seconds<< " seconds"<<endl ;
    */
    
    ///*
    //*********************************************************************************************
    //Vanila Option Quasi Monte Carlo Simulation using Sobol Sequence
    //*********************************************************************************************
    // set samplepath = 0
    Sample_Getherer.ResetMCSamples();
    //
    Random_Sobol RandomSobolSequence_Vanilla(NumberOfDates_Vanila);
    //-----------------------------------------------------------------------------------
    t1=clock();  //clock start
    ExoticBSEngine Vanilla_Sobol_Engine(VanillaOption, rParam, dParam, VolParam, RandomSobolSequence_Vanilla, Spot);
    Vanilla_Sobol_Engine.DoSimulation(Sample_Getherer, NumberOfPaths);
    // sample mean
    results = Sample_Getherer.GetResultsSoFar()[0];
    SampleMean = Sample_Mean(results);
    t2=clock();  //clock ends
    //-----------------------------------------------------------------------------------
    // total amount of time
    diff = (float)t2-(float)t1;
    seconds = diff / CLOCKS_PER_SEC;
    
    //cout<<endl;
    cout <<" QMC Vanilla call price with Sobol sequence = "<< SampleMean <<", std error = " <<sd_Sample_Mean(results) <<", run time = " << seconds<< " seconds"<<endl ;
    cout<<endl;

    
    
     //******************************************************
     // Test Brownian Bridge Simulation
     //******************************************************
    
    cout<<"The following are one path of Brownian Motion with 12 sampled observation point generated by Brownian Motion Bridge:" <<endl;
     MJArray variates(NumberOfDates);
     Random_Brownian_Bridge BrownianBridge(NumberOfDates);
     BrownianBridge.Get_One_Brownian_Bridge_Path(12, 1, variates);
     t2=clock();
     diff = (float)t2-(float)t1;
     seconds = diff / CLOCKS_PER_SEC;
     //output variates
     for (int i=0; i<12; i++) {
     cout<< variates[i]<<endl;
     }
    
    //******************************************************
    // Test Stratified Brownian Bridge Simulation
    //******************************************************
    cout<<endl;
    cout<<"The following are path of Brownian Motion Stratified at Maturity T generated by Brownian Motion Bridge."<<endl;
    cout<<"For demonstration, I choose 10 stratum at the maturity and with 12 discretely observed points during each Brownian Motion process" <<endl;
    vector<vector<MJArray>> BrownianBridgeW;
    int NumberOfStratum = 10;
    int NumberOfPathes = 5;

    BrownianBridge.Proportional_Stratified_Brownian_Bridge( NumberOfStratum, NumberOfPathes, BrownianBridgeW);
    
    //output Stratified_Wds
    cout<<endl;
    cout<< "************ 2st Trial ************"<<endl;
    for (int i=0; i<=12; i++) {
        for (int j=0; j<NumberOfStratum; j++) {
            cout<< BrownianBridgeW[1][j][i]<<" ";
        }
        cout<< endl;
    }
    
    cout<<endl;
    cout<< "************ 5st Trial ************"<<endl;
    for (int i=0; i<=12; i++) {
        for (int j=0; j<NumberOfStratum; j++) {
            cout<< BrownianBridgeW[4][j][i]<<" ";
        }
        cout<< endl;
    }
     /**/
    
    

    /**/
    
    
    cout<<endl;
    cout<<endl;
	return 0;

}
