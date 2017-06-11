#include <iostream>
#include <vector>
#include <cmath>
#include "Project.h"
#include "BSMCalib.h"
#include "Payoff.h"
#include "ModelInit.h"
using namespace std;

int main(){
    Calibrate calib;
    vector<double> S0;
    double s1;
    double s2;
    double r;
    vector<double> sigma;
    cout << "Welcome to Flinn-Pricer" << endl << endl;

    cout << "First we must calculate values for the historical volatilities and correlation" << endl << endl;
    double tau;
    cout << "Enter tau (time interval length):";
    cin >> tau;
    calib.SetTau(tau);
    //row number is dynamic so we find it out from csv file
    calib.SetRows(calib.LineNo());

    calib.ReadCSV();
    //actually perform calculations
    calib.CalibModel();

    cout << "Historical volatility of stock 1 (S_0) is: "<< calib.Getvol_0() << endl;

    cout << "Historical volatility of stock 2 (S_1) is: "<< calib.Getvol_1() << endl;

    cout << "Historical correlation is: " << calib.GetHistCorr() << endl << endl;

    cout << "Enter the initial price of stock 1: ";
    cin.sync();    //flush the cin object.
    cin >> s1;
    S0.push_back(s1);

    cout << "Enter the initial price of stock 2: " ;
    cin >> s2;
    S0.push_back(s2);

    cout << "Enter interest rate r: ";
    cin >> r;

    sigma.push_back(calib.Getvol_0());

    sigma.push_back(calib.Getvol_1());

    BSModel2 BSM(S0, r, sigma, calib.GetHistCorr());

    if(BSM.IsWellDefined() ==1) return 1;

    double t,k_min,k_max;

    int pay_choice;

    cout << "Now lets calculate the time 0 option prices." <<endl;

    cout << "Enter the option expiry time: ";

    cin >> t;

    cout << "Enter the minimum strike price: ";

    cin >> k_min;

    cout << "Enter the maximum strike price: ";

    cin >> k_max;

    cout << "select a payoff type by choosing the corresponding number in the following list: " << endl << endl;

    cout << "1: Spread call" <<endl <<"2: Min call" << endl << "3: Max call" << endl;

    cout << "Payoff choice: ";

    cin >> pay_choice;

    cout << "Time zero option prices are now being calculated and written to CSV files. This may take up to 15 minutes." << endl << endl;
    //collect time zero prices.
    ModelInit minit;
    if(minit.Begin(t,k_min,k_max,pay_choice,BSM)==1) return 1;
    minit.WriteCSVAm();
    minit.WriteCSVEu();
    cout << "CSV files with according strike prices, payoff type and expiry dates have been written." <<endl;

    return 0;


}

