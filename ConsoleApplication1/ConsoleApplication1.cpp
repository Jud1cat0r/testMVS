#include <iostream>
#include "ctime"
#define random(min, max) (min+rand()%(max-min+1))
using namespace std;

const string name[] = { "John", "Karl", "Elisa", "Petr", "Ivan", "Nick", "Tom", "Roman", "Pavel", "Jerry" };

int size1 = 0;

struct Students {
    string name;
    int* array = new int[0];
};

Students* createStruct(int n, int m) {
    Students* student = new Students[n];
    size1 = n;
    int size2 = size(name);
    for (int i = 0, k; i < n; i++) {
        k = random(0, size2 - 1);
        student[i].name = name[k];
        student[i].array = new int[m];
        for (int j = 0; j < m; j++) {
            student[i].array[j] = random(6, 12);
        }
    }
    return student;
}

void showStruct(Students* st) {
    int size2 = _msize(st[0].array) / sizeof(st[0].array[0]);
    for (int i = 0; i < size1; i++) {
        cout << st[i].name << ":\t";
        for (int j = 0; j < size2; j++) {
            cout << st[i].array[j] << " ";
        }
        cout << endl;
    }
    cout << endl;
}

void excludeStruct(Students*& st) {
    int size2 = _msize(st[0].array) / sizeof(st[0].array[0]);
    int counter = 0;
    float summ;
    for (int i = 0; i < size1; i++) {
        summ = 0;
        for (int j = 0; j < size2; j++) {
            summ += st[i].array[j];
        }
        if (summ / size2 < 9) counter++;
    }
    Students* buf = new Students[size1 - counter];
    for (int i = 0, k = 0; i < size1; i++) {
        summ = 0;
        for (int j = 0; j < size2; j++) {
            summ += st[i].array[j];
        }
        if (summ / size2 >= 9) buf[k++] = st[i];
        else delete[] st[i].array;
    }
    delete[] st;
    st = buf;
    size1 -= counter;
}


void sortRec(Students* st, int l, int k = 1)
{
    for (int i = k; st[l].name[i] < st[l + 1].name[i] || st[l].name[i] != '\0' || st[l + 1].name[i] != '\0'; i++)
    {
        if (st[l].name[i] > st[l + 1].name[i])
        {
            swap(st[l], st[l + 1]);
            break;
        }
        else if (st[l].name[i] == st[l + 1].name[i])
        {
            sortRec(st, l, k + 1);
        }
    }
}

void sortStudent(Students* st)
{
    for (int i = 0; i < size1; i++)
    {
        for (int j = 0; j < size1 - 1; j++)
        {
            if (st[j].name[0] > st[j + 1].name[0]) swap(st[j], st[j + 1]);
            else if (st[j].name[0] == st[j + 1].name[0])
            {
                sortRec(st, j);
            }
        }
    }
}

void addStudent(Students*& st)
{
    int size2 = _msize(st[0].array) / sizeof(st[0].array[0]);
    Students* buf = new Students[size1 + 1];
    for (int i = 0; i < size1; i++)
    {
        buf[i].name = st[i].name;
        buf[i].array = new int[size2];
        for (int j = 0; j < size2; j++)
        {
            buf[i].array[j] = st[i].array[j];
        }
    }
    cout << "input name: ";
    cin >> buf[size1].name;
    cout << "input grade: ";
    buf[size1].array = new int[size2];
    for (int i = 0; i < size2; i++)
    {
        cin >> buf[size1].array[i];
    }

    delete[] st;
    st = buf;
    size1++;
}


void addGrade(Students*& st)
{
    int size2 = _msize(st[0].array) / sizeof(st[0].array[0]);
    Students* buf = new Students[size1];
    for (int i = 0; i < size1; i++)
    {
        buf[i].name = st[i].name;
        buf[i].array = new int[size2 + 1];
        for (int j = 0; j < size2; j++)
        {
            buf[i].array[j] = st[i].array[j];
        }
        buf[i].array[size2] = random(6, 12);
    }
    delete[] st;
    st = buf;
}


int main()
{
    srand(time(NULL));
    Students* student = createStruct(6, 8);
    showStruct(student);
    //excludeStruct(student);
    //showStruct(student);

    sortStudent(student);     //Домашнее задание № 1
    //addStudent(student);      //Домашнее задание № 2
    //addGrade(student);        //Домашнее задание № 3
    showStruct(student);

}