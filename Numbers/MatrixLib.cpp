#include <iostream>
#include <vector>
using namespace std;

class Matrix
{
private:
    // attributes
    vector<vector<double>> vals;

public:
    // constructors
    Matrix();                            // initialise an empty matrix
    Matrix(int R, int C);                // prompt the user to enter the elements
    Matrix(int R, int C, double filler); // initialise a matrix with the given elements
    Matrix(Matrix &B);                   // copy constructor

    // methods
    void print();
    int getRowCount();
    int getColCount();

    Matrix subMatrix(int delRow, int delCol); // to get the submatrix after deleting a row and a column
    double det();                             // only if the matrix is a square one
    Matrix minor();                           // only if the matrix is a square one
    Matrix cofactor();                        // only if the matrix is a square one
    Matrix transpose();
    Matrix adjoint(); // only if the matrix is a square one
    Matrix inverse(); // only if the matrix is a square one && .det != 0

    // operators
    Matrix operator+(Matrix B); // + operator overloaded to find the sum of two Matrices
    Matrix operator-(Matrix B); // - operator overloaded to find the difference of two Matrices
    Matrix operator*(Matrix B); // * operator overloaded to find the product of two Matrices
    Matrix operator*(double k); // * operator overloaded to find the scalar product of a Matrix
    // TODO:
    // Matrix operator^(int x);    // ^ operator overloaded to find the power of a Matrix
};

Matrix::Matrix()
{
    // EMPTY MATRIX:
    // no need to intialise the elements as there are none
}
Matrix::Matrix(int R, int C)
{
    for (int i = 0; i < R; i++)
    {
        vector<double> row;
        printf("Enter %d elements for %dth row: ", C, i + 1);
        for (int j = 0; j < C; j++)
        {
            double temp;
            scanf("%lf", &temp);
            row.push_back(temp);
        }
        this->vals.push_back(row);
    }
}
Matrix::Matrix(int R, int C, double filler)
{
    for (int i = 0; i < R; i++)
    {
        vector<double> row(C, filler);
        this->vals.push_back(row);
    }
}
Matrix::Matrix(Matrix &B)
{
    for (int i = 0; i < B.getRowCount(); i++)
    {
        vector<double> row;
        for (int j = 0; j < this->getColCount(); j++)
        {
            row.push_back(B.vals[i][j]);
        }
        this->vals.push_back(row);
    }
}

void Matrix::print()
{
    for (int i = 0; i < this->getRowCount(); i++) // can also use: i < this->vals.size();
    {
        for (int j = 0; j < this->getColCount(); j++) // can also use: j < this->vals[i].size();
        {
            printf(" %5.2lf ", this->vals[i][j]); // I personally prefer printf much more
        }
        printf("\n");
    }
}
int Matrix::getRowCount()
{
    return this->vals.size();
}
int Matrix::getColCount()
{
    return (this->vals.size() > 0) ? this->vals[0].size() : 0;
}

Matrix Matrix::subMatrix(int delRow, int delCol)
{
    if (delRow < 0 || this->getRowCount() <= delRow || delCol < 0 || this->getColCount() <= delCol)
    {
        Matrix sub;
        return sub; // return an empty matrix
    }
    if (this->getRowCount() <= 1 || this->getColCount() <= 1)
    {
        Matrix sub;
        return sub; // return an empty matrix
    }

    Matrix sub(this->getRowCount() - 1, this->getColCount() - 1, 0);

    for (int i = 0, x = 0; i < this->getRowCount(); i++)
    {
        for (int j = 0, y = 0; j < this->getColCount(); j++)
        {
            if (i != delRow && j != delCol)
            {
                sub.vals[x][y] = this->vals[i][j];
            }
            y += (j != delCol);
        }
        x += (i != delRow);
    }
    return sub;
}
double Matrix::det()
{
    if (this->getRowCount() != this->getColCount()) // Not a square matrix
    {
        printf("\nException: Given matrix is a non-square matrix\n");
        return 0;
    }
    if (this->getRowCount() == 1) // base case
    {
        return this->vals[0][0];
    }
    if (this->getRowCount() == 0) // base case
    {
        // NOTE: det of an empty matrix is 1 and not 0
        return 1;
    }

    double ans = 0;

    for (int i = 0; i < this->getRowCount(); i++)
    {
        Matrix sub = this->subMatrix(i, 0);
        double temp = this->vals[i][0] * sub.det();
        ans += (i % 2 == 0) ? (temp) : (0 - temp);
    }
    return ans;
}
Matrix Matrix::minor()
{
    if (this->getRowCount() != this->getColCount()) // Not a square matrix
    {
        printf("\nException: Given matrix is a non-square matrix\n");
        Matrix M;
        return M; // return an empty matrix
    }

    Matrix M(this->getRowCount(), this->getColCount(), 0);

    for (int i = 0; i < this->getRowCount(); i++)
    {
        for (int j = 0; j < this->getColCount(); j++)
        {
            Matrix sub = this->subMatrix(i, j);
            M.vals[i][j] = sub.det();
        }
    }
    return M;
}
Matrix Matrix::cofactor()
{
    if (this->getRowCount() != this->getColCount()) // Not a square matrix
    {
        printf("\nException: Given matrix is a non-square matrix\n");
        Matrix R;
        return R; // return an empty matrix
    }

    Matrix R = this->minor();

    for (int i = 0; i < this->getRowCount(); i++)
    {
        for (int j = 0; j < this->getColCount(); j++)
        {
            R.vals[i][j] *= ((i % 2) == (j % 2)) ? 1 : -1;
        }
    }

    return R;
}
Matrix Matrix::transpose()
{
    Matrix R(this->getColCount() - 1, this->getRowCount() - 1, 0);

    for (int i = 0; i < this->getRowCount(); i++)
    {
        for (int j = 0; j < this->getColCount(); j++)
        {
            R.vals[j][i] = this->vals[i][j];
        }
    }

    return R;
}
Matrix Matrix::adjoint()
{
    if (this->getRowCount() != this->getColCount()) // Not a square matrix
    {
        printf("\nException: Given matrix is a non-square matrix\n");
        Matrix R;
        return R; // return an empty matrix
    }

    Matrix temp = this->cofactor();
    Matrix R = temp.transpose();

    return R;
}
Matrix Matrix::inverse()
{
    if (this->getRowCount() != this->getColCount()) // Not a square matrix
    {
        printf("\nException: Given matrix is a non-square matrix\n");
        Matrix R;
        return R; // return an empty matrix
    }

    double D = this->det();
    if (D == 0)
    {
        printf("\nException: Given matrix has a zero determinant\n");
        Matrix R;
        return R; // return an empty matrix
    }

    Matrix temp = this->adjoint();
    Matrix R = temp * (1 / D);

    return R;
}

Matrix Matrix::operator+(Matrix B)
{
    if (this->getRowCount() != B.getRowCount() || this->getColCount() != B.getColCount())
    {
        // if the arrays are not compatible for addition
        // It returns an empty matrix
        Matrix R;
        return R;
    }

    Matrix R(this->getRowCount(), this->getColCount(), 0);

    for (int i = 0; i < this->getRowCount(); i++)
    {
        for (int j = 0; j < this->getColCount(); j++)
        {
            R.vals[i][j] = (this->vals[i][j] + B.vals[i][j]);
        }
    }

    return R;
}
Matrix Matrix::operator-(Matrix B)
{
    // if (this->rowCount != B.rowCount || this->colCount != B.colCount)
    // {
    //     // no need to check this condition as it is already checked in the + operator
    // }

    Matrix R = (*this) + (B * (-1));
    return R;
}
Matrix Matrix::operator*(Matrix B)
{
    // say this is (P x Q)
    // and B is    (R x S)

    if (this->getColCount() != B.getRowCount()) // Q != R
    {
        // if the arrays are not compatible for multiplication
        // It returns an empty matrix
        Matrix R;
        return R;
    }

    // R is of the order (P x S)
    Matrix R(this->getRowCount(), B.getColCount(), 0);

    for (int i = 0; i < this->getRowCount(); i++) // P
    {
        for (int j = 0; j < B.getColCount(); j++) // S
        {
            for (int k = 0; k < B.getRowCount(); k++) // Q or R
            {
                // C[i][j] += (A[i][k] * B[k][j]);
                R.vals[i][j] += (this->vals[i][k] * B.vals[k][j]);
            }
        }
    }

    return R;
}
Matrix Matrix::operator*(double k)
{
    Matrix R(this->getRowCount(), this->getColCount(), 0);

    for (int i = 0; i < this->getRowCount(); i++)
    {
        for (int j = 0; j < this->getColCount(); j++)
        {
            R.vals[i][j] = (this->vals[i][j] * k);
        }
    }
    return R;
}

int main()
{
    int r, c;

    printf("Number of rows for Matrix A: ");
    scanf("%d", &r);
    printf("Number of cols for Matrix A: ");
    scanf("%d", &c);
    Matrix A(r, c);

    printf("\nMatrix A is \n");
    A.print();

    while (true)
    {
        int choice;
        printf("\n######## MENU ########\n");
        printf("\t1. Matrix Addition\n\t2. Matrix Subtraction\n");
        printf("\t3. Matrix Multiplication\n\t4. Scalar Multiplication\n");
        printf("\t5. Determinant of Matrix\n\t6. Transpose of Matrix\n");
        printf("\t7. Inverse of Matrix\n");
        printf("\t0. Exit\n");
        printf("\nEnter your choice: ");
        scanf("%d", &choice);
        switch (choice)
        {
        case 0:
        {
            printf("Terminated with code = 0\n");
            return 0;
        }
        case 1:
        {
            printf("Number of rows for Matrix B: ");
            scanf("%d", &r);
            printf("Number of cols for Matrix B: ");
            scanf("%d", &c);
            if (r != A.getRowCount() || c != A.getColCount())
            {
                printf("Matrix dimensions are incompatible for Addition\n");
                break;
            }

            Matrix B(r, c);
            printf("\nMatrix A :\n");
            A.print();
            printf("\nMatrix B :\n");
            B.print();

            Matrix temp = A + B;
            A = temp;
            printf("\nMatrix A + Matrix B :\n");
            A.print();
            break;
        }
        case 2:
        {
            printf("Number of rows for Matrix B: ");
            scanf("%d", &r);
            printf("Number of cols for Matrix B: ");
            scanf("%d", &c);
            if (r != A.getRowCount() || c != A.getColCount())
            {
                printf("Matrix dimensions are incompatible for Subtraction\n");
                break;
            }

            Matrix B(r, c);
            printf("\nMatrix A :\n");
            A.print();
            printf("\nMatrix B :\n");
            B.print();

            Matrix temp = A - B;
            A = temp;
            printf("\nMatrix A - Matrix B :\n");
            A.print();
            break;
        }
        case 3:
        {
            printf("Number of rows for Matrix B: ");
            scanf("%d", &r);
            printf("Number of cols for Matrix B: ");
            scanf("%d", &c);
            if (A.getColCount() != r)
            {
                printf("Matrix dimensions are incompatible for Multiplication\n");
                break;
            }

            Matrix B(r, c);
            printf("\nMatrix A :\n");
            A.print();
            printf("\nMatrix B :\n");
            B.print();

            Matrix temp = A * B;
            A = temp;
            printf("\nMatrix A * Matrix B :\n");
            A.print();
            break;
        }
        case 4:
        {
            double k;
            printf("Enter the scalar value: ");
            scanf("%lf", &k);

            printf("\nMatrix A :\n");
            A.print();
            printf("\nk = %lf\n", k);

            Matrix temp = A * k;
            A = temp;
            printf("\nMatrix A * k :\n");
            A.print();
            break;
        }
        case 5:
        {
            printf("\nMatrix A :\n");
            A.print();

            double determinant = A.det();
            printf("\ndet(A) = %lf\n", determinant);
            break;
        }
        case 6:
        {
            printf("\nMatrix A :\n");
            A.print();

            Matrix temp = A.transpose();
            A = temp;
            printf("\nTranspose of A :\n");
            A.print();
            break;
        }
        case 7:
        {
            printf("\nMatrix A :\n");
            A.print();

            Matrix temp = A.inverse();
            A = temp;
            printf("\nInverse of A :\n");
            A.print();
            break;
        }
        default:
        {
            printf("Invalid Choice\n");
            break;
        }
        }
    }
}