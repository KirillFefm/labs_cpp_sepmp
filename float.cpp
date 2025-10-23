#include <iostream>
#include <bitset>
#include <cstring>
#include <iomanip>
#include <cmath>
#include <cstdint>
using namespace std;

void printFloatBinary(float num) {
    uint32_t bits;
    memcpy(&bits, &num, sizeof(float));

    cout << "Число: " << num << endl;
    cout << "Полное двоичное представление: " << bitset<32>(bits) << endl;

    uint32_t sign = (bits >> 31) & 1;
    uint32_t exponent = (bits >> 23) & 0xFF;
    uint32_t mantissa = bits & 0x7FFFFF;

    cout << "Знак: " << sign << " (" << (sign ? "-" : "+") << ")" << endl;
    cout << "Экспонента (8 бит): " << bitset<8>(exponent) << " = " << exponent << " (смещение 127)" << endl;
    cout << "Мантисса (23 бита): " << bitset<23>(mantissa) << endl;

    if (exponent != 0 && exponent != 255) {
        int exp = exponent - 127;
        float mantissa_val = 1.0f;
        for (int i = 22; i >= 0; i--) {
            if (mantissa & (1 << i)) {
                mantissa_val += pow(2.0f, -(23 - i));
            }
        }
        float calculated = (sign ? -1.0f : 1.0f) * mantissa_val * pow(2.0f, exp);
        cout << "Вычисленное значение: " << (sign ? "-" : "") << mantissa_val << " * 2^" << exp << " = " << calculated << endl;
    }
    cout << endl;
}

void findSpacingOne() {
    cout << "=== Задача 2: Поиск чисел с расстоянием 1 ===" << endl;

    float x = 1.0f;
    float prev_x = x;

    while (true) {
        float next = nextafterf(x, INFINITY);
        if (next - x >= 1.0f) {
            cout << "Первые числа a и b с расстоянием >= 1:" << endl;
            cout << "a = " << fixed << setprecision(1) << x << endl;
            cout << "b = " << next << endl;
            cout << "b - a = " << (next - x) << endl;
            break;
        }
        x *= 2.0f;
    }

    x = 1.0f;
    while (x + 1.0f != x) {
        x *= 2.0f;
    }
    cout << "\nЧисло x0, где x + 1 == x:" << endl;
    cout << "x0 = " << x << endl;
    cout << "x0 + 1 = " << (x + 1.0f) << endl;
    cout << "Проверка: (x0 + 1 == x0) = " << ((x + 1.0f) == x ? "true" : "false") << endl;
    cout << endl;
}

void demonstrateNonAssociativity() {
    cout << "=== Задача 3: Отсутствие ассоциативности ===" << endl;

    float a = 1e20f;
    float b = -1e20f;
    float c = 1.0f;

    float result1 = (a + b) + c;
    float result2 = a + (b + c);

    cout << "a = " << a << endl;
    cout << "b = " << b << endl;
    cout << "c = " << c << endl;
    cout << "(a + b) + c = " << result1 << endl;
    cout << "a + (b + c) = " << result2 << endl;
    cout << "(a + b) + c ?= a + (b + c) " << (result1 == result2 ? "Да" : "Нет") << endl;
    cout << endl;
}

void harmonicSeriesConvergence() {
    cout << "=== Задача 4: Сходимость гармонического ряда ===" << endl;

    float sum = 0.0f;
    int k = 1;

    while (true) {
        float term = 1.0f / k;
        float new_sum = sum + term;

        if (new_sum == sum) {
            cout << "k = " << k << endl;
            cout << "Сумма = " << sum << endl;
            cout << "Элемент 1/k = " << term << endl;
            break;
        }

        sum = new_sum;
        k++;
    }
    cout << endl;
}

void forwardBackwardSummation() {
    cout << "=== Задача 5: Суммирование вперед и назад ===" << endl;

    float sum = 0.0f;
    int k = 1;
    while (true) {
        float new_sum = sum + 1.0f / k;
        if (new_sum == sum) break;
        sum = new_sum;
        k++;
    }

    int start = 1;
    int end = k + 100;

    float forward_sum = 0.0f;
    for (int i = start; i <= end; i++) {
        forward_sum += 1.0f / i;
    }

    float backward_sum = 0.0f;
    for (int i = end; i >= start; i--) {
        backward_sum += 1.0f / i;
    }

    cout << "Суммирование от 1 до " << end << ":" << endl;
    cout << "Прямое суммирование: " << forward_sum << endl;
    cout << "Обратное суммирование: " << backward_sum << endl;
    cout << "Разница: " << (forward_sum - backward_sum) << endl;
    cout << endl;
}

void equalityComparison() {
    cout << "=== Задача 6: Сравнение float через == ===" << endl;

    float x = 0.000000002f;
    float z = 0.000000001f;
    float t = x + z;
    float y = 0.000000003f;
    cout << "\nПример: 0.000000002 + 0.000000001== 0.000000003?" << endl;
    cout << "0.000000002 + 0.000000001 = " << setprecision(20) << t << endl;
    cout << "0.000000003 = " << y << endl;
    cout << "x ?= y " << (t == y ? "Да" : "Нет") << endl;
    float a = 5.0f;
    float b = 5.0f;
    cout << "a = 5.0, b = 5.0" << endl;
    cout << "a ?= b " << (a == b ? "Да" : "Нет") << endl;
    cout << endl;
}

int main() {
    cout << fixed << setprecision(10);

    cout << "=== Задача 1: Двоичное представление float ===" << endl;
    printFloatBinary(5.75f);
    printFloatBinary(0.5f);
    printFloatBinary(-2.0f);

    findSpacingOne();
    demonstrateNonAssociativity();
    harmonicSeriesConvergence();
    forwardBackwardSummation();
    equalityComparison();

    return 0;
}