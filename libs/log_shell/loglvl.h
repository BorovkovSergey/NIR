#include <string>

namespace log_shell
{
    // @brief установка уровня логирования
    bool set_lvl( std::string& lvl );
    
    // @brief проверка уровня логирования
    int check_lvl();

    enum
    {
        NO_LOG = 0,         // не логируем ничего
        ONLY_INFO = 1,      // выводятся  только info
        ONLY_SHELL = 2,     // выводятся все сообщения, но не заносятся в лог
        STANDART = 3,       // info, warninig выводится только в shell. error пишется в лог файл
        DEBUG = 4           // все сообщения выводятся и заносятся в лог
    };
}