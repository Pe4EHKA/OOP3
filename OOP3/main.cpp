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
        delete[] data;
    }
    
    void clear() {  //
        delete data;
        data = nullptr;  // Чтобы не указывал на освобожденную память(никуда).
        size = 0;
    }
    
    int get_size() {
        return size;
    }
    
    int& operator[] (int index) {  // Возвращаем ссылку на объект, так как масси динамический.
        assert(size >= 0 && index <= size);
        return data[index];
    }
    
    void resize(int new_size) {  // Метод изменяющий размер массива, но элементы массива не удаляются
        if (new_size == size) {  // Если размер уже такой же, заканчиваем.
            return;
        }
        if (new_size <= 0) {  // Если новый размер <= 0, то очищаем его полностью.
            clear();
            return;
        }
        T* new_data = new T[new_size];
        if (size > 0) {
            int num_of_copies = new_size > size ? size : new_size;
            for (int i = 0; i < num_of_copies; ++i) {
                new_data[i] = data[i];
            }
        }
        delete[] data;  // Освобождаем память, занятую старым массивом.
        
        data = new_data;  // Меняем указатель на новую оласть памяти.
        size = new_size;  // Присваеваем размеру массива новое значение.
    }
    
    void reallocate(int new_size) {  // Быстрая очистка массива с изменением размера.
        clear();
        if (new_size <= 0) {
            return;
        }
        data = new T[new_size];
        size = new_size;
    }
    
    void insert_by_index(T element, int index) {
        assert(index >= 0 && index <= size);  // Проверяем index, не выпадает ли он.
        T* new_data = new T[size + 1];
        for (int i = 0; i < index; ++i) {
            new_data[i] = data[i];
        }
        new_data[index] = element;
        for (int i = index; i < size; ++i) {
            new_data[i + 1] = data[i];
        }
        delete[] data;  // Удаляем старый массив
        data = new_data;
        ++size;
    }
    
    void remove_by_index(int index) {
        assert(index >= 0 && index <= size);  // Проверяем index, не выпадает ли он.
        if (size == 1) {  // Если размер массива 1, очищаем его.
            clear();
            return;
        }
        T* new_data = new T[size - 1];
        for (int i = 0; i < index; ++i) {  // Копируем элементы до индекса
            new_data[i] = data[i];
        }
        for (int i = index + 1; i < size; ++i) {
            new_data[i - 1] = data[i];
        }
        delete[] data;
        data = new_data;
        --size;
    }
    
    void push_front(T element) {
        insert_by_index(element, 0);
    }
    void push_back(T element) {
        insert_by_index(element, size);
    }
    
    bool empty() {
        return size == 0 ? true : false;
    }
    
    void print() {
        for (int i = 0; i < size; ++i) {
            std::cout << data[i] << " ";
        }
        std::cout << std::endl;
    }
    
    
};

int main() {
    
    MyStorage<int> arr;
    std::cout << "Пустой ли массив?" << std::endl;
    std::cout << arr.empty() << std::endl;
    arr.push_back(10);
    std::cout << "----Элементы массива----" << std::endl;
    arr.print();
    
    arr.push_back(20);
    std::cout << "----Элементы массива----" << std::endl;
    arr.print();
    
    arr.push_front(4312);
    std::cout << "----Элементы массива----" << std::endl;
    arr.print();
    
    std::cout << "Пустой ли массив?" << std::endl;
    std::cout << arr.empty() << std::endl;
    
    //std::cout << "----Элементы массива----" << std::endl;
    //arr.print();
    
    
    return 0;
}
