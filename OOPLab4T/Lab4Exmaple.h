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

class DomainIPAssociation {
private:
    std::unordered_map<std::string, std::string> association;

public:
    void createAssociation(const std::string& domain, const std::string& ip) {
        association[domain] = ip;
        std::cout << "Association created: Domain - " << domain << ", IP - " << ip << std::endl;
    }

    std::string getIP(const std::string& domain) {
        if (association.find(domain) != association.end()) {
            return association[domain];
        }
        else {
            return "Error: item not found";
        }
    }

    friend std::ostream& operator<<(std::ostream& os, const DomainIPAssociation& obj) {
        for (const auto& pair : obj.association) {
            os << "Domain: " << pair.first << ", IP: " << pair.second << std::endl;
        }
        return os;
    }

    friend std::istream& operator>>(std::istream& is, DomainIPAssociation& obj) {
        std::string domain, ip;
        std::cout << "Enter domain name: ";
        is >> domain;
        std::cout << "Enter IP address: ";
        is >> ip;
        obj.createAssociation(domain, ip);
        return is;
    }
};

int main() {
    DomainIPAssociation association;

    try {
        association.createAssociation("example.com", "192.168.1.1");
        association.createAssociation("example.net", "192.168.1.2");

        std::cout << "Associations after creation:" << std::endl;
        std::cout << association;

        std::string inputDomain;
        std::cout << "Enter domain name to retrieve IP address: ";
        std::cin >> inputDomain;

        std::string retrievedIP = association.getIP(inputDomain);
        std::cout << "IP address for " << inputDomain << ": " << retrievedIP << std::endl;
    }
    catch (const char* error) {
        std::cerr << "Error: " << error << std::endl;
    }

    return 0;
}
