#include "Statement.h"

Statement::Statement(std::string statement_body, std::string label, int line_number){
    std::vector<Token*> tokens;
    DO dostmt;
    SUBROUTINE substmt;
    tokens.push_back(&dostmt);
    tokens.push_back(&substmt);
    bool tokenfound = false;
    for(std::vector<std::string>::size_type i = 0; i != tokens.size(); i++){ 
        if(tokens[i]->isValid(statement_body)){
            if(tokenfound){
                std::cerr << StringConstants::ERROR_TAG << "Line [" << line_number << "] matches multiple tokens. {'" << statement_body << "'}." << std::endl;
            }
            std::cout << "[" << i << "] " << statement_body << std::endl;
            tokenfound = true;
        }
    };
}