//
//  ExoticBSEngineCtrl.cpp
//  CF2-Barrier Option
//
//  Created by Hang Miao on 2/13/20.
//  Copyright © 2020 Hang Miao. All rights reserved.
//

#include "ExoticBSEngineCtrl.hpp"
#include <cmath>
void ExoticBSEngineCtrl::GetOnePath(MJArray& SpotValues)
{
    
    TheGenerator->GetGaussians(Variates);
    
    double CurrentLogSpot = LogSpot;
    
    for (unsigned long j=0; j < NumberOfTimes; j++)
    {
        CurrentLogSpot += Drifts[j];
        CurrentLogSpot += StandardDeviations[j]*Variates[j];
        SpotValues[j] = exp(CurrentLogSpot);
    }
    
    return;
}




ExoticBSEngineCtrl::ExoticBSEngineCtrl(const Wrapper<PathDependent>& TheProduct_,
                               const Parameters& R_,
                               const Parameters& D_,
                               const Parameters& Vol_,
                               const Wrapper<RandomBase>& TheGenerator_,
                               double Spot_,
                                const PayOffBridge& ThePayOff_)
:
ExoticBSEngine( TheProduct_,
                R_,
                D_,
                Vol_,
                TheGenerator_,
               Spot_),
ThePayOff(ThePayOff_)
{
    
}

void ExoticBSEngineCtrl::DoCtrlSimulation(StatisticsMC& TheGathererY, StatisticsMC& TheGathererX, unsigned long NumberOfPaths)
{
    unsigned long NumOfSpots = TheProduct->GetLookAtTimes().size();
    MJArray SpotValues(NumOfSpots);
    TheseCashFlows.resize(TheProduct->MaxNumberOfCashFlows());
    
    double thisValue;
    double ControlValue;
    for (unsigned long i =0; i < NumberOfPaths; ++i)
    {
        GetOnePath(SpotValues);
        thisValue = DoOnePath(SpotValues);
        TheGathererY.DumpOneResult(thisValue);
        ControlValue = ThePayOff(SpotValues[NumOfSpots-1])*Discounts[0];
        TheGathererX.DumpOneResult(ControlValue);
    }
    
    return;
}
