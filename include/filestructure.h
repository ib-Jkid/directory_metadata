#pragma once
#include <string>
#include <list>
#include <filesystem>
#include <cmath>
#include <iostream>

enum FileType {directory,file};


struct HumanReadable {
    uintmax_t size {};
 
    template <typename Os> friend Os& operator<< (Os& os, HumanReadable hr)
    {
        int i{};
        double mantissa = hr.size;
        for (; mantissa >= 1024.; ++i) {
            mantissa /= 1024.;
        }
        mantissa = std::ceil(mantissa * 10.) / 10.;
        os << mantissa << "BKMGTPE"[i];
        return i == 0 ? os : os << "B (" << hr.size << ')';
    }
};


class FileStructure {

    private:

        std::string name;
        FileType file_type;
        std::string last_modified;
        uintmax_t file_size;
        std::list<FileStructure> children;
        uint directory_count;
        uint file_count;
        std::string path;
        void add_child(FileStructure);

    public: 

        std::string get_name() const;

        std::string get_last_modified() const;

        FileStructure(std::string name, FileType file_type, std::string last_modified, uintmax_t file_size, std::string path );

        void print_structure(int);

        void add_children(std::string);

};


