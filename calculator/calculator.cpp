#include "CalcOfStr.cpp"
#include <iostream>
#include <exception>
#include <string>
#include <cmath>

using namespace std;

// мб постоянная фича - возведение в степень только с преобразованием в целое число 


int main() {

	// TODO: распределение проекта
	// TODO: создание цикла с условием выхода на определённую клавишу 
	// TODO: защита от дурака 

	string s;
	cout << "Enter: " << endl;
	getline(cin, s);
	try {
		cout << "Rez: " << CalcOfStr::calc(s) << endl;
	}
	catch (exception err) {
			cout << "Rez: " << err.what() << endl;
	}
}