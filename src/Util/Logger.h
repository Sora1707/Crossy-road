#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>

namespace logger {
    class CustomOutput {
    public:
        CustomOutput(const std::string& tag) : tag(tag) {}

        // Overloaded stream insertion operator
        template<typename T>
        inline CustomOutput& operator<<(const T& value) {
            if (!isPrinted) {
                std::cout << "[" << tag << "] ";
                isPrinted = true;
            }
            std::cout << value;
            // Chaining
            return *this;
        }

    private:
        std::string tag;
        bool isPrinted = false;
    };

    CustomOutput error("ERROR");
    CustomOutput warn("WARNING");
    CustomOutput success("SUCCESS");
    CustomOutput info("INFO");
}