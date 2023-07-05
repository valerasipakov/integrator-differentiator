// integrator-differentiator.cpp: определяет точку входа для приложения.
//

#include "integrator-differentiator.h"

using namespace std;

int main()
{
	parser pars = parser();

	while (true) {
		try
		{
			system("cls");
			cout << "   Enter your mathematical expression\n";
			cout << "   Use p for Pi and  exp(1) for e\n";
			string expression;
			cout << "   y = ";getline(cin, expression);
			cout << "   y = " << pars.calculate(expression) << endl;
			std::system("pause");
		}
		catch (const std::exception& e)
		{
			std::cout << e.what() << endl;
			std::system("pause");
		}
	}
	}
	

