// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// tbitfield.cpp - Copyright (c) Гергель В.П. 07.05.2001
//   Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (19.04.2015)
//
// Битовое поле

#include "tbitfield.h"

TBitField::TBitField(int len)
{
		if (len >= 0)
	{
		BitLen = len;
		MemLen = (len - 1) / (sizeof(unsigned int) * 8) + 1;
		pMem = new TELEM[MemLen];
		for (int i = 0; i<MemLen; i++) pMem[i] = 0;
	}
	else
	{
		throw 1;
	}
}

TBitField::TBitField(const TBitField &bf) // конструктор копирования
{
	MemLen = bf.MemLen;
	BitLen = bf.BitLen;
	pMem = new TELEM[MemLen];
	for (int i = 0; i<MemLen; i++)
	{
		pMem[i] = bf.pMem[i];
	}
}

TBitField::~TBitField()
{
	delete[] pMem;
}

int TBitField::GetMemIndex(const int n) const // индекс Мем для бита n
{
	if (n >= 0)
	{
		return n / (sizeof(TELEM) * 8);
	}
	else throw 1;
}

TELEM TBitField::GetMemMask(const int n) const // битовая маска для бита n
{
	return 1 << (n - GetMemIndex(n) * sizeof(TELEM) * 8);
}

// доступ к битам битового поля

int TBitField::GetLength(void) const // получить длину (к-во битов)
{
  return BitLen;
}

void TBitField::SetBit(const int n) // установить бит
{
	if (n<BitLen)
	{
		pMem[(*this).GetMemIndex(n)] = pMem[(*this).GetMemIndex(n)] | (*this).GetMemMask(n);
	}
	else throw 1;
}

void TBitField::ClrBit(const int n) // очистить бит
{
	if (n<BitLen)
	{
		pMem[(*this).GetMemIndex(n)] = pMem[(*this).GetMemIndex(n)] & ~(*this).GetMemMask(n);
	}
	else throw 1;
}

int TBitField::GetBit(const int n) const // получить значение бита
{
  if (n<BitLen)
	{
		if (pMem[(*this).GetMemIndex(n)] & (*this).GetMemMask(n))
		{
			return 1;
		}
		else return 0;
	}
	else throw 1;
}

// битовые операции

TBitField& TBitField::operator=(const TBitField &bf) // присваивание
{

	if (BitLen != bf.BitLen)
	{
		MemLen = bf.MemLen;
		BitLen = bf.BitLen;
		delete[] pMem;
		pMem = new TELEM[MemLen];
	}
	for (int i = 0; i<MemLen; i++)
	{
		pMem[i] = bf.pMem[i];
	}
	return *this;

}

int TBitField::operator==(const TBitField &bf) const // сравнение
{
 if ((*this).BitLen == bf.BitLen)
	{
		int f = 1;
		for (int i = 0; i<MemLen; i++)
		{
			if ((*this).pMem[i] != bf.pMem[i])
			{
				f = 0;
				break;
			}
		}
		return f;
	}
	else
	{
		 return 0;
	}
}

int TBitField::operator!=(const TBitField &bf) const // сравнение
{
  if ((*this).BitLen == bf.BitLen)
	{
		int f = 0;
		for (int i = 0; i<MemLen; i++)
		{
			if ((*this).pMem[i] != bf.pMem[i])
			{
				f = 1;
				break;
			}
		}
		return f;
	}
	else
	{
		 return 1;
	}
}

TBitField TBitField::operator|(const TBitField &bf) // операция "или"
{
	int n;
	TBitField c(0);
	if ((*this).BitLen<bf.BitLen)
	{
		n = MemLen;
		c = bf;
	}
	else
	{
		n = bf.MemLen;
		c = *this;
	}
	for (int i = 0; i<n; i++)
	{
		c.pMem[i] = (*this).pMem[i] | bf.pMem[i];
	}
	return c;
}

TBitField TBitField::operator&(const TBitField &bf) // операция "и"
{
	int n;
	TBitField c(0);
	if ((*this).BitLen<bf.BitLen)
	{
		n = MemLen;
		c = bf;
	}
	else
	{
		n = bf.MemLen;
		c = *this;
	}
	for (int i = 0; i<n; i++)
	{
		c.pMem[i] = (*this).pMem[i] & bf.pMem[i];
	}
	return c;
}

TBitField TBitField::operator~(void) // отрицание
{
	TBitField a = (*this);
	for (int i = 0; i<BitLen; i++)
	{
		if (a.GetBit(i))
			a.ClrBit(i);
		else
			a.SetBit(i);
	}
	return a;

}

// ввод/вывод

istream &operator>>(istream &istr, TBitField &bf) // ввод
{
	return istr;
}

ostream &operator<<(ostream &ostr, const TBitField &bf) // вывод
{
	for (int i = 0; i<bf.GetLength(); i++)
	{
		cout << bf.GetBit(i);
	}
	return ostr;
}
