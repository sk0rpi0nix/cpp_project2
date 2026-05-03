#ifndef USER_VECTOR
#define USER_VECTOR

#include "User.h"
#include <iostream>
#include <cstddef>
#include <iterator>

namespace XXX {
    class VectorIterator {
        friend class UserVector;
    public:
        using iterator_category = std::random_access_iterator_tag;
        using value_type = User;
        using difference_type = std::ptrdiff_t;
        using pointer = User*;
        using reference = User&;

        VectorIterator();
        VectorIterator(const VectorIterator& _it);
        
        bool operator==(const VectorIterator& _it) const;
        bool operator!=(const VectorIterator& _it) const;
        bool operator<(const VectorIterator& _it) const;
        bool operator>(const VectorIterator& _it) const;
        bool operator<=(const VectorIterator& _it) const;
        bool operator>=(const VectorIterator& _it) const;

        std::ptrdiff_t operator-(const VectorIterator& other) const;
        User& operator[](std::ptrdiff_t n) const;
        
        VectorIterator& operator+=(std::ptrdiff_t n);
        VectorIterator& operator-=(std::ptrdiff_t n);
        VectorIterator operator+(std::ptrdiff_t n) const;
        VectorIterator operator-(std::ptrdiff_t n) const;

        VectorIterator& operator++();
        VectorIterator operator++(int);
        VectorIterator& operator--();
        VectorIterator operator--(int);
        
        User& operator*() const;
        User* operator->() const;

    private:
        User* m_user;
        explicit VectorIterator(User* _p);
    };

    VectorIterator operator+(std::ptrdiff_t n, const VectorIterator& it);

    class UserVector {
    public:
        typedef VectorIterator iterator;
        typedef VectorIterator const_iterator;

        UserVector();
        UserVector(unsigned _size);
        UserVector(unsigned _size, User _value);
        ~UserVector();

        UserVector(const UserVector& other);
        UserVector& operator=(const UserVector& other);

        void push_back(const User& user);
        size_t getSize() const;
        
        iterator begin();
        iterator end();
        const_iterator begin() const;
        const_iterator end() const;

        friend std::ostream& operator<<(std::ostream&, const UserVector&);

    private:
        User* m_array;
        size_t m_size;
    };
}

#endif