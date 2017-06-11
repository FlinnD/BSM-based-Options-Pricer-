#include <vector>
#include <cmath>
#include "Project.h"
using namespace std;


BSModel2::BSModel2(vector<double> S0_, double r_, vector<double> sigma_, double rho_){
           //constructor just sets object variable values
            S0 = S0_;

            r = r_;

            sigma = sigma_;

            rho = rho_;


}


bool BSModel2::IsWellDefined() const{
    //checks that initial stock prices, interest and correlation are within allowed range
    if(S0[0] >= 0 && S0[1] >= 0 && r >= 0 && rho >= -1){

        if(rho <= 1){

            return 0;

        }

        else{

            return 1;
        }

    }

    else{
        return 1;


    }

}
