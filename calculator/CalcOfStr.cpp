#include <string>
#include <algorithm>
#include <exception>
#include <cmath>

using namespace std;

class CalcOfStr {
public:
	static string calc(string s) {
		if (check_symbols(s) == false)
			throw exception("Invalid character!");

		if (check_parenthesis(s) == false)
			throw exception("Invalid parenthesis!");
		
		s = do_correct_expression(s);

		while (s.rfind('(') != -1) {
			int ind_start = s.rfind('(');
			int ind_finish = s.find(')', ind_start);
			string internal_s;
			internal_s.append(s, ind_start + 1, ind_finish - ind_start - 1);
			string value = find_calc(internal_s);
			s.replace(ind_start, ind_finish - ind_start + 1, value);
		}
		return find_calc(s);
	}

private:
	// Проверить символы в строке
	static bool check_symbols(string s) {
		char allowed_chars[] = { ' ', '1', '2', '3', '4', '5', '6', '7', '8', 
							'9', '0', '.', '(', ')', '/', '*', '^', '+', '-' };

		for (int i = 0; i < s.length(); i++) {
			bool is_invalid_character = true;
			for (int j = 0; j < 19; j++) {
				if (s[i] == allowed_chars[j]) {
					is_invalid_character = false;
					break;
				}
			}
			if (is_invalid_character)
				return false;
			/*if (find(begin(allowed_chars), end(allowed_chars), s[i]) == false)
				return false;*/
		}

		return true;
	}

	static bool check_parenthesis(string s) {
		int count_open = 0;
		for (int i = 0; i < s.length(); i++) {
			if (s[i] == '(')
				count_open++;
			else if (s[i] == ')')
				count_open--;
			if (count_open < 0)
				return false;
		}

		return count_open == 0;
	}


	// Отформатировать выражение
	static string do_correct_expression(string s) {
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

	static string simple_calc(string s, int ind_zn) {
		int ind_start = s.rfind(' ', ind_zn - 2);
		int ind_finish = s.find(' ', ind_zn + 2);
		if (ind_finish == -1)
			ind_finish = s.length();
		string value_1;
		string value_2;
		value_1.append(s, ind_start + 1, ind_zn - ind_start - 2);
		value_2.append(s, ind_zn + 2, ind_finish - ind_zn - 2);

		string value;
		try {
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
		}
		catch (exception) {
			throw exception("Invalid expression!");
		}
		
		
		return s.replace(ind_start + 1, ind_finish - ind_start - 1, value);
	}

	static string find_calc(string s) { // функция расчитывает строки без скобок // распределяет по действиям ( + - / * ^)
	// ^
		while (s.find('^') != -1) {
			int ind_zn = s.find('^');
			s = simple_calc(s, ind_zn);
		}


		// надо переписать код ниже, сократив расчеты и мб в inline if
		// * /
		while (s.find('*') != -1 || s.find('/') != -1) {
			int ind_zn;
			if (s.find('*') < s.find('/') && s.find('*') != -1)
				ind_zn = s.find('*');
			else
				ind_zn = s.find('/');
			s = simple_calc(s, ind_zn);

		}
		// + -
		while (s.find('+') != -1 || s.find("- ") != -1) {
			int ind_zn;
			if (s.find('+') < s.find("- ") && s.find('+') != -1)
				ind_zn = s.find('+');
			else
				ind_zn = s.find("- ");
			s = simple_calc(s, ind_zn);

		}

		if (s[0] == ' ')
			s.erase(0, 1);

		if (s.length() > 0 && s[s.length() - 1] == ' ')
			s.erase(s.length() - 1, 1);

		return s;
	}
};
