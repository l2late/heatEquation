#pragma once
#include <cmath>
const double pi = 3.14159265358979323846;

class Heat1D
{
public:
	Heat1D(const double alpha, const int m, const double dt)
		: M(m, m), m(m), alpha(alpha), dt(dt), wStart(m)
	{
        for(int i = 0; i < m; i++) {
            M[{{i,i}}] = 1 -alpha*dt/0.0625*-2*1;
            M[{{i,i+1}}] =  -alpha*dt/0.0625*1;
            M[{{i+1,i}}] =  M[{{i,i+1}}];
        }
        
		for (int i = 0; i<m; i++)
			wStart[i] = sin(pi*(i / (m + i)));
	}

	// Methods
	Vector<double> exact(double t) const
	{
		return exp(-pow(pi, 2)*alpha*t)*wStart;
	}

	Vector<double> solve(double t_end) const
	{
		Vector<double> w(wStart); // Initialize w with w at t=0
		int iterations;

		for (auto t = 0; t<t_end; t += dt)
		{
			iterations = cg(M, w, w, 0.0001, 50);
		}
		if (iterations == -1) throw "Maximum number of iterations: did not find solution within the maximum tolerance (Conjugate Gradient)";

		return w;
	}

public:
	Matrix<double> M;
	int const m;
	double const alpha;
	double const dt;
	Vector<double> wStart;

};

class Heat2D 
{
	public:
		Heat2D(const double alpha, const int m, const double dt)
			: M(m*m, m*m), m(m), alpha(alpha), dt(dt)
		{
            double dx = 1/(m+1);
            
            for(int i = 0; i<m*m; i++){
                M[{{i,i}}] = 1 -alpha*dt/dx*dx*-2*2;
            
                if((i+1)/m == i/m){
                    M[{{i,i+1}}] =  -alpha*dt/dx*dx*1;
                    M[{{i+1,i}}] =  M[{{i,i+1}}];
                }
                
                if(i+m < m*m){
                    M[{{i,i+m}}] =  -alpha*dt/0.0625*1;
                    M[{{i+m,i}}] =  M[{{i,i+1}}];
                }
        }
            
            
		}

		// Methods
		Vector<double> exact(double t) const
		{
			return exp(-pow(pi, 2)*alpha*t)*wStart;
		}

		Vector<double> solve(double t_end) const
		{
			Vector<double> w(wStart); // Initialize w with w at t=0
			int iterations;

			for (auto t = 0; t<t_end; t += dt)
			{
				iterations = cg(M, w, w, 0.0001, 50);
			}
			if (iterations == -1) throw "Maximum number of iterations: did not find solution within the maximum tolerance (Conjugate Gradient)";

			return w;
		}

	public:
		Matrix<double> M;
		int const m;
		double const alpha;
		double const dt;
		Vector<double> wStart;
};
