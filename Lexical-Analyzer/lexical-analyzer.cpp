#include "lexical-analyzer.h"

Analyzer::Analyzer(std::ifstream& file) :source_file(file) {}

Analyzer::~Analyzer() {
    source_file.close();
}

void Analyzer::run_analyzer() {
    read_in_starting_state();
}


bool  Analyzer::char_is_character(const char& ch) const {
    if (std::find(this->abc.begin(), this->abc.end(), ch) != this->abc.end()) {
        std::cout << ch;
        //std::cout << " is a character" << std::endl;
        return true;
    }
    //std::cout << "ch is not a character" << std::endl;
    return false;
}


bool Analyzer::char_is_num(const char& ch) const {
    if (std::find(this->num.begin(), this->num.end(), ch) != this->num.end()) {
        return true;
    }

    return false;
}

void Analyzer::error(std::string err_msg) const {
    std::cerr << err_msg << std::endl;
    this->~Analyzer();
    exit(-1);
}



void Analyzer::read_in_starting_state() {
    curr_char = this->source_file.get();
    //std::cout << curr_char << std::endl;
    //std::cout << "Starting state" << std::endl;

    if (char_is_character(curr_char))
        read_in_identifier();

    else if (char_is_num(curr_char))
        read_in_number();

    else if (curr_char == '{')
        read_in_comment();

    else if (curr_char == '}')
        error("There was no opening '{'");

    else if (curr_char == '(')
        read_in_found_opening_paranthesis();

    else if (curr_char == '*')
        error("Unexpected '*'");

    else if (curr_char == ')')
        error("Opening '(' missing");

    else if (curr_char == ':')
        read_in_punct();

    else if (curr_char == '=')
        error("Unexpected '='");

    else if (curr_char == '<')
        read_in_less_then();

    else if (curr_char == '>')
        read_in_bigger_then();

    else if (curr_char == ' ')
        read_in_starting_state();

    else if (curr_char == '$')
        read_in_end_of_program();

    else
        error("Char is forbidden here");

}


void Analyzer::read_in_identifier() {
    curr_char = source_file.get();
    //std::cout << curr_char << std::endl;

    if (char_is_character(curr_char))
        read_in_identifier();

    else if (char_is_num(curr_char))
        read_in_identifier();

    else if (curr_char == '{')
        read_in_end_of_identifier();

    else if (curr_char == '}')
        read_in_end_of_identifier();

    else if (curr_char == '(')
        read_in_end_of_identifier();

    else if (curr_char == '*')
        read_in_end_of_identifier();

    else if (curr_char == ')')
        read_in_end_of_identifier();

    else if (curr_char == ':')
        read_in_punct();

    else if (curr_char == '=')
        read_in_end_of_identifier();

    else if (curr_char == '<')
        read_in_end_of_identifier();

    else if (curr_char == '>')
        read_in_end_of_identifier();

    else if (curr_char == ' ')
        read_in_end_of_identifier();

    else if (curr_char == '$')
        read_in_end_of_identifier();

    else
        read_in_end_of_identifier();
}


void Analyzer::read_in_end_of_identifier() {
    std::cout << "  is an identifier";
    std::cout << std::endl; std::cout << curr_char;
    source_file.putback(curr_char);
    //std::cout << curr_char << std::endl;
    read_in_starting_state();
}


void Analyzer::read_in_number() {
    curr_char = source_file.get();
    std::cout << curr_char << std::endl;

    if (char_is_character(curr_char))
        read_in_end_of_number();

    else if (char_is_num(curr_char))
        read_in_number();

    else if (curr_char == '{')
        read_in_end_of_number();

    else if (curr_char == '}')
        read_in_end_of_number();

    else if (curr_char == '(')
        read_in_end_of_number();

    else if (curr_char == '*')
        read_in_end_of_number();

    else if (curr_char == ')')
        read_in_end_of_number();

    else if (curr_char == ':')
        read_in_end_of_number();

    else if (curr_char == '=')
        read_in_end_of_number();

    else if (curr_char == '<')
        read_in_end_of_number();

    else if (curr_char == '>')
        read_in_end_of_number();

    else if (curr_char == ' ')
        read_in_end_of_number();

    else if (curr_char == '$')
        read_in_end_of_number();

    else
        read_in_end_of_number();
}

void Analyzer::read_in_end_of_number() {
    source_file.putback(curr_char);
    std::cout << curr_char << std::endl;
    read_in_starting_state();
}

void Analyzer::read_in_comment() {
    curr_char = source_file.get();
    std::cout << curr_char;

    if (char_is_character(curr_char))
        read_in_comment();

    else if (char_is_num(curr_char))
        read_in_comment();

    else if (curr_char == '{')
        read_in_comment();

    else if (curr_char == '}')
        read_in_end_of_comment();

    else if (curr_char == '(')
        read_in_comment();

    else if (curr_char == '*')
        read_in_comment();

    else if (curr_char == ')')
        read_in_comment();

    else if (curr_char == ':')
        read_in_comment();

    else if (curr_char == '=')
        read_in_comment();

    else if (curr_char == '<')
        read_in_comment();

    else if (curr_char == '>')
        read_in_comment();

    else if (curr_char == ' ')
        read_in_comment();

    else if (curr_char == '$')
        read_in_comment();

    else
        read_in_comment();
}


void Analyzer::read_in_end_of_comment() {
    std::cout << " is a comment" << std::endl;
    read_in_starting_state();
}


void Analyzer::read_in_found_opening_paranthesis() {
    curr_char = source_file.get();

    if (char_is_character(curr_char))
        read_in_correcting();

    else if (char_is_num(curr_char))
        read_in_correcting();

    else if (curr_char == '{')
        read_in_correcting();

    else if (curr_char == '}')
        read_in_correcting();

    else if (curr_char == '(')
        read_in_correcting();

    else if (curr_char == '*')
        read_in_big_comment();

    else if (curr_char == ')')
        read_in_correcting();

    else if (curr_char == ':')
        read_in_correcting();

    else if (curr_char == '=')
        read_in_correcting();

    else if (curr_char == '<')
        read_in_correcting();

    else if (curr_char == '>')
        read_in_correcting();

    else if (curr_char == ' ')
        read_in_correcting();

    else if (curr_char == '$')
        error("End of program is forbidden after '('");

    else
        read_in_correcting();
}

void Analyzer::read_in_big_comment() {
    curr_char = source_file.get();

    if (char_is_character(curr_char))
        read_in_big_comment();

    else if (char_is_num(curr_char))
        read_in_big_comment();

    else if (curr_char == '{')
        read_in_big_comment();

    else if (curr_char == '}')
        read_in_big_comment();

    else if (curr_char == '(')
        read_in_big_comment();

    else if (curr_char == '*')
        read_in_star_in_big_comment();

    else if (curr_char == ')')
        read_in_big_comment();

    else if (curr_char == ':')
        read_in_big_comment();

    else if (curr_char == '=')
        read_in_big_comment();

    else if (curr_char == '<')
        read_in_big_comment();

    else if (curr_char == '>')
        read_in_big_comment();

    else if (curr_char == ' ')
        read_in_big_comment();

    else if (curr_char == '$')
        read_in_big_comment();

    else
        read_in_big_comment();
}

void Analyzer::read_in_star_in_big_comment() {
    curr_char = source_file.get();

    if (char_is_character(curr_char))
        read_in_big_comment();

    else if (char_is_num(curr_char))
        read_in_big_comment();

    else if (curr_char == '{')
        read_in_big_comment();

    else if (curr_char == '}')
        read_in_big_comment();

    else if (curr_char == '(')
        read_in_big_comment();

    else if (curr_char == '*')
        read_in_star_in_big_comment();

    else if (curr_char == ')')
        read_in_end_of_big_comment();

    else if (curr_char == ':')
        read_in_big_comment();

    else if (curr_char == '=')
        read_in_big_comment();

    else if (curr_char == '<')
        read_in_big_comment();

    else if (curr_char == '>')
        read_in_big_comment();

    else if (curr_char == ' ')
        read_in_big_comment();

    else if (curr_char == '$')
        read_in_big_comment();

    else
        read_in_big_comment();
}


void Analyzer::read_in_end_of_big_comment() {
    std::cout << " is a comment" << std::endl;
    read_in_starting_state();
}

void Analyzer::read_in_punct() {
    std::cout << curr_char;
    curr_char = source_file.get();
    std::cout << curr_char;

    if (char_is_character(curr_char))
        read_in_correcting();

    else if (char_is_num(curr_char))
        read_in_correcting();

    else if (curr_char == '{')
        read_in_correcting();

    else if (curr_char == '}')
        read_in_correcting();

    else if (curr_char == '(')
        read_in_correcting();

    else if (curr_char == '*')
        read_in_correcting();

    else if (curr_char == ')')
        read_in_correcting();

    else if (curr_char == ':')
        read_in_correcting();

    else if (curr_char == '=')
        read_in_punct_equality();

    else if (curr_char == '<')
        read_in_correcting();

    else if (curr_char == '>')
        read_in_correcting();

    else if (curr_char == ' ')
        read_in_correcting();

    else if (curr_char == '$')
        error("End of program is forbidden after ':'");

    else
        read_in_correcting();
}

void Analyzer::read_in_punct_equality() {
    std::cout << " is a token" << std::endl;
    read_in_starting_state();
}


void Analyzer::read_in_less_then() {
    std::cout << curr_char;
    curr_char = source_file.get();
    std::cout << curr_char;

    if (char_is_character(curr_char))
        read_in_correcting();

    else if (char_is_num(curr_char))
        read_in_correcting();

    else if (curr_char == '{')
        read_in_correcting();

    else if (curr_char == '}')
        read_in_correcting();

    else if (curr_char == '(')
        read_in_correcting();

    else if (curr_char == '*')
        read_in_correcting();

    else if (curr_char == ')')
        read_in_correcting();

    else if (curr_char == ':')
        read_in_correcting();

    else if (curr_char == '=')
        read_in_less_then_or_equal();

    else if (curr_char == '<')
        read_in_correcting();

    else if (curr_char == '>')
        read_in_less_then_and_bigger_then();

    else if (curr_char == ' ')
        read_in_correcting();

    else if (curr_char == '$')
        error("End of program is forbidden after '<'");

    else
        read_in_correcting();
}

void Analyzer::read_in_less_then_or_equal() {
    std::cout << " is a token" << std::endl;
    read_in_starting_state();
}

void Analyzer::read_in_less_then_and_bigger_then() {
    std::cout << " is a token" << std::endl;
    read_in_starting_state();
}

void Analyzer::read_in_bigger_then() {
    curr_char = source_file.get();

    if (char_is_character(curr_char))
        read_in_correcting();

    else if (char_is_num(curr_char))
        read_in_correcting();

    else if (curr_char == '{')
        read_in_correcting();

    else if (curr_char == '}')
        read_in_correcting();

    else if (curr_char == '(')
        read_in_correcting();

    else if (curr_char == '*')
        read_in_correcting();

    else if (curr_char == ')')
        read_in_correcting();

    else if (curr_char == ':')
        read_in_correcting();

    else if (curr_char == '=')
        read_in_bigger_then_or_equal();

    else if (curr_char == '<')
        read_in_correcting();

    else if (curr_char == '>')
        read_in_correcting();

    else if (curr_char == ' ')
        read_in_correcting();

    else if (curr_char == '$')
        error("End of program is forbidden after '>'");

    else
        read_in_correcting();
}


void Analyzer::read_in_bigger_then_or_equal() {
    std::cout << " is a token" << std::endl;
    read_in_starting_state();
}


void Analyzer::read_in_correcting() {
    source_file.putback(curr_char);
    read_in_starting_state();
}


void Analyzer::read_in_end_of_program() {
    std::cout << "\nThe input has been analyzed successfully!" << std::endl;
}