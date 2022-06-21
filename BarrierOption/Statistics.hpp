//
//  Statistics.hpp
//  CF2-Barrier Option
//
//  Created by Hang Miao on 2/14/20.
//  Copyright © 2020 Hang Miao. All rights reserved.
//

#ifndef Statistics_hpp
#define Statistics_hpp

#include <stdio.h>
#include <math.h>
#include <vector>
#include <numeric> // for accumulate summation min max
#include <algorithm>  // for_each

using std::vector;

double Sample_Mean(const vector<double>& );

double Sample_Var(const vector<double>& );
double Sample_sd(const vector<double>& ); //square root of Sample_Var
double sd_Sample_Mean(const vector<double>& ); //sd of sample mean

double TSS(const vector<double>& ); // total sum of square

double CrossProductSUM(const vector<double>& , const vector<double>&  );

double Sample_Cov(const vector<double>& , const vector<double>&  );

double Sample_Corr(const vector<double>& , const vector<double>&  );

#endif /* Statistics_hpp */
