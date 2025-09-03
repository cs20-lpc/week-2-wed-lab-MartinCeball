#include <string>
#include <iostream>


template <typename T>
ArrayList<T>::ArrayList(int size) {
    maxSize = (size > 0) ? size : 100; // Use provided size or default to 100
    this->length = 0;
    buffer = new T[maxSize];
}


template <typename T>
ArrayList<T>::~ArrayList() {
    delete[] buffer;
}


template <typename T>
void ArrayList<T>::copy(const ArrayList<T>& other) {
    this->maxSize = other.maxSize;
    this->length = other.length;
    this->buffer = new T[this->maxSize];
    for (int i = 0; i < this->length; i++) {
        this->buffer[i] = other.buffer[i];
    }
}


template <typename T>
ArrayList<T>::ArrayList(const ArrayList<T>& other) {
    copy(other);
}


template <typename T>
ArrayList<T>& ArrayList<T>::operator=(const ArrayList<T>& other) {
    if (this != &other) { // Prevent self-assignment
        delete[] buffer;  // Free old memory
        copy(other);      // Copy new data
    }
    return *this;
}




template <typename T>
void ArrayList<T>::append(const T& elem) {
    if (isFull()) {
        throw string("append: error, list is full");
    }
    buffer[this->length] = elem;
    this->length++;
}


template <typename T>
void ArrayList<T>::insert(int position, const T& elem) {
    if (isFull()) {
        throw string("insert: error, list is full");
    }
    // A new element can be inserted at the end (position == length)
    if (position < 0 || position > this->length) {
        throw string("insert: error, position out of bounds");
    }

    // Shift elements to the right to make space
    for (int i = this->length; i > position; i--) {
        buffer[i] = buffer[i - 1];
    }

    buffer[position] = elem;
    this->length++;
}


template <typename T>
void ArrayList<T>::remove(int position) {
    if (position < 0 || position >= this->length) {
        throw string("remove: error, position out of bounds");
    }

    // Shift elements to the left to fill the gap
    for (int i = position; i < this->length - 1; i++) {
        buffer[i] = buffer[i + 1];
    }
    this->length--;
}


template <typename T>
void ArrayList<T>::replace(int position, const T& elem) {
    if (position < 0 || position >= this->length) {
        throw string("replace: error, position out of bounds");
    }
    buffer[position] = elem;
}


template <typename T>
T ArrayList<T>::getElement(int position) const {
    if (position < 0 || position >= this->length) {
        throw string("getElement: error, position out of bounds");
    }
    return buffer[position];
}


template <typename T>
void ArrayList<T>::clear() {
    this->length = 0;
}



template <typename T>
int ArrayList<T>::getLength() const {
    return this->length;
}


template <typename T>
int ArrayList<T>::getMaxSize() const {
    return this->maxSize;
}


template <typename T>
bool ArrayList<T>::isEmpty() const {
    return this->length == 0;
}


template <typename T>
bool ArrayList<T>::isFull() const {
    return this->length == maxSize;
}


template <typename U>
ostream& operator<<(ostream& out, const ArrayList<U>& list) {
    if (list.isEmpty()) {
        out << "List is empty, no elements to display.\n";
    } else {
        for (int i = 0; i < list.getLength(); i++) {
            out << list.getElement(i) << " ";
        }
        out << "\n";
    }
    return out;
}
