//
//  Random_Sobol.hpp
//  CF_QuasiMonteCarlo
//
//  Created by Hang Miao on 2/19/20.
//  Copyright © 2020 Hang Miao. All rights reserved.
//

#ifndef Random_Sobol_hpp
#define Random_Sobol_hpp
#include "Random2.h"
#include <stdio.h>
#include "sobol.hpp"
#include <vector>

class Random_Sobol : public RandomBase
{
public:
    
    Random_Sobol(unsigned long Dimensionality, unsigned long Seed=1);
    
    virtual RandomBase* clone() const;
    virtual void GetUniforms(MJArray& variates);
    virtual void Skip(unsigned long numberOfPaths);
    virtual void SetSeed(unsigned long Seed);
    virtual void Reset();
    virtual void ResetDimensionality(unsigned long NewDimensionality);
    
private:
    
    Sobol InnerGenerator;
    unsigned long InitialSeed;
    
};
#endif /* Random_Sobol_hpp */
