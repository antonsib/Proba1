#include "number.h"
#include <iostream>
using namespace std;
int Number::counter = 0;
Number::Number()//�����������
{
	counter++;
	n = 1;
	a = new int[n];
	a[0] = 0;
};
Number::Number(long num) {//���������� �������� �� �������� �����
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
Number::Number(const char *str)//����������� �������� �� ������
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

Number::Number(Number& other)//����������� �����������
{
	    counter++;
		n = other.n;
		a = new int[n];
		for (int i = 0; i < n; i++)
		{
			a[i] = other.a[i];
		}
}

Number::~Number()//�������������
{
	counter--;
	delete[] a;
}
int Number::getnumber(int i) {//���������� �������� ������������ �������� �������
	return a[i];
}
int Number::getlength() {//���������� ����� �������
	return n;
}
int Number::getcounter() {//���������� ���������� ��������
	return counter;
}
void Number::get() {//����� ������� �� �����
	for (int i = 0; i < n; i++)
		cout << a[i];
	cout << endl;
}
void Number::setLength(int currentLength)//�������� �����
{
	n = currentLength;
}

void Number::setLongNumberValue(int i, int value)//�������� �������� �������
{
	a[i] = value;
}

void Number::setArray(){//������ ����� ������
	delete[] a;
	a = NULL;
	a= new int[n];
}

char* Number::toString(){//������� �� int � char
	char *str = new char[n + 1];
	for (int i = 0; i < n; i++){
		str[i] = a[i] + '0';
	}
	str[n] = '\0';
	return str;
}
void addNull(int maxLength, int tempArray[], Number& object) {//���������� ���������� ����� ��� ���������
	for (int i = 0, j = 0; i < maxLength; i++) {
		if (maxLength - i > object.getlength()) {
			tempArray[i] = 0;
			continue;
		}
		tempArray[i] = object.getnumber(j++);
	}
}

void sum(int maxLength, int resultArray[], int tempArray[], int &carry, Number &object) {//��������� ��� �������
	for (int i = maxLength - 1; i >= 0; i--) {
		resultArray[i] = carry + tempArray[i] + object.getnumber(i);
		carry = resultArray[i] / 10;//���������� ������� � 1 ������ �������
		resultArray[i] = resultArray[i] % 10;
	}
}
void Number::reverseArrayForDiv(int tempArray[], int len) {//�������������� ������
	for (int i = 0, j = len - 1; i < j; i++, j--)
	{
		int k = tempArray[i];
		tempArray[i] = tempArray[j];
		tempArray[j] = k;
	}
}
int *addMemory(int &maxLength, int tempArray[], int resultArray[], int &carry) {//���������� ������ 
	for (int i = 0; i < maxLength; i++) {//�������� ������ ������
		tempArray[i] = resultArray[i];
	}
	delete[]resultArray;
	maxLength++;//��������� �����
	//��������� ������ � ������ +1 �������
	resultArray = new int[maxLength];//������ ��������� ������
	resultArray[0] = carry;//� ������ ������� ������� ���������� ������� �� �����
	for (int i = 1; i < maxLength; i++) {
		resultArray[i] = tempArray[i - 1];
	}
	return resultArray;
}
int Number::digitToInt(char num)//��������� ������ � int,� ���������� �������� 
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

char Number::digitToChar(int num)//��������� int � char,���������� char
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

int Number::helpConvert(char* a, int base, char* c)//��� �������� � ������� ���������
{
	int rest = 0; // ������� �� �������
	char* s; // ���������� ���������� ������������� �������� a/p
	int lena = strlen(a);
	s = new char[lena];
	int flag = 0; // �������� �� ������� ��������� � �������
	for (int i = 0; i < lena; i++)
	{
		int dig = a[i] > 0 ? digitToInt(a[i]) : 0;
		int num = rest * 10 + dig; // ������� �� ������� ����
		s[i] = digitToChar(num / base); // ��������� ������ ��������
		rest = num % base; // ������� �� �������
		if (s[i] != '0') flag = 1; // � ������ ���������� ���������� ���������� ����
	}
	if (flag == 0)  // ������� ����� 0, ������� ������ ��������
	{
		c[0] = digitToChar(rest); return 1; // ������ �������� ������� ����������
	}
	s[lena] = '\0'; // ����������� ���������� ������ ����������
	int sub = helpConvert(s, base, c); // ����������� ����� ��� ���������� �������
	c[sub++] = digitToChar(rest); // ���������� �������� ������� ����������
	return sub;
}
int Number::compare(Number &numOne, Number &numTwo, int& currentLength)
{   //������� ���������
	//���� 1�� > 2���, �� ���������� 1
	//���� 1�� < 2���, �� ���������� -1
	//���� 1�� == 2��, �� ���������� 0
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
	else // ���� ����� ���������� �����, �� ���������� �������� �� ��������
		for (int i = 0; i < currentLength; i++) // ����������� ��������� �������� �����
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
int* Number::reverseArray(Number &object) {//�������� ������ ������� � ����� ������,������������� ��� ��� ����
	int tempLength = object.getlength();
	int* tempArray = new int[tempLength];
	for (int i = 0, j = tempLength - 1; i < tempLength; i++) {
		tempArray[i] = object.getnumber(j);
		j--;
	}
	return tempArray;
}
int* Number::makeArrayForSub(Number &object, int currentLength) {//������� ������ ����� ������ � �������� � ���� ������ �������,�������������� ��� �������������
	int* tempArray = new int[currentLength];
	for (int i = 0, j = object.getlength() - 1; i < currentLength; i++) {
		if (j < 0) {//���������� ���������� �����
			tempArray[i] = 0;
		}
		else {
			tempArray[i] = object.getnumber(j--);
		}
	}
	return tempArray;
}
int* Number::subtraction(Number &obj1, Number &obj2, int currentLength) //��������� 
{
	int* tempArrayOne = reverseArray(obj1); //�������������� ������ ������� ����� (��������)
	int* tempArrayTwo = makeArrayForSub(obj2, currentLength); //������� ����� ����� �������������� � ��������� �������� ����
	for (int i = 0; i < obj2.getlength(); i++) {
		if (tempArrayOne[i] >= tempArrayTwo[i]) {  //���� �������� 1��� > 2���
			tempArrayOne[i] -= tempArrayTwo[i];
		}
		else { //����� 1��� < 2���
			if (tempArrayOne[i + 1] != 0) { //���� ��������� ����� !=0
				tempArrayOne[i] = tempArrayOne[i] + 10 - tempArrayTwo[i]; //����� �������
				tempArrayOne[i + 1]--; //�������� � ���������� �����
			}
			else { //���� ��������� ����� == 0
				tempArrayOne[i] = tempArrayOne[i] + 10 - tempArrayTwo[i]; //����� �������
				i++; //���������� � ��������� �����
				while (tempArrayOne[i] == 0) { //���� ����������� ����

					tempArrayOne[i] = tempArrayOne[i] + 9 - tempArrayTwo[i];
					i++;
				}
				tempArrayOne[i]--; //�������� ������� � ������� ����������� !=0
				i--; //�� ��� �����
			}
		}
	}
	return tempArrayOne;
}
int* Number::mult(int arrayA[], int arrayB[], int lenA, int lenB, int &maxLength) { //��������� 
	maxLength = lenA + lenB + 1;
	int* resultArray = new int[maxLength];
	int carry = 0;
	for (int i = 0; i < maxLength; i++) {//�������� ������
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
	while ((resultArray[maxLength - 1] == 0) && (maxLength != 1)) { //������ ������� �����, ����� ���� ����� = 0, �� 0 �� �������
		maxLength--;
	}
	return resultArray;
}
bool Number::cmp(int arrayOne[], int arrayTwo[], int lengthOne, int lengthTwo) { //�� ���� ����������� �����.���������� ����������� �����.
	if (lengthOne > lengthTwo)
	{
		return false;
	}
	else if (lengthTwo > lengthOne)
	{
		return true;
	}
	else // ���� ����� ���������� �����, �� ���������� �������� �� ��������
		for (int i = lengthOne - 1; i >= 0; i--) // ����������� ��������� �������� �����
		{
			if (arrayOne[i] > arrayTwo[i])
			{
				return false;//���� 1 ����� ������
				break;
			}

			if (arrayOne[i] < arrayTwo[i])
			{
				return true;//���� 2 ����� ������
				break;
			}
		}
}

void Number::subForDiv(int tempArrayOne[], int tempArrayTwo[], int currentLength) //obj1 > obj2 ��������� ��� ������� �������
{
	for (int i = 0; i < currentLength; i++) {
		if (tempArrayOne[i] >= tempArrayTwo[i]) {  //���� �������� 1��� > 2���
			tempArrayOne[i] -= tempArrayTwo[i];
		}
		else { //����� 1��� < 2���
			if (tempArrayOne[i + 1] != 0) { //���� ��������� ����� !=0
				tempArrayOne[i] = tempArrayOne[i] + 10 - tempArrayTwo[i]; //����� �������
				tempArrayOne[i + 1]--; //�������� � ���������� �����
			}
			else { //���� ��������� ����� == 0
				tempArrayOne[i] = tempArrayOne[i] + 10 - tempArrayTwo[i]; //����� �������
				i++; //���������� � ��������� �����
				while (tempArrayOne[i] == 0) { //���� ����������� ����

					tempArrayOne[i] = tempArrayOne[i] + 9 - tempArrayTwo[i];
					i++;
				}
				tempArrayOne[i]--; //�������� ������� � ������� ����������� !=0
				i--; //�� ��� �����
			}
		}
	}
}

void Number::searchLength(int &lenght, int tempArray[]) {//����� ������� ��� ���������� 0
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

void Number::putValue(Number &object, int currentLength, int tempArray[]) {//����� �������� �������,������� 0
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
void Number::add(Number &numOne, Number &numTwo) {//��������
	int maxLength = 0;
	int carry = 0;
	int *tempArray = nullptr;
	int *resultArray = nullptr;
	//���� ����� ������� ����� ������, ��� ������� �����
	if (numOne.getlength() > numTwo.getlength()) {
		maxLength = numOne.getlength();
		tempArray = new int[maxLength];
		resultArray = new int[maxLength];
		//��������� �������� ���� ��� ������������ �� 2 �����
		addNull(maxLength, tempArray, numTwo);
		//������������
		sum(maxLength,resultArray,tempArray, carry, numOne);
		//���� ��� �������� ������, �� ������� ������ � ������� ������
		if (carry) {
			//���������� ������ ��� ���� �������������� ������
			resultArray = addMemory(maxLength, tempArray, resultArray, carry);
		}
	}
	//���� ����� ���������
	else if (numOne.getlength() == numTwo.getlength()) {
		maxLength = numOne.getlength();
		tempArray = new int[maxLength];
		resultArray = new int[maxLength];
		for (int i = maxLength - 1; i >= 0; i--) {
			tempArray[i] = numTwo.getnumber(i);
		}
		sum(maxLength, resultArray, tempArray, carry, numOne);
		if (carry) {
			//���������� ������ ��� ���� �������������� ������
			resultArray = addMemory(maxLength, tempArray, resultArray, carry);
		}
	}
	//���� ����� ������� ����� ������, ��� ������� �����
	else {
		maxLength = numTwo.getlength();
		tempArray = new int[maxLength];
		resultArray = new int[maxLength];
		//��������� �������� ���� ��� ������������
		addNull(maxLength, tempArray, numOne);
		//������������
		sum(maxLength, resultArray, tempArray, carry, numTwo);
		//���� ��� �������� ������, �� ������� ������ � ������� ������
		if (carry) {
			//���������� ������ ��� ���� �������������� ������
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
void Number::deduct(Number& numOne, Number& numTwo) {//���� ������� ���������

	int currentLength = numOne.getlength(); //������� ����� (������������)
	int* resultArray = NULL; //�������������� ������

	int subtract = compare(numOne, numTwo, currentLength); //���������

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
void Number::multiply(Number& numOne, Number& numTwo) {//���� ������� ���������
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

		int divLength = numOne.getlength(); //������� ����� (������������)
		int* resultArray = NULL; //�������������� ������
		int *rest; //�������
		int division = compare(numOne, numTwo, divLength); //���������

		if (division == 1) { //��������� �������� ������� � �������
			int maxLength = 0;
			bool zero = false;
			int* dividend = reverseArray(numOne); //�������
			int* divider = reverseArray(numTwo); //��������
			int* cmpArray = new int[divLength]; //�������
			int* resultArray = new int[divLength]; //��� �������� ����

			//����������� ����������
			int* resultArrayPrev = new int[divLength];
			int* cmpArrayPrev = new int[divLength];
			int* dividendPrev = new int[divLength];

			for (int i = 0; i < divLength; i++) {
				resultArray[i] = 0;
			}
			int k = 0;
			int carry = 0;
			while (k != -1) { //������� ��������
				k = divLength - 1;
				while (resultArray[k] < 10) {
					reverseArrayForDiv(resultArray, divLength); //�������������� ��� ���������
					cmpArray = mult(divider, resultArray, numTwo.getlength(), divLength, maxLength); //�������� �������� ������� �� ��������
					if (cmp(dividend, cmpArray, divLength, maxLength)) { //���������� ������ �����
						k = -1; //��� ������ �� ������� �����
						subForDiv(dividend, cmpArray, divLength); //� dividend ������������ ������� �����
						int count = 0;
						for (int i = 0; i < divLength; i++)
							if (dividend[i] == 0)   //���� ������� == 0, �� ��������� ������� ������
								count++;
						if (count == divLength)
							zero = true;

						break;
					}

					//����������� ���������� ���������
					for (int i = 0; i < divLength; i++)
						resultArrayPrev[i] = resultArray[i];
					for (int i = 0; i < maxLength; i++)
						cmpArrayPrev[i] = cmpArray[i];
					for (int i = 0; i < divLength; i++)
						dividendPrev[i] = dividend[i];

					reverseArrayForDiv(resultArray, divLength); //���������� ������� � ���������� �������
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

		if (division == 2) { //��������� 0
			divLength = 1;
			resultArray = new int[1];
			resultArray[0] = 0;
			numOne.setLength(divLength);
			numOne.setArray();
			numOne.setLongNumberValue(0, resultArray[0]);
			return "0";
		}

		if (division == 3) { //��������� 1
			divLength = 1;
			resultArray = new int[1];
			resultArray[0] = 1;
			numOne.setLength(divLength);
			numOne.setArray();
			numOne.setLongNumberValue(0, resultArray[0]);
			return "0";
		}
	
}

const char* Number::convertTo(int base)//������� � ������ ������� ���������
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

Number operator+(Number &numOne,Number &numTwo) {//����� ���� ��������
	Number result = numOne;
	result.add(result, numTwo);
	return result;
}

Number operator-(Number &numOne, Number &numTwo) {//�������� ���� ��������
	Number result = numOne;
	result.deduct(result, numTwo);
	return result;
}

Number& Number::operator=(const Number& numTwo) {//�������� ������������
	int flag = 1;
	if (n == numTwo.n) {//���������,�� �������� �� ������ ��� ����
		for (int i = 0; i < n; i++)
			if (a[i] != numTwo.a[i])
				flag = 1;
			else flag = 0;
	}
	if (flag == 1) {//���� ������ �� �������� ��� ����
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

Number& operator*(Number &numOne, long num) {//��������� �� 10 � ������� n
	if (numOne.a[0] != 0) {//���� ���� ����� �� 0
		int counter = 0;
		while (num != 1) {//�������,������� ����� ���� ��������
			num = num / 10;
			counter++;
		}
		int *a1 = new int[numOne.n];
		for (int i = 0; i < numOne.n; i++) {//������ ��������� ����� ���������� �������
			a1[i] = numOne.a[i];
		}
		int nlast = numOne.n;//������� ���� � ������ �������
		numOne.n = numOne.n + counter;//������� ����� � �����
		numOne.setArray();//������ ����� ������
		for (int i = 0; i < nlast; i++) {
			numOne.a[i] = a1[i];
		}
		for (int i = nlast; i < numOne.n; i++)
			numOne.a[i] = 0;
		return numOne;
	}
	else return numOne;
}

Number& operator*(Number &numOne, int num) {//��������� �� 10 � ������� n
	if (numOne.a[0] != 0) {//���� ���� ����� �� 0
		int counter = 0;
		while (num != 1) {//�������,������� ����� ���� ��������
			num = num / 10;
			counter++;
		}
		int *a1 = new int[numOne.n];
		for (int i = 0; i < numOne.n; i++) {//������ ��������� ����� ���������� �������
			a1[i] = numOne.a[i];
		}
		int nlast = numOne.n;//������� ���� � ������ �������
		numOne.n = numOne.n + counter;//������� ����� � �����
		numOne.setArray();//������ ����� ������
		for (int i = 0; i < nlast; i++) {
			numOne.a[i] = a1[i];
		}
		for (int i = nlast; i < numOne.n; i++)
			numOne.a[i] = 0;
		return numOne;
	}
	else return numOne;
}

Number& operator/(Number &numOne, long num) {//������� �� 10 � ������� n
	if (num != 0) {//���� �������� �� 0
		if (numOne.a[0] != 0) {//���� ���� ����� �� 0
			int counter = 0;
			while (num != 1) {//�������,������� ����� ���� ��������
				num = num / 10;
				counter++;
			}
			int *a1 = new int[numOne.n];
			for (int i = 0; i < numOne.n; i++) {//������ ��������� ����� ���������� �������
				a1[i] = numOne.a[i];
			}
			int nlast = numOne.n;//������� ���� � ������ �������
			numOne.n = numOne.n - counter;//������� ����� � �����
			if (numOne.n < 1) {
				numOne.n = 1;
				numOne.setArray();//������ ����� ������
				numOne.a[0] = 0;
			}
			else {
				numOne.setArray();//������ ����� ������
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

Number& operator/(Number &numOne, int num) {//������� �� 10 � ������� n
	if (num != 0) {//���� �������� �� 0
		if (numOne.a[0] != 0) {//���� ��� ������ �� 0
			int counter = 0;
			while (num != 1) {//�������,������� ����� ���� ��������
				num = num / 10;
				counter++;
			}
			int *a1 = new int[numOne.n];
			for (int i = 0; i < numOne.n; i++) {//������ ��������� ����� ���������� �������
				a1[i] = numOne.a[i];
			}
			int nlast = numOne.n;//������� ���� � ������ �������
			numOne.n = numOne.n - counter;//������� ����� � �����
			if (numOne.n < 1) {
				numOne.n = 1;
				numOne.setArray();//������ ����� ������
				numOne.a[0] = 0;
			}
			else {
				numOne.setArray();//������ ����� ������
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

Number::operator unsigned long() {//�������������� � ���� unsigned long
	int currentLength = this->n;
	unsigned long longnumber = 0;
	for (int i = 0; i < currentLength; i++) {
		longnumber = longnumber * 10 + this->a[i];
	}
	return longnumber;
}

