#pragma once

#include <cstddef>
#include <initializer_list>
#include <stdexcept>
#include <utility>

template <typename T>
class TVector {
private:
    T* data_;
    std::size_t size_;
    std::size_t capacity_;

public:
    TVector()
        : data_(nullptr),
          size_(0),
          capacity_(0) {
    }

    explicit TVector(std::size_t size)
        : data_(size > 0 ? new T[size]() : nullptr),
          size_(size),
          capacity_(size) {
    }

    TVector(std::size_t size, const T& value)
        : data_(size > 0 ? new T[size] : nullptr),
          size_(size),
          capacity_(size) {
        for (std::size_t i = 0; i < size_; ++i) {
            data_[i] = value;
        }
    }

    TVector(std::initializer_list<T> values)
        : data_(values.size() > 0 ? new T[values.size()] : nullptr),
          size_(values.size()),
          capacity_(values.size()) {
        std::size_t i = 0;

        for (const T& value : values) {
            data_[i++] = value;
        }
    }

    TVector(const TVector& other)
        : data_(other.capacity_ > 0 ? new T[other.capacity_] : nullptr),
          size_(other.size_),
          capacity_(other.capacity_) {
        for (std::size_t i = 0; i < size_; ++i) {
            data_[i] = other.data_[i];
        }
    }

    TVector(TVector&& other) noexcept
        : data_(other.data_),
          size_(other.size_),
          capacity_(other.capacity_) {
        other.data_ = nullptr;
        other.size_ = 0;
        other.capacity_ = 0;
    }

    ~TVector() {
        delete[] data_;
    }

    TVector& operator=(const TVector& other) {
        if (this == &other) {
            return *this;
        }

        T* new_data = other.capacity_ > 0
                          ? new T[other.capacity_]
                          : nullptr;

        for (std::size_t i = 0; i < other.size_; ++i) {
            new_data[i] = other.data_[i];
        }

        delete[] data_;

        data_ = new_data;
        size_ = other.size_;
        capacity_ = other.capacity_;

        return *this;
    }

    TVector& operator=(TVector&& other) noexcept {
        if (this == &other) {
            return *this;
        }

        delete[] data_;

        data_ = other.data_;
        size_ = other.size_;
        capacity_ = other.capacity_;

        other.data_ = nullptr;
        other.size_ = 0;
        other.capacity_ = 0;

        return *this;
    }

    T& operator[](std::size_t index) {
        return data_[index];
    }

    const T& operator[](std::size_t index) const {
        return data_[index];
    }

    T& at(std::size_t index) {
        if (index >= size_) {
            throw std::out_of_range("TVector::at: index out of range");
        }

        return data_[index];
    }

    const T& at(std::size_t index) const {
        if (index >= size_) {
            throw std::out_of_range("TVector::at: index out of range");
        }

        return data_[index];
    }

    T& front() {
        if (empty()) {
            throw std::out_of_range("TVector::front: vector is empty");
        }

        return data_[0];
    }

    const T& front() const {
        if (empty()) {
            throw std::out_of_range("TVector::front: vector is empty");
        }

        return data_[0];
    }

    T& back() {
        if (empty()) {
            throw std::out_of_range("TVector::back: vector is empty");
        }

        return data_[size_ - 1];
    }

    const T& back() const {
        if (empty()) {
            throw std::out_of_range("TVector::back: vector is empty");
        }

        return data_[size_ - 1];
    }

    void push_back(const T& value) {
        if (size_ == capacity_) {
            reserve(capacity_ == 0 ? 1 : capacity_ * 2);
        }

        data_[size_++] = value;
    }

    void push_back(T&& value) {
        if (size_ == capacity_) {
            reserve(capacity_ == 0 ? 1 : capacity_ * 2);
        }

        data_[size_++] = std::move(value);
    }

    void pop_back() {
        if (empty()) {
            throw std::out_of_range("TVector::pop_back: vector is empty");
        }

        --size_;
    }

    void clear() {
        size_ = 0;
    }

    void reserve(std::size_t new_capacity) {
        if (new_capacity <= capacity_) {
            return;
        }

        T* new_data = new T[new_capacity];

        for (std::size_t i = 0; i < size_; ++i) {
            new_data[i] = std::move(data_[i]);
        }

        delete[] data_;

        data_ = new_data;
        capacity_ = new_capacity;
    }

    std::size_t size() const {
        return size_;
    }

    std::size_t capacity() const {
        return capacity_;
    }

    bool empty() const {
        return size_ == 0;
    }
};