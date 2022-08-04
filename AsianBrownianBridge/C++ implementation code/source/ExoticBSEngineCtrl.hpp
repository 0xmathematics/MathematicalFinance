//
//  ExoticBSEngineCtrl.hpp
//  CF2-Barrier Option
//
//  Created by Hang Miao on 2/13/20.
//  Copyright © 2020 Hang Miao. All rights reserved.
//

#ifndef ExoticBSEngineCtrl_hpp
#define ExoticBSEngineCtrl_hpp

#include <stdio.h>
#include "ExoticBSEngine.h"
#include "Random2.h"
#include "PayOffBridge.h"

class ExoticBSEngineCtrl : public ExoticBSEngine
{
    public:
    
    ExoticBSEngineCtrl(const Wrapper<PathDependent>& TheProduct_,
                   const Parameters& R_,
                   const Parameters& D_,
                   const Parameters& Vol_,
                   const Wrapper<RandomBase>& TheGenerator_,
                   double Spot_,
                    const PayOffBridge& ThePayOff_);
    void DoCtrlSimulation(StatisticsMC& TheGathererY, StatisticsMC& TheGathererX, unsigned long NumberOfPaths);
    virtual void GetOnePath(MJArray& SpotValues);
    virtual ~ExoticBSEngineCtrl(){}
    
    private:
    PayOffBridge ThePayOff;
    // store the random generator
};
#endif /* ExoticBSEngineCtrl_hpp */
