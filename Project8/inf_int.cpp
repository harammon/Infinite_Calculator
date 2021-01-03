#define _CRT_SECURE_NO_WARNINGS
#include "inf_int.h"

/*
Originally written by
��ǻ�Ͱ��к�
������
*/

inf_int::inf_int()
{
	this->digits = new char[2];	// �����Ҵ�

	this->digits[0] = '0';		// default �� 0 ����
	this->digits[1] = '\0';
	this->length = 1;
	this->thesign = true;
}

inf_int::inf_int(int n) {
	char buf[100];

	if (n < 0) {		// ���� ó��
		this->thesign = false;
		n = -n;
	}
	else {
		this->thesign = true;
	}

	int i = 0;
	while (n > 0) {			// ���ڸ� ���ڿ��� ��ȯ�ϴ� ����
		buf[i] = n % 10 + '0';

		n /= 10;
		i++;
	}

	if (i == 0) {	// ������ ������ 0�� ���
		new (this) inf_int();	// ������ ��ȣ��...gcc���� �����Ͽ����� �ִٰ� ��. inf_int()�� ��� ������ �ν��Ͻ��� ������. 
	}
	else {
		buf[i] = '\0';

		this->digits = new char[i + 1];
		this->length = i;
		strcpy(this->digits, buf);
	}
}

inf_int::inf_int(const char* str)
{
	int len = strlen(str), i;
	if (str[0] == '-') {
		thesign = false;
		this->length = len - 1;
		this->digits = new char[len];

		this->digits[len - 1] = '\0';
		for (i = 1; i < len; i++) {
			this->digits[len - i - 1] = str[i];
		}
	}
	else {
		thesign = true;
		this->length = len;
		this->digits = new char[len + 1];

		this->digits[len] = '\0';
		for (i = 0; i < len; i++) {
			this->digits[len - i - 1] = str[i];
		}
	}
}

inf_int::inf_int(const inf_int& a) {
	this->digits = new char[a.length + 1];

	strcpy(this->digits, a.digits);
	this->length = a.length;
	this->thesign = a.thesign;
}

inf_int::~inf_int() {
	delete digits;		// �޸� �Ҵ� ����
}

inf_int& inf_int::operator=(const inf_int& a)
{
	if (this->digits) {
		delete this->digits;		// �̹� ���ڿ��� ���� ��� ����.
	}
	this->digits = new char[a.length + 1];

	strcpy(this->digits, a.digits);
	this->length = a.length;
	this->thesign = a.thesign;

	return *this;
}

bool operator==(const inf_int& a, const inf_int& b)
{
	// we assume 0 is always positive.
	if ((strcmp(a.digits, b.digits) == 0) && a.thesign == b.thesign)	// ��ȣ�� ����, ������ ��ġ�ؾ���.
		return true;
	return false;
}

bool operator!=(const inf_int& a, const inf_int& b)
{
	return !operator==(a, b);
}

bool operator>(const inf_int& a, const inf_int& b)
{
	int i;

	if (a.thesign == true && b.thesign == true) {
		if (a.length > b.length) {
			return true;
		}
		else if (a.length < b.length) {
			return false;
		}
		else {
			for (i = a.length - 1; i >= 0; i--) {
				if (a.digits[i] > b.digits[i]) {
					return true;
				}
				else if (a.digits[i] < b.digits[i]) {
					return false;
				}
			}
			return false;
		}
	}
	if (a.thesign == false && b.thesign == false) {
		if (a.length > b.length) {
			return false;
		}
		else if (a.length < b.length) {
			return true;
		}
		else {
			for (i = a.length - 1; i >= 0; i--) {
				if (a.digits[i] > b.digits[i]) {
					return false;
				}
				else if (a.digits[i] < b.digits[i]) {
					return true;
				}
			}
			return false;
		}
	}
	return a.thesign;
}

bool operator<(const inf_int& a, const inf_int& b)
{
	if (operator>(a, b) || operator==(a, b)) {
		return false;
	}
	else {
		return true;
	}
}

inf_int operator+(const inf_int& a, const inf_int& b)
{
	inf_int c;
	unsigned int i;

	if (a.thesign == b.thesign) {	// ������ ��ȣ�� ���� ��� + �����ڷ� ����
		for (i = 0; i < a.length; i++) {
			c.Add(a.digits[i], i + 1);
		}
		for (i = 0; i < b.length; i++) {
			c.Add(b.digits[i], i + 1);
		}

		c.thesign = a.thesign;

		return c;
	}
	else {	// ������ ��ȣ�� �ٸ� ��� - �����ڷ� ����
		c = b;
		c.thesign = a.thesign;

		return a - c;
	}
}

inf_int operator-(const inf_int& a, const inf_int& b)
{
	inf_int c(0);
	unsigned int i;

	if (a.thesign == b.thesign)
	{
		if (a.length > b.length)
		{
			for (i = 0; i < a.length; i++)
			{
				c.Add(a.digits[i], i + 1);
			}
			for (i = 0; i < b.length; i++)
			{
				c.Sub(b.digits[i], i + 1);
			}
			c.thesign = a.thesign;
		}
		else if (a.length == b.length)
		{
			i = a.length - 1;
			while (a.digits[i] == b.digits[i])
			{
				if (0 == i)
					return c;
				i--;
			}
			if (a.thesign && (a.digits[i] > b.digits[i]))
			{
				for (i = 0; i < a.length; i++)
				{
					c.Add(a.digits[i], i + 1);
				}
				for (i = 0; i < b.length; i++)
				{
					c.Sub(b.digits[i], i + 1);
				}
				c.thesign = a.thesign;

			}
			else if (!a.thesign && (a.digits[i] > b.digits[i]))
			{
				for (i = 0; i < a.length; i++)
				{
					c.Add(a.digits[i], i + 1);
				}
				for (i = 0; i < b.length; i++)
				{
					c.Sub(b.digits[i], i + 1);
				}
				c.thesign = a.thesign;
			}
			else if (a.thesign && (a.digits[i] < b.digits[i]))
			{
				for (i = 0; i < a.length; i++)
				{
					c.Add(b.digits[i], i + 1);
				}
				for (i = 0; i < b.length; i++)
				{
					c.Sub(a.digits[i], i + 1);
				}
				c.thesign = !a.thesign;
			}
			else if (!a.thesign && (a.digits[i] < b.digits[i]))
			{
				for (i = 0; i < a.length; i++)
				{
					c.Add(b.digits[i], i + 1);
				}
				for (i = 0; i < b.length; i++)
				{
					c.Sub(a.digits[i], i + 1);
				}
				c.thesign = !a.thesign;
			}
		}
		else if (a.length < b.length)
		{
			for (i = 0; i < b.length; i++)
			{
				c.Add(b.digits[i], i + 1);
			}
			for (i = 0; i < a.length; i++)
			{
				c.Sub(a.digits[i], i + 1);
			}
			c.thesign = !a.thesign;
		}
	}
	else
	{
		c = b;
		c.thesign = a.thesign;

		return a + c;
	}


	while (c.digits[c.length - 1] == '0')
	{
		c.digits[c.length - 1] = '\0';
		c.length = c.length - 1;

	}

	return c;
}

inf_int operator*(const inf_int& a, const inf_int& b)
{
	inf_int c;
	int z, i;
	c.digits[0] = 0;
	if (a.thesign == b.thesign)
	{
		c.thesign = true;
	}
	else
	{
		c.thesign = false;
	}

	c.digits = (char*)realloc(c.digits, a.length + b.length + 1);

	for (i = 0; i < a.length + b.length + 1; i++) {
		c.digits[i] = 0;
	}

	for (int ap = 0; ap < a.length; ap++) {
		for (int bp = 0; bp < b.length; bp++) {
			c.digits[ap + bp] += (a.digits[ap] - '0') * (b.digits[bp] - '0');
			for (z = 0; c.digits[ap + bp] > 9; z++) c.digits[ap + bp] -= 10;
			if (z != 0) {
				c.length = ap + bp + 2;
				c.digits[ap + bp + 1] += z;
			}
			else {
				c.length = ap + bp + 1;
			}
		}
	}
	for (int i = 0; i < c.length; i++) {
		c.digits[i] += '0';
	}

	return c;
}

void inf_int::Sub(const char num, const unsigned int index)   //  a�� index �ڸ����� n�� ����. 0<=n<=9, ex) a�� 411�϶�, Sub(a, 2, 2)�� ����� 391
{
	if (this->length < index) {
		this->digits = (char*)realloc(this->digits, index + 1);

		if (this->digits == NULL) {      // �Ҵ� ���� ����ó��
			std::cout << "Memory reallocation failed, the program will terminate." << std::endl;

			exit(0);
		}

		this->length = index;               // ���� ����
		this->digits[this->length] = '\0';   // �ι��� ����
	}

	if (this->digits[index - 1] < '0') {   // ���� ���� '0'���� ���� �ƽ�Ű���� ��� 0���� ä��. �������� �ʾҴ� ���ο� �ڸ����� ��� �߻�
		this->digits[index - 1] = '0';
	}

	this->digits[index - 1] -= num - '0';   // �� ����


	if (this->digits[index - 1] < '0') {   // ���� ���� �߻��� ���
		this->digits[index - 1] += 10;   // ���� �ڸ������� (�ƽ�Ű��) 10�� ���ϰ�
		Sub('1', index + 1);         // ���ڸ��� 1�� ����
	}
}

inf_int inf_int::Abs() const {
	inf_int temp(*this);
	if (temp.thesign == false)
		temp.thesign = true;
	return temp;
}

std::ostream& operator<<(std::ostream& out, const inf_int& a)
{
	int i;

	if (a.thesign == false) {
		out << '-';
	}
	for (i = a.length - 1; i >= 0; i--) {
		out << a.digits[i];
	}
	return out;
}

void inf_int::Add(const char num, const unsigned int index)	// a�� index �ڸ����� n�� ���Ѵ�. 0<=n<=9, ex) a�� 391�϶�, Add(a, 2, 2)�� ����� 411
{
	if (this->length < index) {
		this->digits = (char*)realloc(this->digits, index + 1);

		if (this->digits == NULL) {		// �Ҵ� ���� ����ó��
			std::cout << "Memory reallocation failed, the program will terminate." << std::endl;

			exit(0);
		}

		this->length = index;					// ���� ����
		this->digits[this->length] = '\0';	// �ι��� ����
	}

	if (this->digits[index - 1] < '0') {	// ���� ���� '0'���� ���� �ƽ�Ű���� ��� 0���� ä��. �������� �ʾҴ� ���ο� �ڸ����� ��� �߻�
		this->digits[index - 1] = '0';
	}

	this->digits[index - 1] += num - '0';	// �� ����


	if (this->digits[index - 1] > '9') {	// �ڸ��ø��� �߻��� ���
		this->digits[index - 1] -= 10;	// ���� �ڸ������� (�ƽ�Ű��) 10�� ����
		Add('1', index + 1);			// ���ڸ��� 1�� ���Ѵ�
	}
}
