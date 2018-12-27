#include "fileWork.h"

bool fileWork::writeEnd( const char * file, std::string& message )
{
    std::ofstream writef;    
    writef.open( file, std::ios::app);  
    if (!writef.is_open()) 
    {
        std::cout << "ERROR: файл " << file << " не доступен\n"; 
        return false; 
    }                 
    writef <<  message;
    writef.close();
    return true;                          
}

bool fileWork::write( const char * file, std::vector<std::string> message )
{
    std::ofstream writef;    
    writef.open( file );  
    if (!writef.is_open()) 
    {
        std::cout << "ERROR: файл " << file << " не доступен\n"; 
        return false; 
    }    
    for ( unsigned int i = 0; i < message.size(); i++ )
    {
        writef <<  message[i];
    }
    writef.close();
    return true;                          
}

std::vector<std::string> fileWork::readAll( const char * file )
{
    std::ifstream readf;    
    std::vector<std::string> answer;
    int i = 0;
    readf.open( file );  
    if (!readf.is_open()) 
    {
        std::cout << "ERROR: файл " << file << " не доступен\n"; 
        return { "" }; 
    }                 
    while ( readf )
    {
        answer.resize( answer.size() + 1 );
        std::getline( readf, answer[i] );
        ++i;
    }
    answer.resize( answer.size() - 1 );
    readf.close();
    return answer;                          
}