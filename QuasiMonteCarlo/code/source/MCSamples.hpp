//
//  MCSamples.hpp
//  CF2-Barrier Option
//
//  Created by Hang Miao on 2/12/20.
//  Copyright © 2020 Hang Miao. All rights reserved.
//

#ifndef MCSamples_hpp
#define MCSamples_hpp

#include <stdio.h>
#include "MCStatistics.h"
#include "wrapper.h"

class MCSamples : public StatisticsMC
{
public:
    
    MCSamples( const unsigned long NumberOfPaths_);
    
    virtual StatisticsMC* clone() const;
    virtual void DumpOneResult(double result);
    virtual std::vector<std::vector<double> > GetResultsSoFar() const;
    void ResetMCSamples();
    
private:
    unsigned long int PathsDone;
    std::vector<double> Samples; //store the price of the barrier option for each path
};

/*
class StatisticsMean : public StatisticsMC
{
    
public:
    
    StatisticsMean();
    virtual void DumpOneResult(double result);
    virtual std::vector<std::vector<double> > GetResultsSoFar() const;
    virtual StatisticsMC* clone() const;
    
private:
    
    double RunningSum;
    unsigned long PathsDone;
    
};
*/

#endif /* MCSamples_hpp */
