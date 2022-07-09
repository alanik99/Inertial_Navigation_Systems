// matrix.h:
#pragma once

#include "Vector.h"

#include <QDebug>

#include <iostream>
#include <cassert>

namespace Math
{
    //!
    //! \brief The Matrix class Матрица
    //!
    template <typename T>
    class Matrix
    {
    public:
        Matrix( size_t row, size_t col ) : row( row ), col( col ),
            data( row, Vector<T>(col) ) {}

        Matrix(std::initializer_list< Vector<T> > il)
        : row( il.size() )
        , col( (*il.begin()).size() )
        , data(il)
        {}

        T& operator()(size_t i, size_t j)
        {
            return data[i][j];
        }

        const T& operator()(size_t i, size_t j) const
        {
            return data[i][j];
        }

        Matrix<T> & operator=( const Matrix<T> & right )
        {
            assert( row == right.rows() && col == right.cols() && "dimenstions must agree" );

            for(size_t i = 0; i < row; ++i)
                for(size_t j = 0; j < col; ++j)
                    data[i][j] = right(i, j);

            return *this;
        }

        Matrix<T> operator*( const Matrix<T> & right ) const
        {
            assert( col == right.rows() && "dimenstions must agree" );

            Matrix<T> result( row, right.cols() );

            for(size_t i = 0; i < row; ++i)
                for(size_t j = 0; j < right.cols(); ++j)
                    result(i, j) = 0;

            for(size_t i = 0; i < row; ++i)
                for(size_t j = 0; j < right.cols(); ++j)
                    for(size_t k = 0; k < col; ++k)
                    {
                        result(i, j) += data[i][k] * right(k, j);
                    }

            return result;
        }

        Matrix<T> operator*( const double right ) const
        {
            Matrix<T> result( row, col );

            for(size_t i = 0; i < row; ++i)
                for(size_t j = 0; j < col; ++j)
                    result(i, j) = data[i][j] * right;

            return result;
        }

        Vector<T> operator*( const Vector<T> & right ) const
        {
            assert( col == right.size() && "dimenstions must agree" );

            Vector<T> result( row );

            for(size_t i = 0; i < row; ++i)
                result[i] = 0;

            for(size_t i = 0; i < row; ++i)
                for(size_t k = 0; k < col; ++k)
                {
                    result[i] += data[i][k] * right[k];
                }

            return result;
        }

        Matrix<T> operator+( const Matrix<T> & right )
        {
            assert( row == right.rows() && col == right.cols() && "dimenstions must agree" );

            Matrix<T> result(row, col);

            for(size_t i = 0; i < row; ++i)
                for(size_t j = 0; j < col; ++j)
                {
                    result(i, j) = data[i][j] + right(i, j);
                }

            return result;
        }

        Matrix<T> operator-( const Matrix<T> & right )
        {
            assert( row == right.rows() && col == right.cols() && "dimenstions must agree" );

            Matrix<T> result(row, col);

            for(size_t i = 0; i < row; ++i)
                for(size_t j = 0; j < col; ++j)
                {
                    result(i, j) = data[i][j] - right(i, j);
                }

            return result;
        }

        Vector<T> getCol( size_t colIndex ) const
        {
            Vector<T> result( row );

            for(size_t i = 0; i < row; ++i)
                result[i] = data[i][colIndex];

            return result;
        }

        const Vector<T> & getRow( size_t rowIndex ) const
        {
            return data[rowIndex];
        }

        void setCol( size_t colIndex, const Vector<T> & columnVector )
        {
            assert( row == columnVector.size() && "dimenstions must agree" );

            for(size_t i = 0; i < row; ++i)
                data[i][colIndex] = columnVector[i];
        }

        void setRow( size_t rowIndex, const Vector<T> & rowVector )
        {
            assert( col == rowVector.size() && "dimenstions must agree" );

            data[rowIndex] = rowVector;
        }

        static Matrix<T> eye(size_t n)
        {
            Matrix<T> result(n, n);

            for(size_t i = 0; i < n; ++i)
                for(size_t j = 0; j < n; ++j)
                    if ( i == j )
                        result(i, j) = 1;

            return result;
        }

        Matrix<T> transpose() const
        {
            Matrix<T> result(col, row);

            for(size_t i = 0; i < row; ++i)
                for(size_t j = 0; j < col; ++j)
                {
                    result(j, i) = data[i][j];
                }

            return result;
        }

        Matrix<T> inv()
        {
            assert( row == col && "matrix must be square" );

            Matrix<T> result = *this;


            double temp;

            Matrix<T> E(row, col);

            for(size_t i = 0; i < row; ++i)
                for(size_t j = 0; j < col; ++j)
                {
                    if (i == j)
                        E(i, j) = 1;
                    else
                        E(i, j) = 0;
                }

            for (size_t k = 0; k < row; k++)
            {
                temp = result(k, k);

                for (size_t j = 0; j < col; j++)
                {
                    result(k, j) /= temp;
                         E(k, j) /= temp;
                }

                for (size_t i = k + 1; i < row; i++)
                {
                    temp = result(i, k);

                    for (size_t j = 0; j < col; j++)
                    {
                        result(i, j) -= result(k, j) * temp;
                             E(i, j) -=      E(k, j) * temp;
                    }
                }
            }

            for (size_t k = col - 1; k > 0; k--)
            {
                for (int i = k - 1; i >= 0; i--)
                {
                    temp = result(i, k);

                    for (size_t j = 0; j < col; j++)
                    {
                        result(i, j) -= result(k, j) * temp;
                             E(i, j) -=      E(k, j) * temp;
                    }
                }
            }

            result = E;

            return result;
        }

        void resize( size_t row, size_t col )
        {
            data.resize( row );
            this->row = row;

            for ( size_t i = 0; i < row; ++i )
                data[i].resize( col );

            this->col = col;
        }

        void print() const
        {
            for(size_t i = 0; i < row; ++i)
            {
                for(size_t j = 0; j < col; ++j)
                    std::cout << data[i][j] << " ";
                std::cout << "\n";
            }
        }

        size_t rows() const  { return row; }
        size_t cols() const  { return col; }

    private:
                      size_t row;
                      size_t col;
        Vector< Vector<T> > data;
    };
}
