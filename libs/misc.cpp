#include "misc.h"
#include "log_shell/messages.h"

#include <string>
#include <wchar.h>

#include <boost/algorithm/string.hpp> 

namespace misc
{

void LowStr( std::string& str )
{
    const std::string lowRus = "абвгдеёжзийклмнопрстуфхцчшщэюя";
    const std::string upRus =  "АБВГДЕЁЖЗИЙКЛМНОПРСТУФХЦЧШЩЭЮЯ";
    const std::string anySymbls = "abcdefjhigklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ !@#$%%^&*()_-=+\"№;:?[]{}\\.,|/'";
    for( unsigned int i = 0; i < str.length(); )
    {
        if ( anySymbls.find( str[i] ) != std::string::npos )
        {
            i++;
            continue;
        }

        for( unsigned int j = 0; j < upRus.length(); )
        {
            if ( str[i] == upRus[j] && str[i+1] == upRus[j+1] )
            {
                str[i] = lowRus[j];
                str[i+1] = lowRus[j+1];
            }
            j += 2;
        }
        i += 2;
    }
    std::transform(str.begin(), str.end(), str.begin(), tolower);
    log_shell::info( "LowStr done" );
}

}