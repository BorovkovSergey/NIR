#include <string>
#include <iostream>
#include <fstream>
#include <vector>

class fileWork
{
    public:
        // @brief Запись сообщения в конец файла
        static bool writeEnd( const char * file, std::string& message );
        // @brief Запись в файл
        static bool write( const char * file, std::vector<std::string> message );
        // @brife Чтение всего файла в вектор
        static std::vector<std::string> readAll( const char * file );
};