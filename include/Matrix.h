#ifndef MATRIX_H
#define MATRIX_H

#include <iostream>
#include <tuple>
#include <Utility.h>

template <class T>
class Matrix{
    public:
        Matrix (const Matrix &m                                                );
        Matrix (const int &_rows = 0, const int &_columns = 0, const T &val = 0);

        ~Matrix(                                                               );

        void setElement(const int &i, const int &j, const T &val               );
        void initialize(const int &_rows, const int &_columns, const T &val = 0);

        T                     getElement   (const int &i, const int &j) const;
        bool                  isOutOfBounds(const int &i, const int &j) const;
        void                  read         (                          ) const;
        void                  print        (                          ) const;
        std::tuple <int, int> getSizes     (                          ) const;

        void add      (const T &val);
        void divide   (const T &val);
        void multiply (const T &val);
        void substract(const T &val);
        void getNPower(const int &n);

        void add       (const Matrix &m);
        void divide    (const Matrix &m);
        void multiply  (const Matrix &m);
        void substract (const Matrix &m);
        void dotProduct(const Matrix &m);

        void add      (const int &i, const int &j, const T &val);
        void divide   (const int &i, const int &j, const T &val);
        void multiply (const int &i, const int &j, const T &val);
        void substract(const int &i, const int &j, const T &val);

        void appendRows   (const Matrix &m);
        void appendColumns(const Matrix &m);

        T      getEchelonForm(const int &artificiallyAdded = 0);
        void   getIdentity   (const int &n);

        T          getTrace      (               );
        T          getDeterminant(               );
        int        getRank       (               );
        void       solveSystem   (const Matrix &b);
        void       getInverse    (               );

        template <class T2>
        Matrix <T>& operator=(const Matrix <T2> &m);
        Matrix <T>& operator=(const Matrix <T> &m );

        bool operator==(const Matrix &m);
        bool operator!=(const Matrix &m);
    private:
        T **matrix = nullptr;
        int rows = 0;
        int columns = 0;
        static const int limit = 1e8;
};

template <class T>
Matrix <T>::Matrix(const int &_rows, const int &_columns, const T &val){
    if(_columns > 0 && _rows > 0 && _columns >= limit/_rows){
        std::cout << "Error in constructor! Matrix size is too big!" << '\n';
    }else{
        rows = _rows;
        columns = _columns;
    }
    matrix = new T*[rows];
    for(int i = 0;i < rows;i++){
        matrix[i] = new T[columns];
        for(int j = 0;j < columns;j++){
            matrix[i][j] = val;
        }
    }
}

template <class T>
Matrix <T>::Matrix(const Matrix &m){
    *this = m;
}

template <class T>
Matrix <T>::~Matrix(){
    for(int i = 0;i < rows;i++){
        delete [] matrix[i];
    }
    delete [] matrix;
    rows = 0;
    columns = 0;
}

template <class T>
void Matrix <T>::setElement(const int &i, const int &j, const T &val){
    if(isOutOfBounds(i, j) == true){
        std::cout << "Error in set element! Indexes are out of bounds!" << '\n';
        return;
    }
    matrix[i][j] = val;
}

template <class T>
void Matrix <T>::initialize(const int &_rows, const int &_columns, const T &val){
    this->~Matrix();
    rows = _rows;
    columns = _columns;
    matrix = new T*[rows];
    for(int i = 0;i < rows;i++){
        matrix[i] = new T[columns];
        for(int j = 0;j < columns;j++){
            matrix[i][j] = val;
        }
    }
}

template <class T>
T Matrix <T>::getElement(const int &i, const int &j) const{
    if(isOutOfBounds(i, j) == true){
        std::cout << "Error in get element! Indexes are out of bounds!" << '\n';
        return 0;
    }
    return matrix[i][j];
}

template <class T>
bool Matrix <T>::isOutOfBounds(const int &i, const int &j) const{
    return i < 0 || i >= rows || j < 0 || j >= columns;
}

template <class T>
void Matrix <T>::read() const{
    std::cout << "Please introduce " << rows << "x" << columns << " numbers!" << '\n';
    for(int i = 0;i < rows;i++){
        for(int j = 0;j < columns;j++){
            std::cin >> matrix[i][j];
        }
    }
}

template <class T>
void Matrix <T>::print() const{
    for(int i = 0;i < rows;i++){
        for(int j = 0;j < columns;j++){
            std::cout << matrix[i][j] << ' ';
        }
        std::cout << '\n';
    }
}

template <class T>
std::tuple <int, int> Matrix <T>::getSizes() const{
    return {rows, columns};
}

template <class T>
void Matrix <T>::add(const T &val){
    for(int i = 0;i < rows;i++){
        for(int j = 0;j < columns;j++){
            matrix[i][j] += val;
        }
    }
}

template <class T>
void Matrix <T>::divide(const T &val){
    for(int i = 0;i < rows;i++){
        for(int j = 0;j < columns;j++){
            matrix[i][j] /= val;
        }
    }
}

template <class T>
void Matrix <T>::multiply(const T &val){
    for(int i = 0;i < rows;i++){
        for(int j = 0;j < columns;j++){
            matrix[i][j] *= val;
        }
    }
}

template <class T>
void Matrix <T>::substract(const T &val){
    for(int i = 0;i < rows;i++){
        for(int j = 0;j < columns;j++){
            matrix[i][j] -= val;
        }
    }
}

template <class T>
void Matrix <T>::add(const Matrix &m){
    if(this->rows != m.rows || this->columns != m.columns){
        std::cout << "Error in add! Matrices don't have the same size!" << '\n';
        return;
    }
    for(int i = 0;i < m.rows;i++){
        for(int j = 0;j < m.columns;j++){
            this->matrix[i][j] += m.matrix[i][j];
        }
    }
}

template <class T>
void Matrix <T>::divide(const Matrix &m){
    if(this->rows != m.rows || this->columns != m.columns){
        std::cout << "Error in divide! Matrices don't have the same size!" << '\n';
        return;
    }
    for(int i = 0;i < m.rows;i++){
        for(int j = 0;j < m.columns;j++){
            this->matrix[i][j] /= m.matrix[i][j];
        }
    }
}

template <class T>
void Matrix <T>::multiply(const Matrix &m){
    if(this->rows != m.rows || this->columns != m.columns){
        std::cout << "Error in multiply! Matrices don't have the same size!" << '\n';
        return;
    }
    for(int i = 0;i < m.rows;i++){
        for(int j = 0;j < m.columns;j++){
            this->matrix[i][j] *= m.matrix[i][j];
        }
    }
}

template <class T>
void Matrix <T>::substract(const Matrix &m){
    if(this->rows != m.rows || this->columns != m.columns){
        std::cout << "Error in substract! Matrices don't have the same size!" << '\n';
        return;
    }
    for(int i = 0;i < m.rows;i++){
        for(int j = 0;j < m.columns;j++){
            this->matrix[i][j] -= m.matrix[i][j];
        }
    }
}

template <class T>
void Matrix <T>::dotProduct(const Matrix &m){
    if(this->columns != m.rows){
        std::cout << "Error in dot product! Matrices can't be multiplied!" << '\n';
        return;
    }
    Matrix <T> ret(this->rows, m.columns);
    for(int i = 0;i < ret.rows;i++){
        for(int j = 0;j < ret.columns;j++){
            int sum = 0;
            for(int k = 0;k < this->columns;k++){
                sum += this->matrix[i][k] * m.matrix[k][j];
            }
            ret.matrix[i][j] = sum;
        }
    }
    *this = ret;
}

template <class T>
void Matrix <T>::add(const int &i, const int &j, const T &val){
    if(isOutOfBounds(i, j) == true){
        std::cout << "Error in add function ! Indexes are out of bounds" << '\n';
        return;
    }
    matrix[i][j] += val;
}

template <class T>
void Matrix <T>::divide(const int &i, const int &j, const T &val){
    if(isOutOfBounds(i, j) == true){
        std::cout << "Error in add function ! Indexes are out of bounds" << '\n';
        return;
    }
    matrix[i][j] /= val;
}

template <class T>
void Matrix <T>::multiply(const int &i, const int &j, const T &val){
    if(isOutOfBounds(i, j) == true){
        std::cout << "Error in add function ! Indexes are out of bounds" << '\n';
        return;
    }
    matrix[i][j] *= val;
}

template <class T>
void Matrix <T>::substract(const int &i, const int &j, const T &val){
    if(isOutOfBounds(i, j) == true){
        std::cout << "Error in add function ! Indexes are out of bounds" << '\n';
        return;
    }
    matrix[i][j] -= val;
}

template <class T>
void Matrix <T>::appendRows(const Matrix &m){
    if(this->columns != m.columns){
        std::cout << "Error in append rows ! Number of columns is not equal" << '\n';
        return;
    }
    Matrix <T> ret(this->rows + m.rows, this->columns);
    for(int i = 0;i < this->rows;i++){
        std::copy(this->matrix[i], this->matrix[i] + this->columns, ret.matrix[i]);
    }
    for(int i = this->rows;i < ret.rows;i++){
        std::copy(m.matrix[i - this->rows], m.matrix[i - this->rows] + m.columns, ret.matrix[i]);
    }
    *this = ret;
}

template <class T>
void Matrix <T>::appendColumns(const Matrix &m){
    if(this->rows != m.rows){
        std::cout << "Error in append columns ! Number of rows is not equal" << '\n';
        return;
    }
    Matrix <T> ret(this->rows, this->columns + m.columns);
    for(int i = 0;i < this->rows;i++){
        std::copy(this->matrix[i], this->matrix[i] + this->columns, ret.matrix[i]);
        for(int j = this->columns;j < ret.columns;j++){
            ret.matrix[i][j] = m.matrix[i][j - this->columns];
        }
    }
    this->~Matrix();
    *this = ret;
}

template <class T>
T Matrix <T>::getEchelonForm(const int &artificiallyAdded){
    Matrix <double> ret;
    ret = *this;
    double det = 1;

    int r, c;
    r = c = 0;
    int rows, columns;
    std::tie(rows, columns) = ret.getSizes();
    while(r < rows && c < columns - artificiallyAdded){
        int k;
        for(k = r;k < rows;k++){
            if(Utility::isEqualToZero(ret.getElement(k, c)) == false){
                break;
            }
        }
        if(k == rows){
            c++;
            continue;
        }
        if(r != k){
            det *= -1;
            for(int j = 0;j < columns;j++){
                int ax = ret.getElement(r, j);
                ret.setElement(r, j, ret.getElement(k, j));
                ret.setElement(k, j, ax);
            }
        }
        for(int j = c + 1;j < columns;j++){
            ret.divide(r, j, ret.getElement(r, c));
        }
        det *= ret.getElement(r, c);
        ret.setElement(r, c, 1);
        for(int i = r + 1;i < rows;i++){
            for(int j = c + 1;j < columns;j++){
                ret.substract(i, j, ret.getElement(i, c) * ret.getElement(r, j));
            }
            ret.setElement(i, c, 0);
        }
        r++;
        c++;
    }

    *this = ret;
    for(int i = 0;i < rows;i++){
        if(this->matrix[i][i] == 0){
            return 0;
        }
    }
    return det;
}

template <class T>
void Matrix <T>::getIdentity(const int &n){
    Matrix <T> ret(n, n);
    for(int i = 0;i < n;i++){
        ret.matrix[i][i] = 1;
    }
    *this = ret;
}

template <class T>
T Matrix <T>::getTrace(){
    if(rows != columns){
        std::cout << "Error in get trace ! Can't get the trace of a non-square matrix" << '\n';
        return 0;
    }
    T ret = 0;
    for(int i = 0;i < rows;i++){
        ret += matrix[i][i];
    }
    return ret;
}

template <class T>
T Matrix <T>::getDeterminant(){
    if(this->rows != this->columns){
        std::cout << "Error in get determinant ! Can't get the determinant of a non-square matrix" << '\n';
        return 0;
    }
    return this->getEchelonForm();
}

template <class T>
int Matrix <T>::getRank(){
    getEchelonForm();
    int ret = 0;
    for(int i = 0;i < rows;i++){
        int j;
        for(j = 0;j < columns;j++){
            if(matrix[i][j] != 0){
                break;
            }
        }
        if(j != columns){
            ret++;
        }
    }
    return ret;
}

template <class T>
void Matrix <T>::solveSystem(const Matrix &b){
    if(this->rows != b.rows){
        std::cout << "Error in solve system ! Number of equations is not equal to number of results" << '\n';
        return;
    }
    this->appendColumns(b);
    this->getEchelonForm(1);
    Matrix <T> ret(1, this->columns - 1);
    for(int i = this->rows - 1;i >= 0;i--){
        int j;
        for(j = 0;j < this->columns;j++){
            if(Utility::isEqualToZero(this->matrix[i][j]) == false){
                ret.matrix[0][j] = this->matrix[i][this->columns - 1];
                for(int k = j + 1;k < this->columns - 1;k++){
                    ret.matrix[0][j] -= ret.matrix[0][k] * this->matrix[i][k];
                }
                break;
            }
        }
        if(j == this->columns && Utility::isEqualToZero(this->matrix[i][j]) == false){
            std::cout << "Error in solve system ! It's impossible given the data !" << '\n';
            return;
        }
    }
    *this = ret;
}

template <class T>
void Matrix <T>::getInverse(){
    if(rows != columns){
        std::cout << "Error in get inverse ! Can't get the determinant of a non-square matrix" << '\n';
        return;
    }
    Matrix <T> I;
    I.getIdentity(rows);
    appendColumns(I);
    double det = this->getEchelonForm(columns / 2);
    if(Utility::isEqualToZero(det) == true){
        std::cout << "Error in get inverse ! Determinant is equal to 0" << '\n';
        return;
    }
    this->print();
    for(int i = rows - 1;i > 0;i--){
        for(int j = i + 1;j < columns;j++){
            matrix[i - 1][j] -= matrix[i][j] * matrix[i - 1][i];
        }
        matrix[i - 1][i] = 0;
    }
    Matrix <T> ret(rows, columns / 2);
    for(int i = 0;i < rows;i++){
        for(int j = ret.columns;j < columns;j++){
            ret.matrix[i][j - ret.columns] = matrix[i][j];
        }
    }
    *this = ret;
}

template <class T>
Matrix <T>& Matrix <T>::operator=(const Matrix <T> &m){
    this->initialize(m.rows, m.columns);
    for(int i = 0;i < this->rows;i++){
        for(int j = 0;j < this->columns;j++){
            this->matrix[i][j] = m.matrix[i][j];
        }
    }
    return *this;
};

template <class T> template <class T2>
Matrix <T>& Matrix <T>::operator=(const Matrix <T2> &m){
    int rows, columns;
    std::tie(rows, columns) = m.getSizes();
    this->initialize(rows, columns);
    for(int i = 0;i < this->rows;i++){
        for(int j = 0;j < this->columns;j++){
            this->matrix[i][j] = m.getElement(i, j);
        }
    }
    return *this;
};

template <class T>
bool Matrix <T>::operator==(const Matrix &m){
    if(this->rows != m.rows || this->columns != m.columns){
        return false;
    }
    for(int i = 0;i < m.rows;i++){
        for(int j = 0;j < m.columns;j++){
            if(this->matrix[i][j] != m.matrix[i][j]){
                return false;
            }
        }
    }
    return true;
}
template <class T>
bool Matrix <T>::operator!=(const Matrix &m){
    return !((*this) == m);
}

#endif // MATRIX_H
