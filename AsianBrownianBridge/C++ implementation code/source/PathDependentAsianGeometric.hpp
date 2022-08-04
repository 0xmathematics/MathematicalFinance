//
//  PathDependentAsianGeometric.hpp
//  CF4_AsianBrownianBridge
//
//  Created by Hang Miao on 3/11/20.
//  Copyright © 2020 Hang Miao. All rights reserved.
//

#ifndef PathDependentAsianGeometric_hpp
#define PathDependentAsianGeometric_hpp

#include "PathDependent.h"
#include "PayOffBridge.h"

class PathDependentAsianGeometric : public PathDependent
{
public:
    
    PathDependentAsianGeometric(const MJArray& LookAtTimes_,
                       double DeliveryTime_,
                       const PayOffBridge& ThePayOff_);
    
    virtual unsigned long MaxNumberOfCashFlows() const;
    virtual MJArray PossibleCashFlowTimes() const;
    virtual unsigned long CashFlows(const MJArray& SpotValues,
                                    std::vector<CashFlow>& GeneratedFlows) const;
    
    virtual ~PathDependentAsianGeometric(){}
    virtual PathDependent* clone() const;
    
private:
    
    double DeliveryTime;
    PayOffBridge ThePayOff;
    unsigned long NumberOfTimes;
};




#endif /* PathDependentAsianGeometric_hpp */
