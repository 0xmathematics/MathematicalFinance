//
//  MCSamples.cpp
//  CF2-Barrier Option
//
//  Created by Hang Miao on 2/12/20.
//  Copyright © 2020 Hang Miao. All rights reserved.
//

#include "MCSamples.hpp"


MCSamples::MCSamples( const unsigned long NumberOfPaths_)
{
    PathsDone=0;
    Samples.resize(NumberOfPaths_)  ;
}
void MCSamples::ResetMCSamples()
{
    PathsDone=0;
}

StatisticsMC* MCSamples::clone() const
{
    return new MCSamples(*this);
}

void MCSamples::DumpOneResult(double OnePathDiscountedPayoff)
{
    Samples[PathsDone] = OnePathDiscountedPayoff;
    ++PathsDone;
}

std::vector<std::vector<double> >  MCSamples::GetResultsSoFar() const
{
    std::vector< std::vector<double> > Results(1);
    Results[0] =Samples;
    return Results;
}
