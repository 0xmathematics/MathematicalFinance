//
//  Random_Brownian_Bridge.cpp
//  CF4_AsianBrownianBridge
//
//  Created by Hang Miao on 3/9/20.
//  Copyright © 2020 Hang Miao. All rights reserved.
//
#include <iostream>
#include <iomanip>
#include <cmath>
#include <vector>
#include "Random_Brownian_Bridge.hpp"
#include "Normals.h"
#include <limits> //for positive and negative infinity

using std::cout;
using std::cin;
using std::endl;
using std::setw;
using std::vector;
RandomBase* Random_Brownian_Bridge::clone() const
{
    return new Random_Brownian_Bridge(*this);
}

//no use just to fulfill the pure function of Base class
void Random_Brownian_Bridge::GetUniforms(MJArray& variates)
{
    InnerGenerator.GetUniforms(variates);
}

//no use just to fulfill the pure function of Base class
void Random_Brownian_Bridge::Skip(unsigned long numberOfPaths)
{
    MJArray tmp(GetDimensionality());
    for (unsigned long j=0; j < numberOfPaths; j++)
        GetUniforms(tmp);
}


void Random_Brownian_Bridge::SetSeed(unsigned long Seed)
{
    InnerGenerator.SetSeed(Seed);
}

void Random_Brownian_Bridge::Reset()
{
    InnerGenerator.Reset();
}


void Random_Brownian_Bridge::ResetDimensionality(unsigned long NewDimensionality)
{
    InnerGenerator.ResetDimensionality(NewDimensionality);
    //InnerGenerator.Reset();
}


Random_Brownian_Bridge::Random_Brownian_Bridge(unsigned long Dimensionality, unsigned long Seed, double left_, double right_)
:    RandomBase(Dimensionality),
dim(Dimensionality),
InnerGenerator(Dimensionality,Seed),
left(left_),
right(right_)
{

}

double Random_Brownian_Bridge::Get_One_Brownian_Bridge(double x0, double x1, double s0, double s1, double s){
    double Z = InnerGenerator.GetOneGaussian();
    return ( (s1-s)*x0 + (s-s0)*x1 )/ (s1-s0) + sqrt((s1-s)*(s-s0)/(s1-s0))*Z;
}

void Random_Brownian_Bridge:: Get_One_Brownian_Bridge_Path(int N, int T, MJArray& variates){
    
    //Creat the original Time Interval
    double dT = (double)T / (double)N;
    MJArray TIME(N+1);
    TIME[0] = 0;
    for (int i=1; i<= N; i++) {
        TIME[i] = TIME[i-1] + dT;
    }

    long m = ceil( log(N)/log(2) );
    long n = pow(2, m);
    
    InnerGenerator.ResetDimensionality(n);
    MJArray Znorms(n);
    InnerGenerator.GetGaussians(Znorms);
    InnerGenerator.ResetDimensionality(dim);
    
    //Creat the New Time Interval with 2^m stick, from 0 to T
    double dt = (double)T / (double)n;
    MJArray time(n+1);
    time[0] = 0;
    for (int i=1; i<= n; i++) {
        time[i] = time[i-1] + dt;
    }

    
    //Generate 2^m Wt using Brownian Bridge
    MJArray W(n+1);
    W[0] = 0; W[n] = sqrt(T)*Znorms[n-1];
    //cout<<"Wn is " <<W[n];
    long J = 1;
    long h = n;
    for (int k = 0; k<m; k++) {
        int imin = h/2;
        int i = imin;
        double l = 0; double r = h;
        for (int j =0; j<J; j++) {
            
            W[i] =  ( (time[r]-time[i])*W[l] + (time[i]-time[l])*W[r] )/(time[r]-time[l]) + sqrt( (time[r]-time[i])*(time[i]-time[l])/(time[r]-time[l]) )*Znorms[i-1];
            i = i+h; l = l+h; r = r+h;
        }
        J = 2*J; h = imin;
    }

    /**/
    // Apply Brownian Bridge again to generate the Wt on the original time scale
    MJArray B(N+1);
    B[0] = W[0]; B[N] = W[n];
    int i = 0; int j = 0;
    while ( i<=N) {
        //cout<<TIME[i]<<endl;
        //cout<<time[j]<<endl;
        if (TIME[i] == time[j]) {
            B[i] = W[i];
            i++;
            j++;
            
        }
        else if (TIME[i] > time[j]){
            if (TIME[i]<time[j+1]) {
                B[i] = Get_One_Brownian_Bridge(W[j], W[j+1], time[j], time[j+1], TIME[i]);
                i++; j++;
            }
            else if(TIME[i]==time[j+1]){
                B[i] = W[j+1];
                j+=2; i++;
            }
            else{
                B[i] = Get_One_Brownian_Bridge(W[j+1], W[j+2], time[j+1], time[j+2], TIME[i]);
                //cout<< "error Ti > tj+1"<<endl;
                j+=2; i++;
            }
        }
        else{
            if (B[i] ==0) {
                cout<< "error Ti < tj"<<endl;
                
            }
            
        }
        //cout<<"i = "<<i<<" Bi is "<<B[i-1]<<endl;
    }
    //cout<< "i="<<i<<endl;
    //cout<< "j="<<j<<endl;
    for (int i=0; i<N; i++) {
        variates[i] = B[i+1];
    }
    
}


void Random_Brownian_Bridge::Get_One_Brownian_Bridge_Path(double w0, double wT, int N, int T, MJArray& variates){
    //Creat the original Time Interval
    double dT = (double)T / (double)N;
    MJArray TIME(N+1);
    TIME[0] = 0;
    for (int i=1; i<= N; i++) {
        TIME[i] = TIME[i-1] + dT;
    }
    
    long m = ceil( log(N)/log(2) );
    long n = pow(2, m);
    
    InnerGenerator.ResetDimensionality(n);
    MJArray Znorms(n);
    InnerGenerator.GetGaussians(Znorms);
    InnerGenerator.ResetDimensionality(dim);
    
    //Creat the New Time Interval with 2^m stick, from 0 to T
    double dt = (double)T / (double)n;
    MJArray time(n+1);
    time[0] = 0;
    for (int i=1; i<= n; i++) {
        time[i] = time[i-1] + dt;
    }
    
    
    //Generate 2^m Wt using Brownian Bridge
    MJArray W(n+1);
    W[0] = wT; W[n] = wT;
    //cout<<"Wn is " <<W[n];
    long J = 1;
    long h = n;
    for (int k = 0; k<m; k++) {
        int imin = h/2;
        int i = imin;
        double l = 0; double r = h;
        for (int j =0; j<J; j++) {
            
            W[i] =  ( (time[r]-time[i])*W[l] + (time[i]-time[l])*W[r] )/(time[r]-time[l]) + sqrt( (time[r]-time[i])*(time[i]-time[l])/(time[r]-time[l]) )*Znorms[i-1];
            i = i+h; l = l+h; r = r+h;
        }
        J = 2*J; h = imin;
    }
    
    /**/
    // Apply Brownian Bridge again to generate the Wt on the original time scale
    MJArray B(N+1);
    B[0] = W[0]; B[N] = W[n];
    int i = 0; int j = 0;
    while ( i<=N) {
        //cout<<TIME[i]<<endl;
        //cout<<time[j]<<endl;
        if (TIME[i] == time[j]) {
            B[i] = W[i];
            i++;
            j++;
            
        }
        else if (TIME[i] > time[j]){
            if (TIME[i]<time[j+1]) {
                B[i] = Get_One_Brownian_Bridge(W[j], W[j+1], time[j], time[j+1], TIME[i]);
                i++; j++;
            }
            else if(TIME[i]==time[j+1]){
                B[i] = W[j+1];
                j+=2; i++;
            }
            else{
                B[i] = Get_One_Brownian_Bridge(W[j+1], W[j+2], time[j+1], time[j+2], TIME[i]);
                //cout<< "error Ti > tj+1"<<endl;
                j+=2; i++;
            }
        }
        else{
            if (B[i] ==0) {
                cout<< "error Ti < tj"<<endl;
                
            }
            
        }
        //cout<<"i = "<<i<<" Bi is "<<B[i-1]<<endl;
    }
    //cout<< "i="<<i<<endl;
    //cout<< "j="<<j<<endl;
    for (int i=0; i<N; i++) {
        variates[i] = B[i+1];
    }
}

void Random_Brownian_Bridge::Proportional_Stratified_Brownian_Bridge( int NumberOfStratum, int NumberOfPathes, vector<vector<MJArray>>& BrownianBridgeW){
    
    //preliminary settings
    int infinity = std::numeric_limits<int>::max();
    int Ninfinity = std::numeric_limits<int>::min();
    double prob = 1/(double)NumberOfStratum;
    
    //create the stratum
    MJArray Stratum(NumberOfStratum+1);
    Stratum[0] =Ninfinity;
    Stratum[NumberOfStratum] =infinity;
    for (int i =1; i<NumberOfStratum; i++) {
        Stratum[i] = InverseCumulativeNormal(prob*i);
    }
    
    //sample the end point Wd from each stratum
    vector<vector<double>> Stratified_Wds; //row dimension is the number of pathes, column dim is number of stratum
    for (int i = 0 ; i<NumberOfPathes; i++) {
        vector<double> Stratified_Wd;
        for (int j = 0 ; j<NumberOfStratum; j++) {
            Stratified_Wd.push_back( Stratum[j]+ (Stratum[j+1]-Stratum[j])*InnerGenerator.GetOneUnif() ) ;
        }
        Stratified_Wds.push_back(Stratified_Wd);
    }
    
    //vector<vector<MJArray>> BrownianBridgeW; // layer 1: each different Trials; Layer 2: RV Wd in each stratum; layer 3: Wt in d dimension generated by Brownian Bridge
    
    for (int i = 0 ; i<NumberOfPathes; i++) {
        vector<MJArray> trials;
        for (int j = 0 ; j<NumberOfStratum; j++) {
            MJArray Path_Wd(dim+1);
            Get_One_Brownian_Bridge_Path(0, Stratified_Wds[i][j], (dim+1), 1, Path_Wd);
            /*
            for (int j=1; j<12; j++) {
                cout<< Path_Wd[j]<<" ";
            }
             */
            trials.push_back(Path_Wd);
        }
        BrownianBridgeW.push_back(trials);
    }
    
    
    
    //create the stratum
    InnerGenerator.GetOneUnif();
    
    
    
    
    
    
}

void Random_Brownian_Bridge::GetGaussians(MJArray& variates){
    
  // transform the brownian bridge back into the iid standard normal RV

}
