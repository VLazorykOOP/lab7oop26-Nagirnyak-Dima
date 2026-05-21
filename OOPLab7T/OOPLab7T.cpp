#include <iostream>
#include <cstring>
#include <fstream>
#include <random>
#include <string>
#include <clocale>

template <typename T>
void swapFirstMinMax(T* arr, int size) {
    if (size <= 1) {
        return;
    }
    int minIdx = 0;
    int maxIdx = 0;
    for (int i = 1; i < size; ++i) {
        if (arr[i] < arr[minIdx]) {
            minIdx = i;
        }
        if (arr[i] > arr[maxIdx]) {
            maxIdx = i;
        }
    }
    T temp = arr[minIdx];
    arr[minIdx] = arr[maxIdx];
    arr[maxIdx] = temp;
}

template <>
void swapFirstMinMax<char*>(char** arr, int size) {
    if (size <= 1) {
        return;
    }
    int minIdx = 0;
    int maxIdx = 0;
    for (int i = 1; i < size; ++i) {
        if (std::strcmp(arr[i], arr[minIdx]) < 0) {
            minIdx = i;
        }
        if (std::strcmp(arr[i], arr[maxIdx]) > 0) {
            maxIdx = i;
        }
    }
    char* temp = arr[minIdx];
    arr[minIdx] = arr[maxIdx];
    arr[maxIdx] = temp;
}

template <typename T>
void insertionSort(T* arr, int size) {
    for (int i = 1; i < size; ++i) {
        T key = arr[i];
        int j = i - 1;
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key;
    }
}

template <>
void insertionSort<char*>(char** arr, int size) {
    for (int i = 1; i < size; ++i) {
        char* key = arr[i];
        int j = i - 1;
        while (j >= 0 && std::strcmp(arr[j], key) > 0) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key;
    }
}

template <typename T>
struct Node {
    T data;
    Node* next;
    Node* prev;
    Node(const T& val) {
        data = val;
        next = nullptr;
        prev = nullptr;
    }
};

template <typename T>
class QueueIterator {
private:
    Node<T>* current;
public:
    QueueIterator(Node<T>* node) {
        current = node;
    }
    T& operator*() {
        return current->data;
    }
    QueueIterator& operator++() {
        if (current != nullptr) {
            current = current->next;
        }
        return *this;
    }
    QueueIterator& operator--() {
        if (current != nullptr) {
            current = current->prev;
        }
        return *this;
    }
    bool operator!=(const QueueIterator& other) const {
        return current != other.current;
    }
    bool operator==(const QueueIterator& other) const {
        return current == other.current;
    }
};

template <typename T>
class Queue {
private:
    Node<T>* head;
    Node<T>* tail;
    int count;
public:
    Queue() {
        head = nullptr;
        tail = nullptr;
        count = 0;
    }
    ~Queue() {
        while (!isEmpty()) {
            pop();
        }
    }
    bool isEmpty() const {
        return head == nullptr;
    }
    int size() const {
        return count;
    }
    void push(const T& val) {
        Node<T>* newNode = new Node<T>(val);
        if (isEmpty()) {
            head = newNode;
            tail = newNode;
        }
        else {
            tail->next = newNode;
            newNode->prev = tail;
            tail = newNode;
        }
        count++;
    }
    T pop() {
        if (isEmpty()) {
            throw std::runtime_error("Empty");
        }
        Node<T>* temp = head;
        T val = temp->data;
        head = head->next;
        if (head != nullptr) {
            head->prev = nullptr;
        }
        else {
            tail = nullptr;
        }
        delete temp;
        count--;
        return val;
    }
    QueueIterator<T> begin() {
        return QueueIterator<T>(head);
    }
    QueueIterator<T> end() {
        return QueueIterator<T>(nullptr);
    }
};

int main() {
    std::setlocale(LC_ALL, "ukr");

    int choice = 0;
    while (true) {
        std::cout << "\n=== МЕНЮ ЛАБОРАТОРНОЇ РОБОТИ 7 ===\n";
        std::cout << "1. Завдання 1.3 та 2.3: Введення з клавіатури\n";
        std::cout << "2. Завдання 1.3 та 2.3: Генерація випадкових чисел\n";
        std::cout << "3. Завдання 1.3 та 2.3: Специфікація шаблону\n";
        std::cout << "4. Завдання 3.3 та 4.3: Робота з чергою та ітератором\n";
        std::cout << "5. Вихід\n";
        std::cout << "Оберіть дію: ";
        std::cin >> choice;

        if (choice == 5) {
            break;
        }

        if (choice == 1) {
            int sizeInt = 5;
            int* arrInt = new int[sizeInt];
            std::cout << "Введіть " << sizeInt << " чисел: ";
            for (int i = 0; i < sizeInt; ++i) {
                std::cin >> arrInt[i];
            }
            std::cout << "Старт: ";
            for (int i = 0; i < sizeInt; ++i) {
                std::cout << arrInt[i] << " ";
            }
            std::cout << "\n";
            swapFirstMinMax(arrInt, sizeInt);
            std::cout << "Заміна: ";
            for (int i = 0; i < sizeInt; ++i) {
                std::cout << arrInt[i] << " ";
            }
            std::cout << "\n";
            insertionSort(arrInt, sizeInt);
            std::cout << "Сорт: ";
            for (int i = 0; i < sizeInt; ++i) {
                std::cout << arrInt[i] << " ";
            }
            std::cout << "\n";
            delete[] arrInt;
        }
        else if (choice == 2) {
            std::random_device rd;
            std::mt19937 gen(rd());
            std::uniform_real_distribution<double> dis(1.0, 100.0);
            int sizeDouble = 5;
            double* arrDouble = new double[sizeDouble];
            for (int i = 0; i < sizeDouble; ++i) {
                arrDouble[i] = dis(gen);
            }
            std::cout << "Рандом: ";
            for (int i = 0; i < sizeDouble; ++i) {
                std::cout << arrDouble[i] << " ";
            }
            std::cout << "\n";
            swapFirstMinMax(arrDouble, sizeDouble);
            std::cout << "Заміна: ";
            for (int i = 0; i < sizeDouble; ++i) {
                std::cout << arrDouble[i] << " ";
            }
            std::cout << "\n";
            insertionSort(arrDouble, sizeDouble);
            std::cout << "Сорт: ";
            for (int i = 0; i < sizeDouble; ++i) {
                std::cout << arrDouble[i] << " ";
            }
            std::cout << "\n";
            delete[] arrDouble;
        }
        else if (choice == 3) {
            int sizeStr = 4;
            char** arrStr = new char* [sizeStr];
            arrStr[0] = const_cast<char*>("cherry");
            arrStr[1] = const_cast<char*>("apricot");
            arrStr[2] = const_cast<char*>("watermelon");
            arrStr[3] = const_cast<char*>("banana");
            std::cout << "Рядки: ";
            for (int i = 0; i < sizeStr; ++i) {
                std::cout << arrStr[i] << " ";
            }
            std::cout << "\n";
            swapFirstMinMax(arrStr, sizeStr);
            std::cout << "Заміна: ";
            for (int i = 0; i < sizeStr; ++i) {
                std::cout << arrStr[i] << " ";
            }
            std::cout << "\n";
            insertionSort(arrStr, sizeStr);
            std::cout << "Сорт: ";
            for (int i = 0; i < sizeStr; ++i) {
                std::cout << arrStr[i] << " ";
            }
            std::cout << "\n";
            delete[] arrStr;
        }
        else if (choice == 4) {
            Queue<std::string> stringQueue;
            std::ofstream outFile("lab7_input.txt");
            if (outFile.is_open()) {
                outFile << "Елемент_1\n";
                outFile << "Елемент_2\n";
                outFile << "Елемент_3\n";
                outFile << "Елемент_4\n";
                outFile.close();
            }
            std::ifstream inFile("lab7_input.txt");
            if (inFile.is_open()) {
                std::string fileData;
                while (inFile >> fileData) {
                    stringQueue.push(fileData);
                }
                inFile.close();
            }
            std::cout << "Ітератор:\n";
            QueueIterator<std::string> it = stringQueue.begin();
            QueueIterator<std::string> itEnd = stringQueue.end();
            while (it != itEnd) {
                std::cout << " -> " << *it << "\n";
                ++it;
            }
            std::cout << "\nЧерга:\n";
            while (!stringQueue.isEmpty()) {
                std::string topVal = stringQueue.pop();
                std::cout << "Поп: " << topVal << "\n";
            }
        }
    }
    return 0;
}