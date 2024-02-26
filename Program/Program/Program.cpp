#include <iostream>
#include <fstream>
#include <string>
#include <stdio.h>

using namespace std;

struct student
{
    string sname;
    string nname;
    string fname;
    string phone_number;
    string group;
    int grade_1;
    int grade_2;
    int grade_3;

    void info_input()
    {
        cout << "Введите фамилию студента: ";
        cin >> sname;
        cout << "Введите имя студента: ";
        cin >> nname;
        cout << "Введите отчество студента: ";
        cin >> fname;
        cout << "Введите номер телефона студента: ";
        cin >> phone_number;
        cout << "Введите группу студента: ";
        cin >> group;
        cout << "Введите оценку студента за 1-ый предмет: ";
        cin >> grade_1;
        cout << "Введите оценку студента за 2-ой предмет: ";
        cin >> grade_2;
        cout << "Введите оценку студента за 3-ий предмет: ";
        cin >> grade_3;
    }

    void info_output()
    {
        cout << "=================================================================================================" << endl << endl;
        cout << "Фамилия студента: " << sname << endl;
        cout << "Имя студента: " << nname << endl;
        cout << "Отчество студента: " << fname << endl;
        cout << "Номер телефона студента: " << phone_number << endl;
        cout << "Группа студента: " << group << endl;
        cout << "Оценка студента за 1-ый предмет: " << grade_1 << endl;
        cout << "Оценка студента за 2-ой предмет: " << grade_2 << endl;
        cout << "Оценка студента за 3-ий предмет: " << grade_3 << endl;
        cout << endl << "=================================================================================================" << endl;
        
    }

    bool for_deliting(string p_num, double mid_gr) {
        if ((phone_number == p_num) && (((double)(grade_1 + grade_2 + grade_3) / 3.0) < mid_gr)) {
            return true;
        }
        else {
            return false;
        }
    }
};

void fun_form(int n, student *stud);
void fun_print(int n);
int fun_delete_matchng(int n, string p_num, double mid_gr);
void fun_add(int n, string name);

int main()
{
    system("chcp 1251");

    int n;
    
    string p_num, sname;
    int mid_gr;

    cout << "Введите количество студентов: ";
    cin >> n;

    student* studs = new student[n];
    
    for (int i = 0; i < n; ++i)
    {
        studs[i].info_input();
    }

    fun_form(n, studs);
    fun_print(n);


    cout << "Введите номер на удаление: ";
    cin >> p_num;
    cout << "Введите среднюю оценку на удаление: ";
    cin >> mid_gr;

    cout << n << endl;
    n = fun_delete_matchng(n, (string)p_num, mid_gr);
    cout << n << endl;
    fun_print(n);

    cout << "Введите фамилию, после которой нужно добавить элемент: ";
    cin >> sname;
    fun_add(n, sname);
    fun_print(n);
}


void fun_form(int n, student* w_mas)
{
    FILE* f;
    if ((f = fopen("database_students.dat", "wb")) == NULL) exit(1);
    student* stud = w_mas;

    fwrite(stud, sizeof(student), n, f);

    fclose(f);
}

void fun_print(int n)
{
    FILE* f;
    if ((f = fopen("database_students.dat", "rb")) == NULL) exit(2);
    student* stud = new student[n];
    //student stud[50];
    fread(stud, sizeof(student), n, f);
    fclose(f);


    for (int i = 0; i < n; ++i)
    {
        cout << stud[i].sname << " " << endl;
    }

    delete[] stud;
}

int fun_delete_matchng(int n, string p_num, double mid_gr)
{
    int dels = 0;
    //student* stud = new student[n];
    student stud[50];
    FILE* f;

    if ((f = fopen("database_students.dat", "rb")) == NULL) exit(3);
    fread(stud, sizeof(student), n, f);
    fclose(f);
    int new_n = n;
    for (int i = 0; i < new_n; ++i) {
        if (stud[i].for_deliting(p_num, mid_gr))
        {   
            cout << stud[i].sname << endl;
            for (int j = i; j < n - 1; j++)
            {
                stud[j] = stud[j + 1];
            }
            dels++;
            new_n--;
        }
    }

    cout << dels << endl;

    if ((f = fopen("database_students.dat", "wb")) == NULL) exit(4);
    fwrite(stud, sizeof(student), n, f);
    fclose(f);
    //delete[] stud;
    return new_n;
}

void fun_add(int n, string name)
{
    student* stud = new student[n + 1];
    //student stud[50];
    FILE* f;


    
    if ((f = fopen("database_students.dat", "rb")) == NULL) exit(3);
    fread(stud, sizeof(student), n + 1, f);
    fclose(f);



    int i = 0;
    bool check = true;
    while ((i < n) && (check)) {
        if (stud[i].sname == name)
        {
            for (int j = n + 1; j > i + 1; j--)
            {
                stud[j] = stud[j - 1];
            }
            check = false;
        }
        ++i;
    }
    
    if (check) {
        cout << "Ошибка поиска";
    }
    else
    {
        stud[i].info_input();
    }

    if ((f = fopen("database_students.dat", "wb")) == NULL) exit(4);
    fwrite(stud, sizeof(student), n + 1, f);
    fclose(f);
    delete[] stud;
    
}
