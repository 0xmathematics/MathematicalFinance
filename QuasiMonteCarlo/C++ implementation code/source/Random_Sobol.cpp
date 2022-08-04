//
//  Random_Sobol.cpp
//  CF_QuasiMonteCarlo
//
//  Created by Hang Miao on 2/19/20.
//  Copyright © 2020 Hang Miao. All rights reserved.
//
#include <limits.h> // for INT_MAX
#include "Random_Sobol.hpp"
//#include "sobol.hpp"
const long m = INT_MAX; //


Random_Sobol::Random_Sobol(unsigned long Dimensionality, unsigned long Seed)
:    RandomBase(Dimensionality),
InnerGenerator(Seed, Dimensionality),
InitialSeed(Seed)
{
    
}

RandomBase* Random_Sobol::clone() const
{
    return new Random_Sobol(*this);
}

void Random_Sobol::GetUniforms(MJArray& variates)
{
    int dim_num = GetDimensionality(); //note that dim_num should be less than 1111 for Sobol
    //float sobol_seq[dim_num];  // working in CodeX; not work in MS VS

    float* sobol_seq = new float[dim_num]; // working in  MS VS
    InnerGenerator.getSobolSeq( sobol_seq );
    for (unsigned long j=0; j < GetDimensionality(); j++)
        variates[j] = sobol_seq[j];
    delete[] sobol_seq;   // working in  MS VS
    
}

void Random_Sobol::Skip(unsigned long numberOfPaths)
{
    MJArray tmp(GetDimensionality());
    for (unsigned long j=0; j < numberOfPaths; j++)
        GetUniforms(tmp);
}

void Random_Sobol::SetSeed(unsigned long Seed)
{
    InitialSeed = Seed;
    InnerGenerator.SetSeed(Seed);
}

void Random_Sobol::Reset()
{
    InnerGenerator.SetSeed(InitialSeed);
}


void Random_Sobol::ResetDimensionality(unsigned long NewDimensionality)
{
    RandomBase::ResetDimensionality(NewDimensionality);
    InnerGenerator.SetSeed(InitialSeed);
}
