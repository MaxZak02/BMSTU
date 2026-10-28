// Захаров Максим ИУ8-14/6 Вариант 9
#include <iostream>
#include <fstream>
#include <utility>
#include <windows.h>

using namespace std;


class Vector
{
    double *p = nullptr;
    int n = 0;

public:
    
    Vector(double *p, int n);
    Vector(int n);
    Vector(const Vector &V);
    Vector(Vector &&V);
    Vector();
    ~Vector();

    
    double& operator[](int index);
    Vector& operator=(const Vector &v2);
    Vector& operator=(Vector &&v2);

   
    friend Vector operator*(double x, const Vector &v2);
    friend Vector operator*(const Vector &v1, double x);
    friend ostream& operator<<(ostream &os, const Vector &v);
    friend istream& operator>>(istream &is, Vector &v);
};



Vector::Vector(double *p, int n)
{
    this->n = n;
    this->p = new double[n];
    for (int i = 0; i < n; i++) this->p[i] = p[i];
    cout << "Vector(double *p, int n)" << endl;
}


Vector::Vector(int n) : n(n)
{
    p = new double[n];
    cout << "Vector(int n)" << endl;
}


Vector::Vector(const Vector &V)
{
    n = V.n;
    p = new double[n];
    for (int i = 0; i < n; i++) p[i] = V.p[i];
    cout << "Vector(const Vector &V) n=" << n << endl;
}


Vector::Vector(Vector &&V)
{
    std::swap(p, V.p);
    std::swap(n, V.n);
    cout << "Vector(Vector&& V)" << endl;
}


Vector::Vector() : p(nullptr), n(0) 
{ 
    cout << "Vector()" << endl; 
}

Vector::~Vector()
{
    cout << "~Vector() n=" << n << endl;
    if (p != nullptr) delete[] p;
}


double& Vector::operator[](int index) 
{ 
    return p[index]; 
}


Vector& Vector::operator=(const Vector &v2)
{
    if (this != &v2) {
        n = v2.n;
        if (p != nullptr) delete[] p;
        p = new double[n];
        for (int i = 0; i < n; i++) p[i] = v2.p[i];
    }
    cout << "operator=(const Vector&)" << endl;
    return *this;
}

Vector& Vector::operator=(Vector &&v2)
{
    if (this != &v2) { 
        std::swap(p, v2.p); 
        std::swap(n, v2.n); 
    }
    cout << "operator=(Vector&&)" << endl;
    return *this;
}

Vector operator*(double x, const Vector &v2)
{
    Vector V(v2.n);
    for (int i = 0; i < v2.n; i++) V.p[i] = x * v2.p[i];
    return V;
}

Vector operator*(const Vector &v1, double x)
{
    Vector V(v1.n);
    for (int i = 0; i < v1.n; i++) V.p[i] = v1.p[i] * x;
    return V;
}

// Вывод в поток
ostream& operator<<(ostream &os, const Vector &v)
{
    os << "n=" << v.n << endl;
    for (int i = 0; i < v.n; i++) os << v.p[i] << " ";
    os << endl;
    return os;
}

// Ввод из потока
istream& operator>>(istream &is, Vector &v)
{
    int nn;
    is >> nn;
    if (!is) return is;
    if (v.p != nullptr) delete[] v.p;
    v.n = nn;
    v.p = new double[nn];
    for (int i = 0; i < nn; i++) is >> v.p[i];
    return is;
}



int main()
{
    SetConsoleCP(65001);
    SetConsoleOutputCP(65001);

    ifstream fin("input.txt");
    ofstream fout("output.txt");

    Vector V1;
    fin >> V1;
    double k;
    fin >> k;

    fout << V1;                     
    fout << "k=" << k << endl;

    V1[0] *= 2;                     
    fout << V1;

    Vector V2 = V1 * k;             
    fout << V2;

    Vector V3 = k * V1;             
    fout << V3;

    Vector V4;
    V4 = V1;                        
    fout << V4;

    Vector V5;
    V5 = std::move(V2);             
    fout << V5;

    Vector V6 = V3;                 
    fout << V6;

    Vector V7 = std::move(V3);      
    fout << V7;

    return 0;
}