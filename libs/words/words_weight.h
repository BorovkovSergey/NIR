#include <string>
#include <vector>
#include "../parser/lindat.h"
namespace words
{
struct word_weight
{
    std::string word;
    unsigned int weight; // добмножаем числитель на 100 чтобы избавиться от остатка до сотых
};

// @brief считаем вес слова количество повторений слова / на количество слов в тексте
// words слова, count количество повторений слов. count[i] соответсвует words[i]
// word_counut - количество слов в тексте
std::vector<word_weight> count_word_weight( std::vector<std::string>& words, std::vector<unsigned int> count, unsigned int word_count );

// @brief считаем вес факта коэф абзаца * summ(words_weight) / количество фактов
void count_fact_weight( parser::parsed_fact& fact, unsigned int facts_count );
}