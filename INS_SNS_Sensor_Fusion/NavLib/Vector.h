// vector.h:
#pragma once

#include <QVector>

#include <vector>
#include <cassert>

namespace Math
{
    //!
    //! \brief The Vector class Вектор
    //!
    template<typename T>
    class Vector : public std::vector<T>
    {
    public:
        Vector<T>() : std::vector<T>(){}

        Vector<T>(std::initializer_list<T> il) : std::vector<T>(il){}

        Vector<T>(std::initializer_list< Vector<T> > il) : std::vector< std::vector<T> >(il){}

        Vector<T>(size_t size) : std::vector<T>(size){}

        Vector<T>( size_t rowSize,  const T & vector  ) : std::vector<T>( rowSize, vector ){}

        Vector<T>& operator=( const QVector<T> & vector )
        {
            this->clear();
            this->resize( vector.size() );

            for (size_t i = 0; i < this->size(); ++i)
                this->data()[i] = vector[i];

            return *this;
        }

        Vector<T> operator*(const Vector<T> & right) const
        {
            assert(this->size() == right.size());

            Vector<T> result(this->size());

            for (size_t i = 0; i < this->size(); ++i)
                result[i] = this->data()[i] * right[i];

            return result;
        }

        Vector<T> operator+(const Vector<T> & right) const
        {
            assert(this->size() == right.size());

            Vector<T> result(this->size());

            for (size_t i = 0; i < this->size(); ++i)
                result[i] = this->data()[i] + right[i];

            return result;
        }

        Vector<T> operator-(const Vector<T> & right) const
        {
            assert(this->size() == right.size());

            Vector<T> result(this->size());

            for (size_t i = 0; i < this->size(); ++i)
                result[i] = this->data()[i] - right[i];

            return result;
        }

        Vector<T> operator-(double num) const
        {
            Vector<T> result(this->size());

            for (size_t i = 0; i < this->size(); ++i)
                result[i] = this->data()[i] - num;

            return result;
        }

        Vector<T> operator+(double num) const
        {
            Vector<T> result(this->size());

            for (size_t i = 0; i < this->size(); ++i)
                result[i] = this->data()[i] + num;

            return result;
        }

        Vector<T> operator*(double num) const
        {
            Vector<T> result(this->size());

            for (size_t i = 0; i < this->size(); ++i)
                result[i] = this->data()[i] * num;

            return result;
        }

        Vector<T> operator/(double num) const
        {
            Vector<T> result(this->size());

            for (size_t i = 0; i < this->size(); ++i)
                result[i] = this->data()[i] / num;

            return result;
        }

        Vector<T> square()
        {
            return this->operator*( *this );
        }
    };

    template<typename T>
    double sum(const Vector<T> & v)
    {
        double sum = 0;
        for (size_t i = 0; i < v.size(); ++i)
            sum += v[i];

        return sum;
    }

    template<typename T>
    Vector<T> sqrt(const Vector<T> & v)
    {
        Vector<T> result( v.size() );

        for (size_t i = 0; i < v.size(); ++i)
            result[i] = sqrt( v[i] );

        return result;
    }
}
