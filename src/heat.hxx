#pragma once

class Heat1D
{
public:
    Heat1D(const double alpha, const int m, const double dt)
    : M(m-1,m-1), m(m), alpha(alpha), dt(dt)
    {
        
        double sumDkij;
        double identity;
        
        for(int i=0; i<m; i++)
        {
            for(int j=0; j<m; j++)
            {
                if(i==j)
                {
                    sumDkij = -2;
                    identity = 1;
                }
                if(abs(j-i)==1)
                {
                    sumDkij = 1;
                    identity = 0;
                }
                else
                {
                    sumDkij = 0;
                    identity = 0;
                }
                M[{{i,j}}] = identity + alpha*dt/pow((1/m+1),2)*sumDkij;
            }
        }
        
        for(int i = 0; i<m; i++)
            w[i] = sin(pi*(i/(m+i)));
    }
    
    // Methods
    
    Vector<double> exact(double t) const
    {
        return exp(-pow(pi,2)*alpha*t)*w;
    }
    
    Vector<double> solve(double t_end) const
    {
        Vector<double> w_min = w;
        
        for(auto t = 0; t<t_end ; t += dt)
        {
            int it = cg(M, w_min, w, 0.01, 50);
            w_min(w);
        }
    }
    
private:
    Matrix<double> M;
    double const m;
    double const alpha;
    double const dt;
    Vector<double> w;
    
};
