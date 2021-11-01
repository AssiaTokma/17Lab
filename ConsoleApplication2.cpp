#include <iostream>
using namespace std;
#include <string>
template <typename T>
class Array { // создаем шаблон массива
private:
	int size; // размер массива
	T a[10];
public:
	Array(int s); // конструктор с размером массива
	~Array(); // деструктор
	int& operator[](int index); // индексация
	void setarray(int size); // метод ввода массива с клавиатуры
	void getarray(int size); // вывод содержимого массива
};
template <typename T>
//конструктор пустого массива
Array<T>::Array(int s) {
	if (s > 0) {
		size = s;
		a[size];
		for (size_t i = 0; i != size; i++) {
			a[i] = 0;
		}
	}
	else cout << "введите положительное число";
}
template <typename T>
//деструктор массива
Array<T>::~Array() {
	delete[]a;
}
template <typename T>
//индексикация
int& Array<T>::operator[](int index) {
	cin >> index;
	if (index <= size) {
		return a[index];
	}
}
template <typename T>
//ввод массива с клавиатуры
void Array<T>::setarray(int size) {
	for (size_t i = 0; i != size; i++) {
		cin >> a[i];
	}
}
template <typename T>
// вывод массива
void Array<T>::getarray(int size) {
	for (size_t i = 0; i != size; i++) {
		cout << a[i] << " ";
	}
}
//перегрузка равенства элементов массива
string comp(int f, int e)
{
	if (f == e)
		return "да, они равны";
	else return "нет, они неравны";
}
string comp(double f, double e)
{
	if (f == e)
		return "да, они равны";
	else return "нет, они неравны";
}
//перегрузка неравенства элементов массива
string comp1(int f, int e)
{
	if (f != e)
		return "да, они неравны";
	else return "нет, они равны";
}
string comp1(double f, double e)
{
	if (f != e)
		return "да, они неравны";
	else return "нет, они равны";
}
int main() {
	int x, y, c;
	setlocale(LC_ALL, "Russian");
	cout << "Введите число элементов массива:" << endl;
	cin >> c;
	Array<int> arr(c);
	cout << "Введите элементы массива" << endl;
	arr.setarray(c);
	cout << endl;
	cout << "массив:" << endl;
	arr.getarray(c);
	cout << endl << endl;
	cout << "введите индексы элементов которые вы хотите проверить на равенство" << endl;
	cout << comp(arr.operator[](1), arr.operator[](1)) << endl << endl;
	cout << "введите индексы элементов которые вы хотите проверить на неравенство" << endl;
	cout << comp1(arr.operator[](1), arr.operator[](1)) << endl << endl;
	arr.~Array();
}