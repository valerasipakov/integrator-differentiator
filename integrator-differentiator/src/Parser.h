#pragma once
#include <iostream>
#include <sstream>
#include <cmath>
#include <stack>
#include <exception>



class parser
{
public:
	double calculate(std::string str);

private:
	struct Leksema
	{
		char type;
		double value;
	};
	double Sin(double x);
	double Cos(double x);
	double Ctg(double x);
	int getRang(char ch);
	void Maths(std::stack <Leksema>& Stack_n, std::stack <Leksema>& Stack_o, Leksema& item);
	void changeLeksema(Leksema& leksema, char type, double value);



};

