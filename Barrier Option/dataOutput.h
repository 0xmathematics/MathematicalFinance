//
//  dataOutput.h
//  Pricing European Option
//  Black-Scholes Formula, Monte Carlo Method, Euler and Milstein Scheme for Numerical Solution of SDE 
//
//  Created by Hang Miao on 6/16/22.
//  Copyright © 2018 Hang Miao. All rights reserved.#pragma once


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

using std::cout;
using std::cin;
using std::endl;
using std::setw;

void writeCSV(std::vector<double>& result, std::string pathname)
{

    ofstream myfile;
    myfile.open(pathname);
    myfile << "samples\n";
    for (int n = 0; n < result.size(); n++)
    {
        myfile << result[n] << endl;
    }
    myfile.close();
};
