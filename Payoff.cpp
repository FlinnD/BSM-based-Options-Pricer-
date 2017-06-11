#include <vector>
#include <cmath>
#include "Payoff.h"

using namespace std;

double Spread::Value(vector<double> S) const{

    if(S[0]-S[1]-k > 0){

        return S[0]-S[1]-k;
    }

    else{

        return 0;
    }

}


double Max::Value(vector<double> S) const{

    if(S[0] > S[1]){

        if(S[0] - k > 0){

            return S[0] -k;
        }

        else{
            return 0;

        }
    }
    else{

        if(S[1] - k > 0){
            return S[1] - k;

        }

        else{

            return 0;
        }
    }

}

double Min::Value(vector<double> S) const{

    if(S[0] < S[1]){

        if(S[0] - k > 0){
            return S[0] -k;
        }

        else{
            return 0;

        }
    }
    else{

        if(S[1] - k > 0){
            return S[1] - k;

        }

        else{

            return 0;
        }
    }

}

// n choose k calculating function.
double Combin(int n, int k){

    double l;
    double ans = 1;
    for(l=1; l<=k; l++){

        ans*=((double)n - (double)k + l)/l;
    }
    return ans;

 }


 double PriceEuropean(const CorrBinModel& model, const Payoff& payoff, int N){
    //find time zero price for euro option with specified payoff.
   double zeroprice = 0;

    for(int j0 = 0; j0<=N; j0++){

        for(int j1 = 0; j1 <= N; j1++){

           zeroprice = zeroprice + model.Prob(N,j0,j1)*payoff.Value(model.S(N,j0,j1));

        }

    }




    return exp(-model.Get_r()*model.Get_h()*N)*zeroprice;



 }

