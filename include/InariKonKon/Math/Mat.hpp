#pragma once

#include "InariKonKon/Math/Vec.hpp"

namespace ikk
{
    template<std::size_t Rows, std::size_t Cols, Number T, MatrixOrdering O = MatrixOrdering::RowMajor>
    class [[nodiscard]] Mat final
    {
        static_assert(Rows >= 1 && Cols >= 1);
    public:
        constexpr Mat() noexcept = default;
        constexpr Mat(T value) noexcept;
        constexpr Mat(std::span<T, Rows * Cols> span) noexcept;
        constexpr Mat(std::array<T, Rows * Cols> array) noexcept;
        constexpr Mat(std::initializer_list<T> list) noexcept;

        constexpr Mat(const Mat&) noexcept = default;
        constexpr Mat(Mat&&) noexcept = default;
        constexpr Mat& operator=(const Mat&) noexcept = default;
        constexpr Mat& operator=(Mat&&) noexcept = default;

        constexpr ~Mat() noexcept = default;

        [[nodiscard]] static constexpr Mat Identity() noexcept requires (Rows == Cols);

        [[nodiscard]] constexpr const T& operator()(std::size_t row, std::size_t column) const noexcept;
        [[nodiscard]] constexpr T& operator()(std::size_t row, std::size_t column) noexcept;

        [[nodiscard]] constexpr const T& at(std::size_t row, std::size_t column) const noexcept;
        [[nodiscard]] constexpr T& at(std::size_t row, std::size_t column) noexcept;

        [[nodiscard]] constexpr const std::array<T, Rows * Cols>& getData() const noexcept;
        [[nodiscard]] constexpr std::array<T, Rows * Cols>& getData() noexcept;

        template<MatrixOrdering U>
        [[nodiscard]] constexpr Mat<Rows, Cols, T, U> convertTo() const noexcept;

        [[nodiscard]] constexpr Mat operator+(const Mat& rhs) const noexcept;
        [[nodiscard]] constexpr Mat operator-(const Mat& rhs) const noexcept;
        [[nodiscard]] constexpr Mat operator*(const Mat& rhs) const noexcept requires (Rows == Cols);
        [[nodiscard]] constexpr Mat operator/(const Mat& rhs) const noexcept requires (Rows == Cols);

        constexpr Mat& operator+=(const Mat& rhs) noexcept;
        constexpr Mat& operator-=(const Mat& rhs) noexcept;
        constexpr Mat& operator*=(const Mat& rhs) noexcept requires (Rows == Cols);
        constexpr Mat& operator/=(const Mat& rhs) noexcept requires (Rows == Cols);

        [[nodiscard]] constexpr Mat operator+(T scalar) const noexcept;
        [[nodiscard]] constexpr Mat operator-(T scalar) const noexcept;
        [[nodiscard]] constexpr Mat operator*(T scalar) const noexcept;
        [[nodiscard]] constexpr Mat operator/(T scalar) const noexcept;

        constexpr Mat& operator+=(T scalar) noexcept;
        constexpr Mat& operator-=(T scalar) noexcept;
        constexpr Mat& operator*=(T scalar) noexcept;
        constexpr Mat& operator/=(T scalar) noexcept;

        [[nodiscard]] constexpr Vec<Rows, T> operator*(const Vec<Cols, T>& vec) const noexcept;

        constexpr void transpose() noexcept;
        constexpr void inverse() noexcept requires (Rows == Cols);

        [[nodiscard]] constexpr Vec<Cols, T> getRow(std::size_t row) const noexcept;
        [[nodiscard]] constexpr Vec<Rows, T> getColumn(std::size_t column) const noexcept;

        constexpr void setRow(std::size_t row, Vec<Cols, T> data) noexcept;
        constexpr void setColumn(std::size_t column, Vec<Rows, T> data) noexcept;
    private:
        std::array<T, Rows * Cols> m_data{};
    };

    template<Number T> using Mat3x3 = Mat<3, 3, T>;
    template<Number T> using Mat4x4 = Mat<4, 4, T>;

    using Mat3x3f = Mat3x3<float>;
    using Mat3x3d = Mat3x3<double>;
    using Mat3x3i = Mat3x3<std::int32_t>;
    using Mat3x3I = Mat3x3<std::int64_t>;
    using Mat3x3u = Mat3x3<std::uint32_t>;
    using Mat3x3U = Mat3x3<std::uint64_t>;

    using Mat4x4f = Mat4x4<float>;
    using Mat4x4d = Mat4x4<double>;
    using Mat4x4i = Mat4x4<std::int32_t>;
    using Mat4x4I = Mat4x4<std::int64_t>;
    using Mat4x4u = Mat4x4<std::uint32_t>;
    using Mat4x4U = Mat4x4<std::uint64_t>;

    template<std::size_t Rows, std::size_t Cols, Number T, MatrixOrdering O>
    constexpr Mat<Rows, Cols, T, O>::Mat(T value) noexcept
    {
        for (std::size_t row = 0; row < Rows; ++row)
            for (std::size_t col = 0; col < Cols; ++col)
                if (row == col)
                    this->at(row, col) = value;
    }

    template<std::size_t Rows, std::size_t Cols, Number T, MatrixOrdering O>
    constexpr Mat<Rows, Cols, T, O>::Mat(std::span<T, Rows * Cols> span) noexcept
    {
        std::copy(span.begin(), span.end(), this->m_data.begin());
    }

    template<std::size_t Rows, std::size_t Cols, Number T, MatrixOrdering O>
    constexpr Mat<Rows, Cols, T, O>::Mat(std::array<T, Rows * Cols> array) noexcept
        : m_data(array) {}

    template<std::size_t Rows, std::size_t Cols, Number T, MatrixOrdering O>
    constexpr Mat<Rows, Cols, T, O>::Mat(std::initializer_list<T> list) noexcept
    {
        assert(list.size() == Rows * Cols);
        std::copy(list.begin(), list.end(), this->m_data.begin());
    }

    template<std::size_t Rows, std::size_t Cols, Number T, MatrixOrdering O>
    constexpr Mat<Rows, Cols, T, O> Mat<Rows, Cols, T, O>::Identity() noexcept requires (Rows == Cols)
    {
        Mat m{};
        for (std::size_t i = 0; i < Rows; ++i)
            m(i, i) = T{1};
        return m;
    }

    template<std::size_t Rows, std::size_t Cols, Number T, MatrixOrdering O>
    constexpr const T& Mat<Rows, Cols, T, O>::operator()(std::size_t row, std::size_t column) const noexcept
    {
        if constexpr (O == MatrixOrdering::RowMajor)
            return this->m_data[row * Cols + column];
        else
            return this->m_data[column * Rows + row];
    }

    template<std::size_t Rows, std::size_t Cols, Number T, MatrixOrdering O>
    constexpr T& Mat<Rows, Cols, T, O>::operator()(std::size_t row, std::size_t column) noexcept
    {
        if constexpr (O == MatrixOrdering::RowMajor)
            return this->m_data[row * Cols + column];
        else
            return this->m_data[column * Rows + row];
    }

    template<std::size_t Rows, std::size_t Cols, Number T, MatrixOrdering O>
    constexpr const T& Mat<Rows, Cols, T, O>::at(std::size_t row, std::size_t column) const noexcept
    {
        if constexpr (O == MatrixOrdering::RowMajor)
            return this->m_data.at(row * Cols + column);
        else
            return this->m_data.at(column * Rows + row);
    }

    template<std::size_t Rows, std::size_t Cols, Number T, MatrixOrdering O>
    constexpr T& Mat<Rows, Cols, T, O>::at(std::size_t row, std::size_t column) noexcept
    {
        if constexpr (O == MatrixOrdering::RowMajor)
            return this->m_data.at(row * Cols + column);
        else
            return this->m_data.at(column * Rows + row);
    }

    template<std::size_t Rows, std::size_t Cols, Number T, MatrixOrdering O>
    constexpr const std::array<T, Rows * Cols>& Mat<Rows, Cols, T, O>::getData() const noexcept
    {
        return this->m_data;
    }

    template<std::size_t Rows, std::size_t Cols, Number T, MatrixOrdering O>
    constexpr std::array<T, Rows * Cols>& Mat<Rows, Cols, T, O>::getData() noexcept
    {
        return this->m_data;
    }

    template<std::size_t Rows, std::size_t Cols, Number T, MatrixOrdering O>
    template<MatrixOrdering U>
    constexpr Mat<Rows, Cols, T, U> Mat<Rows, Cols, T, O>::convertTo() const noexcept
    {
        Mat<Rows, Cols, T, U> result{};
        for (std::size_t r = 0; r < Rows; ++r)
            for (std::size_t c = 0; c < Cols; ++c)
                result(r, c) = (*this)(r, c);
        return result;
    }

    template<std::size_t Rows, std::size_t Cols, Number T, MatrixOrdering O>
    constexpr Mat<Rows, Cols, T, O> Mat<Rows, Cols, T, O>::operator+(const Mat& rhs) const noexcept
    {
        Mat result{};
        for (std::size_t i = 0; i < Rows * Cols; ++i)
            result.m_data[i] = this->m_data[i] + rhs.m_data[i];
        return result;
    }

    template<std::size_t Rows, std::size_t Cols, Number T, MatrixOrdering O>
    constexpr Mat<Rows, Cols, T, O> Mat<Rows, Cols, T, O>::operator-(const Mat& rhs) const noexcept
    {
        Mat result{};
        for (std::size_t i = 0; i < Rows * Cols; ++i)
            result.m_data[i] = this->m_data[i] - rhs.m_data[i];
        return result;
    }

    template<std::size_t Rows, std::size_t Cols, Number T, MatrixOrdering O>
    constexpr Mat<Rows, Cols, T, O> Mat<Rows, Cols, T, O>::operator*(const Mat& rhs) const noexcept requires (Rows == Cols)
    {
        Mat result{};
        for (std::size_t i = 0; i < Rows; ++i)
            for (std::size_t j = 0; j < Cols; ++j)
                for (std::size_t k = 0; k < Cols; ++k)
                    result(i, j) += (*this)(i, k) * rhs(k, j);
        return result;
    }

    template<std::size_t Rows, std::size_t Cols, Number T, MatrixOrdering O>
    constexpr Mat<Rows, Cols, T, O> Mat<Rows, Cols, T, O>::operator/(const Mat& rhs) const noexcept requires (Rows == Cols)
    {
        Mat result = rhs;
        result.inverse();
        return (*this) * result;
    }

    template<std::size_t Rows, std::size_t Cols, Number T, MatrixOrdering O>
    constexpr Mat<Rows, Cols, T, O>& Mat<Rows, Cols, T, O>::operator+=(const Mat& rhs) noexcept
    {
        for (std::size_t i = 0; i < Rows * Cols; ++i)
            this->m_data[i] += rhs.m_data[i];
        return *this;
    }

    template<std::size_t Rows, std::size_t Cols, Number T, MatrixOrdering O>
    constexpr Mat<Rows, Cols, T, O>& Mat<Rows, Cols, T, O>::operator-=(const Mat& rhs) noexcept
    {
        for (std::size_t i = 0; i < Rows * Cols; ++i)
            this->m_data[i] -= rhs.m_data[i];
        return *this;
    }

    template<std::size_t Rows, std::size_t Cols, Number T, MatrixOrdering O>
    constexpr Mat<Rows, Cols, T, O>& Mat<Rows, Cols, T, O>::operator*=(const Mat& rhs) noexcept requires (Rows == Cols)
    {
        *this = *this * rhs;
        return *this;
    }

    template<std::size_t Rows, std::size_t Cols, Number T, MatrixOrdering O>
    constexpr Mat<Rows, Cols, T, O>& Mat<Rows, Cols, T, O>::operator/=(const Mat& rhs) noexcept requires (Rows == Cols)
    {
        *this = *this / rhs;
        return *this;
    }

    template<std::size_t Rows, std::size_t Cols, Number T, MatrixOrdering O>
    constexpr Mat<Rows, Cols, T, O> Mat<Rows, Cols, T, O>::operator+(T scalar) const noexcept
    {
        Mat result = *this;
        result += scalar;
        return result;
    }

    template<std::size_t Rows, std::size_t Cols, Number T, MatrixOrdering O>
    constexpr Mat<Rows, Cols, T, O> Mat<Rows, Cols, T, O>::operator-(T scalar) const noexcept
    {
        Mat result = *this;
        result -= scalar;
        return result;
    }

    template<std::size_t Rows, std::size_t Cols, Number T, MatrixOrdering O>
    constexpr Mat<Rows, Cols, T, O> Mat<Rows, Cols, T, O>::operator*(T scalar) const noexcept
    {
        Mat result = *this;
        result *= scalar;
        return result;
    }

    template<std::size_t Rows, std::size_t Cols, Number T, MatrixOrdering O>
    constexpr Mat<Rows, Cols, T, O> Mat<Rows, Cols, T, O>::operator/(T scalar) const noexcept
    {
        Mat result = *this;
        result /= scalar;
        return result;
    }

    template<std::size_t Rows, std::size_t Cols, Number T, MatrixOrdering O>
    constexpr Mat<Rows, Cols, T, O>& Mat<Rows, Cols, T, O>::operator+=(T scalar) noexcept
    {
        for (auto& e : this->m_data) e += scalar;
        return *this;
    }

    template<std::size_t Rows, std::size_t Cols, Number T, MatrixOrdering O>
    constexpr Mat<Rows, Cols, T, O>& Mat<Rows, Cols, T, O>::operator-=(T scalar) noexcept
    {
        for (auto& e : this->m_data) e -= scalar;
        return *this;
    }

    template<std::size_t Rows, std::size_t Cols, Number T, MatrixOrdering O>
    constexpr Mat<Rows, Cols, T, O>& Mat<Rows, Cols, T, O>::operator*=(T scalar) noexcept
    {
        for (auto& e : this->m_data) e *= scalar;
        return *this;
    }

    template<std::size_t Rows, std::size_t Cols, Number T, MatrixOrdering O>
    constexpr Mat<Rows, Cols, T, O>& Mat<Rows, Cols, T, O>::operator/=(T scalar) noexcept
    {
        for (auto& e : this->m_data) e /= scalar;
        return *this;
    }

    template<std::size_t Rows, std::size_t Cols, Number T, MatrixOrdering O>
    constexpr Vec<Rows, T> Mat<Rows, Cols, T, O>::operator*(const Vec<Cols, T>& vec) const noexcept
    {
        Vec<Rows, T> result{};
        for (std::size_t i = 0; i < Rows; ++i)
        {
            T sum{};
            for (std::size_t j = 0; j < Cols; ++j)
                sum += (*this)(i, j) * vec[j];
            result[i] = sum;
        }
        return result;
    }

    template<std::size_t Rows, std::size_t Cols, Number T, MatrixOrdering O>
    constexpr void Mat<Rows, Cols, T, O>::transpose() noexcept
    {
        Mat tmp = *this;
        for (std::size_t r = 0; r < Rows; ++r)
            for (std::size_t c = 0; c < Cols; ++c)
                (*this)(r, c) = tmp(c, r);
    }

    template<std::size_t Rows, std::size_t Cols, Number T, MatrixOrdering O>
    constexpr void Mat<Rows, Cols, T, O>::inverse() noexcept requires (Rows == Cols)
    {
        Mat a = *this;
        Mat b = Mat::Identity();

        for (std::size_t i = 0; i < Rows; ++i)
        {
            T pivot = a(i, i);
            if (isZero(pivot) == true)
            {
                bool swapped = false;
                for (std::size_t j = i + 1; j < Rows; ++j)
                {
                    if (isZero(a(j, i)) == false)
                    {
                        for (std::size_t k = 0; k < Cols; ++k)
                        {
                            std::swap(a(i, k), a(j, k));
                            std::swap(b(i, k), b(j, k));
                        }
                        pivot = a(i, i);
                        swapped = true;
                        break;
                    }
                }
                if (!swapped)
                    return;
            }

            for (std::size_t k = 0; k < Cols; ++k)
            {
                a(i, k) /= pivot;
                b(i, k) /= pivot;
            }

            for (std::size_t j = 0; j < Rows; ++j)
            {
                if (j == i) continue;
                T factor = a(j, i);
                for (std::size_t k = 0; k < Cols; ++k)
                {
                    a(j, k) -= factor * a(i, k);
                    b(j, k) -= factor * b(i, k);
                }
            }
        }

        *this = b;
    }

    template<std::size_t Rows, std::size_t Cols, Number T, MatrixOrdering O>
    constexpr Vec<Cols, T> Mat<Rows, Cols, T, O>::getRow(std::size_t row) const noexcept
    {
        Vec<Cols, T> result{};
        for (std::size_t c = 0; c < Cols; ++c)
            result[c] = (*this)(row, c);
        return result;
    }

    template<std::size_t Rows, std::size_t Cols, Number T, MatrixOrdering O>
    constexpr Vec<Rows, T> Mat<Rows, Cols, T, O>::getColumn(std::size_t column) const noexcept
    {
        Vec<Rows, T> result{};
        for (std::size_t r = 0; r < Rows; ++r)
            result[r] = (*this)(r, column);
        return result;
    }

    template<std::size_t Rows, std::size_t Cols, Number T, MatrixOrdering O>
    constexpr void Mat<Rows, Cols, T, O>::setRow(std::size_t row, Vec<Cols, T> data) noexcept
    {
        for (std::size_t c = 0; c < Cols; ++c)
            (*this)(row, c) = data[c];
    }

    template<std::size_t Rows, std::size_t Cols, Number T, MatrixOrdering O>
    constexpr void Mat<Rows, Cols, T, O>::setColumn(std::size_t column, Vec<Rows, T> data) noexcept
    {
        for (std::size_t r = 0; r < Rows; ++r)
            (*this)(r, column) = data[r];
    }
}