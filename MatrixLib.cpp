#include <iostream>
using namespace std;

class Matrix
{
private:
    // attributes
    int rowCount;
    int colCount;
    double val[10][10];

public:
    // constructors
    Matrix();
    Matrix(int r, int c);
    Matrix(Matrix &B);

    // methods
    void print();
    int getRowCount();
    int getColCount();

    double det();      // only if the matrix is a square one
    Matrix minor();    // only if the matrix is a square one
    Matrix cofactor(); // only if the matrix is a square one
    Matrix transpose();
    Matrix adjoint(); // only if the matrix is a square one
    Matrix inverse(); // only if the matrix is a square one && .det != 0

    // operators
    Matrix operator+(Matrix B); // + operator overloaded to add two Matrix
    Matrix operator*(Matrix B); // + operator overloaded to mul two Matrix
    Matrix operator*(double k); // + operator overloaded to mul a Matrix with an scalar int
};

Matrix::Matrix()
{
    this->colCount = 0;
    this->rowCount = 0;
    // no need to intialise the elements
    // as there is no element in the matrix
}
Matrix::Matrix(int r, int c)
{
    this->rowCount = min(r, 10);
    this->colCount = min(c, 10);

    for (int i = 0; i < this->rowCount; i++)
    {
        cout << "Enter {" << this->colCount << "} elements for row " << i << " : ";
        for (int j = 0; j < this->colCount; j++)
        {
            cin >> this->val[i][j];
        }
    }
}
Matrix::Matrix(Matrix &B)
{
    this->rowCount = B.rowCount;
    this->colCount = B.colCount;

    for (int i = 0; i < this->rowCount; i++)
    {
        for (int j = 0; j < this->colCount; j++)
        {
            this->val[i][j] = B.val[i][j];
        }
    }
}

void Matrix::print()
{
    for (int i = 0; i < this->rowCount; i++)
    {
        for (int j = 0; j < this->colCount; j++)
        {
            printf(" %5.2lf ", this->val[i][j]); // I personally prefer printf much more
        }
        cout << endl;
    }
}
int Matrix::getRowCount()
{
    return this->rowCount;
}
int Matrix::getColCount()
{
    return this->colCount;
}

double Matrix::det()
{
    if (this->rowCount != this->colCount || this->rowCount == 0) // Not a square matrix
    {
        return 0;
    }
    else if (this->rowCount == 1) // base case
    {
        return this->val[0][0];
    }

    double ans = 0;
    for (int i = 0; i < this->rowCount; i++)
    {
        Matrix sub;
        sub.rowCount = this->rowCount - 1;
        sub.colCount = this->colCount - 1;
        for (int x = 0, j = 0; x < this->rowCount; x++)
        {
            for (int y = 1; x != i && y < this->rowCount; y++)
            {
                sub.val[j][y - 1] = this->val[x][y];
            }
            j += (x != i);
        }

        if (i % 2 == 0)
        {
            ans += this->val[i][0] * sub.det();
        }
        else
        {
            ans -= this->val[i][0] * sub.det();
        }
    }
    return ans;
}
Matrix Matrix::minor()
{
    Matrix M;
    if (this->rowCount != this->colCount || this->rowCount < 2) // Not a square matrix
    {
        return M; // return an empty matrix
    }

    M.rowCount = this->rowCount;
    M.colCount = this->colCount;

    for (int i = 0; i < this->rowCount; i++)
    {
        for (int j = 0; j < this->colCount; j++)
        {
            // lets calculate: M[i][j] = det(sub)
            Matrix sub;
            sub.rowCount = this->rowCount - 1;
            sub.colCount = this->colCount - 1;
            for (int x = 0, p = 0; x < this->rowCount; x++)
            {
                if (x == i)
                {
                    continue;
                }
                for (int y = 0, q = 0; y < this->colCount; y++)
                {
                    if (y == j)
                    {
                        continue;
                    }
                    sub.val[p][q] = this->val[x][y];
                    q += 1;
                }
                p += 1;
            }
            M.val[i][j] = sub.det();
        }
    }
    return M;
}
Matrix Matrix::cofactor()
{
    Matrix R;
    if (this->rowCount != this->colCount || this->rowCount < 2) // Not a square matrix
    {
        return R; // return an empty matrix
    }

    R = this->minor();
    for (int i = 0; i < this->rowCount; i++)
    {
        for (int j = 0; j < this->colCount; j++)
        {
            if ((i % 2) != (j % 2))
            {
                R.val[i][j] = 0 - R.val[i][j];
            }
        }
    }

    return R;
}
Matrix Matrix::transpose()
{
    Matrix R;
    R.rowCount = this->colCount;
    R.colCount = this->rowCount;

    for (int i = 0; i < this->rowCount; i++)
    {
        for (int j = 0; j < this->colCount; j++)
        {
            R.val[j][i] = this->val[i][j];
        }
    }

    return R;
}
Matrix Matrix::adjoint()
{
    Matrix R;
    if (this->rowCount != this->colCount || this->rowCount < 2) // Not a square matrix
    {
        return R; // return an empty matrix
    }

    R = this->cofactor();

    Matrix temp = R.transpose();
    R = temp;

    return R;
}
Matrix Matrix::inverse()
{
    Matrix R;
    if (this->rowCount != this->colCount || this->rowCount == 0) // Not a square matrix
    {
        return R; // return an empty matrix
    }

    double D = this->det();
    if (D == 0)
    {
        return R; // return an empty matrix
    }

    if (this->rowCount == 1)
    {
        R.val[0][0] = 1 / D;
        return R;
    }

    R = this->adjoint();

    Matrix temp = R * (1 / D);
    R = temp;

    return R;
}

Matrix Matrix::operator+(Matrix B)
{
    Matrix R;

    if (this->rowCount != B.rowCount || this->colCount != B.colCount)
    {
        // if the arrays are not compatible for addition
        // It returns an empty matrix
        return R;
    }

    R.rowCount = this->rowCount;
    R.colCount = this->colCount;

    for (int i = 0; i < this->rowCount; i++)
    {
        for (int j = 0; j < this->colCount; j++)
        {
            R.val[i][j] = this->val[i][j] + B.val[i][j];
        }
    }

    return R;
}
Matrix Matrix::operator*(Matrix B)
{
    // say this is (P x Q)
    // and B is    (R x S)
    Matrix R;

    if (this->colCount != B.rowCount) // Q != R
    {
        // if the arrays are not compatible for addition
        // It returns an empty matrix
        return R;
    }

    // R is of the order (P x S)
    R.rowCount = this->rowCount;
    R.colCount = B.colCount;

    for (int i = 0; i < this->rowCount; i++) // P
    {
        for (int j = 0; j < B.colCount; j++) // S
        {
            R.val[i][j] = 0;
            for (int k = 0; k < B.rowCount; k++) // Q or R
            {
                // C[i][j] += (A[i][k] * B[k][j]);
                R.val[i][j] += (this->val[i][k] * B.val[k][j]);
            }
        }
    }

    return R;
}
Matrix Matrix::operator*(double k)
{
    Matrix R;

    R.rowCount = this->rowCount;
    R.colCount = this->colCount;

    for (int i = 0; i < this->rowCount; i++)
    {
        for (int j = 0; j < this->colCount; j++)
        {
            R.val[i][j] = this->val[i][j] * k;
        }
    }
    return R;
}

int main()
{
    int r, c;

    cout << "Number of rows for Matrix A: ";
    cin >> r;
    cout << "Number of cols for Matrix A: ";
    cin >> c;
    Matrix A(r, c);

    cout << "\nMatrix A is \n";
    A.print();

    while (true)
    {
        int choice;
        cout << "\n######## MENU ########\n";
        cout << "\t1. Matrix Addition\n\t2. Matrix Subtraction\n";
        cout << "\t3. Matrix Multiplication\n\t4. Scalar Multiplication\n";
        cout << "\t5. Determinant of Matrix\n\t6. Transpose of Matrix\n";
        cout << "\t7. Inverse of Matrix\n";
        cout << "\t0. Exit\n";
        cout << "\nEnter your choice: ";
        cin >> choice;
        switch (choice)
        {
        case 0:
        {
            cout << "Terminated with code = 0\n";
            return 0;
        }
        case 1:
        {
            cout << "Number of rows for Matrix B: ";
            cin >> r;
            cout << "Number of cols for Matrix B: ";
            cin >> c;
            if (r != A.getRowCount() || c != A.getColCount())
            {
                cout << "Matrix dimensions are incompatible for Addition\n";
                break;
            }

            Matrix B(r, c);
            cout << "\nMatrix A :\n";
            A.print();
            cout << "\nMatrix B :\n";
            B.print();

            Matrix temp = A + B;
            A = temp;
            cout << "\nMatrix A + Matrix B :\n";
            A.print();
            break;
        }
        case 2:
        {
            cout << "Number of rows for Matrix B: ";
            cin >> r;
            cout << "Number of cols for Matrix B: ";
            cin >> c;
            if (r != A.getRowCount() || c != A.getColCount())
            {
                cout << "Matrix dimensions are incompatible for Subtraction\n";
                break;
            }

            Matrix B(r, c);
            cout << "\nMatrix A :\n";
            A.print();
            cout << "\nMatrix B :\n";
            B.print();

            Matrix temp = A + (B * (-1));
            A = temp;
            cout << "\nMatrix A - Matrix B :\n";
            A.print();
            break;
        }
        case 3:
        {
            cout << "Number of rows for Matrix B: ";
            cin >> r;
            cout << "Number of cols for Matrix B: ";
            cin >> c;
            if (A.getColCount() != r)
            {
                cout << "Matrix dimensions are incompatible for Multiplication\n";
                break;
            }

            Matrix B(r, c);
            cout << "\nMatrix A :\n";
            A.print();
            cout << "\nMatrix B :\n";
            B.print();

            Matrix temp = A * B;
            A = temp;
            cout << "\nMatrix A * Matrix B :\n";
            A.print();
            break;
        }
        case 4:
        {
            double k;
            cout << "Enter the scalar value: ";
            cin >> k;

            cout << "\nMatrix A :\n";
            A.print();
            cout << "\nk = " << k << "\n";

            Matrix temp = A * k;
            A = temp;
            cout << "\nMatrix A * k :\n";
            A.print();
            break;
        }
        case 5:
        {
            cout << "\nMatrix A :\n";
            A.print();
            cout << "\ndeterminant(A) = " << A.det() << "\n";
            break;
        }
        case 6:
        {
            cout << "\nMatrix A :\n";
            A.print();

            Matrix temp = A.transpose();
            A = temp;
            cout << "\nTranspose of A :\n";
            A.print();
            break;
        }
        case 7:
        {
            cout << "\nMatrix A :\n";
            A.print();

            Matrix temp = A.inverse();
            A = temp;
            cout << "\nInverse of A :\n";
            A.print();
            break;
        }
        default:
        {
            cout << "Invalid Choice\n";
            break;
        }
        }
    }
}