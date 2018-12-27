#include <fstream>
#include <iostream>

#include <boost/lexical_cast.hpp>

#include "../files_working/fileWork.h"
#include "messages.h"
#include "loglvl.h"

namespace log_shell
{
const char * file = "settings.ini";

bool set_lvl( std::string& lvl )
{
    bool isdone = false;
    std::vector<std::string> settings = fileWork::readAll( file );
    for( unsigned int i = 0; i < settings.size(); i++ )
    {
        if ( settings[i].find("log_level: " + lvl) != std::string::npos )
        {
            error( "Failed to set log level. Log level already was set to " + lvl + ".");
            return false;
        }
        if ( settings[i].find("log_level: ") != std::string::npos )
        {
            settings[i] = "log_level: " + lvl + "\n";
            isdone = true;
            break;
        }
    }
    if ( fileWork::write( file, settings ) )
    {
        info( "Log level was set to " + lvl + "." );
        return true;
    }
    error( "Failed to set log level.");
    return false; 
}

int check_lvl()
{
    std::vector<std::string> settings = fileWork::readAll( file );
    for( unsigned int i = 0; i < settings.size(); i++ )
    {
        if ( settings[i].find("log_level: ") != std::string::npos )
        {
            return atoi( settings[i].erase(settings[i].find("log_level: "), settings[i].find(" ") + 1 ).c_str() ); // доделать уровень лоигрования
        }
    }
    return 10;
}
}