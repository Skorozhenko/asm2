#include <stdio.h>
#include <string.h>
#include <iostream>
#include <malloc.h>

using namespace std;

double matrixDeterminant3x3(double* ma) {
    __asm {
        mov eax, ma

        finit
        //----------------------------
        fld qword ptr[eax]  //a11.
        fld qword ptr[eax + 32] //a22.
        fmulp st(1), st(0)
        fld qword ptr[eax + 64] //a33.
        fmulp st(1), st(0)

        //----------------------------
        fld qword ptr[eax + 16] //a13.
        fld qword ptr[eax + 24] //a21.
        fmulp st(1), st(0)
        fld qword ptr[eax + 56] //a32.
        fmulp st(1), st(0)

        //----------------------------
        fld qword ptr[eax + 8]  //a12.
        fld qword ptr[eax + 40] //a23.
        fmulp st(1), st(0)
        fld qword ptr[eax + 48] //a31.
        fmulp st(1), st(0)

        //----------------------------
        faddp st(1), st(0)
        faddp st(1), st(0)

        //----------------------------
        fld qword ptr[eax + 16] //a13.
        fld qword ptr[eax + 32] //a22.
        fmulp st(1), st(0)
        fld qword ptr[eax + 48] //a31.
        fmulp st(1), st(0)

        //----------------------------
        fld qword ptr[eax + 8]  //a12.
        fld qword ptr[eax + 24] //a21.
        fmulp st(1), st(0)
        fld qword ptr[eax + 64] //a33.
        fmulp st(1), st(0)

        //----------------------------
        fld qword ptr[eax]  //a11.
        fld qword ptr[eax + 40] //a23.
        fmulp st(1), st(0)
        fld qword ptr[eax + 56] //a32.
        fmulp st(1), st(0)

        //----------------------------
        faddp st(1), st(0)
        faddp st(1), st(0)

        //----------------------------
        fsubp st(1), st(0)
    }
}

int main()
{
    setlocale(LC_ALL, "");
    double b1 = 0.0, b2 = 0.0, b3 = 0.0;
    double* M = new double[9];
    cout << "Данная программа предназначена для решения системы трёх линейных уравнений от трёх неизвестных методом Крамера\n";
    cout << "пожалуйста, последовательно введите коэфициенты a11, a12, a13 и b1\n";
    cin >> M[0] >> M[1] >> M[2] >> b1;
    cout << "пожалуйста, последовательно введите коэфициенты a21, a22, a23 и b2\n";
    cin >> M[3] >> M[4] >> M[5] >> b2;
    cout << "пожалуйста, последовательно введите коэфициенты a31, a32, a33 и b3\n";
    cin >> M[6] >> M[7] >> M[8] >> b3;

    double a1j = 0.0, a2j = 0.0, a3j = 0.0;
    double determinant = matrixDeterminant3x3(M);
    cout << determinant << '\n';
    a1j = M[0];
    a2j = M[3];
    a3j = M[6];
    M[0] = b1;
    M[3] = b2;
    M[6] = b3;
    double determinantA1J = matrixDeterminant3x3(M);
    cout << determinantA1J << '\n';
    M[0] = a1j;
    M[3] = a2j;
    M[6] = a3j;

    a1j = M[1];
    a2j = M[4];
    a3j = M[7];
    M[1] = b1;
    M[4] = b2;
    M[7] = b3;
    double determinantA2J = matrixDeterminant3x3(M);
    cout << determinantA2J << '\n';
    M[1] = a1j;
    M[4] = a2j;
    M[7] = a3j;

    a1j = M[2];
    a2j = M[5];
    a3j = M[8];
    M[2] = b1;
    M[5] = b2;
    M[8] = b3;
    double determinantA3J = matrixDeterminant3x3(M);
    cout << determinantA3J << '\n';
    M[2] = a1j;
    M[5] = a2j;
    M[8] = a3j;

    if (determinant == 0) {
        if ((determinantA2J == determinantA3J) && (determinantA1J == determinantA2J)) {
            cout << "система линейных уравнений имеет бесчисленное множество решений (система совместна и неопределённа)" << '\n';
        }
        else {
            cout << "система линейных уравнений решений не имеет (система несовместна)" << '\n';
        }
    }
    else {
        cout << "система линейных уравнений имеет единственное решение (система совместна и определённа)" << '\n';
        cout << "x1= " << determinantA1J / determinant << "\nx2= " << determinantA2J / determinant << "\nx3= " << determinantA3J / determinant << '\n';
    }
}
