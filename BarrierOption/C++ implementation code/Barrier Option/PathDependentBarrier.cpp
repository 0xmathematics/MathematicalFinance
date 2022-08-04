//
//  PathDependentBarrier.cpp
//  HW2
//
//  Created by Hang Miao on 2/8/20.
//  Copyright © 2020 Hang Miao. All rights reserved.
//
#include "PathDependent.h"
#include "PathDependentBarrier.hpp"
//#include <algorithm>
//#include <iterator>
//
//
//

PathDependentBarrier::PathDependentBarrier(const MJArray& LookAtTimes_,
                                       double DeliveryTime_,
                                       const PayOffBridge& ThePayOff_,
                                           const double Barrier_)
:
PathDependent(LookAtTimes_), //base class constructor
DeliveryTime(DeliveryTime_),
ThePayOff(ThePayOff_),
NumberOfTimes(LookAtTimes_.size()),
Barrier(Barrier_)
{
}

unsigned long PathDependentBarrier::MaxNumberOfCashFlows() const
{
    return 1UL;
}

MJArray PathDependentBarrier::PossibleCashFlowTimes() const
{
    /*
    MJArray tmp(GetLookAtTimes());
    return tmp;
    */
    MJArray tmp(1);
    tmp[0] = DeliveryTime;
    return tmp;
}

unsigned long PathDependentBarrier::CashFlows(const MJArray& SpotValues,
                                            std::vector<CashFlow>& GeneratedFlows) const
{
    if (SpotValues.max() < Barrier ) {
        GeneratedFlows[0].TimeIndex = 0;
        GeneratedFlows[0].Amount =  ThePayOff(SpotValues[NumberOfTimes-1]);
        return 1;
    }
    else{
        /*
        int po = std::distance(std::begin(SpotValues), std::find(std::begin(SpotValues), std::end(SpotValues), Barrier));
         */

        GeneratedFlows[0].TimeIndex = 0UL;
        GeneratedFlows[0].Amount = 0.0;
        return 1UL;
    }
}

PathDependent* PathDependentBarrier::clone() const
{
    return new PathDependentBarrier(*this);
}

