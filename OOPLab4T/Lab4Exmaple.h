#pragma once
// 1 
/*Створити тип даних - клас вектор VectorDouble (вектор дійсних чисел), який має
вказівник на double, число елементів size і змінну стану codeError.У класі визначити
o конструктор без параметрів( виділяє місце для одного елемента та інінціалізує
його в нуль);
o конструктор з одним параметром - розмір вектора( виділяє місце та інінціалізує
масив значенням нуль);
o конструктор із двома параметрами - розмір вектора та значення
ініціалізації(виділяє місце (значення перший аргумент) та інінціалізує значенням
другого аргументу).
o деструктор звільняє пам'ять;
o перевантаження операцій (операції перевантажувати через функції класу або
дружні функції, якщо не вказано яким чином це робити):
 унарних префіксних та постфіксних ++ та --: одночасно збільшує
(зменшує) значення елементів масиву на 1.0;
 унарної логічної ! (заперечення): повертає значення true, якщо
елементи якщо size не дорівнює – нулю, інакше false;
 унарний арифметичний - (мінус) : повертає всі елементи масиву класу
вектор з протилежним знаком;
 присвоєння =: копіює вектор(перевантажити через функцію класу);
 присвоєння з (перевантажити через функцію класу)
o += - додаванням векторів;
o -= - відніманням векторів;
o *= - множення, вектора на число;
o /= - ділення, вектора на число;
o %= - остача від ділення, вектора на число;
 арифметичних бінарні:
o + - додавання векторів;
o – - віднімання векторів;
o * - множення, вектора на число;
o / - ділення, вектора на число;
o % - остача від ділення, вектора на число типу int;
 побітові операції зсувів, як дружні операції введення та виведення
вектора у потік (перевантажувати через дружні функції)
o введення >> (побітовий зсув право) ;
o введення << (побітовий зсув ліво);
 рівності == та нерівності!= , функція-операція виконує певні дії над
кожною парою елементів векторів за індексом;
 операцію індексації [] – функцію, яка звертається до елементу масиву
за індексом, якщо індекс невірний функція вказує на останній елемент
масиву та встановлює код помилки у змінну codeError;
*/

#include <iostream>
#include <cmath> // Для функції fmod()

class VectorDouble {
private:
    double* elements; // Вказівник на масив елементів
    int size; // Розмір вектора
    int codeError; // Змінна стану

public:
    // Конструктори
    VectorDouble() {
        size = 1;
        elements = new double[size];
        elements[0] = 0.0;
        codeError = 0;
    }

    VectorDouble(int s) {
        size = s;
        elements = new double[size];
        for (int i = 0; i < size; ++i) {
            elements[i] = 0.0;
        }
        codeError = 0;
    }

    VectorDouble(int s, double initValue) {
        size = s;
        elements = new double[size];
        for (int i = 0; i < size; ++i) {
            elements[i] = initValue;
        }
        codeError = 0;
    }

    // Деструктор
    ~VectorDouble() {
        delete[] elements;
    }

    // Перевантаження операторів
    VectorDouble& operator++() { // Префіксний ++
        for (int i = 0; i < size; ++i) {
            ++elements[i];
        }
        return *this;
    }

    VectorDouble operator++(int) { // Постфіксний ++
        VectorDouble temp(*this);
        operator++();
        return temp;
    }

    VectorDouble operator-() { // Унарний мінус
        VectorDouble result(*this);
        for (int i = 0; i < size; ++i) {
            result.elements[i] = -result.elements[i];
        }
        return result;
    }

    bool operator!() { // Унарний оператор заперечення
        return size != 0;
    }

    VectorDouble& operator=(const VectorDouble& other) { // Оператор присвоєння =
        if (this != &other) {
            delete[] elements;
            size = other.size;
            elements = new double[size];
            for (int i = 0; i < size; ++i) {
                elements[i] = other.elements[i];
            }
        }
        return *this;
    }

    VectorDouble& operator+=(const VectorDouble& other) {
        for (int i = 0; i < size; ++i) {
            elements[i] += other.elements[i];
        }
        return *this;
    }

    VectorDouble& operator-=(const VectorDouble& other) {
        for (int i = 0; i < size; ++i) {
            elements[i] -= other.elements[i];
        }
        return *this;
    }

    VectorDouble& operator*=(double scalar) {
        for (int i = 0; i < size; ++i) {
            elements[i] *= scalar;
        }
        return *this;
    }

    VectorDouble& operator/=(double scalar) {
        if (scalar != 0) {
            for (int i = 0; i < size; ++i) {
                elements[i] /= scalar;
            }
        }
        return *this;
    }

    VectorDouble& operator%=(int modulo) {
        if (modulo != 0) {
            for (int i = 0; i < size; ++i) {
                elements[i] = fmod(elements[i], modulo);
            }
        }
        return *this;
    }

    // Бінарні оператори
    friend VectorDouble operator+(VectorDouble lhs, const VectorDouble& rhs) {
        lhs += rhs;
        return lhs;
    }

    friend VectorDouble operator-(VectorDouble lhs, const VectorDouble& rhs) {
        lhs -= rhs;
        return lhs;
    }

    friend VectorDouble operator*(VectorDouble lhs, double scalar) {
        lhs *= scalar;
        return lhs;
    }

    friend VectorDouble operator/(VectorDouble lhs, double scalar) {
        lhs /= scalar;
        return lhs;
    }

    friend VectorDouble operator%(VectorDouble lhs, int modulo) {
        lhs %= modulo;
        return lhs;
    }
};

/*Побудувати асоційований клас збереження
двох сутностей. В завданні створити клас, який представляє собою асоціативний
масив між двома сутностями. Написати функцію створення набору
асоціативних сутностей. Перевантажити операцію індексації [] – функцію, яка
звертається до об’єкта класу, за однією сутністю, якщо індекс, повертає
асоціативну сутність, якщо відповідної сутності немає в встановлює код
помилки у змінну CodeError, альтернативні звернення через перевантаження
операції виклику функції(); перевантажити дружні операції введення та
виведення. Доменних імен та ІР - адреса.
*/
#include <iostream>
#include <unordered_map>
#include <string>

class AssociatedEntities {
private:
    std::unordered_map<std::string, std::string> data; // Асоційований масив для збереження пар даних

public:
    // Функція додавання асоціативної сутності (доменного імені та IP-адреси)
    void addEntity(const std::string& domain, const std::string& ip) {
        data[domain] = ip;
    }

    // Перевантаження оператора індексації []
    std::string operator[](const std::string& domain) {
        if (data.find(domain) != data.end()) {
            return data[domain];
        }
        else {
            // Встановлення коду помилки у змінну CodeError
            std::cerr << "Error: Domain not found" << std::endl;
            // Повернення порожнього рядка у випадку відсутності сутності
            return "";
        }
    }

    // Перевантаження дружніх операцій введення та виведення
    friend std::ostream& operator<<(std::ostream& os, const AssociatedEntities& ae) {
        for (const auto& pair : ae.data) {
            os << "Domain: " << pair.first << ", IP: " << pair.second << std::endl;
        }
        return os;
    }

    friend std::istream& operator>>(std::istream& is, AssociatedEntities& ae) {
        std::string domain, ip;
        std::cout << "Enter domain: ";
        is >> domain;
        std::cout << "Enter IP address: ";
        is >> ip;
        ae.addEntity(domain, ip);
        return is;
    }
};

int main() {
    AssociatedEntities ae;

    // Додавання асоціативних сутностей
    ae.addEntity("example.com", "192.168.1.1");
    ae.addEntity("google.com", "172.217.168.46");
    ae.addEntity("openai.org", "52.21.5.176");

    // Використання оператора індексації []
    std::cout << "IP address for google.com: " << ae["google.com"] << std::endl;
    std::cout << "IP address for yahoo.com: " << ae["yahoo.com"] << std::endl; // Тестування відсутності сутності

    // Виведення асоціативних сутностей
    std::cout << "Associated Entities:" << std::endl;
    std::cout << ae << std::endl;

    // Введення нової асоціативної сутності за допомогою оператора введення >>
    std::cin >> ae;

    return 0;
}

