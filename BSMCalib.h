#ifndef BSMCalib_H
#define BSMCalib_H

#include <vector>
#include <cmath>

using namespace std;

class Calibrate{


    private:
        void SampCovar(); //helper functions have been made private
        double SampVar(vector<double>* S, vector<double>* r, double* r_bar);
        double tau;
        int rows;
        const int cols = 2; //column number is constant
        double vol_0 = 0;
        double vol_1 = 0;
        vector<double>  S_0;
        vector <double> S_1;
        vector<double> r_1;
        vector<double> r_2;
        double r_bar1 = 0;
        double r_bar2 = 0;
        double covar = 0;


    public:
        double GetTau(){return tau;}
        void SetTau(double tau_){tau=tau_;}
        void SetRows(int rows_){rows = rows_;}
        int LineNo();//find number of rows in csv
        void ReadCSV();
        void CalibModel();
        double Getvol_1();
        double Getvol_0();
        double GetHistCorr();





};
















#endif
