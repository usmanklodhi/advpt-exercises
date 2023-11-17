#pragma once

#include <iostream>
#include <memory>
#include <stdexcept>
#include <vector>



template< class T >
concept Arithmetic = std::is_arithmetic_v< T >;

template< Arithmetic ComponentType >
class Tensor
{
public:
    // Constructs a tensor with rank = 0 and zero-initializes the element.
    Tensor();

    // Constructs a tensor with arbitrary shape and zero-initializes all elements.
    Tensor(const std::vector< size_t >& shape);

    // Constructs a tensor with arbitrary shape and fills it with the specified value.
    explicit Tensor(const std::vector< size_t >& shape, const ComponentType& fillValue);

    // Copy-constructor.
    Tensor(const Tensor< ComponentType >& other);

    // Move-constructor.
    Tensor(Tensor< ComponentType >&& other) noexcept;

    // Copy-assignment
    Tensor&
    operator=(const Tensor< ComponentType >& other);

    // Move-assignment
    Tensor&
    operator=(Tensor< ComponentType >&& other) noexcept;

    // Destructor
    ~Tensor() = default;

    // Returns the rank of the tensor.
    [[nodiscard]] size_t rank() const;

    // Returns the shape of the tensor.
    [[nodiscard]] std::vector< size_t > shape() const;

    // Returns the number of elements of this tensor.
    [[nodiscard]] size_t numElements() const;

    // Element access function
    const ComponentType&
    operator()(const std::vector< size_t >& idx) const;

    // Element mutation function
    ComponentType&
    operator()(const std::vector< size_t >& idx);

private:
    // TODO: Probably you need some members here...
    std::vector<size_t> shape_;  // Represents the shape of the tensor
    std::vector<ComponentType> data_;  // Represents the tensor's elements
};

// TODO: Implement all methods of the Tensor class template.

template <Arithmetic ComponentType>
Tensor<ComponentType>::Tensor() {
    shape_ = std::vector<size_t>();
    data_ = std::vector<ComponentType>();
}

template <Arithmetic ComponentType>
Tensor<ComponentType>::Tensor(const std::vector<size_t>& shape) {
    shape_ = shape;
    data_ = std::vector<ComponentType>(numElements(), 0);
}

template <Arithmetic ComponentType>
Tensor<ComponentType>::Tensor(const std::vector<size_t>& shape, const ComponentType& fillValue) {
    shape_ = shape;
    data_ = std::vector<ComponentType>(numElements(), fillValue);
}

template <Arithmetic ComponentType>
Tensor<ComponentType>::Tensor(const Tensor<ComponentType>& other) {
    shape_ = other.shape_;
    data_ = other.data_;
}

template <Arithmetic ComponentType>
Tensor<ComponentType>::Tensor(Tensor<ComponentType>&& other) noexcept {
    shape_ = std::move(other.shape_);
    data_ = std::move(other.data_);
}

template <Arithmetic ComponentType>
Tensor<ComponentType>::~Tensor() = default;

template <Arithmetic ComponentType>
Tensor<ComponentType>& Tensor<ComponentType>::operator=(const Tensor<ComponentType>& other) {
    shape_ = other.shape_;
    data_ = other.data_;
    return *this;
}

template <Arithmetic ComponentType>
Tensor<ComponentType>& Tensor<ComponentType>::operator=(Tensor<ComponentType>&& other) noexcept {
    shape_ = std::move(other.shape_);
    data_ = std::move(other.data_);
    return *this;
}

template <Arithmetic ComponentType>
size_t Tensor<ComponentType>::rank() const {
    return shape_.size();
}

template <Arithmetic ComponentType>
std::vector<size_t> Tensor<ComponentType>::shape() const {
    return shape_;
}

template <Arithmetic ComponentType>
size_t Tensor<ComponentType>::numElements() const {
    size_t num = 1;
    for (size_t i = 0; i < shape_.size(); i++) {
        num *= shape_[i];
    }
    return num;
}

template <Arithmetic ComponentType>
const ComponentType& Tensor<ComponentType>::operator()(const std::vector<size_t>& idx) const {
    size_t index = 0;
    for (size_t i = 0; i < idx.size(); i++) {
        index += idx[i];
        if (i != idx.size() - 1) {
            index *= shape_[i + 1];
        }
    }
    return data_[index];
}

template <Arithmetic ComponentType>
ComponentType& Tensor<ComponentType>::operator()(const std::vector<size_t>& idx) {
    size_t index = 0;
    for (size_t i = 0; i < idx.size(); i++) {
        index += idx[i];
        if (i != idx.size() - 1) {
            index *= shape_[i + 1];
        }
    }
    return data_[index];
}

// Returns true if the shapes and all elements of both tensors are equal.
template< Arithmetic ComponentType >
bool operator==(const Tensor< ComponentType >& a, const Tensor< ComponentType >& b) {
    if (a.shape() != b.shape()) {
        return false;
    }
    for (size_t i = 0; i < a.numElements(); i++) {
        if (a.data_[i] != b.data_[i]) {
            return false;
        }
    }
    return true;
}

// Pretty-prints the tensor to stdout.
// This is not necessary (and not covered by the tests) but nice to have, also for debugging (and for exercise of course...).
template< Arithmetic ComponentType >
std::ostream&
operator<<(std::ostream& out, const Tensor< ComponentType >& tensor)
{
    // TODO (optional): Implement some nice stdout printer for debugging/exercise.

}

// Reads a tensor from file.
template< Arithmetic ComponentType >
Tensor< ComponentType > readTensorFromFile(const std::string& filename)
{
    // TODO: Implement this function to read in tensors from file.
    //       The format is defined in the instructions.

}

// Writes a tensor to file.
template< Arithmetic ComponentType >
void writeTensorToFile(const Tensor< ComponentType >& tensor, const std::string& filename)
{
    // TODO: Implement this function to write tensors to file.
    //       The format is defined in the instructions.

}
