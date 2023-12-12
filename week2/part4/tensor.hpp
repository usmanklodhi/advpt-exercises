#pragma once

#include <iostream>
#include <memory>
#include <stdexcept>
#include <vector>
#include <fstream>
#include <string>

template <class T>
concept Arithmetic = std::is_arithmetic_v<T>;

template <Arithmetic ComponentType>
class Tensor
{
public:
    // Constructs a tensor with rank = 0 and zero-initializes the element.
    Tensor();

    // Constructs a tensor with arbitrary shape and zero-initializes all elements.
    Tensor(const std::vector<size_t> &shape);

    // Constructs a tensor with arbitrary shape and fills it with the specified value.
    explicit Tensor(const std::vector<size_t> &shape, const ComponentType &fillValue);

    // Copy-constructor.
    Tensor(const Tensor<ComponentType> &other);

    // Move-constructor.
    Tensor(Tensor<ComponentType> &&other) noexcept;

    // Copy-assignment
    Tensor &
    operator=(const Tensor<ComponentType> &other);

    // Move-assignment
    Tensor &
    operator=(Tensor<ComponentType> &&other) noexcept;

    // Destructor
    ~Tensor() = default;

    // Returns the rank of the tensor.
    [[nodiscard]] size_t rank() const;

    // Returns the shape of the tensor.
    [[nodiscard]] std::vector<size_t> shape() const;

    // Returns the number of elements of this tensor.
    [[nodiscard]] size_t numElements() const;

    // Element access function
    const ComponentType &
    operator()(const std::vector<size_t> &idx) const;

    // Element mutation function
    ComponentType &
    operator()(const std::vector<size_t> &idx);

    // Getters
    const std::vector<ComponentType> &getData() const { return data_; }
    const std::vector<size_t> &getShape() const { return shape_; }

    // Setters
    void setData(const std::vector<ComponentType> &data) { data_ = data; }
    void setShape(const std::vector<size_t> &shape) { shape_ = shape; }

private:
    std::vector<size_t> shape_;       // Represents the shape of the tensor
    std::vector<ComponentType> data_; // Represents the tensor's elements
};

template <Arithmetic ComponentType>
Tensor<ComponentType>::Tensor() : shape_({}), data_(1, 0)
{
    // Set shape to an empty vector, indicating rank 0
    // Set data_ with a single, zero-initialized entry
}

template <Arithmetic ComponentType>
Tensor<ComponentType>::Tensor(const std::vector<size_t> &shape)
{
    shape_ = shape;
    data_ = std::vector<ComponentType>(numElements(), 0);
}

template <Arithmetic ComponentType>
Tensor<ComponentType>::Tensor(const std::vector<size_t> &shape, const ComponentType &fillValue)
{
    shape_ = shape;
    data_ = std::vector<ComponentType>(numElements(), fillValue);
}

template <Arithmetic ComponentType>
Tensor<ComponentType>::Tensor(const Tensor<ComponentType> &other)
{
    shape_ = other.shape_;
    data_ = other.data_;
}

template <Arithmetic ComponentType>
Tensor<ComponentType>::Tensor(Tensor<ComponentType> &&other) noexcept
{
    shape_ = std::move(other.shape_);
    data_ = std::move(other.data_);
    other.shape_ = {};
    other.data_ = {0};
}

template <Arithmetic ComponentType>
Tensor<ComponentType> &Tensor<ComponentType>::operator=(const Tensor<ComponentType> &other)
{
    shape_ = other.shape_;
    data_ = other.data_;
    return *this;
}

template <Arithmetic ComponentType>
Tensor<ComponentType> &Tensor<ComponentType>::operator=(Tensor<ComponentType> &&other) noexcept
{
    shape_ = std::move(other.shape_);
    data_ = std::move(other.data_);
    return *this;
}

template <Arithmetic ComponentType>
size_t Tensor<ComponentType>::rank() const
{
    return shape_.size();
}

template <Arithmetic ComponentType>
std::vector<size_t> Tensor<ComponentType>::shape() const
{
    return shape_;
}

template <Arithmetic ComponentType>
size_t Tensor<ComponentType>::numElements() const
{
    if (shape_.empty()) {
        return 1; // Rank 0 tensor has a single element
    }

    size_t num = 1;
    for (size_t i = 0; i < shape_.size(); i++)
    {
        num *= shape_[i];
    }
    return num;
}

template <Arithmetic ComponentType>
const ComponentType &Tensor<ComponentType>::operator()(const std::vector<size_t> &idx) const
{
    int index = 0;
    for (size_t i = 0; i <idx.size() ; ++i)
    {
        int product=idx[i];
        for(size_t j=i+1;j<idx.size();j++){
            product *= shape_[j];
        }
        index += product;
    }
    return data_[index];
}

template <Arithmetic ComponentType>
ComponentType& Tensor<ComponentType>::operator()(const std::vector<size_t>& idx)
{
    int index = 0;
    for (size_t i = 0; i <idx.size() ; ++i)
    {
        int product=idx[i];
        for(size_t j=i+1;j<idx.size();j++){
            product *= shape_[j];
        }
        index += product;
    }
    return data_[index];
}

// Returns true if the shapes and all elements of both tensors are equal.
template <Arithmetic ComponentType>
bool operator==(const Tensor<ComponentType> &a, const Tensor<ComponentType> &b)
{
    // Check if either of the tensors is empty
    if (a.shape() != b.shape())
    {
        return false;
    }
    // create variables aData and bData as placeholders for the data of a and b using Getters
    const std::vector<ComponentType> &aData = a.getData();
    const std::vector<ComponentType> &bData = b.getData();
    for (size_t i = 0; i < a.numElements(); i++)
    {
        if (aData[i] != bData[i])
        {
            return false;
        }
    }
    return true;
}

// Pretty-prints the tensor to stdout.
// This is not necessary (and not covered by the tests) but nice to have, also for debugging (and for exercise of course...).
template <Arithmetic ComponentType>
std::ostream & operator<<(std::ostream &out, const Tensor<ComponentType> &tensor)
{
    // Write the rank of the tensor to output stream
    size_t rank = tensor.rank();
    out<<rank<<"\n";

    // Write the shape of the tensor to output stream
    for(const auto& s : tensor.shape()){
        out<<s<<"\n";
    }

    // Write the tensor elements to output stream
    std::vector<size_t> index(tensor.rank(),0);
    for (size_t i = 0; i < tensor.numElements(); ++i) {
        out<<tensor(index)<<"\n";
        // Move to the next index
        for (int j = tensor.rank()-1; j >= 0;j--) {
            if (++index[j] < tensor.shape()[j]) {
                break;
            }
            index[j] = 0;
        }
    }

    return out;
}

//Reads a tensor from file.
template <Arithmetic ComponentType>
Tensor<ComponentType> readTensorFromFile(const std::string& filename)
{
    // TODO: Implement this function
    Tensor<ComponentType> tensor;
    std::ifstream inputFile(filename);
    if (inputFile.is_open()){
        std::string line;
        if(std::getline(inputFile,line)){
            int rank=std::stoi(line);
            std::vector<size_t> shape(rank,0);
            int i=0;
            while(i<rank){
                std::getline(inputFile,line);
                shape[i]=std::stoi(line);
                i++;
            }
            tensor.setShape(shape);
            tensor.setData(std::vector<ComponentType>(tensor.numElements(), 0));
            //read elements from file
            int totalElements=tensor.numElements();
            std::vector<size_t> index(tensor.rank(),0);
            for (int i = 0; i < totalElements; ++i) {
                std::getline(inputFile,line);
                tensor(index)=std::stoi(line);
                for (int j = tensor.rank()-1; j >= 0;j--) {
                    if (++index[j] < tensor.shape()[j]) {
                        break;
                    }
                    index[j] = 0;
                }
            }
        }
    }else{
        // Handle error: unable to open the file
        std::cerr << "Error: Unable to open file for reading: " << filename << std::endl;
    }
    inputFile.close();
    return tensor;
}

// This is WIP, not yet working
// Explanation (UKL): The function doesn't write anything to the file, but it doesn't throw any errors either.
// Writes a tensor to file.
template <Arithmetic ComponentType>
void writeTensorToFile(const Tensor<ComponentType>& tensor, const std::string& filename)
{
    // Open the file in binary mode for writing
    std::ofstream outFile(filename);

    if (outFile.is_open())
    {
        // Write the rank of the tensor to the file
        size_t rank = tensor.rank();
        outFile<<rank<<"\n";

        // Write the shape of the tensor to the file
        for(const auto& s : tensor.shape()){
            outFile<<s<<"\n";
        }

        // Write the tensor elements to the file
        std::vector<size_t> index(tensor.rank(),0);
        for (size_t i = 0; i < tensor.numElements(); ++i) {
            outFile<<tensor(index)<<"\n";
            // Move to the next index
            for (int j = tensor.rank()-1; j >= 0;j--) {
                if (++index[j] < tensor.shape()[j]) {
                    break;
                }
                index[j] = 0;
            }
        }
        outFile.close();
    }
    else
    {
        // Handle error: unable to open the file
        std::cerr << "Error: Unable to open file for writing: " << filename << std::endl;
        return;
    }
}
