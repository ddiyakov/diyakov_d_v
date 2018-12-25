#include <iostream>
#include <sstream>
#include "rational.h"

using namespace std;

Rational::Rational(const int a)
{
    setChislitel(a);
    setZnamenatel(1);
}

Rational::Rational(const int a, const int b)
{
    setChislitel(a);
    setZnamenatel(b);
    normalize();
}

void Rational::setChislitel(int a)
{
    chis = a;
}

int Rational::getChislitel()
{
    return chis;
}

void Rational::setZnamenatel(int a)
{
    if (a != 0)
        znam = a;
    else
    {
        throw std::exception("Divide by zero exception");
    }
}

int Rational::getZnamenatel() 
{
    return znam;    
}

int nod(int c, int z)
{
    if (z == 0)
        return c;
    else
        return nod(z, c % z);
}

void Rational::normalize()
{
    if (chis != 0 && znam != 0)
    {
        int div = nod(chis, znam);
        chis /= div;
        znam /= div;
    }

    if (znam < 0)
    {
        chis *= -1;
        znam *= -1;
    }
}

bool Rational::operator==(const Rational& rhs) const {
    return (chis == rhs.chis) && (znam == rhs.znam);
}

bool Rational::operator!=(const Rational& rhs) const {
    return !(operator==(rhs));
}

Rational& Rational::operator+=(const Rational& rhs) {
    chis = chis * rhs.znam + rhs.chis * znam;
    znam = znam * rhs.znam;
    normalize();
    return *this;
}

Rational& Rational::operator+=(const int rhs) {
    chis += znam * rhs;
    return *this;
}

Rational& Rational::operator-=(const Rational& rhs) {
    chis = chis * rhs.znam - rhs.chis * znam;
    znam = znam * rhs.znam;
    normalize();
    return *this;
}

Rational& Rational::operator-=(const int rhs) {
    chis -= znam * rhs;
    return *this;
}

Rational& Rational::operator*=(const Rational& rhs) {
    chis = chis * rhs.chis;
    znam = znam * rhs.znam;
    normalize();
    return *this;
}

Rational& Rational::operator*=(const int rhs) {
    chis = chis * rhs;
    normalize();
    return *this;
}

Rational& Rational::operator/=(const Rational& rhs) {
    if (rhs.chis == 0) {
        throw std::exception("Divide by zero exception.");
    }
    chis = chis * rhs.znam;
    znam = znam * rhs.chis;
    normalize();
    return *this;
}

Rational& Rational::operator/=(const int rhs) {
    if (rhs == 0) {
        throw std::exception("Divide by zero exception.");
    }
    znam = znam * rhs;
    normalize();
    return *this;
}

ostream& Rational::writeTo(ostream& ostrm) const
{
    ostrm << leftBrace << chis << separator << znam << rightBrace;
    return ostrm;
}

istream& Rational::readFrom(istream& istrm)
{
    char leftBrace(0);
    int chislitel(0);
    char separator(0);
    int znamenatel(0);
    char rightBrace(0);

    istrm >> leftBrace >> chislitel >> separator >> znamenatel >> rightBrace;

    if (istrm.good())
    {
        if ((Rational::leftBrace == leftBrace) && (Rational::separator == separator)
            && (Rational::rightBrace == rightBrace))
        {
            chis = chislitel;
            znam = znamenatel;
        }
        else
        {
            istrm.setstate(ios_base::failbit);
        }
    }
    return istrm;
}

ostream& operator<<(ostream& ostrm, const Rational& rhs)
{
    return rhs.writeTo(ostrm);
}

istream& operator>>(istream& istrm, Rational& rhs)
{
    return rhs.readFrom(istrm);
}