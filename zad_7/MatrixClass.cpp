#include <iostream>


class Matrix {
private:
    float** m_data;
public:
    Matrix();
    Matrix(float** matrix);
    float getElementAt(int x, int y);
    friend std::ostream &operator<<(std::ostream &output, const Matrix &matrix);
};

Matrix::Matrix() {
    m_data = new float*[3];
    for(int i =0; i<3; i++) {
        m_data[i] = new float[3];
        for(int j=0; j<3; ++j) {
            m_data[i][j] = 0;
        }
    }
}

Matrix::Matrix(float** matrix) {
    m_data = new float*[3];
    for(int i =0; i<3; ++i) {
        m_data[i] = new float[3];
        for(int j=0; j<3; ++j) {
            m_data[i][j] = matrix[i][j];
        }
    }
}

std::ostream &operator<<(std::ostream &output, const Matrix &matrix) {
    output << "[";
    for(int i=0; i<3; ++i) {
        if(i>0) {
            output << " ";
        }
        output << "[";
        for(int j=0; j<3; ++j) {
            output << matrix.m_data[i][j];
            if(j<2) {
                output << ",\t";
            }
        }
        output << "]" << std::endl;
    }
    output << "]" << std::endl;
    return output;
}

float Matrix::getElementAt(int row, int column) {
    return m_data[row][column];
}

int main() {
    Matrix m = Matrix();
    std::cout << m << std::endl;
}
