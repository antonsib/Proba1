#include "number.h"
#include <iostream>
using namespace std;
int Number::counter = 0;
Number::Number()//конструктор
{
	counter++;
	n = 1;
	a = new int[n];
	a[0] = 0;
};
Number::Number(long num) {//коструктор создания из длинного числа
	counter++;
	long buffer = num;
	n = 1;
	while ((buffer /= 10) > 0) n++;
	a = new int[n];
	for (int i = n - 1; i >= 0; i--) {
		a[i] = num % 10;
		num /= 10;
	}
}
Number::Number(const char *str)//конструктор создания из строки
{
	counter++;
	n = 0;
	for (int i = 0; str[i] != '\0'; i++)
		n++;
	a = new int[n];
	for (int i = 0; str[i] != '\0'; i++)
		if (str[i] <= '9' && str[i]>='0') {
			a[i] = str[i] - '0';
		}
		else { 
			cout << "Error!Set the class value again!" << endl; 
			n = 1;
			a[0] = 0;
	    }

}

Number::Number(Number& other)//конструктор копирования
{
	    counter++;
		n = other.n;
		a = new int[n];
		for (int i = 0; i < n; i++)
		{
			a[i] = other.a[i];
		}
}

Number::~Number()//деконструктор
{
	counter--;
	delete[] a;
}
int Number::getnumber(int i) {//возвращает значение определённого элемента массива
	return a[i];
}
int Number::getlength() {//возвращает длину массива
	return n;
}
int Number::getcounter() {//возвращает количество объектов
	return counter;
}
void Number::get() {//вывод массива на экран
	for (int i = 0; i < n; i++)
		cout << a[i];
	cout << endl;
}
void Number::setLength(int currentLength)//изменить длину
{
	n = currentLength;
}

void Number::setLongNumberValue(int i, int value)//изменить значение массива
{
	a[i] = value;
}

void Number::setArray(){//создаёт новый массив
	delete[] a;
	a = NULL;
	a= new int[n];
}

char* Number::toString(){//перевод из int в char
	char *str = new char[n + 1];
	for (int i = 0; i < n; i++){
		str[i] = a[i] + '0';
	}
	str[n] = '\0';
	return str;
}
void addNull(int maxLength, int tempArray[], Number& object) {//Добавление незначащих нулей при сложениии
	for (int i = 0, j = 0; i < maxLength; i++) {
		if (maxLength - i > object.getlength()) {
			tempArray[i] = 0;
			continue;
		}
		tempArray[i] = object.getnumber(j++);
	}
}

void sum(int maxLength, int resultArray[], int tempArray[], int &carry, Number &object) {//Суммирует два массива
	for (int i = maxLength - 1; i >= 0; i--) {
		resultArray[i] = carry + tempArray[i] + object.getnumber(i);
		carry = resultArray[i] / 10;//Записывает остаток в 1 ячейку массива
		resultArray[i] = resultArray[i] % 10;
	}
}
void Number::reverseArrayForDiv(int tempArray[], int len) {//переворачивает массив
	for (int i = 0, j = len - 1; i < j; i++, j--)
	{
		int k = tempArray[i];
		tempArray[i] = tempArray[j];
		tempArray[j] = k;
	}
}
int *addMemory(int &maxLength, int tempArray[], int resultArray[], int &carry) {//довыделяет память 
	for (int i = 0; i < maxLength; i++) {//копируем старый массив
		tempArray[i] = resultArray[i];
	}
	delete[]resultArray;
	maxLength++;//добавляем длину
	//выделение памяти с учётом +1 разряда
	resultArray = new int[maxLength];//создаём удлинённый массив
	resultArray[0] = carry;//в первый элемент массива записываем остаток от суммы
	for (int i = 1; i < maxLength; i++) {
		resultArray[i] = tempArray[i - 1];
	}
	return resultArray;
}
int Number::digitToInt(char num)//переводит символ в int,и возвращает значение 
{
	switch (num)
	{
	case '0': return 0;
	case '1': return 1;
	case '2': return 2;
	case '3': return 3;
	case '4': return 4;
	case '5': return 5;
	case '6': return 6;
	case '7': return 7;
	case '8': return 8;
	case '9': return 9;
	}
}

char Number::digitToChar(int num)//переводит int в char,возвращает char
{
	switch (num)
	{
	case 0: return '0';
	case 1: return '1';
	case 2: return '2';
	case 3: return '3';
	case 4: return '4';
	case 5: return '5';
	case 6: return '6';
	case 7: return '7';
	case 8: return '8';
	case 9: return '9';
	case 10: return 'A';
	case 11: return 'B';
	case 12: return 'C';
	case 13: return 'D';
	case 14: return 'E';
	case 15: return 'F';
	}
}

int Number::helpConvert(char* a, int base, char* c)//для перевода в систему счисления
{
	int rest = 0; // остаток от деления
	char* s; // символьное десятичное представление частного a/p
	int lena = strlen(a);
	s = new char[lena];
	int flag = 0; // проверка на нулевой результат в частном
	for (int i = 0; i < lena; i++)
	{
		int dig = a[i] > 0 ? digitToInt(a[i]) : 0;
		int num = rest * 10 + dig; // делимое на текущем шаге
		s[i] = digitToChar(num / base); // следующий разряд частного
		rest = num % base; // остаток от деления
		if (s[i] != '0') flag = 1; // в случае ненулевого результата установить флаг
	}
	if (flag == 0)  // частное равно 0, базовый случай рекурсии
	{
		c[0] = digitToChar(rest); return 1; // запись старшего разряда результата
	}
	s[lena] = '\0'; // заканчиваем полученную строку результата
	int sub = helpConvert(s, base, c); // рекурсивный вызов для следующего разряда
	c[sub++] = digitToChar(rest); // заполнение текущего разряда результата
	return sub;
}
int Number::compare(Number &numOne, Number &numTwo, int& currentLength)
{   //Функция сравнения
	//Если 1ое > 2ого, то возвращает 1
	//Если 1ое < 2ого, то возвращает -1
	//Если 1ое == 2ое, то возвращает 0
	if (numOne.getlength() > numTwo.getlength())
	{
		currentLength = numOne.getlength();
		return 1;
	}
	else if (numTwo.getlength() > numOne.getlength())
	{
		currentLength = numTwo.getlength();
		return -1;
	}
	else // если числа одинаковой длины, то необходимо сравнить их значения
		for (int i = 0; i < currentLength; i++) // поразрядное сравнение значения чисел
		{
			if (numOne.getnumber(i) > numTwo.getnumber(i))
			{
				return 1;
				break;
			}

			if (numOne.getnumber(i) < numTwo.getnumber(i))
			{
				return -1;
				break;
			}
		}
	return 0;
}
int* Number::reverseArray(Number &object) {//копирует массив объекта в новый массив,переворачивая его при этом
	int tempLength = object.getlength();
	int* tempArray = new int[tempLength];
	for (int i = 0, j = tempLength - 1; i < tempLength; i++) {
		tempArray[i] = object.getnumber(j);
		j--;
	}
	return tempArray;
}
int* Number::makeArrayForSub(Number &object, int currentLength) {//функция создаёт новый массив и копирует в него массив объекта,предварительно его переворачивая
	int* tempArray = new int[currentLength];
	for (int i = 0, j = object.getlength() - 1; i < currentLength; i++) {
		if (j < 0) {//добавление незначащих нулей
			tempArray[i] = 0;
		}
		else {
			tempArray[i] = object.getnumber(j--);
		}
	}
	return tempArray;
}
int* Number::subtraction(Number &obj1, Number &obj2, int currentLength) //Вычитание 
{
	int* tempArrayOne = reverseArray(obj1); //переворачиваем массив первого числа (большего)
	int* tempArrayTwo = makeArrayForSub(obj2, currentLength); //меньшее число также переворачиваем и добавляем значащие нули
	for (int i = 0; i < obj2.getlength(); i++) {
		if (tempArrayOne[i] >= tempArrayTwo[i]) {  //если значение 1ого > 2ого
			tempArrayOne[i] -= tempArrayTwo[i];
		}
		else { //иначе 1ого < 2ого
			if (tempArrayOne[i + 1] != 0) { //если следующее число !=0
				tempArrayOne[i] = tempArrayOne[i] + 10 - tempArrayTwo[i]; //отдаём десяток
				tempArrayOne[i + 1]--; //занимаем у следующего числа
			}
			else { //если следующее число == 0
				tempArrayOne[i] = tempArrayOne[i] + 10 - tempArrayTwo[i]; //отдаём десяток
				i++; //сдвигаемся к следующей цифре
				while (tempArrayOne[i] == 0) { //пока встречаются нули

					tempArrayOne[i] = tempArrayOne[i] + 9 - tempArrayTwo[i];
					i++;
				}
				tempArrayOne[i]--; //занимаем десяток у первого попавшегося !=0
				i--; //на шаг назад
			}
		}
	}
	return tempArrayOne;
}
int* Number::mult(int arrayA[], int arrayB[], int lenA, int lenB, int &maxLength) { //умножение 
	maxLength = lenA + lenB + 1;
	int* resultArray = new int[maxLength];
	int carry = 0;
	for (int i = 0; i < maxLength; i++) {//обнуляем массив
		resultArray[i] = 0;
	}
	for (int i = 0; i < lenA; i++) {
		for (int j = 0; j < lenB; j++) {
			resultArray[i + j] += arrayA[i] * arrayB[j];
		}
	}
	for (int i = 0; i < maxLength; i++) {
		resultArray[i] = carry + resultArray[i];
		carry = resultArray[i] / 10;
		resultArray[i] = resultArray[i] % 10;
	}
	while ((resultArray[maxLength - 1] == 0) && (maxLength != 1)) { //второе условие нужно, чтобы если произ = 0, то 0 не терялся
		maxLength--;
	}
	return resultArray;
}
bool Number::cmp(int arrayOne[], int arrayTwo[], int lengthOne, int lengthTwo) { //на вход перевёрнутые числа.Сравнивает перевёрнутые числа.
	if (lengthOne > lengthTwo)
	{
		return false;
	}
	else if (lengthTwo > lengthOne)
	{
		return true;
	}
	else // если числа одинаковой длины, то необходимо сравнить их значения
		for (int i = lengthOne - 1; i >= 0; i--) // поразрядное сравнение значения чисел
		{
			if (arrayOne[i] > arrayTwo[i])
			{
				return false;//если 1 число больше
				break;
			}

			if (arrayOne[i] < arrayTwo[i])
			{
				return true;//если 2 число больше
				break;
			}
		}
}

void Number::subForDiv(int tempArrayOne[], int tempArrayTwo[], int currentLength) //obj1 > obj2 вычитание для функции деления
{
	for (int i = 0; i < currentLength; i++) {
		if (tempArrayOne[i] >= tempArrayTwo[i]) {  //если значение 1ого > 2ого
			tempArrayOne[i] -= tempArrayTwo[i];
		}
		else { //иначе 1ого < 2ого
			if (tempArrayOne[i + 1] != 0) { //если следующее число !=0
				tempArrayOne[i] = tempArrayOne[i] + 10 - tempArrayTwo[i]; //отдаём десяток
				tempArrayOne[i + 1]--; //занимаем у следующего числа
			}
			else { //если следующее число == 0
				tempArrayOne[i] = tempArrayOne[i] + 10 - tempArrayTwo[i]; //отдаём десяток
				i++; //сдвигаемся к следующей цифре
				while (tempArrayOne[i] == 0) { //пока встречаются нули

					tempArrayOne[i] = tempArrayOne[i] + 9 - tempArrayTwo[i];
					i++;
				}
				tempArrayOne[i]--; //занимаем десяток у первого попавшегося !=0
				i--; //на шаг назад
			}
		}
	}
}

void Number::searchLength(int &lenght, int tempArray[]) {//длина массива без незначащих 0
	for (int i = lenght - 1, key = 1; i >= 0; i--) {
		if (tempArray[i] == 0 && key) {
			lenght--;
			continue;
		}
		else {
			key = 0;
		}
	}
}

void Number::putValue(Number &object, int currentLength, int tempArray[]) {//поиск элемента массива,равного 0
	for (int i = currentLength - 1, key = 1, j = 0; i >= 0; i--) {
		if (tempArray[i] == 0 && key) {
			continue;
		}
		else {
			key = 0;
		}
		object.setLongNumberValue(j++, tempArray[i]);
	}
}
void Number::add(Number &numOne, Number &numTwo) {//сложение
	int maxLength = 0;
	int carry = 0;
	int *tempArray = nullptr;
	int *resultArray = nullptr;
	//Если длина первого числа больше, чем второго числа
	if (numOne.getlength() > numTwo.getlength()) {
		maxLength = numOne.getlength();
		tempArray = new int[maxLength];
		resultArray = new int[maxLength];
		//Добавляем значащие нули для суммирования во 2 число
		addNull(maxLength, tempArray, numTwo);
		//Суммирование
		sum(maxLength,resultArray,tempArray, carry, numOne);
		//Если был сохранен разряд, то очищаем массив и создаем заново
		if (carry) {
			//Добавление памяти под один дополнительный разряд
			resultArray = addMemory(maxLength, tempArray, resultArray, carry);
		}
	}
	//Если длины одинаковы
	else if (numOne.getlength() == numTwo.getlength()) {
		maxLength = numOne.getlength();
		tempArray = new int[maxLength];
		resultArray = new int[maxLength];
		for (int i = maxLength - 1; i >= 0; i--) {
			tempArray[i] = numTwo.getnumber(i);
		}
		sum(maxLength, resultArray, tempArray, carry, numOne);
		if (carry) {
			//Добавление памяти под один дополнительный разряд
			resultArray = addMemory(maxLength, tempArray, resultArray, carry);
		}
	}
	//Если длина второго числа больше, чем первого числа
	else {
		maxLength = numTwo.getlength();
		tempArray = new int[maxLength];
		resultArray = new int[maxLength];
		//Добавляем значащие нули для суммирования
		addNull(maxLength, tempArray, numOne);
		//Суммирование
		sum(maxLength, resultArray, tempArray, carry, numTwo);
		//Если был сохранен разряд, то очищаем массив и создаем заново
		if (carry) {
			//Добавление памяти под один дополнительный разряд
			resultArray = addMemory(maxLength, tempArray, resultArray, carry);
		}
	}
	numOne.setLength(maxLength);
     numOne.setArray();
	for (int i = 0; i < maxLength; i++) {
		numOne.setLongNumberValue(i, resultArray[i]);
	}
	delete[] resultArray;
	delete[] tempArray;
}
void Number::deduct(Number& numOne, Number& numTwo) {//сама функция вычитания

	int currentLength = numOne.getlength(); //текущая длина (максимальная)
	int* resultArray = NULL; //результирующий массив

	int subtract = compare(numOne, numTwo, currentLength); //сравнение

	if (subtract == 1) {
		resultArray = subtraction(numOne, numTwo, currentLength);
	}
	if (subtract == -1) {
		resultArray = subtraction(numTwo, numOne, currentLength);
	}
	if (subtract == 0) {
		currentLength = 1;
		resultArray = new int[1];
		resultArray[0] = 0;
	}
	int  len = currentLength;
	for (int i = currentLength - 1, key = 1; i >= 0; i--) {
		if (resultArray[i] == 0 && key && subtract != 3) {
			len--;
			continue;
		}
		else {
			key = 0;
		}
	}
	numOne.setLength(len);
	numOne.setArray();

	for (int i = currentLength - 1, key = 1, j = 0; i >= 0; i--) {
		if (resultArray[i] == 0 && key && subtract != 3) {
			continue;
		}
		else {
			key = 0;
		}
		setLongNumberValue(j++, resultArray[i]);
	}
	delete[] resultArray;
}
void Number::multiply(Number& numOne, Number& numTwo) {//сама функция умножения
	int* tempArrayOne = reverseArray(numOne);
	int* tempArrayTwo = reverseArray(numTwo);
	int maxLength = 0;

	int* resultArray = mult(tempArrayOne, tempArrayTwo,
		numOne.getlength(), numTwo.getlength(), maxLength);
	numOne.setLength(maxLength);
	numOne.setArray();
	for (int i = 0, j = maxLength - 1; i < maxLength; i++, j--) {
		numOne.setLongNumberValue(i, resultArray[j]);
	}
	delete[] resultArray;
	delete[] tempArrayOne;
	delete[] tempArrayTwo;
}

const char* Number::divide(Number &numOne, Number &numTwo) {
	if (numTwo.getnumber(0) == 0)
		return "Error";

		int divLength = numOne.getlength(); //текущая длина (максимальная)
		int* resultArray = NULL; //результирующий массив
		int *rest; //остаток
		int division = compare(numOne, numTwo, divLength); //сравнение

		if (division == 1) { //получится неполное частное и остаток
			int maxLength = 0;
			bool zero = false;
			int* dividend = reverseArray(numOne); //делимое
			int* divider = reverseArray(numTwo); //делитель
			int* cmpArray = new int[divLength]; //частное
			int* resultArray = new int[divLength]; //для перебора цифр

			//Запоминание предыдущих
			int* resultArrayPrev = new int[divLength];
			int* cmpArrayPrev = new int[divLength];
			int* dividendPrev = new int[divLength];

			for (int i = 0; i < divLength; i++) {
				resultArray[i] = 0;
			}
			int k = 0;
			int carry = 0;
			while (k != -1) { //перебор частного
				k = divLength - 1;
				while (resultArray[k] < 10) {
					reverseArrayForDiv(resultArray, divLength); //переворачиваем для умножения
					cmpArray = mult(divider, resultArray, numTwo.getlength(), divLength, maxLength); //умножаем неполное частное на делитель
					if (cmp(dividend, cmpArray, divLength, maxLength)) { //сравниваем данные числа
						k = -1; //для выхода из вешнего цикла
						subForDiv(dividend, cmpArray, divLength); //в dividend записывается остаток числа
						int count = 0;
						for (int i = 0; i < divLength; i++)
							if (dividend[i] == 0)   //если остаток == 0, то применяем частный случай
								count++;
						if (count == divLength)
							zero = true;

						break;
					}

					//копирование предыдущих показаний
					for (int i = 0; i < divLength; i++)
						resultArrayPrev[i] = resultArray[i];
					for (int i = 0; i < maxLength; i++)
						cmpArrayPrev[i] = cmpArray[i];
					for (int i = 0; i < divLength; i++)
						dividendPrev[i] = dividend[i];

					reverseArrayForDiv(resultArray, divLength); //возвращаем обратно в правильном порядке
					resultArray[k]++;
				}
				while (resultArray[k] == 10) {
					carry = resultArray[k] / 10;
					resultArray[k] %= 10;
					k--;
					if (k == -1) {
						for (int j = 0; j < divLength; j++) {
							resultArray[j] = 9;
						}
						break;
					}
					resultArray[k] += carry;
				}
			}
			if (!zero) {
				subForDiv(dividendPrev, cmpArrayPrev, maxLength);
				maxLength = divLength;
				searchLength(maxLength, resultArrayPrev);
				numOne.setLength(maxLength);
				numOne.setArray();
				putValue(numOne, maxLength, resultArrayPrev);
				maxLength = divLength;
				searchLength(maxLength, dividendPrev);
				char* str = new char[maxLength + 1];
				for (int i = divLength - 1, key = 1, j = 0; i >= 0; i--) {
					if (dividendPrev[i] == 0 && key) {
						continue;
					}
					else {
						key = 0;
					}
					str[j++] = dividendPrev[i] + '0';
				}
				str[maxLength] = '\0';
				return str;
			}
			else {
				maxLength = divLength;
				searchLength(maxLength, resultArray);
				numOne.setLength(maxLength);
				numOne.setArray();
				putValue(numOne, maxLength, resultArray);
				maxLength = divLength;
				char* str = new char[2];
				str[0] = '0';
				str[1] = '\0';
				return str;
			}
		}

		if (division == 2) { //получится 0
			divLength = 1;
			resultArray = new int[1];
			resultArray[0] = 0;
			numOne.setLength(divLength);
			numOne.setArray();
			numOne.setLongNumberValue(0, resultArray[0]);
			return "0";
		}

		if (division == 3) { //получится 1
			divLength = 1;
			resultArray = new int[1];
			resultArray[0] = 1;
			numOne.setLength(divLength);
			numOne.setArray();
			numOne.setLongNumberValue(0, resultArray[0]);
			return "0";
		}
	
}

const char* Number::convertTo(int base)//перевод в другую систему счисления
{
	if (!(2 <= base && base <= 16))
		return "Error";
	char* inStr = this->toString();
	char* outStr = new char[pow(2, this->getlength())];
	int sub = helpConvert(inStr, base, outStr);
	outStr[sub] = '\0';
	delete[] inStr;
	return outStr;
}

Number operator+(Number &numOne,Number &numTwo) {//сумма двух объектов
	Number result = numOne;
	result.add(result, numTwo);
	return result;
}

Number operator-(Number &numOne, Number &numTwo) {//разность двух объектов
	Number result = numOne;
	result.deduct(result, numTwo);
	return result;
}

Number& Number::operator=(const Number& numTwo) {//оператор присваивания
	int flag = 1;
	if (n == numTwo.n) {//проверяем,не копирует ли объект сам себя
		for (int i = 0; i < n; i++)
			if (a[i] != numTwo.a[i])
				flag = 1;
			else flag = 0;
	}
	if (flag == 1) {//если объект не копирует сам себя
		n = numTwo.n;
		delete[] a;
		a = new int[n];
		for (int i = 0; i < n; i++) {
			a[i] = numTwo.a[i];
		}
		return *this;
	}
	else return *this;
}

Number& operator*(Number &numOne, long num) {//умножение на 10 в степени n
	if (numOne.a[0] != 0) {//если само число не 0
		int counter = 0;
		while (num != 1) {//считаем,сколько нулей надо дописать
			num = num / 10;
			counter++;
		}
		int *a1 = new int[numOne.n];
		for (int i = 0; i < numOne.n; i++) {//создаём временную копию начального массива
			a1[i] = numOne.a[i];
		}
		int nlast = numOne.n;//сколько было в старом массиве
		numOne.n = numOne.n + counter;//сколько будет в новом
		numOne.setArray();//создаём новый массив
		for (int i = 0; i < nlast; i++) {
			numOne.a[i] = a1[i];
		}
		for (int i = nlast; i < numOne.n; i++)
			numOne.a[i] = 0;
		return numOne;
	}
	else return numOne;
}

Number& operator*(Number &numOne, int num) {//умножение на 10 в степени n
	if (numOne.a[0] != 0) {//если само число не 0
		int counter = 0;
		while (num != 1) {//считаем,сколько нулей надо дописать
			num = num / 10;
			counter++;
		}
		int *a1 = new int[numOne.n];
		for (int i = 0; i < numOne.n; i++) {//создаём временную копию начального массива
			a1[i] = numOne.a[i];
		}
		int nlast = numOne.n;//сколько было в старом массиве
		numOne.n = numOne.n + counter;//сколько будет в новом
		numOne.setArray();//создаём новый массив
		for (int i = 0; i < nlast; i++) {
			numOne.a[i] = a1[i];
		}
		for (int i = nlast; i < numOne.n; i++)
			numOne.a[i] = 0;
		return numOne;
	}
	else return numOne;
}

Number& operator/(Number &numOne, long num) {//деление на 10 в степени n
	if (num != 0) {//если делитель не 0
		if (numOne.a[0] != 0) {//если само число не 0
			int counter = 0;
			while (num != 1) {//считаем,сколько нулей надо дописать
				num = num / 10;
				counter++;
			}
			int *a1 = new int[numOne.n];
			for (int i = 0; i < numOne.n; i++) {//создаём временную копию начального массива
				a1[i] = numOne.a[i];
			}
			int nlast = numOne.n;//сколько было в старом массиве
			numOne.n = numOne.n - counter;//сколько будет в новом
			if (numOne.n < 1) {
				numOne.n = 1;
				numOne.setArray();//создаём новый массив
				numOne.a[0] = 0;
			}
			else {
				numOne.setArray();//создаём новый массив
				for (int i = 0; i < numOne.n; i++) {
					numOne.a[i] = a1[i];
				}
			}
			return numOne;
		}
		else return numOne;
	}
	else {
		cout << "Error! Division by 0! Returning the original object." << endl;
		return numOne;
	}
}

Number& operator/(Number &numOne, int num) {//деление на 10 в степени n
	if (num != 0) {//если делитель не 0
		if (numOne.a[0] != 0) {//если сам объект не 0
			int counter = 0;
			while (num != 1) {//считаем,сколько нулей надо дописать
				num = num / 10;
				counter++;
			}
			int *a1 = new int[numOne.n];
			for (int i = 0; i < numOne.n; i++) {//создаём временную копию начального массива
				a1[i] = numOne.a[i];
			}
			int nlast = numOne.n;//сколько было в старом массиве
			numOne.n = numOne.n - counter;//сколько будет в новом
			if (numOne.n < 1) {
				numOne.n = 1;
				numOne.setArray();//создаём новый массив
				numOne.a[0] = 0;
			}
			else {
				numOne.setArray();//создаём новый массив
				for (int i = 0; i < numOne.n; i++) {
					numOne.a[i] = a1[i];
				}
				/*for (int i = 0; i < numOne.n; i++)
					cout << numOne.a[i];*/
			}
			return numOne;
		}
		else return numOne;
	}
	else {
		cout << "Error! Division by 0! Returning the original object." << endl;
		return numOne;
	}
}

Number::operator unsigned long() {//преобразование к типу unsigned long
	int currentLength = this->n;
	unsigned long longnumber = 0;
	for (int i = 0; i < currentLength; i++) {
		longnumber = longnumber * 10 + this->a[i];
	}
	return longnumber;
}

