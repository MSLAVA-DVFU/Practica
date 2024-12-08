#include "quadratic.h"
#include <iostream>
#include <string>
#include <cmath>
#include <fstream>
#include <iomanip>

using namespace std;

// ������� ��� �������� ������ ���������
void parseEquation(const string& s, float& a, float& b, float& c, bool& f1) {
    string term = "";
    int k = 0;
    string equation = ' ' + s + ' '; // ��������� ������� ��� �������� ���������

    for (char i : equation) {
        if ((isdigit(i) || i == '.') && (equation[k - 1] != 'x' || i != '2')) {
            term += i;
        }
        else {
            if (i == 'x' && equation[k + 1] == '2') { // ����������� ��� x^2
                if (term.empty() || term == "+" || term == "-") {
                    a += (term == "-") ? -1 : 1;
                }
                else {
                    a += stof(term);
                    f1 = true;
                }
                term = "";
            }
            else if (i == 'x' && equation[k + 1] != '2') { // ����������� ��� x
                if (term.empty() || term == "+" || term == "-") {
                    b += (term == "-") ? -1 : 1;
                }
                else {
                    b += stof(term);
                    f1 = true;
                }
                term = "";
            }
            else if (i == '+' || i == '-') { // ��������� ���������� �����
                if (!term.empty()) {
                    c += stof(term);
                    f1 = true;
                    term = "";
                }
                term += i;
            }
        }
        k++;
    }

    if (!term.empty()) {
        c += stof(term);
        bool f1 = true;
    }
}


// ������� ��� ���������� ������ ����� ������������
void solveWithDiscriminant(float a, float b, float c) {
    if (a != 0) {
        float D = b * b - 4 * a * c;
        if (D == 0) {
            float x = -b / (2 * a);
            cout << "Roots (with discriminant): " << fixed << setprecision(3) << x << ", " << x << endl;
        }
        else if (D > 0) {
            float x1 = (-b + sqrt(D)) / (2 * a);
            float x2 = (-b - sqrt(D)) / (2 * a);
            if (x1 < x2) {
                cout << "Roots (with discriminant): " << fixed << setprecision(3) << x1 << ", " << x2 << endl;
            }
            else {
                cout << "Roots (with discriminant): " << fixed << setprecision(3) << x2 << ", " << x1 << endl;
            }
        }
        else {
            cout << "No float roots" << endl;
        }
    }
    else if (b != 0) {
        float x = -c / b;
        cout << "Root of linear equation: " << fixed << setprecision(3) << x << endl;
    }
    else {
        cout << (c == 0 ? "infinity solutions" : "No solutions") << endl;
    }
}

// ������� ��� ���������� ������ �� ������� �����
void solveWithVieta(float a, float b, float c) {
    if (a == 0) {
        cout << "Impossible to use Vieta, because its no quadratic equation" << endl;
        return;
    }

    float sum = -b / a;
    float product = c / a;

    cout << "With Vieta:\n";
    cout << "Sum of roots: " << fixed << setprecision(3) << sum << endl;
    cout << "Product of roots: " << fixed << setprecision(3) << product << endl;

    // ����� ������ ����� ������� ����� (������� ��������� x^2 - sum * x + product = 0)
    float D = sum * sum - 4 * product;
    if (D < 0) {
        cout << "With Vieta: no float roots." << endl;
    }
    else if (D == 0) {
        float x = sum / 2;
        cout << "With Vieta: " << x << ", " << x << endl;
    }
    else {
        float x1 = (sum + sqrt(D)) / 2;
        float x2 = (sum - sqrt(D)) / 2;
        cout << "With Vieta: " << fixed << setprecision(3) << x1 << ", " << x2 << endl;
    }
}
void solveQuadraticEquation(const string& equation) {
    float a = 0, b = 0, c = 0;
    bool f1 = false;
    try {
        parseEquation(equation, a, b, c, f1);
        if (f1) {
            cout << "Coefs: a = " << a << ", b = " << b << ", c = " << c << endl;
            solveWithDiscriminant(a, b, c);
            solveWithVieta(a, b, c);
        }
        else {
            cout << "Not an equation" << endl;
        }
    }
    catch (const exception& e) {
        cerr << "Error: " << e.what() << endl;
    }
}