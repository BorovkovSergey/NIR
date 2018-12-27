// Rules:
//          * в тексте не должно быть сокращений;
//          * символы " . ! ? " всегда конец предложения;
//          * предложение занесенное в ковычки не счиатется предложением;

#include "libs/files_working/fileWork.h"
#include "libs/log_shell/messages.h"
#include "libs/log_shell/loglvl.h"
#include "libs/sentence/sentence_sep.h"
#include "libs/words/words_counter.h"
#include "libs/synthesis/synthesis_func.h"
#include "libs/consts.h"

#include <iostream>
#include <ctime>
#include <vector>
#include <algorithm>
#include <string>

#include<boost/tokenizer.hpp>

int main ()
{
    std::vector<std::string> text; // исходный текст
    std::vector<std::string> sentences;  // временная переменная с предложениями одного абзаца
    std::vector<std::string> non_duplicate_words; // слова используемые в тексте, без повторений
    std::vector<unsigned int> words_count; // количество повторений слова в тексте, words_count[i] соответсвует non_duplicate_words[i]s
    std::vector<std::string> words; // все слова которые используется в тексте ( с повторением )
    std::vector<words::word_weight> words_with_weight; // вектор в котором структура со словом и весом
    std::vector<parser::parsed_word> parsed_text; // предложение с зависимостями слов
    std::vector<parser::parsed_fact> facts; 
    std::string text_str; // исходный текст, в строке
    std::string buf;
    
    unsigned int sentence_count = 0;
    unsigned int paragraph_coef = FIRST_PARAGRAPH;
    unsigned int buf_int = 0;
    // берем текст из файла в вектор
    text = fileWork::readAll( "text" );

    // запихиваем исходный текст в строковую переменную, чтобы юзать в функциях
    for( unsigned int i = 0; i < text.size(); i++ )
    {
        text_str += text[i];
    }

    // парсим текст на слова и записываем все уникальные слова в отдельный вектор
    words = words::word_parser( text_str );
    non_duplicate_words = words::remove_duplicate( words );

    // считаем количество повторений слов
    words_count = words::word_count( words, non_duplicate_words );

    // считаем вес слов
    words_with_weight = words::count_word_weight( non_duplicate_words, words_count, words.size() );

    for(unsigned int i = 0; i < text.size(); i++ )
    {
        sentences.clear();
        // разбиваем абзацы по предложениям [i] - номер абзаца
        sentences = sentence::seporation( text[i] );

        /* расчет коэффициента абзаца первые 3 абзаца - 8, 
         * последние 3 - 7, остальные - 3 */ 
        if( i > 3 && i < text.size() - 4 )
        {
            paragraph_coef = MIDLE_PARAGRAPH;
        }
        else if ( i >= text.size() - 4 )
        {
            paragraph_coef = LAST_PARAGRAPH;
        }

        for( unsigned int j = 0; j < sentences.size(); j++ )
        {
            // юзаем API сайтик подробнее в хидере
            buf = parser::parse_sentence( sentences[j] );
            // парсим ответ сайтика
            parsed_text = parser::parse_lindat_answer( buf );
            buf.clear();
            // получаем факты из ответов
            if( sentences[j].length() > 20 ) // костыль, я не знаю почему попадаются пустые строки todo: fix it ;[
            {
                facts.push_back( parser::make_facts( parsed_text, sentences[j] ) );
                facts[buf_int].paragraph = paragraph_coef;
                ++buf_int;
            }
            
        }
    }
    for(unsigned int i = 0; i < facts.size(); i++)
    {
        for(unsigned int j = 0; j < facts[i].words.size(); j++ )
        {
            for( unsigned int l = 0; l < words_with_weight.size(); l++ )
            {
                if( words_with_weight[l].word == facts[i].words[j].word )
                {
                    facts[i].words[j].weight = words_with_weight[l].weight;
                }
            }
        }
    }
    for( unsigned int i = 0; i < facts.size(); i++ )
    {       
        words::count_fact_weight( facts[i], facts.size() );
    }

    synthesis::choose_facts( facts );
    
    for( unsigned int i = 0; i < facts.size(); i++ )
    {
        if( facts[i].use_or_not )
        {
            std::cout << facts[i].sentence;
        }
    }
    return 0;
}