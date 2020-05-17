/* Ежемесячная стипендия студента составляет А рублей, а расходы на проживание превышают её и составляют B рублей/месяц.
Рост цен ежемесячно увеличивает расходы на 3%. 
Определить, какую нужно иметь сумму денег, чтобы прожить учебный год (10 месяцев), 
используя только эти деньги и стипендию. Значения А и B вводит пользователь. */

#include <iostream>
#include <string>

using std::cout; using std::cin; using std::endl; using std::string;

// получаем от пользователя сумму
double get_summ(const string& text_to_user)
{
	cout << text_to_user;
	double answer;
	cin >> answer;
	while (cin.fail() || (answer < 0))
	{
		cin.clear();
		cin.ignore(1000, '\n');
		cout << "Ошибка! Повторите ввод: ";
		cin >> answer;
	}
	return answer;
}

// возвращает значение потребности в деньгах на заданное количество месяцев
double demand_calculation(const double stipend, const double expenses, const unsigned short months)
{
	double demand_summ(expenses - stipend);  // суммарную потребность инициализируем значением на 1 месяц
	double changing_expenses = expenses;     // переменные расходы будут каждый месяц возрастать на инфляцию в %
	const double month_inflation = 1.03;     // коэффициент инфляции = 1 + 3%
	for (unsigned short m = 1; m < months; m++)
	{
		changing_expenses *= month_inflation;  // каждый месяц расходы увеличиваются по сравнению с предыдущим месяцем
		demand_summ += (changing_expenses - stipend);
	}
	return demand_summ;
}

int main()
{
	setlocale(LC_CTYPE, "rus"); // для вывода сообщений на кириллице

	double stipend = get_summ("Введите размер стипендии (рублей/месяц): ");
	double living_expenses = get_summ("Введите текущие расходы на проживание (рублей/месяц): ");
	while (living_expenses <= stipend)
		living_expenses = get_summ("По условию, расходы должны превышать стипендию! Введите расходы ещё раз (рублей/месяц): ");
	
	const unsigned short period_in_months = 10;
	cout << "Чтобы прожить " << period_in_months << " месяцев, студенту необходимо ещё " 
		 << demand_calculation(stipend, living_expenses, period_in_months) << " рублей." << endl;
	
	return 0;
}