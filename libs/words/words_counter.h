#include <vector>
#include <string>

namespace words
{

// @brief получает вектор слов из которых состоит предложение
std::vector<std::string> word_parser( std::string& text );

// @brief удаляет из текста все символы кроме букв
void delete_non_word_symbols( std::string& text );

// @brief удаление повторяемых слов
std::vector<std::string> remove_duplicate ( std::vector<std::string>& words );

// @brief считает количество повторяемых слов words_ 
// @param words_ подсчитываемая строка
// @param words строка без дублируемых символов
std::vector<unsigned int> word_count ( std::vector<std::string>& words_, std::vector<std::string>& words );
}
