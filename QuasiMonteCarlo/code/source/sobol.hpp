
//  Random_Sobol.hpp
//  CF_QuasiMonteCarlo
//
//  Created by Hang Miao on 2/19/20.
//  Copyright © 2020 Hang Miao. All rights reserved.

#ifndef sobol_hpp
#define sobol_hpp
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string>
using namespace std;





class Sobol
{
public:
    
    Sobol(int Seed = 1, int dim_num =1);
    void SetSeed(int Seed);
    static unsigned long Max();
    static unsigned long Min();
    void getSobolSeq(float seq[]);
    
    
    int i4_bit_hi1 ( int n );
    int i4_bit_lo0 ( int n );
    int i4_max ( int i1, int i2 );
    int i4_min ( int i1, int i2 );
    void i4_sobol ( int dim_num, int *seed, float quasi[ ] );
    float *i4_sobol_generate ( int m, int n, int skip );
    int i4_uniform ( int b, int c, int *seed );
    
    int i8_bit_hi1 ( long long int n );
    int i8_bit_lo0 ( long long int n );
    long long int i8_max ( long long int i1, long long int i2 );
    long long int i8_min ( long long int i1, long long int i2 );
    void i8_sobol ( int dim_num, long long int *seed, double quasi[ ] );
    double *i8_sobol_generate ( int m, int n, int skip );
    long long int i8_uniform ( long long int b, long long int c, int *seed );
    
    float r4_abs ( float x );
    int r4_nint ( float x );
    float r4_uniform_01 ( int *seed );
    
    double r8_abs ( double x );
    int r8_nint ( double x );
    double r8_uniform_01 ( int *seed );
    
    void r8mat_write ( string output_filename, int m, int n, double table[] );
    
    int tau_sobol ( int dim_num );
    void timestamp ( );
    
private:
    
    int Seed;
    int dim_num;
    
};
#endif /* Random_Sobol_hpp */



