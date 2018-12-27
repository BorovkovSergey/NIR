#include "words_counter.h"
#include "../log_shell/messages.h"
#include "../log_shell/loglvl.h"
#include "../misc.h"

#include <iostream>
#include <ctime>
#include <vector>
#include <algorithm>

#include<boost/tokenizer.hpp>

namespace words
{
const std::string bad_symbols = "@!#$%%^&*()_=+\"№;:?[]{}\\.,|/'";

void delete_bad_symbols( std::vector<std::string>& text )
{
    log_shell::info( "Deleting bad symbols started" );
    for( int i = 0; i < text.size(); i++ )
    {
        for( unsigned int j = 0; j < bad_symbols.length(); )
        {
            if ( text[i].find( bad_symbols[j] ) != std::string::npos )
            {
                text[i].erase( text[i].find(bad_symbols[j]), 1);
            }
            else 
            {
                j++;
            }
        }
        if ( text[i].empty() || text[i] == "-" )
        {
            text.erase( text.begin() + i );
            i--;
            continue;
        }       
    }
    log_shell::info( "Bad symbols was deleted from text" );
}

void prepare_text( std::string& text )
{
    int pos = 0;
    log_shell::info( "Text preparing started." );
    for( unsigned int i = 0; i < bad_symbols.length(); )
    {
        if ( text.find( bad_symbols[i], pos ) != std::string::npos )
        {
            if( text.find( bad_symbols[i], ++pos ) != std::string::npos )
            {
                pos = text.find( bad_symbols[i], pos );
            }  
            if ( pos >= text.length() - 2 )
            {
                pos = 0;
                i++;
                continue;
            }
            if ( text[text.find( bad_symbols[i], pos ) + 1] != ' '  )
            {
                text.resize( text.length() + 1 );
                text.insert( pos + 1, 1, ' ' );
                pos++;
            }
        } 
        else
        {
            pos = 0;
            i++;
        }
    }
    misc::LowStr( text );
    if ( log_shell::check_lvl() == log_shell::DEBUG )
    {
        log_shell::info( "Text was \"" + text + "\" prepared" );
    }
    else
    {
        log_shell::info( "Text was prepared" );
    }
    

}

std::vector<std::string> word_parser( std::string& text )
{
    log_shell::info( "Word parsing started" );
    prepare_text( text );

    typedef boost::tokenizer<boost::char_separator<char>> tokenizer;
    std::vector<std::string> answer;

    boost::char_separator<char> sep{" "};
    tokenizer tok{text, sep};

    for( const auto &tok_iter : tok )
    {
        if( bad_symbols.find( tok_iter ) == std::string::npos )
        {
            answer.push_back( tok_iter );
        }
    }
    answer.erase(answer.end());

    // удаляем лишние символы из текста
    delete_bad_symbols( answer );
    
    log_shell::info( "Text parsing success" );
    return answer;
}

std::vector<std::string> remove_duplicate( std::vector<std::string>& words )
{
    log_shell::info( "Removing duplicate started" );
    std::vector<std::string> answer;
    for( unsigned int i = 0; i < words.size(); i++ )
    {
        if ( std::find( answer.begin(), answer.end(), words[i] ) == answer.end() )
        {
             answer.push_back( words[i] );
        }
    }
    log_shell::info( "Removing duplicate success" );
    return answer;    
}

std::vector<unsigned int> word_count( std::vector<std::string>& words_, std::vector<std::string>& words )
{
    log_shell::info( "Word count started" );
    std::vector<unsigned int> counts( words.size() );
    for( unsigned int i = 0; i < words_.size(); i++ )
    {
        if ( std::find(words.begin(), words.end(), words_[i] ) != words.end() && !words_[i].empty() )
        {
            counts[ std::distance( words.begin(), std::find(words.begin(), words.end(), words_[i] ) ) ]++;
        }
    }
    log_shell::info( "Words count success" );
    return counts;
}

}
