#include <iostream>


class Matrix {
private:
    float **m_data;
public:
    Matrix();

    Matrix(float **matrix);

    Matrix(float v);

    Matrix(std::initializer_list<float> list);

    Matrix(const Matrix &other);

    ~Matrix();


    void transpose();
    float getElementAt(int row, int column);
    void setElementAt(int row, int column, float value);

    Matrix &operator=(const Matrix &other);

    Matrix &operator+(const Matrix &other);

    Matrix &operator+=(const Matrix &other);

    Matrix &operator-(const Matrix &other);

    Matrix &operator-=(const Matrix &other);

    Matrix &operator++(int);

    Matrix &operator++();

    Matrix &operator--(int);

    Matrix &operator--();

    Matrix &operator*(int value);

    Matrix &operator*=(int value);

    Matrix &operator*(const Matrix &other);

    Matrix &operator*=(const Matrix &other);

    friend std::ostream &operator<<(std::ostream &output, const Matrix &matrix);
    friend std::istream &operator>>(std::istream &input, Matrix &matrix);
};

Matrix::Matrix() : m_data{new float *[3]{new float[3]{0, 0, 0}, new float[3]{0, 0, 0}, new float[3]{0, 0, 0}}} {
}

Matrix::Matrix(float **matrix) : m_data{new float *[3]{new float[3], new float[3], new float[3]}} {
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            m_data[i][j] = matrix[i][j];
        }
    }
}

Matrix::Matrix(float v) : m_data{new float *[3]{new float[3]{v, v, v}, new float[3]{v, v, v}, new float[3]{v, v, v}}} {}

Matrix::Matrix(std::initializer_list<float> list) : m_data{
        new float *[3]{new float[3]{0, 0, 0}, new float[3]{0, 0, 0}, new float[3]{0, 0, 0}}} {
    std::initializer_list<float>::iterator it = list.begin();
    for (int i = 0; i < list.size() && i < 9; i++) {
        m_data[i / 3][i % 3] = *it++;
    }
}

Matrix::Matrix(const Matrix &other) : m_data{new float *[3]{new float[3], new float[3], new float[3]}} {
    for (int i = 0; i < 9; ++i) {
        m_data[i / 3][i % 3] = other.m_data[i / 3][i % 3];
    }
}

Matrix::~Matrix() {
    for (int i = 0; i < 3; ++i) {
        delete[] m_data[i];
    }
    delete[] m_data;
}

std::ostream &operator<<(std::ostream &output, const Matrix &matrix) {
    output << "[";
    for (int i = 0; i < 3; ++i) {
        if (i > 0) {
            output << " ";
        }
        output << "[";
        for (int j = 0; j < 3; ++j) {
            output << matrix.m_data[i][j];
            if (j < 2) {
                output << ",\t";
            }
        }
        output << "]" << std::endl;
    }
    output << "]" << std::endl;
    return output;
}

std::istream &operator>>(std::istream &input, Matrix &matrix) {
    for (int i = 0; i < 9; ++i) {
        input >> matrix.m_data[i/3][i%3];
    }
    return input;
}

Matrix &Matrix::operator=(const Matrix &other) {
    for (int i = 0; i < 9; ++i) {
        m_data[i / 3][i % 3] = other.m_data[i / 3][i % 3];
    }
    return *this;
}

Matrix &Matrix::operator+(const Matrix &other) {
    for (int i = 0; i < 9; ++i) {
        m_data[i / 3][i % 3] += other.m_data[i / 3][i % 3];
    }
    return *this;
}

Matrix &Matrix::operator+=(const Matrix &other) {
    for (int i = 0; i < 9; ++i) {
        m_data[i / 3][i % 3] += other.m_data[i / 3][i % 3];
    }
    return *this;
}

Matrix &Matrix::operator-(const Matrix &other) {
    for (int i = 0; i < 9; ++i) {
        m_data[i / 3][i % 3] -= other.m_data[i / 3][i % 3];
    }
    return *this;
}

Matrix &Matrix::operator-=(const Matrix &other) {
    for (int i = 0; i < 9; ++i) {
        m_data[i / 3][i % 3] -= other.m_data[i / 3][i % 3];
    }
    return *this;
}

Matrix &Matrix::operator++(int) {
    Matrix prev = *this;
    for (int i = 0; i < 9; ++i) {
        m_data[i / 3][i % 3] += 1;
    }
    return prev;
}

Matrix &Matrix::operator++() {
    for (int i = 0; i < 9; ++i) {
        m_data[i / 3][i % 3] += 1;
    }
    return *this;
}

Matrix &Matrix::operator--(int) {
    Matrix prev = *this;
    for (int i = 0; i < 9; ++i) {
        m_data[i / 3][i % 3] -= 1;
    }
    return prev;
}

Matrix &Matrix::operator--() {
    for (int i = 0; i < 9; ++i) {
        m_data[i / 3][i % 3] -= 1;
    }
    return *this;
}

Matrix &Matrix::operator*(int value) {
    for (int i = 0; i < 9; ++i) {
        m_data[i / 3][i % 3] *= (float)value;
    }
    return *this;
}

Matrix &Matrix::operator*=(int value) {
    for (int i = 0; i < 9; ++i) {
        m_data[i / 3][i % 3] *= (float)value;
    }
    return *this;
}

Matrix &Matrix::operator*(const Matrix &other) {
    float tmp[3][3];
    for (int i = 0; i < 9; ++i) {
        float result=0;
        for (int j = 0; j < 3; ++j) {
            result += (m_data[i/3][j] * other.m_data[j][i%3]);
        }
        tmp[i / 3][i % 3] = result;
    }
    for (int i = 0; i < 9; ++i) {
        m_data[i / 3][i % 3] = tmp[i / 3][i % 3];
    }
    return *this;
}

Matrix &Matrix::operator*=(const Matrix &other) {
    float tmp[3][3];
    for (int i = 0; i < 9; ++i) {
        float result=0;
        for (int j = 0; j < 3; ++j) {
            result += (m_data[i/3][j] * other.m_data[j][i%3]);
        }
        tmp[i / 3][i % 3] = result;
    }
    for (int i = 0; i < 9; ++i) {
        m_data[i / 3][i % 3] = tmp[i / 3][i % 3];
    }
    return *this;
}

float Matrix::getElementAt(int row, int column) {
    return m_data[row-1][column-1];
}

void Matrix::setElementAt(int row, int column, float value) {
    m_data[row-1][column-1] = value;
}

void Matrix::transpose() {

}


int main() {
    Matrix m = Matrix({1,1,1,1,1,1,1,1,1});
    Matrix w = Matrix({1, 2, 3,4,5,6,7,8,9});
    std::cout << w.getElementAt(3, 2) << std::endl;
}
