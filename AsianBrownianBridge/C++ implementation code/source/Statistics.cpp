//
//  Statistics.cpp
//  CF2-Barrier Option
//
//  Created by Hang Miao on 2/14/20.
//  Copyright © 2020 Hang Miao. All rights reserved.
//

#include "Statistics.hpp"



double Sample_Mean(const vector<double>& Samples){
    unsigned long N = Samples.size();
    double sum = std::accumulate(Samples.begin(), Samples.end(), 0.0);
    return sum/ double(N);
}

double TSS(const vector<double>& X){ // total sum of square
    double mean = Sample_Mean( X);
    double accum = 0.0;
    std::for_each (std::begin(X), std::end(X), [&](const double d) {
        accum += (d - mean) * (d - mean);
    });
    return accum;
}

double Sample_Var(const vector<double>& X){
    unsigned long N = X.size();
    return TSS(X)/(N-1);
}

double Sample_sd(const vector<double>& X){
    double var = Sample_Var(X);
    return sqrt(var);
}

double sd_Sample_Mean(const vector<double>& X){
    double sd = Sample_sd(X);
    return sd/sqrt(X.size());
}

double CrossProductSUM(const vector<double>& X, const vector<double>&  Y){
    unsigned long N = X.size();
    double meanX = Sample_Mean( X);
    double meanY = Sample_Mean( Y);
    double accum = 0.0;
    for (int i =0; i<N; i++) {
        accum+=(X[i]-meanX)*(Y[i]-meanY);
    }
    return accum;
}

double Sample_Cov(const vector<double>& X, const vector<double>& Y ){
    return CrossProductSUM(X,Y)/(X.size()-1);
}

double Sample_Corr(const vector<double>& X, const vector<double>& Y ){
    double cov = Sample_Cov(X,Y);
    double sd_X = Sample_sd(X);
    double sd_Y = Sample_sd(Y);
    
    return cov/(sd_X*sd_Y);
}






