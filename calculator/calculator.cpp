#include "CalcOfStr.cpp"
#include <iostream>
#include <exception>

using namespace std;

// мб постоянная фича - возведение в степень только с преобразованием в целое число 


int main() {

	string s;
	cout << "( ) ^ * / + -\nPress q to exit" << endl;

	while (true) {
		cout << "Enter: " << endl;
		getline(cin, s);
		
		if (s == "q")
			break;

		try {
			cout << "Rez: " << CalcOfStr::calc(s) << endl;
		}
		catch (exception err) {
			cout << "Rez: " << err.what() << endl;
		}
	}	
}