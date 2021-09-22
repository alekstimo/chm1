// чм.1лаба.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include "Rational.h"
#include <fstream>
#include <string>
using namespace std;
void edinica(int i, int k, int n, Rational* a, Rational* b, Rational* c, Rational* p, Rational* q, Rational* f);
void obnulSnizu(int i, int k,int n, Rational* a, Rational* b, Rational* c, Rational* p, Rational* q, Rational* f);
void print(int k, int n, Rational* a, Rational* b, Rational* c, Rational* p, Rational* q, Rational* f);
void obnulSverhu(int i, int k, Rational* a, Rational* b, Rational* c, Rational* p, Rational* q, Rational* f);
void rabota(int k, int n, Rational* a, Rational* b, Rational* c, Rational* p, Rational* q, Rational* f);
bool proverka(int k, Rational* a, Rational* b, Rational* c, Rational* p, Rational* q, Rational* f);
void readVector(ifstream& fin, int n, Rational* arr, bool flag) {
    if (!flag) n = n - 1;
    for (int i = 0; i < n; i++) {
        int k;
        fin >> k;
        arr[i].set(k);
    }
}
void readFromFile(ifstream& fin, int& n, int& k, Rational* a, Rational* b, Rational* c, Rational* p, Rational* q, Rational* f) {
    readVector(fin, n, a, true);
    readVector(fin, n, b, false);
    readVector(fin, n, c, false);
    readVector(fin, n, p, true);
    readVector(fin, n, q, true);
    readVector(fin, n, f, true);
}

int main() {
    int n;
    int k;
    Rational* a, * b, * c, * p, * q, * f;

    ifstream fin("Текст.txt");
    if (!fin.is_open())
        return -1;
    else {
        fin >> n;
        fin >> k;
        a = new Rational[n];
        b = new Rational[n - 1];
        c = new Rational[n - 1];
        p = new Rational[n];
        q = new Rational[n];
        f = new Rational[n];
        readFromFile(fin, n, k, a, b, c, p, q, f);
        print(k, n, a, b, c, p, q, f);
        rabota(k, n, a, b, c, p, q, f);
        print(k, n, a, b, c, p, q, f);
    }
    system("Pause");
    return 0;
}

void print(int k,int n, Rational* a, Rational* b, Rational* c, Rational* p, Rational* q, Rational* f) {
    for (int i = 0; i < n; i++) {
        cout << '|';
        for (int j = 0; j < n; j++) {
            if (j == k)
                cout << p[i];
            else if (i == k) {
                for (int m = 0; m < n; m++) {
                    cout << q[m];
                }
                break;
            }
            else if (i == j + 1) {
                /*if (i == n-1) {
                    cout << c[i - 1];
                }
                else*/
                    cout << c[i-1];
            }
            else if (i == j)
                cout << a[i];
            else if (i == j - 1)
                cout << b[i];
            else
                cout << "0" << "\t";
        }
        cout << '=';
        cout << f[i];
        cout << '|';
        cout << endl;
    }
    cout << "----------------------------" << endl;
    cout << endl;
    
}
void rabota(int k,int n, Rational* a, Rational* b, Rational* c, Rational* p, Rational* q, Rational* f) {
    for (int i = 0; i < k; i++) {
        edinica(i, k, n, a, b, c, p, q, f);
        obnulSnizu(i, k,n, a, b, c, p, q, f);
        //cout << proverka(k, a, b, c, p, q, f) << endl;
        //print(k, n, a, b, c, p, q, f);
    }
    //print(k, n, a, b, c, p, q, f);
    
    for (int i = n - 1; i > k; i--) {
        edinica(i, k, n, a, b, c, p, q, f);
        obnulSverhu(i, k, a, b, c, p, q, f);
        //cout << proverka(k, a, b, c, p, q, f) << endl;
        //print(k, n, a, b, c, p, q, f);
    }
    //print(k, n, a, b, c, p, q, f);
    edinica(k, k, n, a, b, c, p, q, f); 
    for (int i = k; i < n-1; i++) {
        
        obnulSnizu(i, k, n, a, b, c, p, q, f);
        // print(k, n, a, b, c, p, q, f);
        //cout << proverka(k, a, b, c, p, q, f) << endl;
    }
    // print(k, n, a, b, c, p, q, f);
    for (int i = k; i > 0; i--) {
       
        obnulSverhu(i, k, a, b, c, p, q, f);
        //cout << proverka(k, a, b, c, p, q, f) << endl;
        //print(k, n, a, b, c, p, q, f);
    }
}
bool proverka(int k, Rational* a, Rational* b, Rational* c, Rational* p, Rational* q, Rational* f) {
    if((a[k]==p[k])&&(a[k]==q[k])&&(b[k-1]==p[k-1])&&(b[k]==q[k+1])&&(c[k-1]==q[k-1])&&(c[k]==p[k+1]))
        return 1;
    return 0;
}
void edinica(int i, int k,int n, Rational* a, Rational* b, Rational* c, Rational* p, Rational* q, Rational* f) {
    if (i <= k) {
        Rational koef(a[i]);
        a[i] = a[i] / a[i];
        b[i] = b[i] / koef;
        p[i] = p[i] / koef;
        f[i] = f[i] / koef;
        if (i == k) {
            //p[i] = a[i];
            q[i] = a[i];
            /*q[i] = a[i];
            q[i+1] = b[i];
            for (int j = i + 2; j < n; j++) {
                q[j] = q[j] / koef;
            }*/
        }
    }
    else {
        Rational koef(a[i]);
        a[i] = a[i] / a[i];
        c[i-1] = c[i-1] / koef;
        p[i] = p[i] / koef;
        f[i] = f[i] / koef;
    }
}
void obnulSnizu(int i,int k,int n, Rational* a, Rational* b, Rational* c, Rational* p, Rational* q, Rational* f) {
    if (i < k) {
        Rational koef(c[i]);
        c[i] = c[i] - koef * a[i];
        a[i + 1] = a[i + 1] - koef * b[i];
        p[i + 1] = p[i + 1] - koef * p[i];
        f[i + 1] = f[i + 1] - koef * f[i];
        
        if (i != k - 1) {
            koef = q[i];
            q[i] = q[i] - koef * a[i];
            q[i + 1] = q[i + 1] - koef * b[i];
            p[k] = a[k] = q[k] = q[k] - koef * p[i];
            f[k] = f[k] - koef * f[i];
        }
        else {
            q[i+1] = p[i+1];
            q[i] = c[i];
        }
        if (i == k - 2) {
            b[i + 1] = p[i + 1];
            c[i + 1] = q[i + 1];
        }
    }
    else if (i==k) {
        for (int j = k; j < n-1; j++) {
            Rational koef(p[j + 1]);
            p[j + 1] = p[j + 1] - koef * p[k];
            if (j == k) {
                c[j] = p[j + 1];
            }
            f[j + 1] = f[j + 1] - koef * f[k];
        }
    }
    else {
        Rational koef(c[i]);
        c[i] = c[i] - koef * a[i];
        f[i + 1] = f[i + 1] - koef * f[i];
    }
}

void obnulSverhu(int i, int k, Rational* a, Rational* b, Rational* c, Rational* p, Rational* q, Rational* f) {

    Rational koef(b[i - 1]);
    b[i - 1] = b[i - 1] - koef * a[i];
    f[i - 1] = f[i - 1] - koef * f[i];
    
    if(i>k) {
        a[i-1] = a[i-1] - koef * c[i-1];
        p[i-1] = p[i-1] - koef * p[i];
        koef = q[i];
        q[i] = q[i] - koef * a[i];
        q[i-1] = q[i-1] - koef * c[i-1];
        
        if (i != k + 1) {
            q[k] = a[k] = p[k] = p[k] - koef * p[i];
            f[k] = f[k] - koef * f[i];
        }
        if (i == k + 2) {
            c[i - 2] = p[i - 1];
            b[i - 2] = q[i - 1];
       }
    }
    else if (i == k) {
        p[i - 1] = b[i - 1];
        for (int j = k - 2; j >= 0; j--) {
            koef = p[j];
            p[j] = p[j] - koef * p[k];
            f[j] = f[j] - koef * f[k];
        }
    }
    
}