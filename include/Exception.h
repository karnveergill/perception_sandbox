#ifndef EXCEPTION_H
#define EXCEPTION_H

#include <cstdarg>
#include <cstdio>
#include <string>
#include <stdexcept>

class Exception : public std::exception
{
public:
    /**
     * @brief Constructor builds exception with a printf style c string and args 
     */
    Exception(const char* format, ...)
    {
        // Tool to grab pointer to additional args from ... and iterate through 
        va_list args;

        // Start tool build string dry run in nullptr to get buffer length
        va_start(args, format);
        int length = vsnprintf(nullptr, 0, format, args) + 1;
        va_end(args);

        // Handle formatting failure
        if(length < 0)
        {
            m_error_msg = "Exception printf style formatting failed";
            return;
        }

        // Allocate buffer of size length + null terminator
        std::string buffer(length + 1, '\0');

        // Restart va_list for actual use and create formatted message
        va_start(args, format);
        vsnprintf(buffer.data(), buffer.size(), format, args);
        va_end(args);

        // Save message 
        m_error_msg = buffer;
    }

    /*
     * @brief Retrieve 'what' the exception is
     */
    const char* what() const noexcept override
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