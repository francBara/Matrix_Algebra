#include "Fract.h"

Fract::Fract(int n, int d)
{
	num = n;
	den = d;
}

Fract::Fract(int n)
{
	num = n;
	den = 1;
}

Fract::Fract()
{
	num = 0;
	den = 1;
}

void Fract::print()
{
	if (den == 1)
	{
		std::cout << num;
	}
	else
	{
		std::cout << num << "/" << den;
	}
}

void Fract::eq()
{
	int tmpMcd;

	do
	{
		tmpMcd = mcd(num, den);

		num = num / tmpMcd;

		den = den / tmpMcd;

	} while (tmpMcd != 1);
}

void Fract::inverse()
{
	num = -num;
}

Fract Fract::add(Fract f)
{
	Fract nu_fract;

	nu_fract.den = mcm(den, f.den);

	nu_fract.num = (nu_fract.den / den) * num + (nu_fract.den / f.den) * f.num;

	nu_fract.eq();

	return nu_fract;
}

Fract Fract::sub(Fract f)
{
	Fract nu_fract;

	nu_fract.den = mcm(den, f.den);

	nu_fract.num = (nu_fract.den / den) * num - (nu_fract.den / f.den) * f.num;

	nu_fract.eq();

	return nu_fract;
}

Fract Fract::per(Fract f)
{
	Fract nu_fract;

	nu_fract.den = den * f.den;

	nu_fract.num = num * f.num;

	nu_fract.eq();

	return nu_fract;
}

Fract Fract::div(Fract f)
{
	Fract nu_fract;

	nu_fract.den = den * f.num;

	nu_fract.num = num * f.den;

	nu_fract.eq();

	return nu_fract;
}


