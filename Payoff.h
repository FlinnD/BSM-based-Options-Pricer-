#ifndef PAYOFF_H
#define PAYOFF_H

#include <vector>
#include <cmath>
#include<iostream>
#include "Project.h"

using namespace std;

//all payoff types inherit from Payoff and then override the Value method.

class Spread: public Payoff{

    public:
        Spread(double k_){k=k_;}
        double Value(vector<double> S) const;
        double test(){return 545;}

    private:
        double k;

};

class Min: public Payoff{

    public:
        Min(double k_){k=k_;}
        double Value(vector<double> S) const;
        double test(){return 7;}

    private:
        double k;

};


class Max: public Payoff{

    public:
        Max(double k_){k=k_;}
        double Value(vector<double> S) const;
        double test(){return 67;}

    private:
        double k;

};


double Combin(int n, int k);

//method for finding time zero price of the options. didn't really fit in any class.
double PriceEuropean(const CorrBinModel& model, const Payoff& payoff, int N);



#endif
