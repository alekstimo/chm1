#include <iostream>
using namespace std;

class Rational {
	int *a;
	int *b;
	void reduce();
public:
	Rational(int A = 0, int B = 1); 
	Rational(int A);
	Rational(const Rational &obj);
	void set(int A);
	~Rational();

	Rational operator+(Rational obj);
	Rational operator-(Rational obj);
	Rational operator*(Rational obj);
	Rational operator/(Rational obj);

	bool operator==(Rational obj);
	bool operator!=(Rational obj);
	bool operator>(Rational obj);
	bool operator>=(Rational obj);
	bool operator<(Rational obj);
	bool operator<=(Rational obj);

	Rational operator=(Rational obj);

	friend ostream & operator<<(ostream & out, Rational & obj);
	friend istream & operator>>(istream & in, Rational & obj);
};

int nod(int a, int b);
int nok(int a, int b);