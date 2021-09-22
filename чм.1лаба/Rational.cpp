#include "Rational.h"

void Rational::reduce()
{
	if (*b < 0)
	{
		*a *= -1;
		*b *= -1;
	}
	for (int i = *b; i > 1; i--)
		if (*a % i == 0 && *b % i == 0)
		{
			*a /= i;
			*b /= i;
		}
}

Rational::Rational(int A, int B)
{
		a = new int;
		*a = A;
		b = new int;
		*b = B;
}
Rational::Rational(int A)
{
	a = new int;
	*a = A;
	b = new int;
	*b = 1;
}
Rational::Rational(const Rational & obj)
{
	a = new int;
	*a = *(obj.a);
	b = new int;
	*b = *(obj.b);
}
void Rational::set(int A)
{
	*a = A;
}
Rational::~Rational()
{
	delete a;
	delete b;
}

Rational Rational::operator+(Rational obj)
{
	reduce(); obj.reduce();
	Rational temp;
	if (*a == 0) {
		*temp.a = *obj.a;
		*temp.b = *obj.b;
	}
	else if (*b == *obj.b) {
		*temp.a = *a - *obj.a;
		*temp.b = *b;
	}
	else {
		*temp.a = (*a) * (*obj.b) + (*b) * (*obj.a);
		*temp.b *= (*obj.b)*(*b);
	}
	/*if (*b == *obj.b) {
		*temp.a = *a + *obj.a;
		*temp.b = *b;
	}
	else {
		*temp.b = nok(*b, *obj.b);
		*temp.a = (*a)*(*temp.b/(*b))+(*obj.a)*(*temp.b / (*obj.b));
	}*/
	temp.reduce();
	return temp;
}

Rational Rational::operator-(Rational obj)
{
	reduce(); obj.reduce();
	Rational temp;
	if (*a == 0) {
		*temp.a -= *obj.a;
		*temp.b = *obj.b;
	}
	else if (*b == *obj.b) {
		*temp.a = *a - *obj.a;
		*temp.b = *b;
	}
	else {
		*temp.a = (*a) * (*obj.b) - (*b) * (*obj.a);
		*temp.b *= (*obj.b)*(*b);
	}
	/*if (*b == *obj.b) {
		*temp.a = *a - *obj.a;
		*temp.b = *b;
	}
	else {
		*temp.b = nok(*b, *obj.b);
		*temp.a = (*a)*(*temp.b / (*b)) - (*obj.a)*(*temp.b / (*obj.b));
	}*/
	temp.reduce();
	return temp;
}

Rational Rational::operator*(Rational obj)
{
	reduce(); obj.reduce();
	Rational temp;
	*temp.a = (*a) * (*obj.a);
	*temp.b = (*b) * (*obj.b);
	temp.reduce();
	return temp;
}

Rational Rational::operator/(Rational obj)
{
	reduce(); obj.reduce();
	Rational temp;
	*temp.a = (*a)*(*obj.b);
	*temp.b = (*b)*(*obj.a);
	if (*temp.b < 0)
	{
		*temp.a *= -1;
		*temp.b *= -1;
	}
	temp.reduce();
	return temp;

}

bool Rational::operator==(Rational obj)
{
	reduce(); obj.reduce();
	return (*a == *obj.a && *b == *obj.b);
}

bool Rational::operator!=(Rational obj)
{
	reduce(); obj.reduce();
	return (!(*a == *obj.a && *b == *obj.b));
}

bool Rational::operator>(Rational obj)
{
	reduce(); obj.reduce(); bool f = 0;
	if (*b == *obj.b) {
		if (*a > *obj.a) f = 1;
	}
	else
		if ((*a)*(nok(*b, *obj.b) / (*b)) > (*obj.a)*(nok(*b, *obj.b) / (*obj.b))) f = 1;
	return f;
}

bool Rational::operator>=(Rational obj)
{
	return !(operator<(obj));
}

bool Rational::operator<(Rational obj)
{
	reduce(); obj.reduce(); bool f = 0;
	if (*b == *obj.b) {
		if (*a < *obj.a) f = 1;
	}
	else
		if ((*a)*(nok(*b, *obj.b) / (*b)) < (*obj.a)*(nok(*b, *obj.b) / (*obj.b))) f = 1;
	return f;
}

bool Rational::operator<=(Rational obj)
{
	return !(operator>(obj));
}

Rational Rational::operator=(Rational obj)
{
	*a = *(obj.a);
	*b = *(obj.b);
	return *this;
}

ostream & operator<<(ostream & out, Rational & obj)
{
	if (*obj.b == 1) {
		out << /*"a/b = "<<*/ *obj.a << "\t";
	}
	else if (*obj.a == 0) {
		out << /*"a/b = "<<*/ *obj.a << "\t";
	}
	else {
		out << /*"a/b = "<<*/ *obj.a << "/" << *obj.b<<"\t";
	}
	return out;
}

istream & operator>> (istream & in, Rational & obj)
{
	cout << "a = ";
	in >> *obj.a;
	cout << "b = ";
	in >> *obj.b;
	cout << endl;
	return in;
}

int nod(int a, int b)
{
	while (a > 0 && b > 0) {
		if (a > b)
			a %= b;
		else
			b %= a;
	}
	return a + b;
}

int nok(int a, int b)
{
	int n = nod(a, b);
	if (n != 0)
		n = (a*b) / n;
	else n = 0;
	return n;
}
