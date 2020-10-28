#include <iostream>
#include <time.h>
using namespace std;

// Прототипы функций
int get_random_number(int r_min, int r_max);
int* create_random_vector(int size, int min, int max);
int* create_vector_by_user_input(int size);
long long int get_consist_scalar_product(int* vector1, int* vector2, int size);
long long int get_parallel_scalar_product(int* vector1, int* vector2, int size, int t_value);
int input(int v_min, int v_max);
void test();
void run();

int main() {
    int command;
    do {
        setlocale(LC_CTYPE, "rus");
        cout << "Список команд:" << endl;
        cout << "1) Тестирование алгоритма с помощью ручного ввода векторов" << endl;
        cout << "2) Рабочий прогон алгоритма для указанной длины векторов" << endl;
        cout << "0) Завершить работу программы" << endl;
        cout << "Введите команду:" << endl;
        command = input(0, 2);
        if (command == 1) {
            test(); // Запуск тестирования алгоритма
        }
        else if (command == 2) {
            run(); // Запуск рабочего прогона алгоритма
        }
    } while (command != 0);
}

// Метод генерации случайного числа
int get_random_number(int r_min, int r_max) {
    int r_number = rand() % (r_max - r_min + 1) + r_min;
    return r_number;
}

// Метод создания вектора путем заполнения его случайными числами
int* create_random_vector(int size, int min, int max) {
    int* vector = new int[size];
    for (int i = 0; i < size; i++) {
        vector[i] = get_random_number(min, max);
    }
    return vector;
}

// Метод ввода вектора с клавиатуры
int* create_vector_by_user_input(int size) {
    bool flag = false;
    int* vector = new int[size];
    for (int i = 0; i < size; i++) {
        vector[i] = input(1, 10);
    }
    return vector;
}

// Метод последовательного поиска скалярного произведения
long long int get_consist_scalar_product(int* vector1, int *vector2, int size) {
    long long int scalar_product = 0;
    for (int i = 0; i < size; i++) {
        scalar_product += (long long int)vector1[i] * vector2[i];
    }
    return scalar_product;
}

// Метод параллельного поиска скалярного произведения
long long int get_parallel_scalar_product(int* vector1, int* vector2, int size, int t_value) {
    long long int scalar_product = 0;
    #pragma omp parallel for reduction(+:scalar_product) num_threads(t_value)
    for (intptr_t i = 0; i < size; i++) {
        scalar_product += (long long int)vector1[i] * vector2[i];
    }
    return scalar_product;
}

// Метод фильтрации ввода
int input(int v_min, int v_max) {
    cout << ">>> ";
    int num;
    while (!(cin >> num) || (num < v_min || num > v_max)) {
        cin.clear();
        while (cin.get() != '\n');
        cout << "Вы ввели недопустимое значение!" << endl;
        cout << "Повторите ввод." << endl;
        cout << ">>> ";
    }
    return num;
}

// Метод тестирования алгоритма
void test() {
    cout << endl;
    cout << "Запуск тестирования алгоритма" << endl;
    int size = 10;
    cout << "Введите построчно элементы вектора А:" << endl;
    int* vector1 = create_vector_by_user_input(size);
    cout << "Введите построчно вектора В" << endl;
    int* vector2 = create_vector_by_user_input(size);
    long long int scalar_product = get_consist_scalar_product(vector1, vector2, size);
    cout << "Скалярное произведение данных векторов равно " << scalar_product << endl;
    cout << "Тестирование успешно завершено" << endl;
    cout << endl;
}

// Метод запуска рабочего прогона алгоритма
void run() {
    cout << endl;
    cout << "Запуск рабочего прогона алгоритма" << endl;
    cout << "Введите длину векторов: " << endl;
    int size = input(100, 100000000);
    long long int scalar_product;
    int min = 0;
    int max = 100;
    int* vector1 = create_random_vector(size, min, max);
    int* vector2 = create_random_vector(size, min, max);
    int start;
    int stop;
    int thread_v;
    cout << endl;
    // Последовательно
    cout << "Запуск последовательного выполнения алгоритма:" << endl;
    start = clock();
    scalar_product = get_consist_scalar_product(vector1, vector2, size);
    stop = clock();
    cout << "Скалярное произведение векторов равно " << scalar_product << "." << endl;
    cout << "Последовательное выполнение алгоритма заняло " << stop - start << " мс" << endl;  
    cout << endl;
    // 2 потока
    cout << "Запуск параллельного выполнения алгоритма:" << endl;
    thread_v = 2;
    start = clock();
    scalar_product = get_parallel_scalar_product(vector1, vector2, size, thread_v);
    stop = clock();
    cout << "Скалярное произведение векторов равно " << scalar_product << "." << endl;
    cout << "Параллельное выполнение алгоритма заняло " << stop - start << " мс при " << thread_v << " потоках" << endl;
    cout << endl;
    // 4 потока
    cout << "Запуск параллельного выполнения алгоритма:" << endl;
    thread_v = 4;
    start = clock();
    scalar_product = get_parallel_scalar_product(vector1, vector2, size, thread_v);
    stop = clock();
    cout << "Скалярное произведение векторов равно " << scalar_product << "." << endl;
    cout << "Параллельное выполнение алгоритма заняло " << stop - start << " мс при " << thread_v << " потоках" << endl;
    cout << endl;
    // 8 потоков
    cout << "Запуск параллельного выполнения алгоритма:" << endl;
    thread_v = 8;
    start = clock();
    scalar_product = get_parallel_scalar_product(vector1, vector2, size, thread_v);
    stop = clock();
    cout << "Скалярное произведение векторов равно " << scalar_product << "." << endl;
    cout << "Параллельное выполнение алгоритма заняло " << stop - start << " мс при " << thread_v << " потоках" << endl;
    cout << endl;
    // 16 потоков
    cout << "Запуск параллельного выполнения алгоритма:" << endl;
    thread_v = 16;
    start = clock();
    scalar_product = get_parallel_scalar_product(vector1, vector2, size, thread_v);
    stop = clock();
    cout << "Скалярное произведение векторов равно " << scalar_product << "." << endl;
    cout << "Параллельное выполнение алгоритма заняло " << stop - start << " мс при " << thread_v << " потоках" << endl;
    cout << endl;
    // 32 потока
    cout << "Запуск параллельного выполнения алгоритма:" << endl;
    thread_v = 32;
    start = clock();
    scalar_product = get_parallel_scalar_product(vector1, vector2, size, thread_v);
    stop = clock();
    cout << "Скалярное произведение векторов равно " << scalar_product << "." << endl;
    cout << "Параллельное выполнение алгоритма заняло " << stop - start << " мс при " << thread_v << " потоках" << endl;
    cout << endl;
}