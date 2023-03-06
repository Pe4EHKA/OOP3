#include <iostream>
#include <cassert>

template <class T>
class MyStorage {
private:
    int size;
    T* data;
public:
    
    MyStorage() : size(0), data(nullptr) {}
    
    MyStorage(int size) : size(size) {
        assert(size >= 0);  // Если условие не выполняется = ошибка.
        if (size > 0) {
            data = new T[size];
        }
    }
    
    ~MyStorage() {
        delete data;
    }
    
    void clear() {
        delete data;
        data = nullptr;  // Чтобы не указывал на освобожденную память(никуда).
        size = 0;
    }
    
    void getsize() {
        return size;
    }
    
    int& operator[] (int index) {
        assert(size >= 0 && index <= size);
        return data[index];
    }
    
};

int main() {
    std::cout << "Hello, World!\n";
    return 0;
}
