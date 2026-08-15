#ifndef EXCEPTION_H
#define EXCEPTION_H

#include <cstdarg>
#include <cstdio>
#include <string>
#include <stdexcept>
////////////////////////////////////////////////////////////////////////////////
class Exception : public std::exception
{
public:
    /**
     * @brief Constructor builds exception with a printf style c string and args 
     */
    Exception(const char* format, ...)
        : m_error_msg(format)
    {
        // Tool to grab pointer to additional args from ... and iterate through 
        va_list args;
        // Start tool and look for all arguments after format string
        va_start(args, format);
        // Dry run building the string in a nullptr and get buffer length
        int length = vsnprintf(nullptr, 0, format, args) + 1;
        // Clean up tool
        va_end(args);

        // Dynamically allocate memory for buffer
        char* buffer = new char[length];

        // Restart va_list for actual use
        va_start(args, format);
        vsnprintf(buffer, length, format, args);
        va_end(args);

        // Save message and free dynamically allocated buffer
        m_error_msg = buffer;
        delete[] buffer; 
    }

    /**
     * @brief Destructor
     */
    ~Exception() _NOEXCEPT {}

    /*
     * @brief Retrieve 'what' the exception is
     */
    const char* what() const _NOEXCEPT override
    {
        return m_error_msg.c_str();
    }

private:
    /*
     * @brief Stores exception string
     */
    std::string m_error_msg;
};

#endif // EXCEPTION_H