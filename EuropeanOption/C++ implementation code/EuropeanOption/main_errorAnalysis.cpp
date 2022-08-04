//
//  main_errorAnalysis.cpp
//  Pricing European Option
//  Black-Scholes Formula, Monte Carlo Method, Euler and Milstein Scheme for Numerical Solution of SDE 
//
//  Created by Hang Miao on 2/6/18.
//  Copyright © 2018 Hang Miao. All rights reserved.
//

//
//
/*
#include <time.h> 
#include <stdlib.h>
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


#include <iostream>
using std::ostream;
using std::istream;
using std::cout;
using std::cin;
using std::endl;
using std::fixed;
#include <iomanip>
using std::setw;
using std::setprecision;
#include <vector>
using std::vector;
#include <string>
using std::string;
#include <fstream>
using namespace std;



int main()
{

    ofstream myfile;
    myfile.open ("Dataset_error.csv");
    myfile << "NumberOfPaths,SimpleMCcallmean,SimpleMCputmean,SimpleMCCallError,SimpleMCputError,EulerSpotCallmean,EulerSpotPutmean,EulerSpotCallError,EulerSpotPutError,EulerLogSpotCallmean,EulerLogSpotPutmean,EulerLogSpotCallError,EulerLogSpotPutError,MilsteinCallmean,MilsteinPutmean,MilsteinCallError,MilsteinPutError,\n";
    const double Expiry = 1;
    const double Strike = 110;
    const double Spot = 100;
    const double Vol = 0.3;
    const double r = 0.05;
    const double d = 0.02;
    const unsigned long steps = 252;
    //const unsigned long NumberOfPaths = 100000;
    unsigned long NumberOfPaths = 50;
    unsigned long nextNumberOfPaths = 100;
    double callError;   
    double putError;
    double EcallError;  // Euler
    double EputError;
    double LcallError;  // log
    double LputError;
    double McallError;  // Milstein
    double MputError;


    //9.05705
    //15.6724
    
    while (NumberOfPaths<= 100000) {
        vector<double> EulerResult;
        vector<double> mresult;
        vector<double> MilsteinSchemeResult;
        vector<double> logEulerResult;
        
        double callVar = 0;
        double putVar = 0;
        double EcallVar = 0;
        double EputVar = 0;
        double LcallVar = 0;
        double LputVar = 0;
        double McallVar = 0;
        double MputVar = 0;
        
        double callsum = 0;
        double putsum = 0;
        double Ecallsum = 0;
        double Eputsum = 0;
        double Lcallsum = 0;
        double Lputsum = 0;
        double Mcallsum = 0;
        double Mputsum = 0;
        
        for (int i = 0; i <50 ; i++) {
            srand (time(NULL));
                            mresult = SimpleMonteCarlo1(Expiry,
                                                       Strike,
                                                       Spot,
                                                       Vol,
                                                       r,
                                                       d,
                                                       NumberOfPaths);
            
                            EulerResult = EulerSchemeMC(Expiry,
                                                       Strike,
                                                       Spot,
                                                       Vol,
                                                       r,
                                                       d,
                                                       NumberOfPaths,
                                                       steps);
            
                            logEulerResult =logEulerSchemeMC(Expiry,
                                                            Strike,
                                                            Spot,
                                                            Vol,
                                                            r,
                                                            d,
                                                            NumberOfPaths,
                                                            steps);
            
                            MilsteinSchemeResult = MilsteinSchemeMC(Expiry,
                                                                   Strike,
                                                                   Spot,
                                                                   Vol,
                                                                   r,
                                                                   d,
                                                                   NumberOfPaths,
                                                                   steps);
            callsum+=mresult[0];
            putsum +=mresult[1];
            callVar+=(mresult[0]-9.05705)*(mresult[0]-9.05705);
            putVar+=(mresult[1]-15.6724)*(mresult[1]-15.6724);
            
            Ecallsum+=EulerResult[0];
            Eputsum +=EulerResult[1];
            EcallVar+=(EulerResult[0]-9.05705)*(EulerResult[0]-9.05705);
            EputVar+=(EulerResult[1]-15.6724)*(EulerResult[1]-15.6724);
            
            Lcallsum+=logEulerResult[0];
            Lputsum +=logEulerResult[1];
            LcallVar+=(logEulerResult[0]-9.05705)*(logEulerResult[0]-9.05705);
            LputVar+=(logEulerResult[1]-15.6724)*(logEulerResult[1]-15.6724);
            
            Mcallsum+=MilsteinSchemeResult[0];
            Mputsum +=MilsteinSchemeResult[1];
            McallVar+=(MilsteinSchemeResult[0]-9.05705)*(MilsteinSchemeResult[0]-9.05705);
            MputVar+=(MilsteinSchemeResult[1]-15.6724)*(MilsteinSchemeResult[1]-15.6724);
        }
        callError =sqrt(callVar/50/NumberOfPaths);
        putError =sqrt(putVar/50/NumberOfPaths);
        EcallError =sqrt(EcallVar/50/NumberOfPaths);
        EputError =sqrt(EputVar/50/NumberOfPaths);
        LcallError =sqrt(LcallVar/50/NumberOfPaths);
        LputError =sqrt(LputVar/50/NumberOfPaths);
        McallError =sqrt(McallVar/50/NumberOfPaths);
        MputError =sqrt(MputVar/50/NumberOfPaths);
        
        myfile <<NumberOfPaths <<","<< callsum/50 <<","<<putsum/50<< ","<<callError << ","<<putError <<","<< Ecallsum/50 <<","<<Eputsum/50<< ","<<EcallError << ","<<EputError<<","<< Lcallsum/50 <<","<<Lputsum/50<< ","<<LcallError << ","<<LputError  <<","<< Mcallsum/50 <<","<< Mputsum/50<< ","<< McallError << ","<<MputError <<",\n";

        
        unsigned long temp = nextNumberOfPaths;
        nextNumberOfPaths += NumberOfPaths;
        NumberOfPaths += temp;
        cout<<NumberOfPaths<<endl;
    }

myfile.close();
    
    return 0;
}
