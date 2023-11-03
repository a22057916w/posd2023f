#pragma once

#include "file.h"
#include "folder.h"
#include "visitor.h"
#include <fstream>
#include <iostream>
#include <sstream>

class StreamOutVisitor : public Visitor {
public:
    void visitFile(File * file) override {
        std::ifstream t(file->path());
        std::stringstream buffer;

        buffer << t.rdbuf(); 

        _result += "_____________________________________________\n";
        _result += file->path() + "\n";
        _result += "---------------------------------------------\n";
        _result += buffer.str() + "\n";
        _result += "_____________________________________________\n";
    }

    void visitFolder(Folder * folder) override {
        Iterator * it = folder->createIterator();

        for(it->first(); !it->isDone(); it->next()) {
            it->currentItem()->accept(this);
            if(dynamic_cast<File *>(it->currentItem()))
                _result += "\n";
        }
    }

    string getResult() const {
        return _result;
    }

private:
    string _result;
};