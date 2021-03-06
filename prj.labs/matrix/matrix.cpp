#include <iostream>
#include <sstream>
#include "matrix.h"

Matrix::Matrix(const int sizex, const int sizey) {
    if (sizex < 0 || sizey < 0) {
        throw std::exception("Size should not be negative");
    }

    size_x = sizex;
    size_y = sizey;

    data_ = new int *[size_y];

    for (int i(0); i < size_y; i++) {
        data_[i] = new int[size_x];
    }
}

Matrix::Matrix(const Matrix &rhs) {
    size_x = rhs.size_x;
    size_y = rhs.size_y;

    data_ = new int *[size_y];

    for (int i(0); i < size_y; i++) {
        data_[i] = new int[size_x];
    }

    for (int i(0); i < size_y; i++) {
        for (int j(0); j < size_x; j++) {
            data_[i][j] = rhs.data_[i][j];
        }
    }
}

Matrix& Matrix::operator=(const Matrix &rhs) {
	if (this != &rhs) {
		for (int i(0); i < size_y; i++) {
			delete[] data_[i];
		}
		delete[] data_;

		size_x = rhs.size_x;
		size_y = rhs.size_y;
		data_ = new int *[size_y];

		for (int i(0); i < size_y; i++) {
			data_[i] = new int[size_x];
		}

		for (int i(0); i < size_y; i++) {
			for (int j(0); j < size_x; j++) {
				data_[i][j] = rhs.data_[i][j];
			}
		}
	}
	return *this;
}

int &Matrix::at(const int i, const int j) {
	if (i < 0 || j < 0 || i >= size_x || j >= size_y) {
        throw std::exception("Size should not be negative");
    }
    return data_[i][j];
}

int Matrix::getSizeX() {
    return size_x;
}

int Matrix::getSizeY() {
    return size_y;
}

Matrix::~Matrix() {
    for (int i(0); i < size_y; i++) {
        delete[] data_[i];
    }
    delete[] data_;
}

std::ostream &Matrix::writeTo(std::ostream &ostrm) const {
    ostrm << "{ ";
    for (int i(0); i < size_y; i++) {
        for (int j(0); j < size_x; j++) {
            ostrm << data_[i][j] << " ";
        }
        ostrm << "}" << std::endl;
    }
    return ostrm;
}

std::istream &Matrix::readFrom(std::istream &istrim) {
    return istrim;
}

std::ostream &operator<<(std::ostream &ostrm, const Matrix &rhs) {
    return rhs.writeTo(ostrm);
}

std::istream &operator>>(std::istream &istrm, Matrix &rhs) {
    return rhs.readFrom(istrm);
}
