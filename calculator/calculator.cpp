#include <iostream>
#include <string>

using namespace std;

// мб постоянная фича - возведение в степень только с преобразованием в целое число 

int main()	{
	
	// TODO: создание цикла с условием выхода на определённую клавишу 
	// TODO: функции подсчета 
	// TODO: защита от дурака 

}

// функция правильно работает со строкой в формате:
	// строка начинается с числа, а не с пробела или знака
	// перед ( скобкой есть пробел, после его нет
	// перед ) противоположно
	// знаки разделены пробелами 

string main_calc(string s) { // функция обрабытавает строку со скобками и отдает на подсчет по отдельности без скобок
	while (int ind_start = s.rfind('(') != -1) {
		ind_start;
		int ind_finish = s.find(')', ind_start);
		string internal_s;
		internal_s.append(s, ind_start + 1, ind_finish - ind_start - 1);
		string value = find_calc(internal_s);
		s.replace(ind_start, ind_finish - ind_start - 1, value);
	}
	return find_calc(s);

	/*if (int ind_start = s.find('(') != -1) {
		int ind_finish = s.rfind(')');
		string internal_s;
		internal_s.append(s, ind_start + 1, ind_finish - ind_start - 1);

	}*/
}

string find_calc(string s) { // функция расчитывает строки без скобок // распределяет по действиям ( + - / * ^)
	// ^
	while (int ind_zn = s.find('^') != -1) 
		s = calc(s, ind_zn);

	// * /
	while (s.find('*') != -1 || s.find('/') != -1) {
		int ind_zn;
		if (s.find('*') < s.find('/') && s.find('*') != -1)
			ind_zn = s.find('*');
		else
			ind_zn = s.find('/');
		s = calc(s, ind_zn);

	}
	// + -
	while (s.find('*') != -1 || s.find('/') != -1) {
		int ind_zn;
		if (s.find('*') < s.find('/') && s.find('*') != -1)
			ind_zn = s.find('*');
		else
			ind_zn = s.find('/');
		s = calc(s, ind_zn);

	}
}


string calc(string s, int ind_zn) {
	int ind_start = s.rfind(' ', ind_zn);
	int ind_finish = s.find(' ', ind_zn);
	if (ind_finish == -1)
		ind_finish = s.length();
	string value_1;
	string value_2;
	value_1.append(s, ind_start + 1, ind_zn - ind_start - 2);
	value_2.append(s, ind_zn + 2, ind_finish - ind_zn - 2);

	string value;
	switch (s[ind_zn])
	{
	case '^':
		value = to_string(stoi(value_1) ^ stoi(value_2));
		break;
	case '*':
		value = to_string(stof(value_1) * stof(value_2));
		break;
	case '/':
		value = to_string(stof(value_1) / stof(value_2));
		break;
	case '+':
		value = to_string(stof(value_1) + stof(value_2));
		break;
	case '-':
		value = to_string(stof(value_1) - stof(value_2));
		break;
	default:
		break;
	}

	
	return s.replace(ind_start + 1, ind_finish - ind_start - 1, value);	
}


// Запуск программы: CTRL+F5 или меню "Отладка" > "Запуск без отладки"
// Отладка программы: F5 или меню "Отладка" > "Запустить отладку"

// Советы по началу работы 
//   1. В окне обозревателя решений можно добавлять файлы и управлять ими.
//   2. В окне Team Explorer можно подключиться к системе управления версиями.
//   3. В окне "Выходные данные" можно просматривать выходные данные сборки и другие сообщения.
//   4. В окне "Список ошибок" можно просматривать ошибки.
//   5. Последовательно выберите пункты меню "Проект" > "Добавить новый элемент", чтобы создать файлы кода, или "Проект" > "Добавить существующий элемент", чтобы добавить в проект существующие файлы кода.
//   6. Чтобы снова открыть этот проект позже, выберите пункты меню "Файл" > "Открыть" > "Проект" и выберите SLN-файл.
