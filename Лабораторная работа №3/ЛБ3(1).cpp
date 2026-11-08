// Вариант 9 Захаров Максим ИУ8-14/6 

#include <iostream>
#include <string>
#include <fstream>
#include <vector>
using namespace std;


struct SCHOOL
{
    string City;
    int    Number;
    string Specialization;
    int    Students;
};


void print_schools(ostream& out, vector<SCHOOL>& Schools)
{
    for (auto& pos : Schools)
        out << pos.City << ". Школа N " << pos.Number
        << ". " << pos.Specialization
        << ", учеников: " << pos.Students << endl;
}


void write_schools(const string& file_name, const string& mode,
    vector<SCHOOL>& Schools)
{
    int n = (int)Schools.size();

    if (mode == "text")
    {

        ofstream foutt(file_name);
        foutt << n << endl;
        for (auto& pos : Schools)
        {

            foutt << pos.City << endl << pos.Specialization << endl;
            foutt << pos.Number << ' ' << pos.Students << endl;
        }
        foutt.close();
    }
    else if (mode == "binary")
    {

        ofstream foutb(file_name, ios::binary);
        foutb.write((char*)&n, sizeof(n));
        for (auto& pos : Schools)
        {

            foutb << pos.City << ends << pos.Specialization << ends;
            foutb.write((char*)&pos.Number, sizeof(pos.Number));
            foutb.write((char*)&pos.Students, sizeof(pos.Students));
        }
        foutb.close();
    }
}


void read_schools(const string& file_name, const string& mode,
    vector<SCHOOL>& Schools)
{
    int n;

    if (mode == "text")
    {
        ifstream fint(file_name);
        if (!fint)
        {
            cout << endl << "Error, file not found" << endl;
            return;
        }
        fint >> n;
        Schools.resize(n);
        for (auto& pos : Schools)
        {
            fint.ignore(2, '\n');
            getline(fint, pos.City);
            getline(fint, pos.Specialization);
            fint >> pos.Number;
            fint >> pos.Students;
        }
        fint.close();
    }
    else if (mode == "binary")
    {
        ifstream finb(file_name, ios::binary);
        if (!finb)
        {
            cout << endl << "Error, file not found" << endl;
            return;
        }
        finb.read((char*)&n, sizeof(n));
        Schools.resize(n);
        for (auto& pos : Schools)
        {

            getline(finb, pos.City, '\0');
            getline(finb, pos.Specialization, '\0');
            finb.read((char*)&pos.Number, sizeof(pos.Number));
            finb.read((char*)&pos.Students, sizeof(pos.Students));
        }
        finb.close();
    }
}

int main(int argc, const char* argv[])
{
    if (argc != 4)
    {
        cerr << "Error: Use four parameters\n";
        return 5;
    }

    const string mode(argv[1]);
    const string open_mode(argv[2]);
    const string file_name(argv[3]);

    vector<SCHOOL> Schools;

    if (mode == "write")
    {
        int n;
        cout << "n=";
        cin >> n;
        Schools.resize(n);

        for (int i = 0; i < n; i++)
        {
            cout << "School N=" << (i + 1) << endl;
            cout << "City: ";
            cin.ignore();
            getline(cin, Schools[i].City);
            cout << "Specialization: ";
            getline(cin, Schools[i].Specialization);
            cout << "Number: ";
            cin >> Schools[i].Number;
            cout << "Students: ";
            cin >> Schools[i].Students;
        }

        write_schools(file_name, open_mode, Schools);
        cout << "Data written to " << file_name << endl;
    }
    else if (mode == "read")
    {
        read_schools(file_name, open_mode, Schools);

        if (Schools.empty())
        {
            cout << "No data or file not found" << endl;
            return 1;
        }


        print_schools(cout, Schools);
    }
    else
    {
        cerr << "Error: mode must be 'write' or 'read'\n";
        return 2;
    }

    return 0;
}
