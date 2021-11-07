#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <windows.h>
#include <conio.h>


using namespace std;

string DOW(int);
void show_menu()   // Функция показа меню
{
	cout << "                  ---------------------------------------------------" << endl;
	cout << "                  --           Работа расписания пациентов.        --" << endl;
	cout << "                  ---------------------------------------------------" << endl;
	cout << "                  ---------------------------------------------------" << endl;
	cout << "                  --          Выберите желаемую операцию:          --" << endl;
	cout << "                  -- --------------------------------------------- --" << endl;
	cout << "                  -- |  1. Формирование расписания с файла.      | --" << endl;
	cout << "                  -- |  2. Показать расписание на неделю.        | --" << endl;
	cout << "                  -- |  3. Показать расписание конкретного дня.  | --" << endl;
	cout << "                  -- |  4. Добавить запись.                      | --" << endl;
	cout << "                  -- |  5. Удалить запись.                       | --" << endl;
	cout << "                  -- |  6. Сохранить расписание в файл.          | --" << endl;
	cout << "                  -- --------------------------------------------- --" << endl;
	cout << "                  ---------------------------------------------------" << endl;
	cout << "                  ---------------------------------------------------" << endl;
}
class Time_Table
{
private:
	struct Pacient   // Структура пациент
	{
		int day;
		string name;
		int time;
		int insurance;
		Pacient* next;
		Pacient* prev;
	};
	Pacient* Head;  //Начало списка
	Pacient* Tail; // Конец списка


public:
	Time_Table() { Head = Tail = NULL; }; // Инициализация списка
	bool Head_chker() { if (Head == NULL) return 1; else return 0; } // Проверка на существование списка
	~Time_Table();  // Деструктор списка
	void show_day();   // Показывает список на определенный день
	void show_week();  // Показывает список на всю неделю
	void push(int, string, int, int);   // Вставка пациента в конкретный день в список
	void pop(int, string, int, int);  // Удаление пациента из конкретного дня в конкретное время
	bool Repeat_Checker(int);  //Функция проверки на одинаковое время в одинаковый день
	void File_Save(ofstream&); // Функция сохранения расписания в файл
	void File_Read(ifstream&, Time_Table&); //Функция чтения расписания с файла

};

bool Time_Table::Repeat_Checker(int i)
{
	Pacient* temp = Head;
	while (temp != NULL)
	{
		if (temp->time == i) return 0;
		temp = temp->next;
	}
	return 1;
}

Time_Table::~Time_Table()
{
	while (Head)
	{
		Tail = Head->next;
		delete Head;
		Head = Tail;
	}
}

void Time_Table::push(int D, string N, int T, int I)
{
	Pacient* person = new Pacient; //Создаем нового пациента
	bool err = ((D > 5 || D < 1) || (T > 17 || T < 8));
	if (err)
		cout << "Мы работаем с понедельника по пятницу. С 8:00 утра до 17:00 вечера." << endl;
	else
	{

		person->day = D;
		person->name = N;   // Инициализируем его данные
		person->time = T;
		person->insurance = I;
		if (Head == NULL)   // Если  списка нет, то наш пациент - начальный и последний
		{
			person->prev = NULL;
			person->next = NULL;
			Head = Tail = person;
			cout << " Запись успешно добавлена!" << endl;
		}
		else
		{
			if (Repeat_Checker(person->time)) // Если в одном списке время совпадает, создать записть невозможно.
			{
				Pacient* temp = Head;
				bool flag = true;
				bool checker = person->time == temp->time;

				if (person->time < temp->time)  //Если пациент должен стать раньше головы
				{
					Head->prev = person;
					person->next = Head;
					person->prev = NULL;
					Head = person;
				}
				else  // Если пациент по времени позже головы
				{
					while (flag)
					{
						if (temp->next == NULL)   // Если добрались до конца списка
						{
							person->prev = temp;
							person->next = NULL;      //Пациент становится хвостом
							temp->next = person;
							Tail = person;
							flag = 0;
						}
						else   // Иначе шагаем пока не будем позже 1 пациента и раньше другого
						{
							temp = temp->next;

							if (person->time < temp->time)   //Если стали раньше другого пациента, меняем все ссылки
							{
								person->next = temp;
								person->prev = temp->prev;
								temp->prev->next = person;
								temp->prev = person;
								flag = 0;
							}

						}
					}
				}
				cout << " Запись успешно добавлена!" << endl;
			}
			else cout << "Запись не может быть осущствлена. Время занято." << endl;
		}
	}
}

void Time_Table::pop(int D, string N, int T, int I)
{
	if (Head == NULL) cout << "Список пуст. Удаление невозможно." << endl; // Если список пустой, выводим сообщение
	else
	{
		if (Head == Tail)  // Если всего 1 элемент в списке - удаляем
		{
			delete Head;
			Head = Tail = NULL;
		}
		else
		{
			bool flag = true;
			Pacient* temp = Head;
			while (flag)
			{
				if (D == temp->day && N == temp->name && temp->time == T && I == temp->insurance)  // Если наши данные и данные из списка совпадают
				{
					if (temp == Head)   // Если это головной элемент
					{
						temp->next->prev = NULL;
						Head = temp->next;
						delete temp;       // Удаляем голову
						flag = false;
					}
					else
					{
						if (temp == Tail)   // Если хвостовой элемент
						{
							temp->prev->next = NULL;
							Tail = temp->prev;
							delete temp;   // Удаляем хвост
							flag = false;
						}
						else
						{
							temp->prev->next = temp->next;
							temp->next->prev = temp->prev;  // Если посередине элемент, выставляемадреса
							delete temp;
							flag = false;
						}
					}
				}
				else temp = temp->next;  // Если данные не совпадают, прыгаем дальше
			}
		}
		cout << "Удаление прошло успешно" << endl;
	}

}

void File_Read(ifstream& f, Time_Table* W)
{
	string name, blank;
	int day, time_pass, insurance;
	if (!f)
	{
		cout << "Ошибка открытия файла. Чтобы загрузить сохраненный файл переименуйте его в input.txt!" << endl;
	}
	else
	{

		while (!f.eof())
		{
			f >> name;
			f >> day;
			f >> time_pass;
			f >> insurance;
			W[day - 1].push(day, name, time_pass, insurance);
		}
		cout << "Файл был успешно считан.";
		cout << blank;
	}
}

void Time_Table::show_day()
{
	Pacient* temp = Head;  // Начиная с головы, показываем нужную информацию и перескакиваем по указателям, пока не дойдем до хвоста
	while (temp != NULL)
	{
		cout << endl << "Назначенный день:" << DOW(temp->day) << endl;
		cout << "Фамилия пациента: " << temp->name << endl;
		cout << "Мед. полис:" << temp->day << endl;
		cout << "Время приема: " << temp->time << ":00" << endl << endl;
		temp = temp->next;
	}
}

void Time_Table::File_Save(ofstream& f)
{
	Pacient* temp = Head;  // Начиная с головы, показываем нужную информацию и перескакиваем по указателям, пока не дойдем до хвоста
	while (temp != NULL)
	{
		f << endl << "Назначенный день:" << DOW(temp->day) << endl;
		f << "Фамилия пациента: " << temp->name << endl;
		f << "Мед. полис:" << temp->day << endl;
		f << "Время приема: " << temp->time << ":00" << endl << endl;
		temp = temp->next;
	}
}
int main()
{
	setlocale(LC_ALL, "Russian");

	Time_Table RJD1, RJD2, RJD3, RJD4, RJD5;  // Массив из 5 расписаний на каждый день недели
	Time_Table week[5] = { RJD1, RJD2, RJD3, RJD4, RJD5 };

	string name;   // Данные для 1-го пациента
	int time_pass, insurance;
	int k, day;

	show_menu();
	cout << endl << "Введите пункт меню. " << endl;
	k = _getch();
	cout << endl;

	while (k != 'Q')
	{

		switch (k)
		{
		case '1':
		{
			ifstream r("input.txt");
			File_Read(r, week);
			r.close();


		}; break;

		case '2':
		{

			for (int i = 0; i < 5; i++)
			{
				cout << "-----------------------" << DOW(i + 1) << "------------------------" << endl;
				if (week[i].Head_chker())
					cout << "Записей на сегодня нет!" << endl;
				else
					week[i].show_day();
				cout << "------------------------------------------------------" << endl;
			}

			cout << endl << "--------------------------ВЫХОДНОЙ---------------------------" << endl;
			cout << "--------------------------ВЫХОДНОЙ---------------------------" << endl;


		}; break;


		case '3':
		{
			cout << endl << "Введите день: ";
			cin >> day;
			cout << "-------------" << DOW(day) << "---------" << endl;

			if (week[day - 1].Head_chker())
				cout << "Записей на сегодня нет" << endl;
			else
				week[day - 1].show_day();

		}; break;


		case '4':
		{
			cout << "Введите фамилию: ";
			cin >> name;
			cout << "Введите номер мед. полиса: ";
			cin >> insurance;
			cout << "Введите день приема: ";
			cin >> day;
			cout << "Введите время приема: ";
			cin >> time_pass;

			week[day - 1].push(day, name, time_pass, insurance);
		}; break;

		case '5':
		{

			cout << "-------Удаление записи-------" << endl;
			cout << "Введите фамилию пациента, удаляемого из списка: ";
			cin >> name;
			cout << "Введите номер мед. полиса: ";
			cin >> insurance;
			cout << "Введите назначенный день приема: ";
			cin >> day;
			cout << "Введите время приема: ";
			cin >> time_pass;
			week[day - 1].pop(day, name, time_pass, insurance);
		}; break;


		case '6':
		{
			ofstream f("output.txt");
			for (int i = 0; i < 5; i++)
			{
				f << "-----------------------" << DOW(i + 1) << "------------------------" << endl;
				if (week[i].Head_chker())
					f << "Записей на сегодня нет!" << endl;
				else
					week[i].File_Save(f);
				f << "------------------------------------------------------" << endl;
			}

			f << endl << "--------------------------ВЫХОДНОЙ---------------------------" << endl;
			f << "--------------------------ВЫХОДНОЙ---------------------------" << endl;
			f.close();
			cout << "Расписание успешно сохранено в файл!\n Чтобы загрузить сохраненный файл переименуйте его в input.txt!" << endl;
		}; break;

		default:
		{
			cout << "Простите, данной цифры в меню нет. Попробуйте ещё раз.";
		}; break;
		};
		cout << "\n\nДля перехода в главное меню нажмите на любую кнопку.";
		_getch();
		system("CLS");
		show_menu();
		cout << endl << "Введите пункт меню." << endl;
		k = _getch();
		cout << endl;

	}

	return 0;
}

string DOW(int D)   // (Day of Week)Функция показа дней недели в зависимости от int
{
	switch (D)
	{
	case 1: return "Понедельник"; break;
	case 2: return "Вторник"; break;
	case 3: return "Среда"; break;
	case 4: return "Четверг"; break;
	case 5: return "Пятница"; break;
	default: return "Не рабочий день.";
	}
}
