#pragma once
#include <cmath>

const double pi = 3.14159265358979323846;

class Heat1D
{
public:
	Heat1D(const double alpha, const int m, const double dt)
		: M(m, m), m(m), alpha(alpha), dt(dt), wStart(m)
	{
        double dx = 1/( static_cast<double>(m) +1 );
        
        for(int i = 0; i < m; i++) {
            M[{{i,i}}] = 1 -alpha*dt/(pow(dx,2))*-2;
            if(i<m-1){
                M[{{i,i+1}}] =  -alpha*dt/(pow(dx,2));
                M[{{i+1,i}}] =  M[{{i,i+1}}];
            }
        }
		for (int i = 0; i<m; i++)
			wStart[i] = sin(pi*(i+1)*dx);
	}

	// Methods
	Vector<double> exact(double t) const
	{
        return exp(-pow(pi,2)*alpha*t)*wStart;
	}

	Vector<double> solve(double t_end) const
	{
		Vector<double> w(wStart); // Initialize w with w at t=0
		int iterations;

		for (double t = 0; t<t_end; t = t + dt)
		{
			iterations = cg(M, w, w, 0.00001, 50);
            if (iterations == -1) throw "\nMaximum number of iterations: did not find solution within the maximum tolerance (Conjugate Gradient)";
		}
		return w;
	}
    
    void print()
    {
        M.print();
    }

private:
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
			: M(m*m, m*m), m(m), alpha(alpha), dt(dt), wStart(m*m)
		{
            double dx = 1/(static_cast<double>(m)+1);
            
            for(int i = 0; i<m*m; i++)
			{
                M[{{i,i}}] = 1 -alpha*dt/(dx*dx)*-2*2;
            
                if((i+1)/m == i/m)
				{
                    M[{{i,i+1}}] =  -alpha*dt/(dx*dx)*1;
                    M[{{i+1,i}}] =  M[{{i,i+1}}];
                }
                
                if(i+m < m*m)
				{
                    M[{{i,i+m}}] =  -alpha*dt/(dx*dx)*1;
                    M[{{i+m,i}}] =  M[{{i,i+m}}];
                }
			}
            
            for(int i = 0; i<m; i++) {
                for(int j = 0; j<m; j++)
                    wStart[i+j*m] = sin(pi*(i+1)*dx)*sin(pi*(j+1)*dx);
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

			for (double t = 0; t<t_end; t += dt)
			{
				iterations = cg(M, w, w, 0.00001, 50);
			}
			if (iterations == -1) throw "Maximum number of iterations: did not find solution within the maximum tolerance (Conjugate Gradient)";

			return w;
		}
    
    // Print function.
    void print()
    {
        M.print();
    }

	private:
		Matrix<double> M;
		int const m;
		double const alpha;
		double const dt;
		Vector<double> wStart;
};


// Recursively compute the initial heat distribution for n dimensions
// function template
template<int n>
double CalculateWStart(int i, int m, double dx)
{
	int index = (int)(i / pow(m, n - 1));
	double j = i - (int)(index *pow(m, n - 1));
	
//	std::cout << "calculating the " << index + 1 << "th index in the dimension: " << n << std::endl;
	//std::cout << "index in layer below =  " << j << std::endl;
	return sin(pi*(index + 1)*dx)*CalculateWStart<n - 1>(j, m, dx);
};

// function specialization for n = 1
template<>
double CalculateWStart<1>(int i, int m, double dx)
{
	// std::cout << "calculating the " << i+1  << "th index in the dimension: " << 1 << std::endl;
	return sin(pi*(i + 1)*dx);
};

template<int n>
class Heat
{
    public:
        Heat(const double alpha, const int m, const double dt)
            : M(pow(m, n), pow(m, n)), m(m), alpha(alpha), dt(dt), wStart(pow(m,n))
        {
            double dx = 1/(static_cast<double>(m)+1);

			for (int i = 0; i < pow(m, n); i++)
			{
				M[{ {i, i}}] = 1 - alpha*dt / (dx*dx) * -2 * n;
				
				for (int j = 0; j < n; j++)
				{
					if ((int)(i / pow(m, j + 1)) == (int)((i + pow(m, j)) / pow(m, j + 1)) && (int)(i + pow(m, j)) < pow(m, n))
					{
						M[{ {i, (int)(i + pow(m, j))}}] = -alpha*dt / (dx*dx);
						M[{ {(int)(i + pow(m, j)), i }}] = -alpha*dt / (dx*dx);
					}
				}
			}                     
            
			// Build initial temperature distribution
			for (int i = 0; i < pow(m, n); i++) 
			{
					wStart[i] = CalculateWStart<n>(i, m, dx);	
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

            for (double t = 0; t<t_end; t += dt)
            {
                iterations = cg(M, w, w, 0.0001, 50);
            }
            if (iterations == -1) throw "Maximum number of iterations: did not find solution within the maximum tolerance (Conjugate Gradient)";

            return w;
        }
    
        void print()
        {
            M.print();
        }

    private:
        Matrix<double> M;
        int const m;
        double const alpha;
        double const dt;
        Vector<double> wStart;
};
