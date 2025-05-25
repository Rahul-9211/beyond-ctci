#include <iostream>
#include <stdexcept>
using namespace std;

class DynamicArray {
private:
    int* data;
    int capacity;
    int length;

    void resize() {
        int newCapacity = capacity * 2;
        int* newData = new int[newCapacity];
        for (int i = 0; i < length; ++i) {
            newData[i] = data[i];
        }
        delete[] data;
        data = newData;
        capacity = newCapacity;
    }

public:
    DynamicArray(int initialCapacity = 4) {
        capacity = initialCapacity;
        data = new int[capacity];
        length = 0;
    }

    ~DynamicArray() {
        delete[] data;
    }

    void append(int x) {
        if (length == capacity) {
            resize();
        }
        data[length++] = x;
    }

    int get(int i) const {
        if (i < 0 || i >= length) {
            throw out_of_range("Index out of bounds");
        }
        return data[i];
    }

    void set(int i, int x) {
        if (i < 0 || i >= length) {
            throw out_of_range("Index out of bounds");
        }
        data[i] = x;
    }

    int size() const {
        return length;
    }

    void pop_back() {
        if (length == 0) {
            throw underflow_error("Array is empty");
        }
        if((length/capacity)*100 <= 50){
            capacity = capacity/2;
        }
        --length;

    }

    int pop(int i) {
        if (i < 0 || i >= length) {
            throw out_of_range("Index out of bounds");
        }
        int removed = data[i];
        for (int j = i; j < length - 1; ++j) {
            data[j] = data[j + 1];
        }
        --length;
        return removed;
    }

    bool contains(int x) const {
        for (int i = 0; i < length; ++i) {
            if (data[i] == x) return true;
        }
        return false;
    }

    void insert(int i, int x) {
        if (i < 0 || i > length) {
            throw out_of_range("Index out of bounds");
        }
        if (length == capacity) {
            resize();
        }
        for (int j = length; j > i; --j) {
            data[j] = data[j - 1];
        }
        data[i] = x;
        ++length;
    }

    int remove(int x) {
        for (int i = 0; i < length; ++i) {
            if (data[i] == x) {
                pop(i);
                return i;
            }
        }
        return -1;
    }
};


int main() {
    DynamicArray d;
    d.append(1);
    d.append(2);
    d.append(3);
    d.insert(1, 99);         // [1, 99, 2, 3]
    d.set(2, 55);            // [1, 99, 55, 3]
    d.remove(99);            // [1, 55, 3]
    cout << d.get(1) << "\n";  // prints 55
    cout << d.contains(3) << "\n";  // prints 1 (true)
    cout << d.pop(0) << "\n";      // prints 1
    cout << d.size() << "\n";      // prints 2
}
