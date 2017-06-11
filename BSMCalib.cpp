#include <iostream>
#include <vector>
#include <cmath>
#include <string>
#include <fstream>
#include "Project.h"
#include "BSMCalib.h"
using namespace std;


void Calibrate::ReadCSV(){


        ifstream file1("data.csv");
        double r[rows][cols];
        if(file1.is_open()){
            for (int i = 0; i < rows; i++) {
                for (int j = 0; j < cols; j++) {
                    file1 >> r[i][j];//write each point to array
                    file1.get(); // get rid of the comma
                }
            }

            for (int i=0; i < rows; i++){
                S_0.push_back(r[i][0]); //fill up array S_0 with data.csv values

            }

            for(int i = 0; i < rows; i++){
                S_1.push_back(r[i][1]);


            }

        }


}


void Calibrate::CalibModel(){


    double svar_0 = SampVar(&S_0, &r_1, &r_bar1); //find sample variances by passing variable addresses as arguments.

    double svar_1 = SampVar(&S_1, &r_2, &r_bar2);


    vol_0 = sqrt(svar_0)/sqrt(tau); //historical volatility 1
    vol_1 = sqrt(svar_1)/sqrt(tau); //historical volatility 2

    SampCovar();

}


double Calibrate::SampVar(vector<double>* S, vector<double>* r, double* r_bar){//finds sample variance. Uses pointers so the function can be used twice

    double svar = 0;
    double m = (double)(rows-1); //rows is data type int so typecast is needed.

    (*r).resize(rows);

    for(int i = rows-1; i >= 1; i--){ //ignore the (*r)[0] entry as i =1,..,m for log returns.

        (*r)[i] = log(((*S)[i]/ (*S)[i-1]));


    }


    for(int i =1; i <rows; i++){

        svar = svar + pow((*r)[i],2);


    }

    for(int i =1; i < rows; i++){
        *r_bar = *r_bar + (*r)[i];

    }


     *r_bar = (1/m)*(*r_bar);

     svar = (1/(m- 1))* svar - (m/(m-1))*pow(*r_bar,2);

     return svar;

}


void Calibrate::SampCovar(){
    double m = (double)(rows-1);
    for(int i =1; i < rows; i++){
       covar = covar + r_1[i]*r_2[i];



    }

   covar = (1/(m-1))*covar - (m/(m-1))*r_bar1*r_bar2;



}

int Calibrate::LineNo(){

    ifstream file("data.csv");
    if (file.is_open()) {
        int lineno = 0;
        string na;
        while(getline(file,na)){ //count the number of lines in data.csv
            lineno++;


        }
     rows = lineno;
     file.close();
    }
    return rows;
}



double Calibrate::GetHistCorr(){

    return (covar/(tau*vol_1*vol_0));
}

double Calibrate::Getvol_0()
{
    return vol_0;
}

double Calibrate::Getvol_1()
{
    return vol_1;
}

