#pragma once

const double pi = 3.14159265358979323846;

class Heat1D
{
public:
	Heat1D(const double alpha, const int m, const double dt)
		: M(m, m), m(m), alpha(alpha), dt(dt)
	{
		double sumDkij;
		double identity;

		for (int i = 0; i<m; i++)
		{
			for (int j = 0; j<m; j++)
			{
				// node is itself
				if (i == j)
				{
					sumDkij = -2;
					identity = 1;
				}
				// node is right neighbor in first dimension
				
				if (i/m == j/m && j == i+1)
				{
					sumDkij = 1;
					identity = 0;
				}
				else
				{
					sumDkij = 0;
					identity = 0;
				}
				M[{ {i, j}}] = identity + alpha*dt / pow((1 / m + 1), 2)*sumDkij;
			}
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
			: M(m, m), m(m), alpha(alpha), dt(dt)
		{
			Matrix<double> D(m,m);

			for (int i = 0; i < m; i++)
			{
				for (int j = 0; j < m; j++)
				{
					if (i == j)
						D[{ {i, j}}] = 1;

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

	private: 
		Matrix<double> M;
		int const m;
		double const alpha;
		double const dt;
		Vector<double> wStart;
};