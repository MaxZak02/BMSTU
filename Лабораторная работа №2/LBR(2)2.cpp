// Захаров Максим ИУ8-14/6 вариант 9
#include <iostream>
#include <vector>
#include <windows.h>
using namespace std;


class Square 
{
protected:               
    double a;            
public:
    Square(double a)     
    {
        this->a = a;
    }

    
    virtual double perimeter() const
    {
        return 4 * a;
    }

    
    virtual void print() const
    {
        cout << "Квадрат: a = " << a
             << ", P = " << perimeter() << endl;
    }

    virtual ~Square() {} 
};


class Priamougolnik : public Square 
{
    double b;           
public:

    Priamougolnik(double a, double b) : Square(a)
    {
        this->b = b;
    }

    double perimeter() const override
    {
        return 2 * (a + b);
    }

    
    void print() const override
    {
        Square::print(); 
        cout << "Прямоугольник: b = " << b
             << ", P = " << perimeter() << endl;
    }
};


int main()
{
    SetConsoleCP(65001);
SetConsoleOutputCP(65001);
    
    Square sq(5);
    Priamougolnik rect(5, 3);

    cout << "=== Вызов методов через объекты ===" << endl;
    sq.print();
    rect.print();
    cout << endl;

    
    cout << "=== Статический полиморфизм (вызов через объект/тип) ===" << endl;
    Square s2(4);
    cout << "s2.perimeter() = " << s2.perimeter() << endl; 
    Priamougolnik r2(4, 2);
    cout << "r2.perimeter() = " << r2.perimeter() << endl; 
    cout << "r2.Square::perimeter() = " << r2.Square::perimeter()
         << " (явный вызов базового метода)" << endl;
    cout << endl;

    
    cout << "=== Динамический полиморфизм (через указатель базового класса) ===" << endl;
    Square* p = &sq;
    p->print();          
    p = &rect;
    p->print();          
    cout << endl;

    
    vector<Square*> v;
    v.push_back(&sq);     
    v.push_back(&rect);   

    cout << "=== Данные всех объектов из вектора указателей ===" << endl;
    double sum = 0.0;
    for (size_t i = 0; i < v.size(); i++)
    {
        v[i]->print();              
        sum += v[i]->perimeter();   
    }
    cout << "Сумма периметров всех фигур = " << sum << endl;

    return 0;
}