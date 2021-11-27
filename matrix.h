#ifndef __MATRIX_H__
#define __MATRIX_H__

#include "vector.h"

struct Matrix {
	double m[3][3];
	Matrix() {}
	Matrix(double diagonalElement)
	{
		for (int i = 0; i < 3; i++)
			for (int j = 0; j < 3; j++)
				if (i == j) m[i][j] = diagonalElement;
				else m[i][j] = 0.0;
	}
};

inline Vector operator * (const Vector& v, const Matrix& m)
{
	return Vector(
		v.x * m.m[0][0] + v.y * m.m[1][0] + v.z * m.m[2][0],
		v.x * m.m[0][1] + v.y * m.m[1][1] + v.z * m.m[2][1],
		v.x * m.m[0][2] + v.y * m.m[1][2] + v.z * m.m[2][2]
	);
}

inline void operator *= (Vector& v, const Matrix& a) { v = v*a; }

Matrix operator * (const Matrix& a, const Matrix& b); //!< matrix multiplication; result = a*b
Matrix inverseMatrix(const Matrix& a); //!< finds the inverse of a matrix (assuming it exists)
double determinant(const Matrix& a); //!< finds the determinant of a matrix

Matrix rotationAroundX(double angle); //!< returns a rotation matrix around the X axis; the angle is in radians
Matrix rotationAroundY(double angle); //!< same as above, but rotate around Y
Matrix rotationAroundZ(double angle); //!< same as above, but rotate around Z

#endif // __MATRIX_H__
