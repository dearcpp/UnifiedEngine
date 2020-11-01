#ifndef UNIFIED_CORE_MATH_MATRIX_HPP
#define UNIFIED_CORE_MATH_MATRIX_HPP

#include <unified/core/math/matrix_fwd.hpp>
#include <unified/core/math/point_fwd.hpp>

#include <initializer_list>
#include <memory>

UNIFIED_BEGIN_NAMESPACE

template <class _type, u32 _rows, u32 _columns>
class Matrix
{
public:

    _OSL_CONSTEXPR Matrix() _OSL_NOEXCEPT {
        std::fill(&_data[0][0], &_data[_rows][0], _type());
    }

    _OSL_CONSTEXPR Matrix(std::initializer_list<std::initializer_list<_type>> matrix) _OSL_NOEXCEPT {
        u32 i = 0;
        for (auto &r : matrix) {
            std::copy(r.begin(), r.end(), _data[i++]);
        }
    }

    _OSL_CONSTEXPR Matrix(_type const &fill) _OSL_NOEXCEPT {
        std::fill(&_data[0][0], &_data[_rows][0], fill);
    }

    _OSL_CONSTEXPR _type operator()(u32 row, u32 column) const _OSL_NOEXCEPT {
        return _data[row][column];
    }

    _OSL_CONSTEXPR _type &operator()(u32 row, u32 column) _OSL_NOEXCEPT {
        return _data[row][column];
    }

    _OSL_CONSTEXPR u32 rows() const _OSL_NOEXCEPT {
        return _rows;
    }

    _OSL_CONSTEXPR u32 columns() const _OSL_NOEXCEPT {
        return _columns;
    }

    _OSL_CONSTEXPR u32 size() const _OSL_NOEXCEPT {
        return _rows * _columns;
    }

    _type *data() {
        return reinterpret_cast<_type*>(_data);
    }

private:

    _type _data[_rows][_columns];

};

typedef Matrix<unsigned, 3, 3> Matrix3x3u;
typedef Matrix<int,      3, 3> Matrix3x3i;
typedef Matrix<float,    3, 3> Matrix3x3f;
typedef Matrix<double,   3, 3> Matrix3x3d;

typedef Matrix<unsigned, 4, 4> Matrix4x4u;
typedef Matrix<int,      4, 4> Matrix4x4i;
typedef Matrix<float,    4, 4> Matrix4x4f;
typedef Matrix<double,   4, 4> Matrix4x4d;

template <class _type, uint32_t _rows, uint32_t _columns>
_OSL_CONSTEXPR Point<_type, _columns> operator*(Matrix<_type, _rows, _columns> const &l, Point<_type, _columns> const &r) _OSL_NOEXCEPT {
    Point<_type, _columns> result;
    for (u32 col = 0; col < l.columns(); col++) {
        for (u32 row = 0; row < l.rows(); row++) {
            result[col] += l(col, row) * r[row];
        }
    }
    return result;
}

template <class _type, uint32_t _rows, uint32_t _columns>
_OSL_CONSTEXPR Matrix<_type, _rows, _columns> operator*(Matrix<_type, _rows, _columns> l, Matrix<_type, _rows, _columns> const &r) _OSL_NOEXCEPT {
    for (u32 col = 0; col < l.columns(); col++) {
        for (u32 row = 0; row < l.rows(); row++) {
            l(col, row) *= r(col, row);
        }
    }
    return l;
}

template <class _type, u32 _dimension>
_OSL_CONSTEXPR Point<_type, _dimension> translate(Matrix<_type, _dimension + 1, _dimension + 1> const &matrix, Point<_type, _dimension> const &move) _OSL_NOEXCEPT {
    Point<_type, _dimension> result;

    for (u32 col = 0; col < matrix.columns(); col++) {
        for (u32 row = 0; row < matrix.rows(); row++) {
            if (col < _dimension && row < _dimension)
                result[col] += matrix(col, row) * move[row];
            else if (col < _dimension)
                result[col] += matrix(col, row) * 1;
        }
    }

    return result;
}

UNIFIED_END_NAMESPACE

#endif