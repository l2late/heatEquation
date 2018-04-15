#pragma once

// Conjugate Gradient Function
template<typename T>
int cg(const Matrix<T> &A, const Vector<T> &b, Vector<T> &x, T tol, int maxiter)
{
	Vector<T> r = b - A.matvec(x); p(r);
	T alpha, beta;

		for (k = 0; k < maxiter; k++)
		{
			alpha = dot(r, r) / dot(A.matvec(p), p);
			x += alpha*p;
			r -= alpha*A.matvec(p);
			if (dot(r, r) < tol*tol)
				break;
			beta = dot(r, r) / dot(r, r);
			p = r + beta*p;
		}
	return (dot(r, r) < tol*tol) ? k + 1 : -1;

}