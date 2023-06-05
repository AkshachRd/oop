#include <iostream>
#include <array>
#include <optional>

const int MATRIX_SIZE = 3;

using namespace std;
using Matrix = array<array<double, MATRIX_SIZE>, MATRIX_SIZE>;

Matrix InvertMatrix(const Matrix& matrix, bool& wasError);

int main()
{
    Matrix matrix{ {{1, 2, -1}, {-2, 0, 1}, {1, -1, 0}} };

    bool wasError = false;
    Matrix res = InvertMatrix(matrix, wasError);
    for (int i = 0; i < matrix.size(); i++)
    {
        for (int j = 0; j < matrix.size(); j++)
        {
            cout << res[i][j] << " ";
        }
        cout << endl;
    }

    Matrix mult;
    // Initializing elements of matrix mult to 0.
    for (int i = 0; i < matrix.size(); ++i)
        for (int j = 0; j < matrix.size(); ++j)
        {
            mult[i][j] = 0;
        }

    // Multiplying matrix a and b and storing in array mult.
    for (int i = 0; i < matrix.size(); ++i)
        for (int j = 0; j < matrix.size(); ++j)
            for (int k = 0; k < matrix.size(); ++k)
            {
                mult[i][j] +=  res[k][j] * matrix[i][k];
            }

    for (int i = 0; i < matrix.size(); i++)
    {
        for (int j = 0; j < matrix.size(); j++)
        {
            cout << mult[i][j] << " ";
        }
        cout << endl;
    }
}

void GetCofactor(const Matrix& matrix, Matrix& cofactors, int p, int q, int dimension)
{
    int i = 0;
    int j = 0;

    for (int row = 0; row < dimension; row++)
    {
        for (int col = 0; col < dimension; col++)
        {
            if (row != p && col != q)
            {
                cofactors[i][j++] = matrix[row][col];

                if (j == dimension - 1)
                {
                    j = 0;
                    i++;
                }
            }
        }
    }
}

int GetDeterminant(const Matrix& matrix, int dimension)
{
    int det = 0;

    if (dimension == 1)
    {
        return matrix[0][0];
    }

    Matrix cofactors;
    int sign = 1;

    for (int i = 0; i < dimension; i++)
    {
        GetCofactor(matrix, cofactors, 0, i, dimension);
        det += sign * matrix[0][i] * GetDeterminant(cofactors, dimension - 1);

        sign *= -1;
    }

    return det;
}

Matrix Adjoint(const Matrix& matrix, bool& wasError)
{
    Matrix resultMatrix;

    if (matrix.size() == 1)
    {
        resultMatrix[0][0] = 1;
        return resultMatrix;
    }

    int sign = 1;
    Matrix cofactors;

    for (int i = 0; i < matrix.size(); i++) {
        for (int j = 0; j < matrix.size(); j++)
        {
            GetCofactor(matrix, cofactors, i, j, matrix.size());

            sign = ((i + j) % 2 == 0) ? 1 : -1;
            resultMatrix[j][i] = (sign) * (GetDeterminant(cofactors, matrix.size() - 1));
        }
    }

    return resultMatrix;
}

Matrix InvertMatrix(const Matrix& matrix, bool& wasError)
{
    Matrix resultMatrix;

    int det = GetDeterminant(matrix, matrix.size());
    if (det == 0)
    {
        cout << "Singular matrix, can't find its inverse";
        wasError = true;
    }

    for (int i = 0; i < matrix.size(); i++)
    {
        for (int j = 0; j < matrix.size(); j++)
        {
            resultMatrix[i][j] = Adjoint(matrix, wasError)[i][j] / double(det);
        }
    }

    return resultMatrix;
}