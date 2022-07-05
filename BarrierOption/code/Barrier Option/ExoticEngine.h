//
//
//                      ExoticEngine.h
//
//

#ifndef EXOTIC_ENGINE_H
#define EXOTIC_ENGINE_H
#include "wrapper.h"
#include "Parameters.h"
#include "PathDependent.h"
#include "MCStatistics.h"
#include <vector>
#include "minmax.h"
class ExoticEngine
{
    friend class ExoticBSEngineCtrl; //for Control Variates Simulation to get access to the private member
    
    
public:

    ExoticEngine(const Wrapper<PathDependent>& TheProduct_,
                 const Parameters& r_);

    virtual void GetOnePath(MJArray& SpotValues)=0;

    void DoSimulation(StatisticsMC& TheGatherer, unsigned long NumberOfPaths );

    virtual ~ExoticEngine(){}
    double DoOnePath(const MJArray& SpotValues) const;

private:
    
    Wrapper<PathDependent> TheProduct;
    Parameters r;
    MJArray Discounts;
    mutable std::vector<CashFlow> TheseCashFlows;
};

#endif


