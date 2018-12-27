#include "sentence_sep.h"
#include "../log_shell/messages.h"

namespace sentence
{

std::vector<std::string> seporation( const std::string& sentence ) 
{
    log_shell::info("Text seporation by sentences started.");
    std::vector<std::string> answer;
    std::string buf;
    int start_pos = 0;
    bool sentence_found = false;
    bool quotes_found = false;  
    for ( unsigned int i = 0; i < sentence.length(); i++ )
    {
        // пихаем в вектор предложение когда нашли
        if ( sentence_found )
        {
            sentence_found = false;
            answer.push_back( sentence.substr( start_pos, i - start_pos ) );
            start_pos = i; 
        }

        if ( sentence[i] == '"' && !quotes_found )
        {
            quotes_found = true;
            continue;
        }
        else if ( sentence[i] == '"' && quotes_found )
        {
            quotes_found = false;
            continue;
        }
        if ( quotes_found )
        {
            continue;
        }
        
        if ( sentence[i] == '.' || sentence[i] == '!' || sentence[i] == '?' )
        {
            if ( sentence[i] == '.' && sentence[i+1] == '.' && sentence[i+1] == '.' ||
                 sentence[i] == '?' && sentence[i+1] == '?' && sentence[i+1] == '?' || 
                 sentence[i] == '!' && sentence[i+1] == '!' && sentence[i+1] == '!' )
            {
                i += 2;
            }
            sentence_found = true;
            continue;
        }
    }
    answer.push_back( sentence.substr( start_pos, sentence.length() ) ); 
    log_shell::info("Text seporation by sentences done.");
    return answer;
}


std::vector<std::string> seporation_by_paragraph( std::string text )
{   
    int pos_p_end = 0;
    std::vector<std::string> answer;
    for( unsigned int i = 0; ; i++ )
    {
        pos_p_end = text.find( "\n" );
        if ( pos_p_end != std::string::npos )
        {
            answer.resize( answer.size() + 1 );
            answer.push_back( text.substr( 0, pos_p_end ) );
            text.erase( 0, pos_p_end + 1 );
        }
        else
        {
            break;
        }
    }
}

}