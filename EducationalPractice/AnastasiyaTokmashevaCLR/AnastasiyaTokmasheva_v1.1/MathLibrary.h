// MathLibrary.h
#include <string>
#pragma once

namespace MathLibrary
{
    using namespace std;
    class Arithmetic
    {
    public:
        // Returns a + b
        static double Addr(double a, double b);

        // Returns a - b
        static double Subtract(double a, double b);

        // Returns a * b
        static double Multiply(double a, double b);

        // Returns a / b
        static double Divide(double a, double b);
    };

    class Operation 
    {
    public:
        static std::string Replace(std::string& str, const std::string& from, const std::string& to);
    };
}