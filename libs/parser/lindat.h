#include <vector>
#include <string>

namespace parser
{
    struct parsed_word
    {
        std::string word;       // слово
        unsigned int depend;    // номер зависимого слова
        bool is_verb;           // если глагол то true
        unsigned int weight;
        bool is_punct;
        unsigned int index;
    };

     struct parsed_fact
     {
         std::vector<parsed_word> words;
         std::string sentence;
         unsigned int weight;
         unsigned int paragraph;
         bool use_or_not;
     };

    // @brief парсим предложение при помощи API сайтика lindat.mff.cuni.cz
    std::string parse_sentence( std::string& sentence );

    // @brief парсим ответ от сайтика
    std::vector<parsed_word> parse_lindat_answer( std::string& text );

    // @brief из распаршеного предложения получаем факты ( глагол и зависимые от него слова )
    parsed_fact make_facts( std::vector<parsed_word>& parsed_words, std::string& sentence );
}