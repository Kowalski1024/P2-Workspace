#include <iostream>
#include <algorithm>

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

    void identity();

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

    friend bool operator<(Matrix &one, const Matrix &two);
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
        for (int j = 0; j < 2; ++j) {
            output << matrix.m_data[i][j];
            output << ",\t";
        }
        output << matrix.m_data[i][2];
        output << "]";
        if (i < 2) {
            output << std::endl;
        }
    }
    output << "]" << std::endl;
    return output;
}

std::istream &operator>>(std::istream &input, Matrix &matrix) {
    for (int i = 0; i < 9; ++i) {
        input >> matrix.m_data[i / 3][i % 3];
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
    Matrix result = Matrix(*this);
    for (int i = 0; i < 9; ++i) {
        result.m_data[i / 3][i % 3] += other.m_data[i / 3][i % 3];
    }
    return result;
}

Matrix &Matrix::operator+=(const Matrix &other) {
    return *this = operator+(other);
}

Matrix &Matrix::operator-(const Matrix &other) {
    Matrix result = Matrix(*this);
    for (int i = 0; i < 9; ++i) {
        result.m_data[i / 3][i % 3] -= other.m_data[i / 3][i % 3];
    }
    return result;
}

Matrix &Matrix::operator-=(const Matrix &other) {
    return *this = operator-(other);
}

Matrix &Matrix::operator++(int) {
   Matrix prev = Matrix(*this);
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
   Matrix prev = Matrix(*this);
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
    Matrix result = Matrix(*this);
    for (int i = 0; i < 9; ++i) {
        result.m_data[i / 3][i % 3] *= (float) value;
    }
    return result;
}

Matrix &Matrix::operator*=(int value) {
    return *this = operator*(value);
}

Matrix &Matrix::operator*(const Matrix &other) {
    Matrix res = Matrix(*this);
    float tmp[3][3];
    for (int i = 0; i < 9; ++i) {
        float result = 0;
        for (int j = 0; j < 3; ++j) {
            result += (m_data[i / 3][j] * other.m_data[j][i % 3]);
        }
        tmp[i / 3][i % 3] = result;
    }
    for (int i = 0; i < 9; ++i) {
        res.m_data[i / 3][i % 3] = tmp[i / 3][i % 3];
    }
    return res;
}

Matrix &Matrix::operator*=(const Matrix &other) {
    return *this = operator*(other);
}

float Matrix::getElementAt(int row, int column) {
    return m_data[row - 1][column - 1];
}

void Matrix::setElementAt(int row, int column, float value) {
    m_data[row - 1][column - 1] = value;
}

void Matrix::transpose() {
    for (size_t i = 0; i < 3; i++) {
        for (size_t j = i + 1; j < 3; j++) {
            std::swap(m_data[i][j], m_data[j][i]);
        }
    }
}

// tworzyc nowa czy nadpisywac?
void Matrix::identity() {
    *this = Matrix({1, 0, 0, 0, 1, 0, 0, 0, 1});
}

bool operator<(Matrix &one, const Matrix &two) {
    double sum1 = 0, sum2 = 0;
    for (int i = 0; i < 9; ++i) {
        sum1 += one.m_data[i / 3][i % 3];
        sum2 += two.m_data[i / 3][i % 3];
    }
    if (sum1 < sum2) {
        return true;
    } else {
        return false;
    }
}


int main() {
    {
        Matrix mat[3];
        mat[0] = Matrix(9.1);
        mat[1] = Matrix(5.25);
        mat[2] = Matrix(6.99);
        std::cout << "Before sorting: " << std::endl;
        for (int i = 0; i < 3; ++i) {
            std::cout << mat[i] << std::endl;
        }
        std::sort(mat, mat + 3, operator<);
        std::cout << "After sorting: " << std::endl;
        for (int i = 0; i < 3; ++i) {
            std::cout << mat[i] << std::endl;
        }
    }

    {
        Matrix matOne = Matrix({1.2, 2.2, 3.2, 3.2, 2.2, 1.2, 1.2, 2.2, 3.2});
        Matrix matTwo = Matrix({1, 2, 3, 4, 5, 6, 7, 8, 9});
        std::cout << "Operands for multiplication: " << std::endl;
        std::cout << matOne << std::endl;
        std::cout << matTwo << std::endl;
        std::cout << "Result: " << std::endl;
        matOne *= matTwo;
        std::cout << matOne << std::endl;
    }

}
