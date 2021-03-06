#include <iostream>
#include <sstream>
#include "complex.h"

Complex::Complex(const double real,
                 const double imaginary) : re(real), im(imaginary) {
    re = real;
    im = imaginary;
}

Complex::Complex(const double real) : Complex(real, 0.0) {}

Complex::Complex(const Complex& obj) {
	re = obj.re;
	im = obj.im;
}

Complex& Complex::operator=(const Complex& obj) {
	re = obj.re;
	im = obj.im;
}

bool Complex::operator==(const Complex &rhs) const {
    if (this != &rhs) {
        return ((re * rhs.re >= 0) && (im * rhs.im >= 0) && (std::abs(std::abs(re) - std::abs(rhs.re)) < 0.000001)) &&
               (std::abs((std::abs(im) - std::abs(rhs.im)) < 0.000001));
    }
    return true;
}

bool Complex::operator!=(const Complex &rhs) const {
    return !operator==(rhs);
}

Complex operator+(const Complex &lhs, const Complex &rhs) {
    Complex result(lhs.re + rhs.re, lhs.im + rhs.im);
    return result;
}

Complex operator-(const Complex &lhs, const Complex &rhs) {
    Complex result(lhs.re - rhs.re, lhs.im - rhs.im);
    return result;
}

Complex operator*(const Complex &lhs, const Complex &rhs) {
    Complex result(lhs.re * rhs.re - lhs.im * rhs.im,
                   lhs.re * rhs.im + lhs.im * rhs.re);
    return result;
}

Complex operator/(const Complex &lhs, const Complex &rhs) {
    if (rhs.re == 0 && rhs.im == 0) {
        throw std::exception("Divide by zero exception.");
    } else {
        Complex result((lhs.re * rhs.re + lhs.im * rhs.im) / (rhs.re * rhs.re + rhs.im * rhs.im),
                       (lhs.im * rhs.re - lhs.re * rhs.im) / (rhs.re * rhs.re + rhs.im * rhs.im));
        return result;
    }
}

Complex &Complex::operator+=(const Complex &rhs) {
    re += rhs.re;
    im += rhs.im;
    return *this;
}

Complex &Complex::operator-=(const Complex &rhs) {
    re -= rhs.re;
    im -= rhs.im;
    return *this;
}

Complex &Complex::operator*=(const Complex &rhs) {
    double tempRe = re;
    re = re * rhs.re - im * rhs.im;
    im = tempRe * rhs.im + im * rhs.re;
    return *this;
}

Complex &Complex::operator/=(const Complex &rhs) {
    if (rhs.re == 0 && rhs.im == 0) {
        throw std::exception("Divide by zero exception.");
    } else {
        double tempRe = re;
        re = (re * rhs.re + im * rhs.im) / (rhs.re * rhs.re + rhs.im * rhs.im);
        im = (im * rhs.re - tempRe * rhs.im) / (rhs.re * rhs.re + rhs.im * rhs.im);
        return *this;
    }
}

Complex &Complex::operator+=(const double rhs) {
    return operator+=(Complex(rhs));
}

Complex &Complex::operator-=(const double rhs) {
    return operator-=(Complex(rhs));
}

Complex &Complex::operator*=(const double rhs) {
    return operator*=(Complex(rhs));
}

Complex &Complex::operator/=(const double rhs) {
    return operator/=(Complex(rhs));
}

std::ostream &Complex::writeTo(std::ostream &ostrm) const {
    ostrm << leftBrace << re << separator << im << rightBrace;
    return ostrm;
}

std::istream &Complex::readFrom(std::istream &istrm) {
    char leftBrace(0);
    double real(0.0);
    char comma(0);
    double imaganary(0.0);
    char rightBrace(0);
    istrm >> leftBrace >> real >> comma >> imaganary >> rightBrace;
    if (istrm.good()) {
        istrm.setstate(std::ios_base::failbit);
    }
    return istrm;
}

std::ostream &operator<<(std::ostream &ostrm, const Complex &rhs) {
    return rhs.writeTo(ostrm);
}

std::istream &operator>>(std::istream &istrm, Complex &rhs) {
    return rhs.readFrom(istrm);
}