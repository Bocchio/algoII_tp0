#ifndef VECTOR_HPP_
#define VECTOR_HPP_

#include <cstddef>  // Needed for size_t
#include <stdexcept>  // For exceptions
#include <utility>

template <typename T>
class Vector {
    T *data;
    size_t size;
    size_t alloc_size;
    static const size_t INIT_CHOP = 10;
    static const size_t CHOP_SIZE = 20;

    //
    void resize(size_t new_size) {
        T *aux = new T[new_size];
        for (size_t i = 0; i < size; i++)
            aux[i] = data[i];
        delete []data;
        data = aux;
        alloc_size = new_size;
    }

 public:
    Vector() {
        size = 0;
        alloc_size = INIT_CHOP;
        data = new T[alloc_size];
    }

    Vector(const Vector& other) {
        std::cout << "Copy constructor called." << std::endl;
        size = other.size;
        alloc_size = other.alloc_size;
        data = new T[alloc_size];
        for (size_t i = 0; i < size; i++) {
            data[i] = other.data[i];
        }
    }

    template <typename VectorIterator>
    Vector(const VectorIterator& first, const VectorIterator& last) {
        size = 0;
        alloc_size = INIT_CHOP;
        data = new T[alloc_size];
        for (VectorIterator it = first; it != last; ++it) {
            if (size >= alloc_size)
                resize(alloc_size + CHOP_SIZE);
            data[size] = *it;
            size++;
        }
    }

    ~Vector() {
        std::cout << "Delete called" << std::endl;
        delete []data;
    }

    T& operator[](size_t pos) const {
        if (pos >= size)
            throw std::out_of_range("The index is out of range.");
        return data[pos];
    }

    void append(const T &object) {
        if (size >= alloc_size)
            resize(alloc_size + CHOP_SIZE);
        data[size] = object;
        size++;
    }

    void remove(size_t pos) {
        if (pos < size) {
            delete data[pos];
            for (size_t i = pos; i < size - 1; ++i)
                data[i] = data[i+1];
            if (pos != (size - 1))
                delete data[size - 1];
            size--;
        }
        if (alloc_size - size > CHOP_SIZE)
            resize(alloc_size - CHOP_SIZE);
    }

    // Useful for the copy and swap idiom implementation of operator=
    void swap(Vector &r) throw() {
        using std::swap;

        swap(data, r.data);
        swap(size, r.size);
        swap(alloc_size, r.alloc_size);
    }

    Vector& operator=(Vector other) {
        std::cout << "operator= called." << std::endl;
        other.swap(*this);
        return *this;
    }

    size_t getSize() const {
        return size;
    }

    // Iterator support
    typedef T* iterator;
    iterator begin() {
        return &data[0];
    }
    iterator end() {
        return &data[size];
    }
};

#endif  // VECTOR_HPP_
