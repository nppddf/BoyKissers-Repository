#pragma once

#include <algorithm>
#include <cstddef>
#include <stdexcept>
#include <utility>

template <class T>
class SafeVector {
public:
    SafeVector() noexcept;
    explicit SafeVector(std::size_t initialCapacity);
    SafeVector(const SafeVector& other);
    SafeVector& operator=(const SafeVector& other);
    SafeVector(SafeVector&& other) noexcept;
    SafeVector& operator=(SafeVector&& other) noexcept;
    ~SafeVector();

    void push_back(const T& value);
    void push_back(T&& value);

    template <class... Args>
    T& emplace_back(Args&&... args);

    void resize(std::size_t newSize);
    void clear();

    std::size_t size() const noexcept;
    std::size_t capacity() const noexcept;
    bool empty() const noexcept;

    T& operator[](std::size_t index);
    const T& operator[](std::size_t index) const;
    T& at(std::size_t index);
    const T& at(std::size_t index) const;

    T* begin() noexcept;
    T* end() noexcept;
    const T* begin() const noexcept;
    const T* end() const noexcept;
    const T* cbegin() const noexcept;
    const T* cend() const noexcept;

    void swap(SafeVector& other) noexcept;

private:
    void ensureCapacity(std::size_t minCapacity);
    void reallocate(std::size_t newCapacity);

    T* data_;
    std::size_t size_;
    std::size_t capacity_;
};

template <class T>
SafeVector<T>::SafeVector() noexcept
    : data_(nullptr), size_(0), capacity_(0)
{
}

template <class T>
SafeVector<T>::SafeVector(std::size_t initialCapacity)
    : data_(nullptr), size_(0), capacity_(0)
{
    if(initialCapacity > 0)
        reallocate(initialCapacity);
}

template <class T>
SafeVector<T>::SafeVector(const SafeVector& other)
    : data_(nullptr), size_(0), capacity_(0)
{
    if(other.capacity_ > 0)
    {
        data_ = new T[other.capacity_];
        for(std::size_t i = 0; i < other.size_; ++i)
            data_[i] = other.data_[i];
    }
    size_ = other.size_;
    capacity_ = other.capacity_;
}

template <class T>
SafeVector<T>& SafeVector<T>::operator=(const SafeVector& other)
{
    if(this == &other)
        return *this;

    SafeVector copy(other);
    swap(copy);
    return *this;
}

template <class T>
SafeVector<T>::SafeVector(SafeVector&& other) noexcept
    : data_(other.data_), size_(other.size_), capacity_(other.capacity_)
{
    other.data_ = nullptr;
    other.size_ = 0;
    other.capacity_ = 0;
}

template <class T>
SafeVector<T>& SafeVector<T>::operator=(SafeVector&& other) noexcept
{
    if(this == &other)
        return *this;

    delete[] data_;
    data_ = other.data_;
    size_ = other.size_;
    capacity_ = other.capacity_;

    other.data_ = nullptr;
    other.size_ = 0;
    other.capacity_ = 0;
    return *this;
}

template <class T>
SafeVector<T>::~SafeVector()
{
    delete[] data_;
}

template <class T>
void SafeVector<T>::push_back(const T& value)
{
    ensureCapacity(size_ + 1);
    data_[size_++] = value;
}

template <class T>
void SafeVector<T>::push_back(T&& value)
{
    ensureCapacity(size_ + 1);
    data_[size_++] = std::move(value);
}

template <class T>
template <class... Args>
T& SafeVector<T>::emplace_back(Args&&... args)
{
    ensureCapacity(size_ + 1);
    data_[size_] = T(std::forward<Args>(args)...);
    return data_[size_++];
}

template <class T>
void SafeVector<T>::resize(std::size_t newSize)
{
    ensureCapacity(newSize);
    if(newSize > size_)
        for(std::size_t i = size_; i < newSize; ++i)
            data_[i] = T();

    size_ = newSize;
}

template <class T>
void SafeVector<T>::clear()
{
    for(std::size_t i = 0; i < size_; ++i)
        data_[i] = T();
    size_ = 0;
}

template <class T>
std::size_t SafeVector<T>::size() const noexcept
{
    return size_;
}

template <class T>
std::size_t SafeVector<T>::capacity() const noexcept
{
    return capacity_;
}

template <class T>
bool SafeVector<T>::empty() const noexcept
{
    return size_ == 0;
}

template <class T>
T& SafeVector<T>::operator[](std::size_t index)
{
    return data_[index];
}

template <class T>
const T& SafeVector<T>::operator[](std::size_t index) const
{
    return data_[index];
}

template <class T>
T& SafeVector<T>::at(std::size_t index)
{
    if(index >= size_)
        throw std::out_of_range("SafeVector::at out of range");
    return data_[index];
}

template <class T>
const T& SafeVector<T>::at(std::size_t index) const
{
    if(index >= size_)
        throw std::out_of_range("SafeVector::at out of range");
    return data_[index];
}

template <class T>
T* SafeVector<T>::begin() noexcept
{
    return data_;
}

template <class T>
T* SafeVector<T>::end() noexcept
{
    return data_ ? data_ + size_ : nullptr;
}

template <class T>
const T* SafeVector<T>::begin() const noexcept
{
    return data_;
}

template <class T>
const T* SafeVector<T>::end() const noexcept
{
    return data_ ? data_ + size_ : nullptr;
}

template <class T>
const T* SafeVector<T>::cbegin() const noexcept
{
    return begin();
}

template <class T>
const T* SafeVector<T>::cend() const noexcept
{
    return end();
}

template <class T>
void SafeVector<T>::swap(SafeVector& other) noexcept
{
    std::swap(data_, other.data_);
    std::swap(size_, other.size_);
    std::swap(capacity_, other.capacity_);
}

template <class T>
void SafeVector<T>::ensureCapacity(std::size_t minCapacity)
{
    if(minCapacity <= capacity_)
        return;

    std::size_t newCapacity = capacity_ == 0 ? 1 : capacity_;
    while(newCapacity < minCapacity)
        newCapacity *= 2;
    reallocate(newCapacity);
}

template <class T>
void SafeVector<T>::reallocate(std::size_t newCapacity)
{
    if(newCapacity == 0)
    {
        delete[] data_;
        data_ = nullptr;
        capacity_ = 0;
        size_ = 0;
        return;
    }

    T* newData = new T[newCapacity];
    for(std::size_t i = 0; i < size_; ++i)
        newData[i] = data_[i];

    delete[] data_;
    data_ = newData;
    capacity_ = newCapacity;
}

template <class T>
void swap(SafeVector<T>& lhs, SafeVector<T>& rhs) noexcept
{
    lhs.swap(rhs);
}
