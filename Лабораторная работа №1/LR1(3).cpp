
//Вариант 9 Захаров Максим ИУ8-14/6 цикл for
#include <iostream>
#include <cmath>

using namespace std;

const double P = 3.141592;


double f(double x)
{
    
    return tan(x) * tan(x) + 1 / (tan(x) * tan(x));
}


double f2(double x)
{
    return tan(x) - 1 / tan(x) - 2 * x;
}

int main()
{
   
    double a = P / 6;
    double b = P / 3;
    int n = 40;

    double m = (b - a) / n;
    double s = (f(a) + f(b)) / 2;

    
    for (int i = 1; i < n; i++)
        s += f(a + i * m);

    double S = s*m;
    double I = f2(b) - f2(a);

    
    cout << "S = " << S << endl;
    cout << "I = " << I << endl;

    return 0;
}