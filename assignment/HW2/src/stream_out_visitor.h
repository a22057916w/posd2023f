#pragma once

#include "file.h"
#include "folder.h"
#include "visitor.h"


#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

class StreamOutVisitor : public Visitor {
public:
    void visitFile(File * file) { 
        std::ifstream fin(file->path());

        if(!fin.is_open())
            throw std::string("Open Fail.");
        
        std::stringstream input_string;
        // Put the file path
        input_string << "_____________________________________________\n";
        input_string << file->path() << "\n";
        input_string << "---------------------------------------------\n";

        // Read and output the file contents line by line
        std::string line;
        while (std::getline(fin, line)) {
            input_string << line << std::endl;
        }
        input_string << "_____________________________________________\n";

        fin.close();

        _output += input_string.str();
        
    }

    void visitFolder(Folder * folder) {
        auto it = folder->createIterator();
         for(it->first(); !it->isDone(); it->next()) {
            it->currentItem()->accept(this);

            if(it->currentItem()->type() == "file")
                _output += "\n";
         }
    }

    string getResult() const { return _output; }

private:
    string _name;
    string _output = "";
};