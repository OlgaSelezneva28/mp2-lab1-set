// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// tbitfield.cpp - Copyright (c) Гергель В.П. 07.05.2001
//   Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (19.04.2015)
//
// Битовое поле

#include "tbitfield.h"

TBitField::TBitField(int len)
{
	BitLen = len;
	if (len<0) throw 1;
	MemLen=(BitLen + sizeof(TELEM)*8 - 1)/(sizeof(TELEM)*8);
	pMem=new TELEM[MemLen];
		for (int i = 0; i < MemLen; ++i)
			pMem[i] = 0;
}

TBitField::TBitField(const TBitField &bf) // конструктор копирования
{
	BitLen=bf.BitLen;
	MemLen=bf.MemLen;
	pMem= new TELEM[bf.MemLen];
		for (int i = 0; i < MemLen; ++i)
			pMem[i] = bf.pMem[i];
}

TBitField::~TBitField()
{
	delete []pMem;
}

int TBitField::GetMemIndex(const int n) const // индекс Мем для бита n
{
	if ((n<0) || (n>BitLen)) throw -1;
	return (n/(sizeof(TELEM)*8));
}

TELEM TBitField::GetMemMask(const int n) const // битовая маска для бита n
{
	if ((n<0) || (n>BitLen)) throw -1;
	return (1 << ((n) % (sizeof(TELEM)*8)));
}

// доступ к битам битового поля

int TBitField::GetLength(void) const // получить длину (к-во битов)
{
	return BitLen;
}

void TBitField::SetBit(const int n) // установить бит
{
	if ((n<0) || (n>BitLen)) throw -2;
	pMem[GetMemIndex(n)]=(pMem[GetMemIndex(n)])|(GetMemMask(n));
}

void TBitField::ClrBit(const int n) // очистить бит
{
	if ((n<0) || (n>BitLen)) throw -3; 
	pMem[GetMemIndex(n)]=(pMem[GetMemIndex(n)])&(~GetMemMask(n));
}

int TBitField::GetBit(const int n) const // получить значение бита
{
	  if ((n<0) || (n>BitLen)) throw -4;
	  return ((pMem[GetMemIndex(n)])&(GetMemMask(n)));
}

// битовые операции

TBitField& TBitField::operator=(const TBitField &bf) // присваивание
{
	if (this == &bf)
		return *this;
	delete []pMem;
	BitLen=bf.BitLen;
	MemLen=bf.MemLen;
	pMem= new TELEM[bf.MemLen];
	if (pMem != NULL)
		for (int i = 0; i < MemLen; ++i)
			pMem[i] = bf.pMem[i];
	return *this;
}

int TBitField::operator==(const TBitField &bf) const // сравнение
{
	if (BitLen!=bf.BitLen) 
		return 0;
	for(int i=0;i<MemLen; ++i)
	{
		if(pMem[i]!=bf.pMem[i]) 
			return 0;
	}
	return 1;
}

int TBitField::operator!=(const TBitField &bf) const // сравнение
{
	if (*this == bf) return 0;
	return 1;
}

TBitField TBitField::operator|(const TBitField &bf) // операция "или"
{

	if (bf.BitLen > BitLen)
	{
		TBitField temp(bf);
		for(int i = 0; i < MemLen; i++) 
			temp.pMem[i] = pMem[i] | bf.pMem[i];
		return temp;
	}
	else
	{
		TBitField temp(*this);
		for(int i = 0; i < bf.MemLen;i++) 
			temp.pMem[i] = pMem[i] | bf.pMem[i];
		return temp;
	}
}

TBitField TBitField::operator&(const TBitField &bf) // операция "и"
{
	if (bf.BitLen > BitLen)
	{
		TBitField temp(bf.BitLen);
		for(int i = 0; i < bf.MemLen; i++) 
			temp.pMem[i] = pMem[i] & bf.pMem[i];
		return temp;
	}
	else
	{
		TBitField temp(BitLen);
		for(int i = 0; i < MemLen;i++) 
			temp.pMem[i] = pMem[i] & bf.pMem[i];
		return temp;
	}
}

TBitField TBitField::operator~(void) // отрицание
{
	TBitField res(BitLen); 
	for (int i=0; i<BitLen;++i) 
	{ 
		if (GetBit(i)) res.ClrBit(i); 
		else res.SetBit(i); 
	}
	return res;
}

// ввод/вывод

istream &operator>>(istream &istr, TBitField &bf) // ввод
{
	char num;
	istr>>num;
	int i=0;
	int n=bf.GetLength();
	while (i<n)
	{
		if (num==1) bf.SetBit(i);
		else bf.ClrBit(i);
		i++;
	}

  return istr;
}

ostream &operator<<(ostream &ostr, const TBitField &bf) // вывод
{
	int n=bf.GetLength();
	for (int i = 0; i <n; i++)
  {
    if (bf.GetBit(i)) ostr << "1";
    else ostr << "0";
  }
  ostr << endl;

  return ostr;
}
