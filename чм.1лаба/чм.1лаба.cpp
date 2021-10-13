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
int proverka2(int n, Rational* a, Rational* b);
int proverka3(int n, Rational* a, Rational* c);
bool proverka4(int k, int stop1);
void change(int stop1, int stop2);
void badnull(Rational* a, int k, int& nul1, int& nul2) {
    Rational null(0, 1);
    if (a[k - 1] == null) {
        nul1 = k - 1;
    }
    if (a[k + 1] == null) {
        nul2 = k + 1;
    }
}
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
    Rational null(0, 1);
    int nul1=-1, nul2=-1;
    badnull(a, k, nul1, nul2);
    int stop1 = proverka2(n, a, b);
    int stop2 = proverka3(n, a, c);
    if (a[0] != null)  {                                        //не ноль на а[0][0]
        if (a[n - 1] != null) {                                 //не ноль на a[n-1][n-1]
            if (proverka4(k, stop1)||(stop1>k+1)) {               // ноль на главной и верхней побочной за испорченными или его нет
                if (proverka4(k, stop2)||(stop2<k-1)) {           // ноль на главной и нижней побочной до испорченных или его нет
                    for (int i = 0; i < k; i++) {               //если обоих нет случаев + если после сверху и до снизу + 
                        edinica(i, k, n, a, b, c, p, q, f);     //+ если есть сверху после и нет снизу
                        obnulSnizu(i, k, n, a, b, c, p, q, f);
                    }
                    for (int i = n - 1; i > k; i--) {
                        edinica(i, k, n, a, b, c, p, q, f);
                        obnulSverhu(i, k, a, b, c, p, q, f);
                    }
                    edinica(k, k, n, a, b, c, p, q, f);
                    for (int i = k; i < n - 1; i++) {
                        obnulSnizu(i, k, n, a, b, c, p, q, f);
                    }
                    for (int i = k; i > 0; i--) {
                        obnulSverhu(i, k, a, b, c, p, q, f);
                    }
                }
                else  if (stop1!=stop2){                                    
                    if ((stop2 != -1)&&(stop1!=-1)) {                    // ноль на главной и нижней побочной после испорченных + ноль на главной и верхней побочной после 
                        change(stop1, stop2);
                        if (stop1 != stop2 + 1) {
                            for (int i = 0; i < k; i++) {
                                edinica(i, k, n, a, b, c, p, q, f);
                                obnulSnizu(i, k, n, a, b, c, p, q, f);
                            }
                            for (int i = n - 1; i > stop1; i--) {
                                edinica(i, k, n, a, b, c, p, q, f);
                                obnulSverhu(i, k, a, b, c, p, q, f);

                            }
                            for (int i = stop1 - 1; i > stop2; i--) {
                                edinica(i, k, n, a, b, c, p, q, f);
                                obnulSverhu(i, k, a, b, c, p, q, f);

                            }
                            for (int i = stop2 - 1; i > k; i--) {
                                edinica(i, k, n, a, b, c, p, q, f);
                                obnulSverhu(i, k, a, b, c, p, q, f);

                            }
                            for (int i = k + 1; i < stop2; i++) {
                                obnulSnizu(i, k, n, a, b, c, p, q, f);

                            }
                            for (int i = stop2 + 1; i < stop1; i++) {
                                obnulSnizu(i, k, n, a, b, c, p, q, f);

                            }
                            for (int i = stop1 + 1; i < n - 1; i++) {
                                obnulSnizu(i, k, n, a, b, c, p, q, f);

                            }
                            edinica(stop1, k, n, a, b, c, p, q, f);
                            obnulSverhu(stop1, k, a, b, c, p, q, f);
                            obnulSnizu(stop1, k, n, a, b, c, p, q, f);
                            edinica(stop2, k, n, a, b, c, p, q, f);
                            obnulSverhu(stop2, k, a, b, c, p, q, f);
                            obnulSnizu(stop2, k, n, a, b, c, p, q, f);
                            edinica(k, k, n, a, b, c, p, q, f);
                            obnulSnizu(k, k, n, a, b, c, p, q, f);
                            obnulSverhu(k, k, a, b, c, p, q, f);
                            /*for (int i = k; i > 0; i--) {

                                obnulSverhu(i, k, a, b, c, p, q, f);

                            }*/
                        }
                    }
                    else if (stop1 == -1) { //  если нет сверху и есть после снизу
                       
                        for (int i = 0; i < k; i++) {              
                            edinica(i, k, n, a, b, c, p, q, f);     
                            obnulSnizu(i, k, n, a, b, c, p, q, f);
                        }
                        for (int i = k-1; i > 0; i--) {
                            obnulSverhu(i, k, a, b, c, p, q, f);
                        }
                        for (int i = k+1; i < n - 1; i++) {
                            edinica(i, k, n, a, b, c, p, q, f);
                            obnulSnizu(i, k, n, a, b, c, p, q, f);
                        }
                        edinica(n-1, k, n, a, b, c, p, q, f);
                        for (int i = n - 1; i > k; i--) {
                            obnulSverhu(i, k, a, b, c, p, q, f);
                        }
                    
                        edinica(k, k, n, a, b, c, p, q, f);
                        obnulSnizu(k, k, n, a, b, c, p, q, f);
                        obnulSverhu(k, k, a, b, c, p, q, f);
                        
                    }
                }
            }
            else if (proverka4(k, stop2) || (stop2 > k+1)) {                            //ноль на главной и верхней побочной до испорченных  + ноль на главной и нижней побочной за испорченными + что то еще я стерла нечаянно
              
                if (nul1!=-1) {
                    if (nul1 != stop1 + 1) {
                        for (int i = k - 2; i > 0; i--) {
                            edinica(i, k, n, a, b, c, p, q, f);
                            obnulSverhu(i, k, a, b, c, p, q, f);
                          //  cout << proverka(k, a, b, c, p, q, f) << " ";
                        }
                        //cout << endl;
                        edinica(0, k, n, a, b, c, p, q, f);
                        for (int i = 0; i < k - 1; i++) {
                            obnulSnizu(i, k, n, a, b, c, p, q, f);
                          //  cout << proverka(k, a, b, c, p, q, f) << " ";
                        }
                        //cout << endl;
                        edinica(k - 1, k, n, a, b, c, p, q, f);
                        obnulSverhu(k - 1, k, a, b, c, p, q, f);
                        obnulSnizu(k - 1, k, n, a, b, c, p, q, f);
                        //cout << proverka(k, a, b, c, p, q, f) << " " << endl;
                    }
                }
                else {
                    for (int i = k - 1; i > 0; i--) {
                        edinica(i, k, n, a, b, c, p, q, f);
                        obnulSverhu(i, k, a, b, c, p, q, f);
                    }
                    edinica(0, k, n, a, b, c, p, q, f);
                    for (int i = 0; i < k; i++) {
                        obnulSnizu(i, k, n, a, b, c, p, q, f);
                    }
                }

                if (nul2 != -1) {
                    if (nul2 != stop2 + 1) {
                        for (int i = k + 2; i < n - 1; i++) {
                            edinica(i, k, n, a, b, c, p, q, f);
                            obnulSnizu(i, k, n, a, b, c, p, q, f);

                        }
                        edinica(n - 1, k, n, a, b, c, p, q, f);
                        for (int i = n - 1; i > k+1; i--) {
                            obnulSverhu(i, k, a, b, c, p, q, f);
                        }
                        edinica(k + 1, k, n, a, b, c, p, q, f);
                        obnulSverhu(k + 1, k, a, b, c, p, q, f);
                        obnulSnizu(k + 1, k, n, a, b, c, p, q, f);
                    }
                }
                else {
                    for (int i = k + 1; i < n - 1; i++) {
                        edinica(i, k, n, a, b, c, p, q, f);
                        obnulSnizu(i, k, n, a, b, c, p, q, f);
                        //cout << proverka(k, a, b, c, p, q, f) << " ";
                    }
                    //cout << endl;
                    edinica(n - 1, k, n, a, b, c, p, q, f);
                    for (int i = n - 1; i > k; i--) {
                        obnulSverhu(i, k, a, b, c, p, q, f);
                      //  cout << proverka(k, a, b, c, p, q, f) << " ";
                    }
                   // cout << endl;
                }
                edinica(k, k, n, a, b, c, p, q, f);
                obnulSverhu(k, k, a, b, c, p, q, f);
                obnulSnizu(k, k, n, a, b, c, p, q, f);
               // cout << proverka(k, a, b, c, p, q, f) << " " << endl;
               
            }
            else if (stop1 != stop2) {              //ноль на главной и верхней побочной до испорченных + ноль на главной и нижней побочной до испорченных
                change(stop1, stop2);
                if (stop1 != stop2 + 1) {
                    for (int i = n - 1; i > k; i--) {
                        edinica(i, k, n, a, b, c, p, q, f);
                        obnulSverhu(i, k, a, b, c, p, q, f);
                    }

                    for (int i = k + 1; i < n - 1; i++) {
                        obnulSnizu(i, k, n, a, b, c, p, q, f);
                    }
                    for (int i = 0; i < stop2; i++) {
                        edinica(i, k, n, a, b, c, p, q, f);
                        obnulSnizu(i, k, n, a, b, c, p, q, f);
                    }
                    for (int i = stop2+1; i < stop1; i++) {
                        edinica(i, k, n, a, b, c, p, q, f);
                        obnulSnizu(i, k, n, a, b, c, p, q, f);
                    }
                    for (int i = stop1+1; i < k - 1; i++) {
                        edinica(i, k, n, a, b, c, p, q, f);
                        obnulSnizu(i, k, n, a, b, c, p, q, f);
                    }
                    for (int i = k - 2; i > stop2; i--) {
                        obnulSverhu(i, k, a, b, c, p, q, f);
                    }
                    for (int i = stop2 + 1; i > stop1; i--) {
                        obnulSverhu(i, k, a, b, c, p, q, f);
                    }
                    for (int i = stop1 + 1; i > 0; i--) {
                        obnulSverhu(i, k, a, b, c, p, q, f);
                    }
                    edinica(stop1, k, n, a, b, c, p, q, f);
                    obnulSverhu(stop1, k, a, b, c, p, q, f);
                    obnulSnizu(stop1, k, n, a, b, c, p, q, f);
                    edinica(stop2, k, n, a, b, c, p, q, f);
                    obnulSverhu(stop2, k, a, b, c, p, q, f);
                    obnulSnizu(stop2, k, n, a, b, c, p, q, f);
                    edinica(k, k, n, a, b, c, p, q, f);
                    obnulSnizu(k, k, n, a, b, c, p, q, f);
                    obnulSverhu(k, k, a, b, c, p, q, f);
                   /* for (int i = k; i > 0; i--) {

                        obnulSverhu(i, k, a, b, c, p, q, f);

                    }*/
                }

            }
        }
    }
}
void change(int stop1, int stop2) {
    if (stop1 < stop2) {
        stop1 += stop2;
        stop2 -= stop1;
        stop1 -= stop2;
    }
}
bool proverka(int k, Rational* a, Rational* b, Rational* c, Rational* p, Rational* q, Rational* f) {
    if((a[k]==p[k])&&(a[k]==q[k])&&(b[k-1]==p[k-1])&&(b[k]==q[k+1])&&(c[k-1]==q[k-1])&&(c[k]==p[k+1]))
        return 1;
    return 0;
}
int proverka2(int n, Rational* a, Rational* b) {
    Rational null(0, 1);
    for (int i = 1; i < n; i++) {
        if ((a[i] == b[i-1]) && (b[i-1] == null))
            return i;
    }
    return -1;
}
int proverka3(int n, Rational* a, Rational* c) {
    Rational null(0, 1);
    for (int i = 0; i < n-1; i++) {
        if ((a[i] == c[i]) && (a[i] == null))
            return i;
    }
    return -1;
}
bool proverka4(int k, int stop1) {
    if ((stop1 == -1) || (stop1 == k))
        return true;
    return false;
}
void edinica(int i, int k,int n, Rational* a, Rational* b, Rational* c, Rational* p, Rational* q, Rational* f) {
    
        Rational koef(a[i]);
        a[i] = a[i] / a[i];
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
        if (i > 0) {
            c[i - 1] = c[i - 1] / koef;
        }
        if (i < n - 1) {
            b[i] = b[i] / koef;
        }
    
}
void obnulSnizu(int i,int k,int n, Rational* a, Rational* b, Rational* c, Rational* p, Rational* q, Rational* f) {
    if (i != k) {
        Rational koef(c[i]);
        c[i] = c[i] - koef * a[i];
        a[i + 1] = a[i + 1] - koef * b[i];
        p[i + 1] = p[i + 1] - koef * p[i];
        f[i + 1] = f[i + 1] - koef * f[i];
        
        if ((i != k - 1)&&(i < k)) {
            koef = q[i];
            q[i] = q[i] - koef * a[i];
            q[i + 1] = q[i + 1] - koef * b[i];
            p[k] = a[k] = q[k] = q[k] - koef * p[i];
            f[k] = f[k] - koef * f[i];
        }
        else if (i < k ) {
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
    //else {
    //    Rational koef(c[i]);
    //    c[i] = c[i] - koef * a[i];
    //    f[i + 1] = f[i + 1] - koef * f[i]; //дописать добавку когда обнуление снизу после испорченных с изменением столбца р
    //    p[i + 1] = p[i + 1] - koef * p[i];
    //}
}

void obnulSverhu(int i, int k, Rational* a, Rational* b, Rational* c, Rational* p, Rational* q, Rational* f) {

    Rational koef(b[i - 1]);
    b[i - 1] = b[i - 1] - koef * a[i];
    f[i - 1] = f[i - 1] - koef * f[i];
    
    if(i!=k) {
        a[i-1] = a[i-1] - koef * c[i-1];
        p[i-1] = p[i-1] - koef * p[i];
        if (i > k) {
            koef = q[i];
            q[i] = q[i] - koef * a[i];
            q[i - 1] = q[i - 1] - koef * c[i - 1];

            if (i != k + 1) {
                q[k] = a[k] = p[k] = p[k] - koef * p[i];
                f[k] = f[k] - koef * f[i];
            }
            if (i == k + 2) {
                c[i - 2] = p[i - 1];
                b[i - 2] = q[i - 1];
            }
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
    //дописать на случай когда обнуление сверху до испорченных с изменением столбца p
}