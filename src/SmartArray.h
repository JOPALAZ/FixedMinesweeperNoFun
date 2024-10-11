#pragma once
#include <cstring>
#include <iostream>
#include <string>
template <class DataType> class SmartArray {
public:
  template <typename T> int find(T &data) {
    for (unsigned i{}; i < size; ++i) {
      if (this->data[i] == data) {
        return i;
      }
    }
    return -1;
  }
  unsigned getSize() const { return size; }
  SmartArray() { this->data = new DataType[1]; }
  template <typename T> void push_front(T &data) {
    if (capacity == size)
      this->resize(capacity * 2);
    for (unsigned i{size}; i > 1; --i) {
      this->data[i] = this->data[i - 1];
    }
    T buf = data;
    this->data[0] = buf;
    size++;
  }
  template <typename T> void push_back(T &data) {
    if (capacity == size)
      this->resize(capacity * 2);
    T buf = data;
    this->data[size++] = buf;
  }
  template <typename T> void push_front(const T &data) {
    if (capacity == size)
      this->resize(capacity * 2);
    for (unsigned i{size}; i > 1; --i) {
      this->data[i] = this->data[i - 1];
    }
    T buf = data;
    this->data[0] = buf;
    size++;
  }
  template <typename T> void push_back(const T &data) {
    if (capacity == size)
      this->resize(capacity * 2);
    this->data[size++] = data;
  }
  DataType &operator[](const unsigned &u) { return data[u]; }
  void clear() {
    if (data) {
      delete[] data;
    }
    capacity = 1;
    data = new DataType[capacity];
    size = 0;
  }
  ~SmartArray() {
    if (this->data) {
      delete[] this->data;
    }
  }

private:
  void resize(unsigned capacity) {

    try {
      DataType *buf = new DataType[capacity];
      if (capacity > size) {
        for (unsigned i{}; i < this->size; ++i) {
          buf[i] = data[i];
        }
      } else {
        throw std::runtime_error(
            "WHEN RESIZING CAPACITY HAS TO BE HIGHER THAN SIZE");
      }
      if (this->data) {
        delete[] data;
      }
      this->data = buf;
      buf = nullptr;
      this->capacity = capacity;
    } catch (std::bad_alloc &a) {
      std::cout << "ALLOCATION FAILED " << a.what() << '\n';
    } catch (std::exception &e) {
      std::cout << "SOMETHING WENT WRONG " << e.what() << '\n';
    }
  }
  DataType *data;
  unsigned size = 0;
  unsigned capacity = 1;
};
