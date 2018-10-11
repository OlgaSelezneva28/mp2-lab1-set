// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// tset.cpp - Copyright (c) Гергель В.П. 04.10.2001
//   Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (19.04.2015)
//
// Множество - реализация через битовые поля

#include "tset.h"

TSet::TSet(int mp) : BitField(mp)
{
	if ((mp < 0) && (mp > MaxPower)) throw 2;
	MaxPower=mp;
}

// конструктор копирования
TSet::TSet(const TSet &s) : BitField(s.BitField)
{
	MaxPower=s.MaxPower;
}

// конструктор преобразования типа
TSet::TSet(const TBitField &bf) : BitField(bf)
{
	MaxPower = bf.GetLength();
}

TSet::operator TBitField() 
{
	return BitField;
}

int TSet::GetMaxPower(void) const // получить макс. к-во эл-тов
{
	return MaxPower;
}

int TSet::IsMember(const int Elem) const // элемент множества?
{
	if((Elem < 0) || (Elem > MaxPower)) throw 8;
	return BitField.GetBit(Elem);
}

void TSet::InsElem(const int Elem) // включение элемента множества
{
	if((Elem < 0) || (Elem > MaxPower)) throw 8;
	BitField.SetBit(Elem);
}

void TSet::DelElem(const int Elem) // исключение элемента множества
{
	if((Elem < 0) || (Elem > MaxPower)) throw 8;
	BitField.ClrBit(Elem);
}

// теоретико-множественные операции

TSet& TSet::operator=(const TSet &s) // присваивание
{
	MaxPower = s.MaxPower;
	BitField = s.BitField;
	return *this;
}


int TSet::operator==(const TSet &s) const // сравнение
{
  if (MaxPower != s.MaxPower) return 0;
	if (BitField==s.BitField) return 1;
	else return 0;
}

int TSet::operator!=(const TSet &s) const // сравнение
{
	if (*this == s) return 0;
	return 1;
}

TSet TSet::operator+(const TSet &s) // объединение
{
	TSet res (BitField | s.BitField);
	return res;
}

TSet TSet::operator+(const int Elem) // объединение с элементом
{
	if((Elem < 0) || (Elem > MaxPower)) throw 8;
	TSet res(BitField);
	res.BitField.SetBit(Elem);
	return res;
}

TSet TSet::operator-(const int Elem) // разность с элементом
{
	if((Elem < 0) || (Elem > MaxPower)) throw 8;
	TSet res(BitField);
	res.BitField.ClrBit(Elem);
	return res;
}

TSet TSet::operator*(const TSet &s) // пересечение
{
	TSet res(BitField & s.BitField);
	return res;
}

TSet TSet::operator~(void) // дополнение
{
	TSet res(BitField);
	res.BitField=~(BitField);
	return res;
}

// перегрузка ввода/вывода

istream &operator>>(istream &istr, TSet &s) // ввод
{
	int num;
	while (istr >> num)
	{
		istr >> num;
		if ((num <0) || (num>s.MaxPower)) throw 2;
		s.BitField.SetBit(num);
	}
	return istr;
}

ostream& operator<<(ostream &ostr, const TSet &s) // вывод
{
	for (int i = 0;i < s.MaxPower; i++)
	{
		if (s.IsMember(i)) ostr << i;
		else throw -5;
	}
	return ostr;
}
