#include "mat4.h"
#define N 4
namespace egc {
    mat4& egc::mat4::operator=(const mat4& srcMatrix)
    {
        for (int i = 0; i < 4; i++)
            for (int j = 0; j < 4; j++)
                this->at(i, j) = srcMatrix.at(i, j);
        return *this;
    }
    mat4 mat4::operator*(float scalarValue) const
    {
        mat4 rez = *this;
        for (int i = 0; i < 16; i++)
            rez.matrixData[i] *= scalarValue;
        return rez;
    }
    mat4 mat4::operator*(const mat4& srcMatrix) const
    {
        mat4 m1 = *this;
        mat4 rez;
        float s = 0.0f;
        int k = 0;
        for (int k = 0; k < 4; k++)
            for (int i = 0; i < 4; i++)
            {
                s = 0.0f;
                for (int j = 0; j < 4; j++)
                    s += m1.at(k, j) * srcMatrix.at(j, i);
                rez.at(k, i) = s;
            }

        return rez;
    }
    mat4 mat4::operator /(float scalarValue) const
    {
        mat4 rez = *this;
        for (int i = 0; i < 16; i++)
            rez.matrixData[i] /= scalarValue;
        return rez;
    }
    vec4 mat4::operator*(const vec4& srcVector) const
    {
        vec4 rez;
        float s = 0.0f;
        float src[4] = { srcVector.x,srcVector.y,srcVector.z,srcVector.w };
        float v[4];
        for (int i = 0; i < 4; i++)
        {
            s = 0;
            for (int j = 0; j < 4; j++)
                s += this->at(i, j) * src[j];
            v[i] = s;
        }
        rez.x = v[0];
        rez.y = v[1];
        rez.z = v[2];
        rez.w = v[3];
        return rez;
    }
    mat4 mat4::operator+(const mat4& srcMatrix) const
    {
        mat4 m3;
        for (int i = 0; i < 4; i++)
            for (int j = 0; j < 4; j++)
                m3.at(i, j) = this->at(i, j) + srcMatrix.at(i, j);
        return m3;
    }
    float& mat4::at(int i, int j)
    {
        return this->matrixData[4 * j + i];
    }
    const float& mat4::at(int i, int j) const
    {
        return this->matrixData[4 * j + i];
    }
    void getCofactor(float mat[N][N], float temp[N][N], int p,
        int q, int n)
    {
        int i = 0, j = 0;

        // Looping for each element of the matrix
        for (int row = 0; row < n; row++)
        {
            for (int col = 0; col < n; col++)
            {
                //  Copying into temporary matrix only those
                //  element which are not in given row and
                //  column
                if (row != p && col != q)
                {
                    temp[i][j++] = mat[row][col];

                    // Row is filled, so increase row index and
                    // reset col index
                    if (j == n - 1)
                    {
                        j = 0;
                        i++;
                    }
                }
            }
        }
    }
    float determinantOfMatrix(float mat[N][N], int n)
    {
        float D = 0; // Initialize result

        //  Base case : if matrix contains single element
        if (n == 1)
            return mat[0][0];

        float temp[N][N]; // To store cofactors

        int sign = 1; // To store sign multiplier

        // Iterate for each element of first row
        for (int f = 0; f < n; f++)
        {
            // Getting Cofactor of mat[0][f]
            getCofactor(mat, temp, 0, f, n);
            D += sign * mat[0][f] * determinantOfMatrix(temp, n - 1);

            // terms are to be added with alternate sign
            sign = -sign;
        }

        return D;
    }

    float mat4::determinant() const
    {
        float mat[N][N];
        for (int i = 0; i < 4; i++)
            for (int j = 0; j < 4; j++)
                mat[i][j] = this->at(i, j);
        float det = determinantOfMatrix(mat, N);


        return det;

    }

    mat4 mat4::transpose() const
    {
        mat4 mt;

        for (int i = 0; i < 4; i++)
        {
            for (int j = 0; j < 4; j++)
            {
                mt.at(i, j) = this->at(j, i);

            }

        }
        return mt;
    }

    void adjoint(float A[][N], float adj[][N])
    {
        if (N == 1)
        {
            adj[0][0] = 1.0f;
            return;
        }

        // temp is used to store cofactors of A[][] 
        int sign = 1;
        float temp[N][N];

        for (int i = 0; i < N; i++)
        {
            for (int j = 0; j < N; j++)
            {

                getCofactor(A, temp, i, j, N);

                sign = ((i + j) % 2 == 0) ? 1 : -1;

                adj[j][i] = (sign)*determinantOfMatrix(temp, N - 1);
            }
        }
    }
    mat4 mat4::inverse() const
    {
        float adj[N][N]; //adjoint
        float m[N][N]; //this
        float det = determinant();
        mat4 rez;
        for (int i = 0; i < N; i++)
            for (int j = 0; j < N; j++)
                m[i][j] = this->at(i, j);
        adjoint(m, adj);
        for (int i = 0; i < N; i++)
            for (int j = 0; j < N; j++)
                rez.at(i, j) = adj[i][j];
        rez = rez / det; //adjoint / determinant
        return rez;

    }
}
