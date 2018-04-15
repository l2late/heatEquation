#pragma once

// Conjugate Gradient Function
template<typename T>
int cg(const Matrix<T> &A, const Vector<T> &b, Vector<T> &x, T tol, int maxiter)
{
    Matrix<T> helperA = A;
	Vector<T> r = b - helperA.matvec(x), p(r);
	T alpha, beta;
    auto k = 0;
		for (k = 0; k < maxiter; k++)
		{
			alpha = dot(r, r) / dot(helperA.matvec(p), p);
			x = x + alpha*p;
			r = r + alpha*helperA.matvec(p);
			if (dot(r, r) < tol*tol)
				break;
			beta = dot(r, r) / dot(r, r);
			p = r + beta*p;
		}
	return (dot(r, r) < tol*tol) ? k + 1 : -1;

}
