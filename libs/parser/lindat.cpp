#include "lindat.h"
#include "../files_working/fileWork.h"
#include "../log_shell/messages.h"
#include <iostream>
#include <algorithm>
namespace parser
{


static void erasex(std::string& text, std::string target, unsigned int count)
{
    for( unsigned int i = 0; i < count; i++)
    {
        text.erase( 0, text.find( target, text.find( target ) + 1 ) );
    }
    text.erase( text.find( target, text.find( target ) + 1 ) , text.length() - text.find( target ) );   
    text.erase( 0 , 2 );  
}

std::string parse_sentence( std::string& sentence )
{
    std::string answer;
    log_shell::info("Parse sentence started.");
    std::string request = "curl --data \
                          'model=russian-syntagrus-ud-2.3-181115&tokenizer=&tagger=&parser=&data=" + sentence + 
                          "' http://lindat.mff.cuni.cz/services/udpipe/api/process >temp";
    system( request.c_str() );
     
    std::vector<std::string> lindat_answer = fileWork::readAll("temp");
    for( unsigned int i = 0; i < lindat_answer.size(); i++ )
    {
        answer += lindat_answer[i];
    }
    log_shell::info("Parse sentence stoped.");
    return answer;
}

std::vector<parsed_word> parse_lindat_answer( std::string& text )
{
    log_shell::info("Parse lindat answer started.");
    std::string buf;
    std::vector<parsed_word> answer(1);
    for( unsigned int i = 0; ; )
    {   
        if( text.find("\\n" + std::to_string(++i) + "\\t") == std::string::npos )
        {
            break;
        }
        buf = text.substr( text.find("\\n" + std::to_string( i ) + "\\t" ) + 2, 
                           text.find( "\\n" + std::to_string( ++i ) + "\\t" ) - text.find( "\\n" + std::to_string( --i ) + "\\t" ) - 2 );
        answer.resize( answer.size() + 1 );
        answer[i].word = ( buf.substr( buf.find( "\\t" ) + 2,  buf.find( "\\t", buf.find( "\\t" ) + 2 ) -  buf.find( "\\t" ) - 2 ) );
        if( buf.find("\\tVERB\\t") != std::string::npos )
        {
            answer[i].is_verb = true;
        }
        else
        {
            answer[i].is_verb = false;
        }
        if ( buf.find("\\tPUNCT\\t") != std::string::npos )
        {
            answer[i].is_punct = true;
        }
        erasex(buf, "\\t", 5);
        answer[i].depend = std::atoi( buf.c_str() );
    }
    answer.erase( answer.begin(), answer.begin() + 1 );
    log_shell::info("Parse lindat answer stoped.");
    return answer;
}

parsed_fact make_facts( std::vector<parsed_word>& parsed_words, std::string& sentence )
{
    log_shell::info("Making facts was started");

    std::vector<unsigned int> verbs;
    parsed_fact answer;
    answer.sentence = sentence;
    for( unsigned int i = 0; i < parsed_words.size(); ++i )
    {
        if( parsed_words[i].is_verb || parsed_words[i].depend == 0 )
        {
            verbs.push_back( i + 1 );
        }
    }

    for( unsigned int i = 0; i < parsed_words.size(); i++ )
    {
        if ( parsed_words[i].is_punct )
        {
            continue;
        }
        if( find( verbs.begin(), verbs.end(), parsed_words[i].depend ) != verbs.end() || parsed_words[i].is_verb || parsed_words[i].depend == 0 )
        {
            answer.words.push_back( parsed_words[i] );
        }
    }
    log_shell::info("Making facts was stopped");
    return answer;
}

}    