#include "headers/Vector.h"

namespace XXX {

    VectorIterator::VectorIterator() : m_user(nullptr) {}

    VectorIterator::VectorIterator(const VectorIterator& _it) : m_user(_it.m_user) {}

    VectorIterator::VectorIterator(User* _p) : m_user(_p) {}

    bool VectorIterator::operator==(const VectorIterator& _it) const {
        return m_user == _it.m_user;
    }

    bool VectorIterator::operator!=(const VectorIterator& _it) const {
        return m_user != _it.m_user;
    }

    bool VectorIterator::operator<(const VectorIterator& _it) const {
        return m_user < _it.m_user;
    }

    bool VectorIterator::operator>(const VectorIterator& _it) const {
        return m_user > _it.m_user;
    }

    bool VectorIterator::operator<=(const VectorIterator& _it) const {
        return m_user <= _it.m_user;
    }

    bool VectorIterator::operator>=(const VectorIterator& _it) const {
        return m_user >= _it.m_user;
    }

    std::ptrdiff_t VectorIterator::operator-(const VectorIterator& other) const {
        return m_user - other.m_user;
    }

    User& VectorIterator::operator[](std::ptrdiff_t n) const {
        return *(m_user + n);
    }

    VectorIterator& VectorIterator::operator+=(std::ptrdiff_t n) {
        m_user += n;
        return *this;
    }

    VectorIterator& VectorIterator::operator-=(std::ptrdiff_t n) {
        m_user -= n;
        return *this;
    }

    VectorIterator VectorIterator::operator+(std::ptrdiff_t n) const {
        return VectorIterator(m_user + n);
    }

    VectorIterator VectorIterator::operator-(std::ptrdiff_t n) const {
        return VectorIterator(m_user - n);
    }

    VectorIterator& VectorIterator::operator++() {
        ++m_user;
        return *this;
    }

    VectorIterator VectorIterator::operator++(int) {
        VectorIterator tmp = *this;
        ++(*this);
        return tmp;
    }

    VectorIterator& VectorIterator::operator--() {
        --m_user;
        return *this;
    }

    VectorIterator VectorIterator::operator--(int) {
        VectorIterator tmp = *this;
        --(*this);
        return tmp;
    }

    User& VectorIterator::operator*() const {
        return *m_user;
    }

    User* VectorIterator::operator->() const {
        return m_user;
    }

    VectorIterator operator+(std::ptrdiff_t n, const VectorIterator& it) {
        return it + n;
    }

    UserVector::UserVector() : m_array(nullptr), m_size(0) {}

    UserVector::UserVector(unsigned _size) : m_size(_size) {
        if (_size > 0) {
            m_array = new User[_size];
        } else {
            m_array = nullptr;
        }
    }

    UserVector::UserVector(unsigned _size, User _value) : m_size(_size) {
        if (_size > 0) {
            m_array = new User[_size];
            for (unsigned i = 0; i < _size; ++i) {
                m_array[i] = _value;
            }
        } else {
            m_array = nullptr;
        }
    }

    UserVector::~UserVector() {
        delete[] m_array;
    }

    UserVector::UserVector(const UserVector& other) : m_size(other.m_size) {
        if (m_size > 0) {
            m_array = new User[m_size];
            for (size_t i = 0; i < m_size; ++i) {
                m_array[i] = other.m_array[i];
            }
        } else {
            m_array = nullptr;
        }
    }

    UserVector& UserVector::operator=(const UserVector& other) {
        if (this != &other) {
            delete[] m_array;
            m_size = other.m_size;
            if (m_size > 0) {
                m_array = new User[m_size];
                for (size_t i = 0; i < m_size; ++i) {
                    m_array[i] = other.m_array[i];
                }
            } else {
                m_array = nullptr;
            }
        }
        return *this;
    }

    void UserVector::push_back(const User& user) {
        User* newArray = new User[m_size + 1];
        for (size_t i = 0; i < m_size; ++i) {
            newArray[i] = m_array[i];
        }
        newArray[m_size] = user;
        delete[] m_array;
        m_array = newArray;
        m_size++;
    }

    size_t UserVector::getSize() const {
        return m_size;
    }

    UserVector::iterator UserVector::begin() {
        return iterator(m_array);
    }

    UserVector::iterator UserVector::end() {
        return iterator(m_array + m_size);
    }

    UserVector::const_iterator UserVector::begin() const {
        return const_iterator(m_array);
    }

    UserVector::const_iterator UserVector::end() const {
        return const_iterator(m_array + m_size);
    }

    std::ostream& operator<<(std::ostream& out, const UserVector& vec) {
        for (size_t i = 0; i < vec.m_size; ++i) {
            out << vec.m_array[i] << "\n";
        }
        return out;
    }

}