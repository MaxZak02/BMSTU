#include <iostream>
#include <string>
#include <vector>
#include <windows.h>   

using namespace std;


struct Disciplina
{
    string name;
    int    mark;
};

struct Student
{
    string fio;
    vector<Disciplina> disc;
};



Disciplina inputDisciplina()

{
    Disciplina d;
    cout << "  Предмет: ";
    cin.ignore();
    getline(cin, d.name);
    cout << "  Оценка: ";
    cin >> d.mark;
    return d;
}


void printDisciplina(const Disciplina& d)
{
    cout << d.name << " (" << d.mark << ")";
}


Student inputStudent(int number)
{
    Student s;
    cout << "Студент " << number << endl;
    cout << " ФИО: ";
    cin.ignore();                    
    getline(cin, s.fio);

    int m;   
    cout << " Кол-во предметов: ";
    cin >> m;
    for (int j = 0; j < m; j++)
    {
        cout << " Предмет " << j + 1 << ":" << endl;
        s.disc.push_back(inputDisciplina());
    }
    return s;
}


void printStudent(const Student& s)
{
    cout << s.fio << ": ";
    for (size_t j = 0; j < s.disc.size(); j++)
    {
        printDisciplina(s.disc[j]);
        if (j + 1 < s.disc.size()) cout << ", ";
    }
    cout << endl;
}


int main()
{
    
    SetConsoleCP(65001);        
    SetConsoleOutputCP(65001);  

    int n;
    cout << "Кол-во студентов ";
    cin >> n;

    vector<Student> group(n);

    for (int i = 0; i < n; i++)
        group[i] = inputStudent(i + 1);

    cout << endl << "----- Введённые данные -----" << endl;
    for (int i = 0; i < n; i++)
        printStudent(group[i]);
        
    int bd = 0;

     for (int i = 0; i < n; i++)
    {
        int d = 0;
        for(size_t j = 0; j < group[i].disc.size(); j++)
        {
            if (group[i].disc[j].mark == 2)
                d++;
        }
    
        if (d ==0)
            bd++;
    }

    cout << endl;
    cout << "Студентов без задолженностей: " << bd << endl;

    return 0;
}