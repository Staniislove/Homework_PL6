#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <vector>
using namespace std;
struct Auto
{
    double cost;
    string brand;
    double power;
    string model;
};

Auto* Init(Auto A)
{
    Auto* B = new Auto;
    *B = A;
    return B;
}

void Del(Auto* A)
{
    delete A;
}

void A_Print(Auto* A)
{
    cout << endl << endl;
    cout << "Цена: " << A->cost << "    ";
    cout << "Марка: " << A->brand << "    ";
    cout << "Мощность: " << A->power << "    ";
    cout << "Модель: " << A->model << endl << endl;
}

struct Tree
{
    Auto* data;
    Tree* left;
    Tree* right;
};

bool sort_str(string a, string b)
{
    vector <string> v = { a, b };
    sort(v.begin(), v.end());
    if (v[0] == a) return true;
    else return false;
}

void Add_cost(Tree*& T, Auto* data)
{
    if (!T)
    {
        T = new Tree;
        T->data = data;
        T->left = NULL;
        T->right = NULL;
        return;
    }
    if (data->cost < T->data->cost) Add_cost(T->left, data);
    else Add_cost(T->right, data);
}

void Add_model(Tree*& T, Auto* data)
{
    if (!T)
    {
        T = new Tree;
        T->data = data;
        T->left = NULL;
        T->right = NULL;
        return;
    }
    if (sort_str(data->model , T->data->model)) Add_model(T->left, data);
    else Add_model(T->right, data);
}

void Print(Tree* T)
{
    if (!T) return;
    Print(T->left);
    A_Print(T->data);
    Print(T->right);
}

void Delete(Tree*& T)
{
    if (T)
    {
        if (T->left) Delete(T->left);
        if (T->right) Delete(T->right);
        Del(T->data);
        delete T;
        T = NULL;
    }
}

void Print_cost(Tree* T, float cost)
{
    if (!T) return;
    Print_cost(T->left, cost);
    if (T->data->cost < cost) A_Print(T->data);
    Print_cost(T->right, cost);
}

void Print_model(Tree* T, char a)
{
    if (!T) return;
    Print_model(T->left, a);
    if (T->data->model[0] == a) A_Print(T->data);
    Print_model(T->right, a);
}

int main()
{
    setlocale(LC_ALL, "Russian");
    Auto A;
    Tree* T = NULL;
    int m = 1;
    while (m)
    {
        ifstream file("Autos.txt");
        string line;
        system("cls");
        cout << "1. Сортировать по названию модели" << endl;
        cout << "2. Сортировать по цене" << endl;
        cout << "3. Показать модели авто, начинающиеся с указанной буквы" << endl;
        cout << "0. Выход" << endl;
        cin >> m;
        switch (m)
        {
        case 1:
        {
            while (getline(file, line))
            {
                istringstream line_F(line);
                line_F >> A.cost >> A.brand >> A.power >> A.model;
                Add_model(T, Init(A));
            }
            system("cls");
            Print(T);
            system("pause");
            break;
        }
        case 2:
        {
            while (getline(file, line))
            {
                istringstream line_F(line);
                line_F >> A.cost >> A.brand >> A.power >> A.model;
                Add_cost(T, Init(A));
            }
            system("cls");
            Print(T);
            system("pause");
            break;
        }
        case 3:
        {
            char a;
            cout << "Буква = "; cin >> a;
            while (getline(file, line))
            {
                istringstream line_F(line);
                line_F >> A.cost >> A.brand >> A.power >> A.model;
                Add_model(T, Init(A));
            }
            system("cls");
            Print_model(T, a);
            system("pause");
            break;
        }
        }
        Delete(T);
        file.close();
    }
    return 0;
}