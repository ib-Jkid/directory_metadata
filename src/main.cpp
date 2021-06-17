#include <string>
#include <iostream>
#include <filesystem>
#include <chrono>
#include <algorithm>
#include <iomanip>
#include <fstream>
#include <list>
#include <cmath>

#include "filestructure.h"

int main(int argc, const char* argv[]) {

    try {
        const auto path = argc == 2 ? std::filesystem::path { argv[1] } : std::filesystem::current_path();

        std::filesystem::directory_entry base_entry_dir(path);

        std::string file_name = "";

        uintmax_t file_size = 0;

        auto cftime = std::chrono::system_clock::to_time_t(std::chrono::file_clock::to_sys(base_entry_dir.last_write_time()));

        std::string last_modified = std::asctime(std::localtime(&cftime));

        FileType file_type = FileType::file;

        if(base_entry_dir.is_directory()) {
            
            file_type = FileType::directory;
        }else {
            file_size = base_entry_dir.file_size();

        
        }

        FileStructure base_structure(file_name,file_type,last_modified,file_size, path); 

        base_structure.add_children(path);

        base_structure.print_structure(0);
    }catch(const std::runtime_error& error) {
        std::cerr << error.what();
    }

    

   
       
}