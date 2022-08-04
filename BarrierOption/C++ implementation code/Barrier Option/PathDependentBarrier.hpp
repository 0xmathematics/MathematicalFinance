//
//  PathDependentBarrier.hpp
//  HW2
//
//  Created by Hang Miao on 2/8/20.
//  Copyright © 2020 Hang Miao. All rights reserved.
//

#ifndef PathDependentBarrier_hpp
#define PathDependentBarrier_hpp

#include <stdio.h>
#include "PathDependent.h"
#include "PayOffBridge.h"

class PathDependentBarrier : public PathDependent
{
public:
    
    PathDependentBarrier(const MJArray& LookAtTimes_,
                       double DeliveryTime_,
                       const PayOffBridge& ThePayOff_,
                         const double Barrier_);
    
    virtual unsigned long MaxNumberOfCashFlows() const;
    virtual MJArray PossibleCashFlowTimes() const;
    virtual unsigned long CashFlows(const MJArray& SpotValues,
                                    std::vector<CashFlow>& GeneratedFlows) const;
    virtual ~PathDependentBarrier(){}
    virtual PathDependent* clone() const;
    
private:
    double Barrier;
    double DeliveryTime;
    PayOffBridge ThePayOff;
    unsigned long NumberOfTimes;
};





#endif /* PathDependentBarrier_hpp */
