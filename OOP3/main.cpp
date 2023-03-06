#include <iostream>
#include <cassert>
#include <cstdlib>
#include <ctime>

template <class T>
class MyStorage {
private:
    int size;
    T* data;
    
    void MergeSort(T *arr, int a_len) {
        if (a_len <= 1) {
            return;
        }
        int firstLen = a_len / 2;
        int secondLen = a_len - firstLen;
        MergeSort(arr, firstLen);
        MergeSort(arr + firstLen, secondLen);  // arr + firstlen -> вернется массив после первых firstLen элементов
        T *c = new T[a_len];
        Merge(arr, firstLen, arr + firstLen, secondLen, c);
        for (int i = 0; i < a_len; ++i) {
            arr[i] = c[i];
        }
        delete[] c;
    }
    
    void Merge(const T *arr, int a_len, const T *b, int b_len, T *c) {
        int i = 0;
        int j = 0;
        while(i < a_len && j < b_len) {
            if (arr[i] <= b[j]) {
                c[i + j] = arr[i];
                ++i;
            } else {
                c[i + j] = b[j];
                ++j;
            }
        }
        while (i < a_len) {
            c[i + j] = arr[i];
            ++i;
        }
        while (j < b_len) {
            c[i + j] = b[j];
            ++j;
        }
        
    }
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
    
    T pop(int index) {  // Уничтожение объекта. Возвращаем объект для использования, но освобождаем память из под него.
        assert(index >= 0 && index <= size);  // Проверяем index, не выпадает ли он.
        T to_return = data[index];
        if (size == 1) {  // Если размер массива 1, очищаем его.
            clear();
            return to_return;
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
        return to_return;
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
    
    void sort() {
        MergeSort(data, size);
    }
    
    T mul() {  // Умножение элементов массива
        
    }
    
    
};

int random(int a, int b) {
    if (a > 0) return a + rand() % (b - a);
    else return a + rand() % (a * -1 + b);
}



int main() {
    
    srand(time(NULL));
    
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
    for (int i = 0; i < 3; ++i) {
        std::cout << "----Элементы массива---- при " << i + 1 << " последовательной вставки" << std::endl;
        arr.push_front(random(25, 50));
        arr.print();
        arr.insert_by_index(random(1, 5), arr.get_size() - random(0, arr.get_size()));
        arr.print();
        arr.push_back(random(100, 150));
        arr.print();
    }
    std::cout << std::endl;
    std::cout << "----Массив после сортировки----" << std::endl;
    arr.sort();
    arr.print();
    std::cout << "-------------------------------" << std::endl;


    std::cout << "----Случайное удаление элементов----" << std::endl;
    std::cout << "------------Массив------------" << std::endl;
    arr.print();
    std::cout << "------------------------------" << std::endl;
    std::cout << std::endl;
    int n = arr.get_size();
    int index = 0;
    for (int i = 0; i < n; ++i) {
        std::cout << "---Массив после " << i + 1 << " удаления элемента---" << std::endl;
        index = random(0, arr.get_size());
        arr.remove_by_index(index);
        std::cout << "---Удален элемент под индексом " << index << " ---" << std::endl;
        arr.print();
    }
    if (arr.empty()) {
        std::cout << "Empty!" << std::endl;
    }
    int num_of_functions = 0;
    int key = 0;
    std::cout << "Введите кол-во выполнений функций ";
    std::cin >> num_of_functions;
    std::cout << std::endl;
    for (int i = 0; i < num_of_functions; ++i) {
        key = random(1, 4);
        if (key == 1) {
            std::cout << "---Вызвался метод push_back--- Функция под номером - " << i + 1 <<  std::endl;
            arr.push_back(random(0, 100));
            std::cout << "Итоговый массив: ";
            arr.print();
        }
        else if (key == 2) {
            std::cout << "---Вызвался метод push_front--- Функция под номером - " << i + 1<< std::endl;
            arr.push_front(random(100, 200));
            std::cout << "Итоговый массив: ";
            arr.print();
        }
        else if (key == 3 && !arr.empty()) {
            key = random(0, arr.get_size());
            std::cout << "---Вывод элемента рандомного индекса--- Индекс = " << key << " Функция под номером - " << i + 1<< std::endl;
            std::cout << arr[key] << std::endl;
            std::cout << "Итоговый массив: ";
            arr.print();
        }
        else if (key == 4 && !arr.empty()) {
            key = random(0, arr.get_size());
            std::cout << "---Уничтожение рандомного элемента из массива--- Индекс = " << key << " Функция под номером - " << i  + 1 << std::endl;
            std::cout << arr.pop(key) << std::endl;
            std::cout << "Итоговый массив: ";
            arr.print();
        }
    }
    std::cout << "---------Уничтожение рандомного элемента из массива---------" << std::endl;
    arr.clear();
    arr.push_back(190);
    arr.push_front(45);
    std::cout << "Итоговый массив: ";
    arr.print();
    std::cout << arr.pop(random(0, arr.get_size())) << std::endl;
    std::cout << "Массив после метода pop: ";
    arr.print();
    
    //std::cout << "----Элементы массива----" << std::endl;
    //arr.print();
    
    return 0;
}
