#include "messages.h"
#include "loglvl.h"
#include "../files_working/fileWork.h"

namespace log_shell
{
const char* log_file = "everything.log";

std::string get_time()
{
    time_t seconds = time( NULL );
    tm* timeinfo = localtime( &seconds );
    std::string answer = asctime( timeinfo );
    answer.erase( answer.find("\n"), 1 );
    return answer;
}

void info( std::string message )
{
    int lvl = check_lvl();
    if ( lvl == NO_LOG )
    {
        return;
    }
    std::string answer = get_time();
    answer += " INFO: " + message + "\n"; 
    if ( lvl == DEBUG )
    {
        fileWork::writeEnd( log_file, answer );
    }
    std::cout << answer;
}

void error( std::string message )
{
    int lvl = check_lvl();
    if ( lvl == ONLY_INFO || lvl == NO_LOG )
    {
        return;
    }
    std::string answer = get_time();
    answer += " ERORR: " + message + "\n"; 
    std::cout << answer;
    if ( lvl != ONLY_SHELL )
    {
        fileWork::writeEnd( log_file, answer );
    }
}

void warning( std::string message )
{
    int lvl = check_lvl();
    if ( lvl == ONLY_INFO || lvl == NO_LOG )
    {
        return;
    }
    std::string answer = get_time();
    answer += " WARNING: " + message + "\n"; 
    std::cout << answer;
    if ( lvl == DEBUG )
    {
        fileWork::writeEnd( log_file, answer );
    }
}

} // namespace log 


