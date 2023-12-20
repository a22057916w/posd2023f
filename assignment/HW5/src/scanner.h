# pragma once

#include <string>
#include <sstream>

class Scanner{
public:
    void setInput(std::string input){
        ss.clear();
        _input = input;
        ss.str(_input);
    }

    std::string nextToken(){
        std::string token;
        ss >> token;

        return token;
    }

    double nextDouble(){
        double token;
        ss >> token;

        return token;
    }
    
    bool isDone() const {
        return ss.eof();
    }
    
private:
    std::string _input;
    std::stringstream ss;
};