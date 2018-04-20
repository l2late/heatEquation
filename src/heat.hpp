#pragma once

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
    // Analytic solver
	Vector<double> exact(double t) const
	{
        return exp(-pow(pi,2)*alpha*t)*wStart;
	}

    // Numeric conjugate gradient solver
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
    
    // Print function for printing attribute M
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
        // Analytic solver
		Vector<double> exact(double t) const
		{
			return exp(-pow(pi, 2)*2*alpha*t)*wStart;
		}

        // Numeric conjugate gradient solver
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
    
    // Print function for printing attribute M
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
