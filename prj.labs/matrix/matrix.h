  #pragma once
#ifndef MATRIX_H
#define MATRIX_H

#include <iostream>
#include <sstream>

class Matrix {
 public:
    Matrix() = default;

    Matrix(const int size_x, const int size_y);

    Matrix(const Matrix &rhs);

	Matrix& operator=(const Matrix &rhs);

    int getSizeX();

    int getSizeY();

    int &at(const int i, const int j);

    ~Matrix();

    std::ostream &writeTo(std::ostream &ostrm) const;

    std::istream &readFrom(std::istream &istrim);

 private:
    int **data_{nullptr};
    int size_x{0};
    int size_y{0};
};

std::ostream &operator<<(std::ostream &ostrm, const Matrix &rhs);

std::istream &operator>>(std::istream &istrm, Matrix &rhs);

#endif 