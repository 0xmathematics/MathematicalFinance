//
//  PathDependentAsianGeometric.cpp
//  CF4_AsianBrownianBridge
//
//  Created by Hang Miao on 3/11/20.
//  Copyright © 2020 Hang Miao. All rights reserved.
//

#include "PathDependentAsianGeometric.hpp"
#include <cmath>
PathDependentAsianGeometric::PathDependentAsianGeometric(const MJArray& LookAtTimes_,
                                       double DeliveryTime_,
                                       const PayOffBridge& ThePayOff_)
:
PathDependent(LookAtTimes_),
DeliveryTime(DeliveryTime_),
ThePayOff(ThePayOff_),
NumberOfTimes(LookAtTimes_.size())
{
}


unsigned long PathDependentAsianGeometric::MaxNumberOfCashFlows() const
{
    return 1UL;
}

MJArray PathDependentAsianGeometric::PossibleCashFlowTimes() const
{
    MJArray tmp(1UL);
    tmp[0] = DeliveryTime;
    return tmp;
}

unsigned long PathDependentAsianGeometric::CashFlows(const MJArray& SpotValues,
                                            std::vector<CashFlow>& GeneratedFlows) const
{
    //double sum = SpotValues.sum();
    double product=1;
    for (int i=0; i<NumberOfTimes; i++) {
        product= product*SpotValues[i];
    }
    double oneOverd = (double)1/(double)NumberOfTimes;
    double mean = pow(product, oneOverd);
    
    GeneratedFlows[0].TimeIndex = 0UL;
    GeneratedFlows[0].Amount = ThePayOff(mean);
    
    return 1UL;
}


PathDependent* PathDependentAsianGeometric::clone() const
{
    return new PathDependentAsianGeometric(*this);
}
