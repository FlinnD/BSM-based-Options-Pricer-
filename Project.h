#ifndef PROJECT_H
#define PROJECT_H

#include <vector>
#include <ostream>
#include <cmath>

#define EPSILON 0.00001

using namespace std;

class BSModel2
{
	public:
		//Constructor.
		BSModel2 (vector<double> S0_, double r_, vector<double> sigma_, double rho_);

		//Returns 1 if model parameters satisfy the requirements stated in the model, otherwise 0.
		bool IsWellDefined () const;

	public:
		//member functions to allow access to values of internal parameters
		vector<double> Get_S0() const { return S0;}
		double Get_r() const { return r;}
		vector<double> Get_sigma() const { return sigma;}
		double Get_rho() const { return rho;}

	private:
		// Initial stock price vector
		vector<double> S0;

		// Interest rate
		double r;

		// Vector of volatilities
		vector<double> sigma;

		// Correlation between log-returns of the two assets
		double rho;
};

class CorrBinModel
{
    public:
        //Constructor. Computes qs, alphas and betas, but does not include any error checking.
        CorrBinModel (const BSModel2& model, double h_);

        //Computes stock price at node (j0,j1) time step n
        vector<double> S (int n, int j0, int j1) const;

        //returns 1 if 0<q[k]<1 for k=0,1
        bool IsArbitrageFree() const;

        //Probability of node (j0,j1) at time step n
        double Prob(int n, int j0, int j1) const;

        //Returns continuously compounded interest rate
        double Get_r() const {return r;}

        //Returns size of time step
        double Get_h() const { return h;}

        //Returns risk-neutral probability parameters
        vector<double> Get_q() const { return q;}

private:

    // Initial stock price vector
    vector<double> S0;

    // Interest rate
    double r;

    // Duration between time steps
    double h;

    // Vector of drifts
    vector<double> alpha;

    // Vector of volatility coefficients
    vector<double> beta;

    // Risk-neutral probabilities
    vector<double> q;
};

class Payoff
{
    public:
        virtual double Value(vector<double> S) const = 0;
};

// Prices American option with given Payoff in CorrBinModel.
inline double PriceAmerican (const CorrBinModel& model, const Payoff& payoff, int N)
{
    vector<vector<double> > v,pv;
    vector<double> q = model.Get_q();
    double d = exp(-model.Get_r()*model.Get_h()),
           q00d = d*(1-q[0])*(1-q[1]),
           q01d = d*(1-q[0])*q[1],
           q10d = d*q[0]*(1-q[1]),
           q11d = d*q[0]*q[1];
    double ev,cv;
    v.resize(N+1);
    for(int j0=0; j0<=N; j0++)
    {
        v[j0].resize(N+1);
        for(int j1=0; j1<=N; j1++)
            v[j0][j1] = payoff.Value(model.S(N,j0,j1));
    }
    for(int n=N-1; n>=0; n--)
    {
        pv=v;
        for(int j0=0;j0<=n;j0++)
            for(int j1=0; j1 <= n; j1++)
            {
                ev = payoff.Value(model.S(n,j0,j1));
                cv = q00d*pv[j0][j1]+q01d*pv[j0][j1+1]+q10d*pv[j0+1][j1]+q11d*pv[j0+1][j1+1];
                v[j0][j1] = (ev>cv)?ev:cv;
            }
    }
    return v[0][0];
};

//This function may be useful when debugging your program.
//It allows vectors to be displayed easily, for example,
//try cout << a; if a is a vector<any type>.
template<class T> ostream& operator<< (ostream& output, const vector<T>& array)
{
    output << "(" << array[0];
    for (size_t i = 1; i < array.size(); i++)
        output << "," << array[i];
    output << ")";

    return output;
};

#endif // PROJECT_H
