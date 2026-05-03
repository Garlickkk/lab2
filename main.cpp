#include <iostream>
#include <string>
#include <sstream>
#include <limits>
#include <vector>
#include "dynamic_array.hpp"
#include "linked_list.hpp"
#include "array_sequence.hpp"
#include "list_sequence.hpp"
#include "bit_sequence.hpp"
#include "map_reduce_tasks.hpp"

void runAllTests();

template <class T>
std::ostream& operator<<(std::ostream& os, const Sequence<T>& seq) {
    os << "[";
    for (int i = 0; i < seq.GetLength(); i++) {
        if (i > 0) os << ", ";
        os << seq.Get(i);
    }
    os << "]";
    return os;
}

inline void printBits(std::ostream& os, const BitSequence& seq) {
    for (int i = 0; i < seq.GetLength(); i++) {
        os << (seq.Get(i) ? '1' : '0');
    }
}

Sequence<int>* currentIntSeq = nullptr;
MutableBitSequence* currentBitSeq = nullptr;

enum SeqType {
    ARRAY_MUTABLE,
    ARRAY_IMMUTABLE,
    LIST_MUTABLE,
    LIST_IMMUTABLE,
    BIT_SEQUENCE
};

SeqType currentSeqType = ARRAY_MUTABLE;
bool isBitMode = false;

void selectInitialType() {
    std::cout << "\n========================================\n";
    std::cout << "   ВЫБОР ТИПА ПОСЛЕДОВАТЕЛЬНОСТИ\n";
    std::cout << "========================================\n";
    std::cout << "1. MutableArraySequence   (изменяемый массив)\n";
    std::cout << "2. ImmutableArraySequence (неизменяемый массив)\n";
    std::cout << "3. MutableListSequence    (изменяемый список)\n";
    std::cout << "4. ImmutableListSequence  (неизменяемый список)\n";
    std::cout << "5. BitSequence            (битовая последовательность)\n";
    std::cout << "==========================\n";
    std::cout << "Ваш выбор: ";

    int choice;
    std::cin >> choice;

    if (currentIntSeq != nullptr) {
        delete currentIntSeq;
        currentIntSeq = nullptr;
    }
    if (currentBitSeq != nullptr) {
        delete currentBitSeq;
        currentBitSeq = nullptr;
    }

    switch (choice) {
        case 1:
            currentSeqType = ARRAY_MUTABLE;
            isBitMode = false;
            currentIntSeq = new MutableArraySequence<int>();
            std::cout << "\nСоздана пустая MutableArraySequence<int>\n";
            break;
        case 2:
            currentSeqType = ARRAY_IMMUTABLE;
            isBitMode = false;
            currentIntSeq = new ImmutableArraySequence<int>();
            std::cout << "\nСоздана пустая ImmutableArraySequence<int>\n";
            break;
        case 3:
            currentSeqType = LIST_MUTABLE;
            isBitMode = false;
            currentIntSeq = new MutableListSequence<int>();
            std::cout << "\nСоздана пустая MutableListSequence<int>\n";
            break;
        case 4:
            currentSeqType = LIST_IMMUTABLE;
            isBitMode = false;
            currentIntSeq = new ImmutableListSequence<int>();
            std::cout << "\nСоздана пустая ImmutableListSequence<int>\n";
            break;
        case 5:
            currentSeqType = BIT_SEQUENCE;
            isBitMode = true;
            currentBitSeq = new MutableBitSequence();
            std::cout << "\nСоздана пустая MutableBitSequence\n";
            break;
        default:
            std::cout << "\nНеверный выбор! Создана последовательность по умолчанию.\n";
            currentSeqType = ARRAY_MUTABLE;
            isBitMode = false;
            currentIntSeq = new MutableArraySequence<int>();
    }
}

void printMenu() {
    std::cout << "\n========== МЕНЮ ==========\n";
    std::cout << "1. Создать новую последовательность (int)\n";
    std::cout << "2. Показать текущую последовательность\n";
    std::cout << "3. Добавить элемент в конец (Append)\n";
    std::cout << "4. Добавить элемент в начало (Prepend)\n";
    std::cout << "5. Вставить элемент по индексу (InsertAt)\n";
    std::cout << "6. Получить элемент по индексу (Get)\n";
    std::cout << "7. Получить подпоследовательность (GetSubsequence)\n";
    std::cout << "8. Объединить с другой последовательностью (Concat)\n";
    std::cout << "9. Map (применить функцию ко всем элементам)\n";
    std::cout << "10. Where (фильтрация)\n";
    std::cout << "11. Reduce (свёртка)\n";
    std::cout << "12. Zip (поэлементная операция с другой последовательностью)\n";
    std::cout << "13. Skip (пропустить N элементов)\n";
    std::cout << "14. Take (взять N элементов)\n";
    std::cout << "15. Работа с BitSequence\n";
    std::cout << "16. Map-Reduce задачи (П-задачи)\n";
    std::cout << "17. Запустить все тесты\n";
    std::cout << "0. Выход\n";
    std::cout << "==========================\n";
    std::cout << "Текущий тип: ";
    switch (currentSeqType) {
        case ARRAY_MUTABLE:   std::cout << "MutableArraySequence"; break;
        case ARRAY_IMMUTABLE: std::cout << "ImmutableArraySequence"; break;
        case LIST_MUTABLE:    std::cout << "MutableListSequence"; break;
        case LIST_IMMUTABLE:  std::cout << "ImmutableListSequence"; break;
        case BIT_SEQUENCE:    std::cout << "BitSequence"; break;
    }
    std::cout << "\n==========================\n";
    std::cout << "Выберите действие: ";
}

void printBitMenu() {
    std::cout << "\n========== BitSequence ==========\n";
    std::cout << "1. Создать BitSequence из строки (например: 10110)\n";
    std::cout << "2. Показать текущую BitSequence\n";
    std::cout << "3. Append бит\n";
    std::cout << "4. Prepend бит\n";
    std::cout << "5. InsertAt бит\n";
    std::cout << "6. Get бит по индексу\n";
    std::cout << "7. Побитовое AND с другой BitSequence\n";
    std::cout << "8. Побитовое OR с другой BitSequence\n";
    std::cout << "9. Побитовое XOR с другой BitSequence\n";
    std::cout << "10. Побитовое NOT\n";
    std::cout << "11. Получить длину\n";
    std::cout << "0. Вернуться в главное меню\n";
    std::cout << "=================================\n";
    std::cout << "Выберите действие: ";
}

void createSequence() {
    std::cout << "\n--- Создание последовательности (int) ---\n";
    std::cout << "Выберите тип:\n";
    std::cout << "1. MutableArraySequence\n";
    std::cout << "2. ImmutableArraySequence\n";
    std::cout << "3. MutableListSequence\n";
    std::cout << "4. ImmutableListSequence\n";
    std::cout << "Ваш выбор: ";

    int typeChoice;
    std::cin >> typeChoice;

    std::cout << "Введите элементы через пробел (Enter для завершения): ";
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::string line;
    std::getline(std::cin, line);
    std::stringstream ss(line);

    if (currentIntSeq != nullptr) {
        delete currentIntSeq;
        currentIntSeq = nullptr;
    }

    int val;
    std::vector<int> items;
    while (ss >> val) {
        items.push_back(val);
    }

    switch (typeChoice) {
        case 1:
            if (items.empty()) {
                currentIntSeq = new MutableArraySequence<int>();
            } else {
                currentIntSeq = new MutableArraySequence<int>(items.data(), items.size());
            }
            currentSeqType = ARRAY_MUTABLE;
            isBitMode = false;
            std::cout << "Создана MutableArraySequence\n";
            break;
        case 2:
            if (items.empty()) {
                currentIntSeq = new ImmutableArraySequence<int>();
            } else {
                currentIntSeq = new ImmutableArraySequence<int>(items.data(), items.size());
            }
            currentSeqType = ARRAY_IMMUTABLE;
            isBitMode = false;
            std::cout << "Создана ImmutableArraySequence\n";
            break;
        case 3:
            if (items.empty()) {
                currentIntSeq = new MutableListSequence<int>();
            } else {
                currentIntSeq = new MutableListSequence<int>(items.data(), items.size());
            }
            currentSeqType = LIST_MUTABLE;
            isBitMode = false;
            std::cout << "Создана MutableListSequence\n";
            break;
        case 4:
            if (items.empty()) {
                currentIntSeq = new ImmutableListSequence<int>();
            } else {
                currentIntSeq = new ImmutableListSequence<int>(items.data(), items.size());
            }
            currentSeqType = LIST_IMMUTABLE;
            isBitMode = false;
            std::cout << "Создана ImmutableListSequence\n";
            break;
        default:
            std::cout << "Неверный выбор!\n";
    }

    if (currentIntSeq != nullptr) {
        std::cout << "Текущая последовательность: " << *currentIntSeq << std::endl;
    }
}

void showSequence() {
    if (isBitMode) {
        if (currentBitSeq == nullptr) {
            std::cout << "BitSequence не создана. Сначала выполните пункт 1 в меню BitSequence.\n";
            return;
        }
        std::cout << "Текущая BitSequence: ";
        printBits(std::cout, *currentBitSeq);
        std::cout << " (длина: " << currentBitSeq->GetLength() << ")\n";
    } else {
        if (currentIntSeq == nullptr) {
            std::cout << "Последовательность не создана. Сначала выполните пункт 1.\n";
            return;
        }
        std::cout << "Текущая последовательность: " << *currentIntSeq << std::endl;
        std::cout << "Длина: " << currentIntSeq->GetLength() << std::endl;
        if (currentIntSeq->GetLength() > 0) {
            std::cout << "Первый элемент: " << currentIntSeq->GetFirst() << std::endl;
            std::cout << "Последний элемент: " << currentIntSeq->GetLast() << std::endl;
        }
    }
}

void appendElement() {
    if (isBitMode) {
        if (currentBitSeq == nullptr) {
            std::cout << "BitSequence не создана.\n";
            return;
        }
        int bit;
        std::cout << "Введите бит (0 или 1): ";
        std::cin >> bit;
        currentBitSeq->Append(bit != 0);
        std::cout << "Результат: ";
        printBits(std::cout, *currentBitSeq);
        std::cout << std::endl;
    } else {
        if (currentIntSeq == nullptr) {
            std::cout << "Последовательность не создана.\n";
            return;
        }
        int val;
        std::cout << "Введите значение для добавления в конец: ";
        std::cin >> val;

        Sequence<int>* newSeq = currentIntSeq->Append(val);
        if (newSeq != currentIntSeq) {
            delete currentIntSeq;
            currentIntSeq = newSeq;
        }
        std::cout << "Результат: " << *currentIntSeq << std::endl;
    }
}

void prependElement() {
    if (isBitMode) {
        if (currentBitSeq == nullptr) {
            std::cout << "BitSequence не создана.\n";
            return;
        }
        int bit;
        std::cout << "Введите бит (0 или 1): ";
        std::cin >> bit;
        currentBitSeq->Prepend(bit != 0);
        std::cout << "Результат: ";
        printBits(std::cout, *currentBitSeq);
        std::cout << std::endl;
    } else {
        if (currentIntSeq == nullptr) {
            std::cout << "Последовательность не создана.\n";
            return;
        }
        int val;
        std::cout << "Введите значение для добавления в начало: ";
        std::cin >> val;

        Sequence<int>* newSeq = currentIntSeq->Prepend(val);
        if (newSeq != currentIntSeq) {
            delete currentIntSeq;
            currentIntSeq = newSeq;
        }
        std::cout << "Результат: " << *currentIntSeq << std::endl;
    }
}

void insertAt() {
    if (isBitMode) {
        if (currentBitSeq == nullptr) {
            std::cout << "BitSequence не создана.\n";
            return;
        }
        int index, bit;
        std::cout << "Введите индекс: ";
        std::cin >> index;
        std::cout << "Введите бит (0 или 1): ";
        std::cin >> bit;

        try {
            currentBitSeq->InsertAt(bit != 0, index);
            std::cout << "Результат: ";
            printBits(std::cout, *currentBitSeq);
            std::cout << std::endl;
        } catch (const std::exception& e) {
            std::cout << "Ошибка: " << e.what() << std::endl;
        }
    } else {
        if (currentIntSeq == nullptr) {
            std::cout << "Последовательность не создана.\n";
            return;
        }
        int val, index;
        std::cout << "Введите индекс: ";
        std::cin >> index;
        std::cout << "Введите значение: ";
        std::cin >> val;

        try {
            Sequence<int>* newSeq = currentIntSeq->InsertAt(val, index);
            if (newSeq != currentIntSeq) {
                delete currentIntSeq;
                currentIntSeq = newSeq;
            }
            std::cout << "Результат: " << *currentIntSeq << std::endl;
        } catch (const std::exception& e) {
            std::cout << "Ошибка: " << e.what() << std::endl;
        }
    }
}

void getElement() {
    if (isBitMode) {
        if (currentBitSeq == nullptr) {
            std::cout << "BitSequence не создана.\n";
            return;
        }
        int index;
        std::cout << "Введите индекс: ";
        std::cin >> index;

        try {
            std::cout << "Бит[" << index << "] = " << currentBitSeq->Get(index) << std::endl;
        } catch (const std::exception& e) {
            std::cout << "Ошибка: " << e.what() << std::endl;
        }
    } else {
        if (currentIntSeq == nullptr) {
            std::cout << "Последовательность не создана.\n";
            return;
        }
        int index;
        std::cout << "Введите индекс: ";
        std::cin >> index;

        try {
            std::cout << "Элемент[" << index << "] = " << currentIntSeq->Get(index) << std::endl;
        } catch (const std::exception& e) {
            std::cout << "Ошибка: " << e.what() << std::endl;
        }
    }
}

void getSubsequence() {
    if (isBitMode) {
        if (currentBitSeq == nullptr) {
            std::cout << "BitSequence не создана.\n";
            return;
        }
        int start, end;
        std::cout << "Введите startIndex: ";
        std::cin >> start;
        std::cout << "Введите endIndex: ";
        std::cin >> end;

        try {
            Sequence<bool>* sub = currentBitSeq->GetSubsequence(start, end);
            std::cout << "Подпоследовательность: ";
            printBits(std::cout, *dynamic_cast<BitSequence*>(sub));
            std::cout << std::endl;
            delete sub;
        } catch (const std::exception& e) {
            std::cout << "Ошибка: " << e.what() << std::endl;
        }
    } else {
        if (currentIntSeq == nullptr) {
            std::cout << "Последовательность не создана.\n";
            return;
        }
        int start, end;
        std::cout << "Введите startIndex: ";
        std::cin >> start;
        std::cout << "Введите endIndex: ";
        std::cin >> end;

        try {
            Sequence<int>* sub = currentIntSeq->GetSubsequence(start, end);
            std::cout << "Подпоследовательность: " << *sub << std::endl;
            delete sub;
        } catch (const std::exception& e) {
            std::cout << "Ошибка: " << e.what() << std::endl;
        }
    }
}

void concatSequence() {
    if (isBitMode) {
        std::cout << "Concat для BitSequence не реализован.\n";
        return;
    }

    if (currentIntSeq == nullptr) {
        std::cout << "Текущая последовательность не создана.\n";
        return;
    }

    std::cout << "Создайте последовательность для объединения:\n";
    std::cout << "Введите элементы через пробел: ";
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::string line;
    std::getline(std::cin, line);
    std::stringstream ss(line);

    std::vector<int> items;
    int val;
    while (ss >> val) {
        items.push_back(val);
    }

    Sequence<int>* other = nullptr;
    std::cout << "Выберите тип для второй последовательности:\n";
    std::cout << "1. MutableArraySequence\n2. ImmutableArraySequence\n3. MutableListSequence\n4. ImmutableListSequence\n";
    int typeChoice;
    std::cin >> typeChoice;

    switch (typeChoice) {
        case 1:
            other = new MutableArraySequence<int>(items.data(), items.size());
            break;
        case 2:
            other = new ImmutableArraySequence<int>(items.data(), items.size());
            break;
        case 3:
            other = new MutableListSequence<int>(items.data(), items.size());
            break;
        case 4:
            other = new ImmutableListSequence<int>(items.data(), items.size());
            break;
        default:
            std::cout << "Неверный выбор\n";
            return;
    }

    try {
        Sequence<int>* result = currentIntSeq->Concat(other);
        if (result != currentIntSeq) {
            delete currentIntSeq;
            currentIntSeq = result;
        }
        std::cout << "Результат объединения: " << *currentIntSeq << std::endl;
    } catch (const std::exception& e) {
        std::cout << "Ошибка: " << e.what() << std::endl;
    }

    delete other;
}

void mapOperation() {
    if (isBitMode) {
        std::cout << "Map для BitSequence не реализован.\n";
        return;
    }

    if (currentIntSeq == nullptr) {
        std::cout << "Последовательность не создана.\n";
        return;
    }

    std::cout << "Выберите функцию Map:\n";
    std::cout << "1. Умножить на число\n";
    std::cout << "2. Прибавить число\n";
    std::cout << "3. Возвести в квадрат\n";
    std::cout << "4. Пользовательская функция (лямбда)\n";
    int choice;
    std::cin >> choice;

    std::function<int(int)> func;
    int arg;

    switch (choice) {
        case 1:
            std::cout << "Введите множитель: ";
            std::cin >> arg;
            func = [arg](int x) { return x * arg; };
            break;
        case 2:
            std::cout << "Введите слагаемое: ";
            std::cin >> arg;
            func = [arg](int x) { return x + arg; };
            break;
        case 3:
            func = [](int x) { return x * x; };
            break;
        case 4:
            std::cout << "Введите лямбда-выражение (будет использована x*2+1): ";
            func = [](int x) { return x * 2 + 1; };
            break;
        default:
            std::cout << "Неверный выбор\n";
            return;
    }

    Sequence<int>* result = currentIntSeq->Map(func);
    std::cout << "Результат Map: " << *result << std::endl;
    delete result;
}

void whereOperation() {
    if (isBitMode) {
        std::cout << "Where для BitSequence не реализован.\n";
        return;
    }

    if (currentIntSeq == nullptr) {
        std::cout << "Последовательность не создана.\n";
        return;
    }

    std::cout << "Выберите фильтр:\n";
    std::cout << "1. > N\n";
    std::cout << "2. < N\n";
    std::cout << "3. == N\n";
    std::cout << "4. Чётные\n";
    std::cout << "5. Нечётные\n";
    int choice;
    std::cin >> choice;

    std::function<bool(int)> pred;
    int arg;

    switch (choice) {
        case 1:
            std::cout << "Введите N: ";
            std::cin >> arg;
            pred = [arg](int x) { return x > arg; };
            break;
        case 2:
            std::cout << "Введите N: ";
            std::cin >> arg;
            pred = [arg](int x) { return x < arg; };
            break;
        case 3:
            std::cout << "Введите N: ";
            std::cin >> arg;
            pred = [arg](int x) { return x == arg; };
            break;
        case 4:
            pred = [](int x) { return x % 2 == 0; };
            break;
        case 5:
            pred = [](int x) { return x % 2 != 0; };
            break;
        default:
            std::cout << "Неверный выбор\n";
            return;
    }

    Sequence<int>* result = currentIntSeq->Where(pred);
    std::cout << "Результат Where: " << *result << std::endl;
    delete result;
}

void reduceOperation() {
    if (isBitMode) {
        std::cout << "Reduce для BitSequence не реализован.\n";
        return;
    }

    if (currentIntSeq == nullptr) {
        std::cout << "Последовательность не создана.\n";
        return;
    }

    std::cout << "Выберите операцию Reduce:\n";
    std::cout << "1. Сумма\n";
    std::cout << "2. Произведение\n";
    std::cout << "3. Максимум\n";
    std::cout << "4. Минимум\n";
    int choice;
    std::cin >> choice;

    std::function<int(int, int)> func;
    int init;

    switch (choice) {
        case 1:
            func = [](int a, int b) { return a + b; };
            init = 0;
            break;
        case 2:
            func = [](int a, int b) { return a * b; };
            init = 1;
            break;
        case 3:
            func = [](int a, int b) { return a > b ? a : b; };
            init = currentIntSeq->GetLength() > 0 ? currentIntSeq->Get(0) : 0;
            break;
        case 4:
            func = [](int a, int b) { return a < b ? a : b; };
            init = currentIntSeq->GetLength() > 0 ? currentIntSeq->Get(0) : 0;
            break;
        default:
            std::cout << "Неверный выбор\n";
            return;
    }

    int result = currentIntSeq->Reduce(func, init);
    std::cout << "Результат Reduce: " << result << std::endl;
}

void zipOperation() {
    if (isBitMode) {
        std::cout << "Zip для BitSequence не реализован.\n";
        return;
    }

    if (currentIntSeq == nullptr) {
        std::cout << "Текущая последовательность не создана.\n";
        return;
    }

    std::cout << "Введите элементы второй последовательности через пробел: ";
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::string line;
    std::getline(std::cin, line);
    std::stringstream ss(line);

    std::vector<int> items;
    int val;
    while (ss >> val) {
        items.push_back(val);
    }

    MutableArraySequence<int> other(items.data(), items.size());

    std::cout << "Выберите операцию Zip:\n";
    std::cout << "1. Сложение\n";
    std::cout << "2. Вычитание (first - second)\n";
    std::cout << "3. Умножение\n";
    int choice;
    std::cin >> choice;

    std::function<int(int, int)> func;
    switch (choice) {
        case 1:
            func = [](int a, int b) { return a + b; };
            break;
        case 2:
            func = [](int a, int b) { return a - b; };
            break;
        case 3:
            func = [](int a, int b) { return a * b; };
            break;
        default:
            std::cout << "Неверный выбор\n";
            return;
    }

    Sequence<int>* result = currentIntSeq->Zip(&other, func);
    std::cout << "Результат Zip: " << *result << std::endl;
    delete result;
}

void skipOperation() {
    if (isBitMode) {
        std::cout << "Skip для BitSequence не реализован.\n";
        return;
    }

    if (currentIntSeq == nullptr) {
        std::cout << "Последовательность не создана.\n";
        return;
    }
    int n;
    std::cout << "Сколько элементов пропустить? ";
    std::cin >> n;
    Sequence<int>* result = currentIntSeq->Skip(n);
    std::cout << "Результат Skip(" << n << "): " << *result << std::endl;
    delete result;
}

void takeOperation() {
    if (isBitMode) {
        std::cout << "Take для BitSequence не реализован.\n";
        return;
    }

    if (currentIntSeq == nullptr) {
        std::cout << "Последовательность не создана.\n";
        return;
    }
    int n;
    std::cout << "Сколько элементов взять? ";
    std::cin >> n;
    Sequence<int>* result = currentIntSeq->Take(n);
    std::cout << "Результат Take(" << n << "): " << *result << std::endl;
    delete result;
}

void bitSequenceMenu() {
    if (!isBitMode) {
        std::cout << "Вы не в режиме BitSequence. Используйте пункт 1 главного меню для создания int-последовательности,\n";
        std::cout << "или перезапустите программу и выберите BitSequence в начальном меню.\n";
        return;
    }

    int choice;
    do {
        printBitMenu();
        std::cin >> choice;

        switch (choice) {
            case 1: {
                std::cout << "Введите строку из 0 и 1: ";
                std::string bits;
                std::cin >> bits;
                int len = bits.length();
                bool* arr = new bool[len];
                for (int i = 0; i < len; i++) {
                    arr[i] = (bits[i] == '1');
                }
                if (currentBitSeq != nullptr) delete currentBitSeq;
                currentBitSeq = new MutableBitSequence(arr, len);
                delete[] arr;
                std::cout << "Создана BitSequence: ";
                printBits(std::cout, *currentBitSeq);
                std::cout << std::endl;
                break;
            }
            case 2:
                if (currentBitSeq == nullptr) {
                    std::cout << "BitSequence не создана.\n";
                } else {
                    std::cout << "Текущая BitSequence: ";
                    printBits(std::cout, *currentBitSeq);
                    std::cout << " (длина: " << currentBitSeq->GetLength() << ")\n";
                }
                break;
            case 3: {
                if (currentBitSeq == nullptr) {
                    std::cout << "BitSequence не создана.\n";
                    break;
                }
                int bit;
                std::cout << "Введите бит (0 или 1): ";
                std::cin >> bit;
                currentBitSeq->Append(bit != 0);
                std::cout << "Результат: ";
                printBits(std::cout, *currentBitSeq);
                std::cout << std::endl;
                break;
            }
            case 4: {
                if (currentBitSeq == nullptr) {
                    std::cout << "BitSequence не создана.\n";
                    break;
                }
                int bit;
                std::cout << "Введите бит (0 или 1): ";
                std::cin >> bit;
                currentBitSeq->Prepend(bit != 0);
                std::cout << "Результат: ";
                printBits(std::cout, *currentBitSeq);
                std::cout << std::endl;
                break;
            }
            case 5: {
                if (currentBitSeq == nullptr) {
                    std::cout << "BitSequence не создана.\n";
                    break;
                }
                int index, bit;
                std::cout << "Введите индекс: ";
                std::cin >> index;
                std::cout << "Введите бит (0 или 1): ";
                std::cin >> bit;
                try {
                    currentBitSeq->InsertAt(bit != 0, index);
                    std::cout << "Результат: ";
                    printBits(std::cout, *currentBitSeq);
                    std::cout << std::endl;
                } catch (const std::exception& e) {
                    std::cout << "Ошибка: " << e.what() << std::endl;
                }
                break;
            }
            case 6: {
                if (currentBitSeq == nullptr) {
                    std::cout << "BitSequence не создана.\n";
                    break;
                }
                int index;
                std::cout << "Введите индекс: ";
                std::cin >> index;
                try {
                    std::cout << "Бит[" << index << "] = " << currentBitSeq->Get(index) << std::endl;
                } catch (const std::exception& e) {
                    std::cout << "Ошибка: " << e.what() << std::endl;
                }
                break;
            }
            case 7: {
                if (currentBitSeq == nullptr) {
                    std::cout << "BitSequence не создана.\n";
                    break;
                }
                std::cout << "Введите вторую BitSequence (строка из 0 и 1): ";
                std::string bits;
                std::cin >> bits;
                int len = bits.length();
                bool* arr = new bool[len];
                for (int i = 0; i < len; i++) {
                    arr[i] = (bits[i] == '1');
                }
                MutableBitSequence other(arr, len);
                delete[] arr;
                try {
                    BitSequence* result = currentBitSeq->BitwiseAnd(&other);
                    std::cout << "AND: ";
                    printBits(std::cout, *result);
                    std::cout << std::endl;
                    delete result;
                } catch (const std::exception& e) {
                    std::cout << "Ошибка: " << e.what() << std::endl;
                }
                break;
            }
            case 8: {
                if (currentBitSeq == nullptr) {
                    std::cout << "BitSequence не создана.\n";
                    break;
                }
                std::cout << "Введите вторую BitSequence (строка из 0 и 1): ";
                std::string bits;
                std::cin >> bits;
                int len = bits.length();
                bool* arr = new bool[len];
                for (int i = 0; i < len; i++) {
                    arr[i] = (bits[i] == '1');
                }
                MutableBitSequence other(arr, len);
                delete[] arr;
                try {
                    BitSequence* result = currentBitSeq->BitwiseOr(&other);
                    std::cout << "OR: ";
                    printBits(std::cout, *result);
                    std::cout << std::endl;
                    delete result;
                } catch (const std::exception& e) {
                    std::cout << "Ошибка: " << e.what() << std::endl;
                }
                break;
            }
            case 9: {
                if (currentBitSeq == nullptr) {
                    std::cout << "BitSequence не создана.\n";
                    break;
                }
                std::cout << "Введите вторую BitSequence (строка из 0 и 1): ";
                std::string bits;
                std::cin >> bits;
                int len = bits.length();
                bool* arr = new bool[len];
                for (int i = 0; i < len; i++) {
                    arr[i] = (bits[i] == '1');
                }
                MutableBitSequence other(arr, len);
                delete[] arr;
                try {
                    BitSequence* result = currentBitSeq->BitwiseXor(&other);
                    std::cout << "XOR: ";
                    printBits(std::cout, *result);
                    std::cout << std::endl;
                    delete result;
                } catch (const std::exception& e) {
                    std::cout << "Ошибка: " << e.what() << std::endl;
                }
                break;
            }
            case 10: {
                if (currentBitSeq == nullptr) {
                    std::cout << "BitSequence не создана.\n";
                    break;
                }
                BitSequence* result = currentBitSeq->BitwiseNot();
                std::cout << "NOT: ";
                printBits(std::cout, *result);
                std::cout << std::endl;
                delete result;
                break;
            }
            case 11: {
                if (currentBitSeq == nullptr) {
                    std::cout << "BitSequence не создана.\n";
                    break;
                }
                std::cout << "Длина BitSequence: " << currentBitSeq->GetLength() << std::endl;
                break;
            }
            case 0:
                std::cout << "Возврат в главное меню.\n";
                break;
            default:
                std::cout << "Неверный выбор!\n";
        }
    } while (choice != 0);
}

void mapReduceTasks() {
    if (isBitMode) {
        std::cout << "Map-Reduce задачи только для int-последовательностей.\n";
        return;
    }

    if (currentIntSeq == nullptr) {
        std::cout << "Последовательность не создана. Сначала создайте последовательность.\n";
        return;
    }

    std::cout << "\n--- Map-Reduce задачи (П-задачи) ---\n";
    std::cout << "1. (min, max, avg) за 1 проход\n";
    std::cout << "2. Медиана\n";
    std::cout << "3. Список всех префиксов\n";
    std::cout << "4. Список всех постфиксов\n";
    std::cout << "5. Поэлементная сумма с отражением\n";
    std::cout << "Выберите задачу: ";

    int choice;
    std::cin >> choice;

    try {
        switch (choice) {
            case 1: {
                std::tuple<double, double, double> result = computeMinMaxAvg(currentIntSeq);
                std::cout << "min = " << std::get<0>(result)
                     << ", max = " << std::get<1>(result)
                     << ", avg = " << std::get<2>(result) << std::endl;
                break;
            }
            case 2: {
                double median = computeMedian(currentIntSeq);
                std::cout << "Медиана = " << median << std::endl;
                break;
            }
            case 3: {
                Sequence<Sequence<int>*>* prefixes = computePrefixes(currentIntSeq);
                std::cout << "Префиксы:\n";
                for (int i = 0; i < prefixes->GetLength(); i++) {
                    std::cout << "  " << *(prefixes->Get(i)) << std::endl;
                }
                for (int i = 0; i < prefixes->GetLength(); i++) {
                    delete prefixes->Get(i);
                }
                delete prefixes;
                break;
            }
            case 4: {
                Sequence<Sequence<int>*>* suffixes = computeSuffixes(currentIntSeq);
                std::cout << "Постфиксы:\n";
                for (int i = 0; i < suffixes->GetLength(); i++) {
                    std::cout << "  " << *(suffixes->Get(i)) << std::endl;
                }
                for (int i = 0; i < suffixes->GetLength(); i++) {
                    delete suffixes->Get(i);
                }
                delete suffixes;
                break;
            }
            case 5: {
                Sequence<int>* result = computeMirrorSum(currentIntSeq);
                std::cout << "Зеркальная сумма: " << *result << std::endl;
                delete result;
                break;
            }
            default:
                std::cout << "Неверный выбор!\n";
        }
    } catch (const std::exception& e) {
        std::cout << "Ошибка: " << e.what() << std::endl;
    }
}

void runTests() {
    std::cout << "\n--- Запуск всех тестов ---\n";
    runAllTests();
}

int main() {
    std::cout << "========================================\n";
    std::cout << "   ЛР №2\n";
    std::cout << "========================================\n";

    selectInitialType();

    int choice;
    do {
        printMenu();
        std::cin >> choice;

        switch (choice) {
            case 1: createSequence(); break;
            case 2: showSequence(); break;
            case 3: appendElement(); break;
            case 4: prependElement(); break;
            case 5: insertAt(); break;
            case 6: getElement(); break;
            case 7: getSubsequence(); break;
            case 8: concatSequence(); break;
            case 9: mapOperation(); break;
            case 10: whereOperation(); break;
            case 11: reduceOperation(); break;
            case 12: zipOperation(); break;
            case 13: skipOperation(); break;
            case 14: takeOperation(); break;
            case 15: bitSequenceMenu(); break;
            case 16: mapReduceTasks(); break;
            case 17: runTests(); break;
            case 0:
                std::cout << "ЗАВЕРШЕНИЕ РАБОТЫ \n";
                break;
            default:
                std::cout << "Неверный выбор\n";
        }
    } while (choice != 0);

    if (currentIntSeq != nullptr) delete currentIntSeq;
    if (currentBitSeq != nullptr) delete currentBitSeq;

    return 0;
}
