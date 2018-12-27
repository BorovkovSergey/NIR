#include <iostream>
#include <string>

namespace log_shell
{
    // @brief Вывод информации на консоль
    void info( std::string message );
    // @brief Вывод ошибки на консоль и запись в лог
    void error( std::string message );
    // @brief Вывод предупреждения на консоль и запись в лог
    void warning( std::string message );
    
} // namespace log