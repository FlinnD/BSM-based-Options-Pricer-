#include <vector>
#include <cmath>
#include "Project.h"
#include "Payoff.h"
using namespace std;


CorrBinModel::CorrBinModel(const BSModel2& model, double h_){
    vector<double> sigma = model.Get_sigma();
    S0 = model.Get_S0();


    double rho = model.Get_rho();
    r = model.Get_r();
    h = h_;

    alpha.push_back((r-(1/2)*pow(sigma[0],2))*h);

    alpha.push_back((r-(1/2)*pow(sigma[1],2))*h);

    beta.push_back(sigma[0]*sqrt(h));

    beta.push_back(sigma[1]*rho*sqrt(h));

    beta.push_back(sigma[1]*sqrt((1-pow(rho,2)*h)));


    q.push_back((exp(r*h)*S0[0]-S(1,0,0)[0])/(S(1,1,0)[0]-S(1,0,0)[0]));

    q.push_back((exp(r*h)*S0[1] - S(1,0,0)[1] + q[0]*S(1,0,0)[1] - q[0]*S(1,1,0)[1])/(S(1,0,0)[1]+q[0]*S(1,0,0)[1]-q[0]*S(1,1,0)[1]+S(1,0,1)[1]-q[0]*S(1,0,1)[1]+q[0]*S(1,1,1)[1]));


}


vector<double> CorrBinModel::S(int n, int j0, int j1) const{
    vector<double> S;

    S.push_back(S0[0]*exp(alpha[0]*n+beta[0]*(2*j0-n)));

    S.push_back(S0[1]*exp(alpha[1]*n+beta[1]*(2*j0-n)+beta[2]*(2*j1-n)));


    return S;
}


 bool CorrBinModel::IsArbitrageFree() const{
    //if risk neutral probabilities aren't within allowed range return 1.
    if(q[0]>0 && q[1] > 0 ){

        if(q[0]<1 && q[1] < 1){
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


 double CorrBinModel::Prob(int n, int j0, int j1) const{

    //calculate risk neutral prob for any node at any time using Combinatorics.
    return Combin(n,j0)*pow(q[0],j0)*pow((1-q[0]),(n-j0))*Combin(n,j1)*pow(q[1],j1)*pow((1-q[1]),(n-j1));




 }


