#ifndef VECTOR_H
#define VECTOR_H

#include <iostream>
#include <cstddef>
#include <iterator>
#include <stdexcept>

namespace XXX {

// Предварительное объявление для корректной работы friend
template <typename T> class Vector;

template <typename T>
class VectorIterator {
    // Разрешаем Vector<T> доступ к приватным полям итератора
    template <typename> friend class Vector;
public:
    using iterator_category = std::random_access_iterator_tag;
    using value_type = T;
    using difference_type = std::ptrdiff_t;
    using pointer = T*;
    using reference = T&;

    VectorIterator() : m_ptr(nullptr) {}
    VectorIterator(const VectorIterator& other) : m_ptr(other.m_ptr) {}
    explicit VectorIterator(T* p) : m_ptr(p) {}

    // Сравнение
    bool operator==(const VectorIterator& other) const { return m_ptr == other.m_ptr; }
    bool operator!=(const VectorIterator& other) const { return m_ptr != other.m_ptr; }
    bool operator< (const VectorIterator& other) const { return m_ptr <  other.m_ptr; }
    bool operator> (const VectorIterator& other) const { return m_ptr >  other.m_ptr; }
    bool operator<=(const VectorIterator& other) const { return m_ptr <= other.m_ptr; }
    bool operator>=(const VectorIterator& other) const { return m_ptr >= other.m_ptr; }

    // Арифметика и индексация
    difference_type operator-(const VectorIterator& other) const { return m_ptr - other.m_ptr; }
    reference operator[](difference_type n) const { return *(m_ptr + n); }
    VectorIterator& operator+=(difference_type n) { m_ptr += n; return *this; }
    VectorIterator& operator-=(difference_type n) { m_ptr -= n; return *this; }
    VectorIterator operator+(difference_type n) const { return VectorIterator(m_ptr + n); }
    VectorIterator operator-(difference_type n) const { return VectorIterator(m_ptr - n); }

    // Инкремент/Декремент
    VectorIterator& operator++()    { ++m_ptr; return *this; }
    VectorIterator  operator++(int) { VectorIterator tmp = *this; ++(*this); return tmp; }
    VectorIterator& operator--()    { --m_ptr; return *this; }
    VectorIterator  operator--(int) { VectorIterator tmp = *this; --(*this); return tmp; }

    // Разыменование
    reference operator*()  const { return *m_ptr; }
    pointer   operator->() const { return m_ptr; }

private:
    T* m_ptr;
};

// Не-член оператора сложения (n + it)
template <typename T>
VectorIterator<T> operator+(std::ptrdiff_t n, const VectorIterator<T>& it) {
    return it + n;
}

template <typename T>
class Vector {
public:
    using iterator       = VectorIterator<T>;
    using const_iterator = VectorIterator<T>;

    Vector() : m_array(nullptr), m_size(0) {}


    T& at(std::size_t index) {
        if (index >= m_size) {
            throw std::out_of_range("Ошибка: индекс выходит за границы вектора.");
        }
        return m_array[index];
    }

    const T& at(std::size_t index) const {
        if (index >= m_size) {
            throw std::out_of_range("Ошибка: индекс выходит за границы вектора.");
        }
        return m_array[index];
    }



    T& operator[](std::size_t index) {
        return m_array[index];
    }
    
    const T& operator[](std::size_t index) const {
        return m_array[index];
    }

    // ... (остальные методы)
    
    
    explicit Vector(std::size_t size) : m_size(size) {
        m_array = (size > 0) ? new T[size] : nullptr;
    }

    Vector(std::size_t size, const T& value) : m_size(size) {
        if (size > 0) {
            m_array = new T[size];
            for (std::size_t i = 0; i < size; ++i) {
                m_array[i] = value;
            }
        } else {
            m_array = nullptr;
        }
    }

    ~Vector() { delete[] m_array; }

    // Правило трёх (конструктор копирования)
    Vector(const Vector& other) : m_size(other.m_size) {
        if (m_size > 0) {
            m_array = new T[m_size];
            for (std::size_t i = 0; i < m_size; ++i) {
                m_array[i] = other.m_array[i];
            }
        } else {
            m_array = nullptr;
        }
    }

    // Правило трёх (оператор присваивания)
    Vector& operator=(const Vector& other) {
        if (this != &other) {
            delete[] m_array;
            m_size = other.m_size;
            if (m_size > 0) {
                m_array = new T[m_size];
                for (std::size_t i = 0; i < m_size; ++i) {
                    m_array[i] = other.m_array[i];
                }
            } else {
                m_array = nullptr;
            }
        }
        return *this;
    }

    void push_back(const T& value) {
        T* newArray = new T[m_size + 1];
        for (std::size_t i = 0; i < m_size; ++i) {
            newArray[i] = m_array[i];
        }
        newArray[m_size] = value;
        delete[] m_array;
        m_array = newArray;
        ++m_size;
    }

    std::size_t getSize() const { return m_size; }

    iterator begin()       { return iterator(m_array); }
    iterator end()         { return iterator(m_array + m_size); }
    const_iterator begin() const { return const_iterator(m_array); }
    const_iterator end()   const { return const_iterator(m_array + m_size); }

    friend std::ostream& operator<<(std::ostream& out, const Vector<T>& vec) {
        for (std::size_t i = 0; i < vec.m_size; ++i) {
            out << vec.m_array[i] << "\n";
        }
        return out;
    }

private:
    T* m_array;
    std::size_t m_size;
};

} // namespace XXX

#endif // VECTOR_H