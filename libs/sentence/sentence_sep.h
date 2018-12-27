#include <vector>
#include <string>

namespace sentence
{

// @brief разделяем текст на параграфы
// мб не придется юзать :((
std::vector<std::string> seporation_by_paragraph( const std::string& text );

// @brief разделяет текст на предложения. Каждое предложение заносится в вектор.
std::vector<std::string> seporation( const std::string& sentence );



}