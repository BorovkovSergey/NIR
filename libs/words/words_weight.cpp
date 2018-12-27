#include "words_weight.h"
#include "../log_shell/messages.h"

namespace words
{
std::vector<word_weight> count_word_weight( std::vector<std::string>& words, std::vector<unsigned int> count, unsigned int word_count )
{
    log_shell::info("Word weight count started");

    if( words.size() != count.size() )
    {
        log_shell::error("count_word_weight количество слов в векторе words не совпадает с количеством слов в векторе count.");
    }

    std::vector<word_weight> answer(words.size());
    
    for( unsigned int i = 0; i < words.size(); i++)
    {
        answer.resize( answer.size()+1 );
        answer[i].word = words[i];
        answer[i].weight = count[i] * 1000000 / word_count;
    }

    log_shell::info("Word weight count stoped");

    return answer;
}

void count_fact_weight( parser::parsed_fact& fact, unsigned int facts_count )
{
    log_shell::info("Fact weight count started ");
    unsigned int summ_weight = 0;
    unsigned int werb_counter = 0;
    unsigned int delitel = 0;
    for( unsigned int i = 0; i < fact.words.size(); i++ )
    {
        summ_weight += fact.words[i].weight;
        if( fact.words[i].is_verb )
        {
            ++werb_counter;
        }
    }
    if( werb_counter == 0 )
    {
        delitel = facts_count;    
    }
    else
    {
        delitel = facts_count * werb_counter;
    }
    fact.weight = fact.paragraph * summ_weight / delitel;
    log_shell::info("Fact weight count stoped ");
}

}