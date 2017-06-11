#include <iostream>
#include <vector>
#include <ostream>
#include <cmath>
#include<fstream>
using namespace std;


int main(){

    ifstream file ("data.csv");
    double S_0[14];
    string value1;
    string value2;
    double S_1[14];
    double i = 0;
    while (file.good())
    {
     getline(file, value1, ',');
     getline(file, value2, ',');
     i++;
    }

    cout << value1 << endl;

    cout << value2 << endl;

}
