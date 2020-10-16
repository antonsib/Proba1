#pragma once
class Number
{
public:
	Number();
	Number(long num);
	Number(const char *str);
	Number(Number& other);
	void add(Number &numOne, Number &numTwo);
	void deduct(Number& numOne, Number& numTwo);
	void setLength(int currentLength);
	void setLongNumberValue(int i, int value);
	void setArray();
	void get();
	int getnumber(int i);
	int getlength();
	int getcounter();
	void multiply(Number &numOne, Number &numTwo);
    const char* divide(Number &numOne, Number &numTwo);
	char* toString();
    const char* convertTo(int base);
	friend Number operator+(Number &numOne, Number &numTwo);
	friend Number operator-(Number &numOne, Number &numTwo);
	Number& operator=(const Number& numTwo );
	friend Number& operator*(Number &numOne,long num);
	friend Number& operator*(Number &numOne, int num);
	friend Number& operator/(Number &numOne, int num);
	friend Number& operator/(Number &numOne, long num);
	operator unsigned long();
	~Number();
   private:
	int n;
	int *a;
	static int counter;
	int *mult(int arrayA[], int arrayB[], int lenA, int lenB, int &maxLength);
	bool cmp(int arrayOne[], int arrayTwo[], int lengthOne, int lengthTwo);
	void subForDiv(int tempArrayOne[], int tempArrayTwo[], int currentLength);
	void searchLength(int &lenght, int tempArray[]);
	void reverseArrayForDiv(int tempArray[], int len);
	char digitToChar(int num);
	int digitToInt(char num);
	int helpConvert(char* a, int base, char* c);
	void putValue(Number &object, int currentLength, int tempArray[]);
	int compare(Number &numOne, Number &numTwo, int& currentLength);
	int* makeArrayForSub(Number &object, int currentLength);
	int* reverseArray(Number &object);
	int* subtraction(Number &obj1, Number &obj2, int currentLength);
};

