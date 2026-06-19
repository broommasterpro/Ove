#pragma once
#include <string>
#include <vector>


enum class TokenType {
    exit,
    int_lit,
    semi
};

struct Token {
    TokenType type;
    std::optional<std::string> value;
};


//reading more than one semi -> fix
//no semi -> fix
//consume whitespace -> fix
//1 byte consumer -> fix
class Tokenizer {
public:
    inline explicit  Tokenizer(std::string src)
        : m_src(std::move(src)){

    }

    std::vector<Token>tokenize() {
        std::vector<Token> tokens;
        std::string buf;

        while (peak().has_value()) {
            if (std::isalpha(peak().value())){
                buf.push_back(consume());
                while (peak().has_value() && std::isalnum(peak().value())) {
                    buf.push_back(consume());
                }
                if (buf == "exit"){
                    tokens.push_back({.type = TokenType::exit});
                    buf.clear();
                    continue;
                }
                else {
                    std::cerr << "This is messed up!" << std::endl;
                    exit(EXIT_FAILURE);
                }
            }
            else if (std::isdigit(peak().value())) {
                buf.push_back(consume());
                while (peak().has_value() && std::isdigit(peak().value())) {
                    buf.push_back(consume());
                }
                tokens.push_back({.type = TokenType::int_lit, .value = buf});
                buf.clear();
                continue;
            }
            else if (peak().value() == ';') {
                consume();
                tokens.push_back({.type = TokenType::semi});
                continue;
            }
            else if (std::isspace(peak().value())) {
                consume();
                continue;
            }
            else {
                std::cerr << "This is messed up!" << std::endl;
                exit(EXIT_FAILURE);
            }
        }
        return tokens;
    }
private:
    //peaking and consuming here
    [[nodiscard]] std::optional<char> peak(int ahead = 1)const {
        if (m_index + ahead >= m_src.length()) {
            return {};
        }
        else {
            return m_src.at(m_index);
        }
    }

    char consume() {
        //need to change the increment stuff
        return m_src.at(m_index++);
    }

    const std::string m_src;
    int m_index = 0;

};