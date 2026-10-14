#include <cmath>
#include <iomanip>
#include <iostream>
#include <string>
#include <vector>

constexpr double PI = 3.14159265358979323846;

void printHelp(const char* program) {
    std::cout << "Калькулятор площадей\n\n"
              << "Использование:\n"
              << "  " << program << " -o circle <radius>\n"
              << "  " << program << " --operation circle <radius>\n"
              << "  " << program << " -o triangle <a> <b> <c>\n"
              << "  " << program << " --operation triangle <a> <b> <c>\n";
}

bool parseNumber(const std::string& text, double& number) {
    try {
        std::size_t pos = 0;
        number = std::stod(text, &pos);
        return pos == text.size() && std::isfinite(number);
    } catch (...) {
        return false;
    }
}

int main(int argc, char* argv[]) {
	
    if (argc == 1) {
        printHelp(argv[0]);
        return 0;
    }

    if (argc < 3) {
        std::cerr << "Ошибка: недостаточно аргументов.\n";
        printHelp(argv[0]);
        return 1;
    }

    if (std::string(argv[1]) != "-o" &&
        std::string(argv[1]) != "--operation") {
        std::cerr << "Ошибка: используйте -o или --operation.\n";
        return 1;
    }

    std::string operation = argv[2];
    int firstOperand = 3;
    int operandCount = argc - firstOperand;

    if (operation != "circle" && operation != "triangle") {
        std::cerr << "Ошибка: неизвестная операция.\n";
        return 1;
    }

    int expectedCount = (operation == "circle") ? 1 : 3;

    if (operandCount != expectedCount) {
        std::cerr << "Ошибка: неверное количество параметров.\n";
        return 1;
    }

    std::vector<double> values;

    for (int i = firstOperand; i < argc; ++i) {
        double number = 0.0;

        if (!parseNumber(argv[i], number) || number <= 0.0) {
            std::cerr << "Ошибка: параметры должны быть положительными числами.\n";
            return 1;
        }

        values.push_back(number);
    }

    double area = 0.0;

    if (operation == "circle") {
        area = PI * values[0] * values[0];
    } else {
        double a = values[0];
        double b = values[1];
        double c = values[2];

        if (a + b <= c || a + c <= b || b + c <= a) {
            std::cerr << "Ошибка: из указанных сторон нельзя составить треугольник.\n";
            return 1;
        }

        double p = (a + b + c) / 2.0;
        area = std::sqrt(p * (p - a) * (p - b) * (p - c));
    }

    std::cout << std::fixed << std::setprecision(4);
    std::cout << "Площадь: " << area << '\n';

    return 0;
}