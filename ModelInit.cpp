#include <iostream>
#include <vector>
#include <cmath>
#include <fstream>
#include <string>
#include "Project.h"
#include "BSMCalib.h"
#include "Payoff.h"
#include "ModelInit.h"

using namespace std;

int ModelInit::Begin(double t,double k_min,double k_max,double pay_choice,BSModel2 BSM_){
    //method fills two vectors with prices for various strike prices and expiry dates.
    vector<double> sol1;
    vector<double> sol2;
    k1 = k_min;
    k2 = k_max;
    for(int i = 0; i <= 10; i++){

            for(int j = 1; j <= 5; j++){

                k_i = k_min + ((double)i/10)*(k_max-k_min);

                //SetPayoff(pay_choice);
               if(pay_choice == 1){

                   Spread pay(k_i);
                   h_j = t/100*(double)j;
                   CorrBinModel corr(BSM_, h_j);
                   if(corr.IsArbitrageFree() ==1) return 1;
                   sol1.push_back(PriceEuropean(corr, pay, 100*j)); //value in each column in a some row for euro option price.
                   sol2.push_back(PriceAmerican(corr, pay, 100*j));
                   if(j == 5){
                        //we have now finished the row so add row to another vector corresponding to a column.
                        solE.push_back(sol1);
                        sol1.clear(); // empty sol1 so we can fill it up again for new row.
                        solA.push_back(sol2);
                        sol2.clear();

                   }

                }

                else if(pay_choice == 2){

                    Min pay(k_i);
                    h_j = t/100*(double)j;
                    CorrBinModel corr(BSM_, h_j);
                    if(corr.IsArbitrageFree() ==1) return 1;
                    sol1.push_back(PriceEuropean(corr, pay, 100*j));
                  //  cout << PriceEuropean(corr, pay, 100*j)  << endl;
                    sol2.push_back(PriceAmerican(corr, pay, 100*j));
                    if(j == 5){
                        solE.push_back(sol1);
                        sol1.clear();
                        solA.push_back(sol2);
                        sol2.clear();

                   }
                }

                else{


                   Max pay(k_i);
                   h_j = t/100*(double)j;
                   CorrBinModel corr(BSM_, h_j);
                   if(corr.IsArbitrageFree() ==1) return 1;
                   sol1.push_back(PriceEuropean(corr, pay, 100*j));
                  // cout << PriceEuropean(corr, pay, 100*j)  << endl;
                   sol2.push_back(PriceAmerican(corr, pay, 100*j));
                   if(j == 5){
                        solE.push_back(sol1);
                        sol1.clear();
                        solA.push_back(sol2);
                        sol2.clear();

                   }
                }

            }

        }
    return 0;

}

void ModelInit::WriteCSVAm(){

ofstream outputA("Aprices.csv");


outputA<< "," << "N=100" << "," << "N=200" <<"," << "N=300" <<"," << "N=400" <<"," << "N=500" << endl; //headers.

for(int i = 0; i <= 10; i++){

        outputA << "K=" << k1 + ((double)i/10)*(k2-k1) << ","; //each row begins with the strike price
        for(int j = 0; j <= 4; j++){

                outputA << solA[i][j] << ","; //insert a value into the csv in the right col and row.

        }
        outputA<< endl;
}

outputA.close();

}


void ModelInit::WriteCSVEu(){

ofstream outputE ("Eprices.csv");


outputE<< "," << "N=100" << "," << "N=200" <<"," << "N=300" <<"," << "N=400" <<"," << "N=500" << endl;

for(int i = 0; i <= 10; i++){
        outputE << "K=" << k1 + ((double)i/10)*(k2-k1) << ",";

        for(int j = 0; j <= 4; j++){
                outputE << solE[i][j] << ",";

        }
        outputE<< endl;

}

outputE.close();
}


