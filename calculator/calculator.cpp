#include <iostream>
#include <string>
#include <cmath>

using namespace std;

// мб постоянная фича - возведение в степень только с преобразованием в целое число 


// функция правильно работает со строкой в формате:
	// строка начинается с числа, а не с пробела или знака
	// перед ( скобкой есть пробел, после его нет
	// перед ) противоположно
	// знаки разделены пробелами 

bool char_exist_in_array(char ch, char *arr, int n) {
	for (int i = 0; i < n; i++) { // SIZEOF работает неправильно
		if (ch == arr[i])
			return true;
	}
	return false;
}


bool check_expression(string s) { // мб это не надо, а просто выкидывать ошибки при парсинге 
	// Проверка на знаки 
	char allowed_chars[] = { '1', '2', '3', '4', '5', '6', '7', '8', '9', '0',
		'.', '(', ')', '/', '*', '^', '+', '-', ' ' };
	for (int i = 0; i < s.length(); i++) {
		if (char_exist_in_array(s[i], allowed_chars, 19) == false)
			return false;
	}

	// Проверка количества скобок
	int count_open = 0;
	for (int i = 0; i < s.length(); i++) {
		if (s[i] == '(')
			count_open++;
		else if (s[i] == ')')
			count_open--;
		if (count_open < 0)
			return false;
	}

	if (count_open != 0)
		return false;
	//return count_open == 0;
	
	return true;
	// правильность открывания скобок и их количесво
	// количество знаков подряд
}

string do_correct_expression(string s) {
	// удалить лишние пробелы
	int i = 0;
	while (i < s.length()) { // == while (true)
		int ind = s.find(' ', i);
		if (ind == -1)
			break;
		if (ind == s.length() - 1) {
			s.erase(ind, 1);
			break;
		}
		while (s[ind + 1] == ' ') {
			s.erase(ind, 1);
		}
		i = ind + 1;
	}

	// доставить нужные
	char arr[7] = { '(', ')', '^', '*', '/', '+', '-' };
	// ПРОБЛЕМЫ С МИНУСОМ (КОГДА НУЖНО УКАЗАТЬ ОТРИЦАТЕЛЬНОЕ ЧИСЛО)
	for (int j = 0; j < 7; j++) {
		i = 0;
		while (i < s.length()) { // == while (true)
			int ind = s.find(arr[j], i);
			
			if (ind < 0)
				break;

			i = ind + 1;

			if (ind == 0) {
				s.insert(ind, " ");
				i++;
				if (s[ind + 2] != ' ') {
					s.insert(ind + 2, " ");
					i++;
				}
				continue;
			}
			
			if (ind == s.length() - 1) {
				s.insert(ind + 1, " ");
				if (s[ind - 1] != ' ') {
					s.insert(ind, " ");
					i++;
				}
				continue;
			}

			if (s[ind - 1] != ' ') {
				s.insert(ind, " ");
				i++;
				if (s[ind + 2] != ' ') {
					s.insert(ind + 2, " ");
					i++;
				}
			}
			else if (s[ind + 1] != ' ') {
				s.insert(ind + 1, " ");
				i++;
			}
		}
	}

	i = 0;
	while (i < s.length()) { // == while (true)
		int ind = s.find(" - ", i);
		if (ind == -1)
			break;
		i = ind + 3;
		if (ind == 0) {
			s.erase(ind + 2, 1);
			continue;
		}

		// сюда можно подставить метод поиска элемента в массиве
		for (int j = 0; j < 7; j++) {
			if (arr[j] == s[ind - 1]) {
				s.erase(ind + 2, 1);
				break;
			}
		}
	}

	
	return s;
}


string calc(string s, int ind_zn) {
	int ind_start = s.rfind(' ', ind_zn - 2);
	int ind_finish = s.find(' ', ind_zn + 2);
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
		value = to_string(pow(stoi(value_1), stoi(value_2)));
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
		// error
		break;
	}


	return s.replace(ind_start + 1, ind_finish - ind_start - 1, value);
}

string find_calc(string s) { // функция расчитывает строки без скобок // распределяет по действиям ( + - / * ^)
	// ^
	while (s.find('^') != -1) {
		int ind_zn = s.find('^');
		s = calc(s, ind_zn);
	}
		

	// надо переписать код ниже, сократив расчеты и мб в inline if
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
	while (s.find('+') != -1 || s.find("- ") != -1) {
		int ind_zn;
		if (s.find('+') < s.find("- ") && s.find('+') != -1)
			ind_zn = s.find('+');
		else
			ind_zn = s.find("- ");
		s = calc(s, ind_zn);

	}

	if (s[0] == ' ')
		s.erase(0, 1);

	if (s[s.length() - 1] == ' ')
		s.erase(s.length() - 1, 1);

	return s;
}


string main_calc(string s) { // функция обрабытавает строку со скобками и отдает на подсчет по отдельности без скобок
	if (check_expression(s) == false)
		return "Fail expression";
	s = do_correct_expression(s);

	while (s.rfind('(') != -1) {
		int ind_start = s.rfind('(');
		int ind_finish = s.find(')', ind_start);
		string internal_s;
		internal_s.append(s, ind_start + 1, ind_finish - ind_start - 1);
		string value = find_calc(internal_s);
		//s.replace(ind_start, ind_finish - ind_start - 1, value);
		s.replace(ind_start, ind_finish - ind_start + 1, value);
	}
	return find_calc(s);

	/*if (int ind_start = s.find('(') != -1) {
		int ind_finish = s.rfind(')');
		string internal_s;
		internal_s.append(s, ind_start + 1, ind_finish - ind_start - 1);

	}*/
}


int main() {

	// TODO: распределение проекта
	// TODO: создание цикла с условием выхода на определённую клавишу 
	// TODO: защита от дурака 

	string s;
	cout << "Enter :" << endl;
	getline(cin, s);
	cout << "Rez:" << main_calc(s) << endl;

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
