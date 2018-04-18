#pragma once

// Conjugate Gradient Function
template<typename T>
int cg(const Matrix<T> &A, const Vector<T> &b, Vector<T> &x, T tol, int maxiter)
{
    Matrix<T> helperA = A; // Else the matvec function won't work (const matrix as input)
    Vector<T> r = b - helperA.matvec(b), p(r), rNew;
    T alpha, beta;
    auto k = 0;
        for (k = 0; k < maxiter; k++)
        {
            alpha = dot(r, r) / dot(helperA.matvec(p), p);
            x = x + alpha*p;
            rNew = r - alpha*helperA.matvec(p);
            if (dot(rNew, rNew) < tol*tol)
                break;
            beta = dot(rNew, rNew) / dot(r, r);
            p = rNew + beta*p;
            r = rNew;
        }
    return (dot(rNew, rNew) < tol*tol) ? k + 1 : -1;
}
