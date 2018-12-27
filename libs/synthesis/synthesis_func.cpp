#include "synthesis_func.h"
#include "../log_shell/messages.h"

#include <algorithm>

namespace synthesis
{
    void choose_facts( std::vector<parser::parsed_fact>& facts )
    {
        log_shell::info( "Start choosing facts" );
        std::vector<unsigned int> facts_weight;
        int buf;
        for( unsigned int i = 0; i < facts.size(); i++ )
        {
            facts_weight.push_back( facts[i].weight );
        }

        std::sort( facts_weight.begin(), facts_weight.end() );
        facts_weight.erase( facts_weight.begin(), facts_weight.end() - facts_weight.size() / 2 );
        for( unsigned int i = 0; i < facts.size(); i++ )
        {
            if( find( facts_weight.begin(), facts_weight.end(), facts[i].weight ) != facts_weight.end() )
            {
                facts[i].use_or_not = true;
            }
            else
            {
                facts[i].use_or_not = false;
            }
        }
        log_shell::info( "Choosing facts was stoped" );
    }
}