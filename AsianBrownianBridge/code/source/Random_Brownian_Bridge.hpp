//
//  Random_Brownian_Bridge.hpp
//  CF4_AsianBrownianBridge
//
//  Created by Hang Miao on 3/9/20.
//  Copyright © 2020 Hang Miao. All rights reserved.
//

#ifndef Random_Brownian_Bridge_hpp
#define Random_Brownian_Bridge_hpp

#include <stdio.h>
#include "ParkMiller.h"
#include "sobol.hpp"


class  Random_Brownian_Bridge: public RandomBase
{
public:
    
    Random_Brownian_Bridge(unsigned long Dimensionality, unsigned long Seed=1, double left_ =0, double right_ = 0);
    
    virtual RandomBase* clone() const;
    virtual void GetUniforms(MJArray& variates);
    virtual void Skip(unsigned long numberOfPaths);
    virtual void SetSeed(unsigned long Seed);
    virtual void Reset();
    
    virtual void GetGaussians(MJArray& variates);
    virtual void ResetDimensionality(unsigned long NewDimensionality);
    
    double Get_One_Brownian_Bridge(double x0, double x1, double s0, double s1, double s);
    void Get_One_Brownian_Bridge_Path(int Num, int T, MJArray& variates);
    void Get_One_Brownian_Bridge_Path(double w0, double wT, int N, int T, MJArray& variates);
    void Proportional_Stratified_Brownian_Bridge( int NumberOfStratum, int NumberOfPathes, vector<vector<MJArray>>& BrownianBridgeW);
private:
    RandomParkMiller InnerGenerator;
    int dim; // Back up Dimension which equals to the number of dates. The original dimension maybe modified during the brownian bridge Generation process, in order to generate 2^m of Intermediary value, we have to change the dimension to 2^m to apply the GetGaussian Method
    double left;
    double right;

    
};
#endif /* Random_Brownian_Bridge_hpp */
