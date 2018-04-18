#pragma once
#include <cmath>
#include <tuple>
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
            
            for(int i = 0; i<m*m; i++)
			{
                M[{{i,i}}] = 1 -alpha*dt/dx*dx*-2*2;
            
                if((i+1)/m == i/m)
				{
                    M[{{i,i+1}}] =  -alpha*dt/dx*dx*1;
                    M[{{i+1,i}}] =  M[{{i,i+1}}];
                }
                
                if(i+m < m*m)
				{
                    M[{{i,i+m}}] =  -alpha*dt/0.0625*1;
                    M[{{i+m,i}}] =  M[{{i,i+1}}];
                }
			}                      
		}

		// Methods
		Vector<double> exact(double t) const
		{
			return exp(-pow(pi, 2)*2*alpha*t)*wStart;
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


template<int n>
class Neighbor
{
	public:
		double value;
		int i;
		int j;

	Neighbor(int i, int j)
		: value(Neighbor<n-1>::value) i(i),j(j)
	{
	if (j / pow(m, n) == i / pow(m, n)
		value += 1;
};

template<>
class Neighbor<1>
{
public:
	double value;
	int i;
	int j;

Neighbor(int i,int j)
	: value(0), i(i),j(j)
	{
		if (j/ m == i/m)
			value += 1;
	}
};


template<int n>
class Heat 
{
	public:
		Heat(const double alpha, const int m, const double dt)
			: M(pow(m, n), pow(m, n)), m(m), alpha(alpha), dt(dt)
		{
            double dx = 1/(m+1);
            
            for(int i = 0; i<pow(m,n); i++)
			{
				for (int j = 0; j < pow(m, n); j++)
				{
					if (i==j)
						M[{ {i, j}}] = 1-alpha*dt / dx*dx * -2*n;
					else
						M[{ {i, j}}] = -alpha*dt / dx*dx * Neighbor<n>(i, j);
				}
			}                      
		}

		// Methods
		Vector<double> exact(double t) const
		{
			return exp(-pow(pi, 2)*alpha*t*n)*wStart;
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

	
	Matrix<double> M;
	int const m;
	double const alpha;
	double const dt;
	Vector<double> wStart;
};




};
