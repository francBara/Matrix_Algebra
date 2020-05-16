#ifndef FRACT_H
#define FRACT_H

#include <iostream>
#include "Utils.h"


class Fract
{
	public:
		int num;
		int den;
	
	public:
		Fract(int, int);
		Fract(int);
		Fract();
		void eq();
		void inverse();	
		Fract add(Fract);
		Fract sub(Fract);
		Fract per(Fract);
		Fract div(Fract);

		void print();
};

#endif
