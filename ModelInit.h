#include <iostream>
#include <vector>
#include <cmath>
#include "Project.h"
#include "BSMCalib.h"
#include "Payoff.h"

using namespace std;


class ModelInit{
    public:

        void WriteCSVAm();
        void WriteCSVEu(); // write to Aprices and Eprices.
        int Begin(double t,double k_min,double k_max,double pay_choice,BSModel2 BSM_); //does most of the work. Fills up vectors containing time zero option prices.

    private:
        double k_i, h_j;
        vector< vector<double> > solE; // stores time zero prices for euro options
        vector< vector<double> > solA; // stores time zero prices for Am options
        double k1, k2;





};


