#pragma once

#include <iostream>
#include <memory>
#include <stdexcept>
#include <vector>
#include <fstream>
#include <string>



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
    std::vector<size_t> shape_;  // Represents the shape of the tensor
    std::vector<ComponentType> data_;  // Represents the tensor's elements
};

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
operator<<(std::ostream& out, const Tensor< ComponentType >& tensor) {
    const std::vector<size_t>& shape = tensor.shape();
    size_t rank = tensor.rank();

    // Print the rank and shape
    out << "Rank: " << rank << ", Shape: [";
    for (size_t i = 0; i < rank; ++i) {
        out << shape[i];
        if (i < rank - 1) {
            out << ", ";
        }
    }
    out << "]" << std::endl;

    // Print the tensor elements
    out << "Tensor Elements:" << std::endl;
    for (size_t i = 0; i < shape[0]; ++i) {
        for (size_t j = 0; j < shape[1]; ++j) {
            for (size_t k = 0; k < shape[2]; ++k) {
                // Assuming a 3D tensor, adjust as needed for other ranks
                out << "Tensor[" << i << "][" << j << "][" << k << "] = " << tensor({i, j, k}) << std::endl;
            }
        }
    }

    return out;
}

// Reads a tensor from file.
template< Arithmetic ComponentType >
Tensor< ComponentType > readTensorFromFile(const std::string& filename) {
    // Open the file in binary mode for reading
    std::ifstream inFile(filename, std::ios::binary);

    if (!inFile.is_open()) {
        // Handle error: unable to open the file
        std::cerr << "Error: Unable to open file for reading." << std::endl;
        // Return an empty tensor or throw an exception based on your error handling strategy
        return Tensor< ComponentType >();
    }

    // Read the rank of the tensor from the file
    size_t rank;
    inFile.read(reinterpret_cast<char*>(&rank), sizeof(size_t));

    // Read the shape of the tensor from the file
    std::vector<size_t> shape(rank);
    inFile.read(reinterpret_cast<char*>(shape.data()), rank * sizeof(size_t));

    // Read the tensor elements from the file
    size_t numElements = 1;
    for (size_t dim : shape) {
        numElements *= dim;
    }

    std::vector<ComponentType> data(numElements);
    inFile.read(reinterpret_cast<char*>(data.data()), numElements * sizeof(ComponentType));

    // Close the file
    inFile.close();

    // Create and return the tensor
    return Tensor< ComponentType >(shape, data);
}

// Writes a tensor to file.
template< Arithmetic ComponentType >
void writeTensorToFile(const Tensor< ComponentType >& tensor, const std::string& filename) {
    // Open the file in binary mode for writing
    std::ofstream outFile(filename, std::ios::binary);

    if (!outFile.is_open()) {
        // Handle error: unable to open the file
        std::cerr << "Error: Unable to open file for writing." << std::endl;
        return;
    }

    // Write the rank of the tensor to the file
    size_t rank = tensor.rank();
    outFile.write(reinterpret_cast<const char*>(&rank), sizeof(size_t));

    // Write the shape of the tensor to the file
    const std::vector<size_t>& shape = tensor.shape();
    outFile.write(reinterpret_cast<const char*>(shape.data()), rank * sizeof(size_t));

    // Write the tensor elements to the file
    const std::vector<ComponentType>& data = tensor.getData();
    outFile.write(reinterpret_cast<const char*>(data.data()), data.size() * sizeof(ComponentType));

    // Close the file
    outFile.close();
}
