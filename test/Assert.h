#include <iostream>

template<typename A, typename B>
void ASSERT_EQUAL(const A& a, const B& b, const char* message = nullptr)
{
    if (a != b) {
        if (message != nullptr) {
            std::cout << message << ": ";
        }
        std::cout << "expected " << a << " but got " << b << std::endl;
        exit(1);
    }
}
