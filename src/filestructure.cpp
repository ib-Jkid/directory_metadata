#include "filestructure.h"


void print_spaces(int number) {
    for(int x = 0; x < number; x++) {
        std::cout << "\t";
    }
}



FileStructure::FileStructure(std::string name, FileType file_type, std::string last_modified, uintmax_t file_size, std::string path )
: name(name), file_type(file_type), file_size(file_size), last_modified(last_modified), directory_count(0), file_count(0), path(path)  {}

void FileStructure::add_child(FileStructure child) {

    for (std::list<FileStructure>::iterator it = this->children.begin(); it != this->children.end(); ++it) {

        if(it->get_last_modified() > child.get_last_modified()) {

            this->children.insert(it, child);
            return;

        }
    }

    this->children.push_front(child);
}


std::string FileStructure::get_name() const {
    return this->name;
}


std::string FileStructure::get_last_modified() const {
    return this->last_modified;
}



void FileStructure::print_structure(int level) {
    
    
    print_spaces(level);
    std::cout << "Path: " << this->path<< "/" << this->name << "\n";
    print_spaces(level);
    std::cout << "Type: " << ((this->file_type == FileType::directory)? "Directory" : "File") << "\n";
    print_spaces(level);

    if(this->file_type == FileType::directory) {
        std::cout << "Files: " << this->file_count << "\n";
        print_spaces(level);

        std::cout << "Directories: " << this->directory_count << "\n";
        print_spaces(level);
    }

    std::cout << "Bytes: " << HumanReadable{this->file_size} << "\n";
    print_spaces(level);

    std::cout << "Last Modified At: " << this->last_modified << "\n";
    
    std::cout << "\n\n";


    if(this->file_type == FileType::directory) {
    
        for(std::list<FileStructure>::iterator it = this->children.begin(); it != this->children.end(); ++it) {

            it->print_structure(level+1);
            
        }

    }

    

}


void FileStructure::add_children(std::string path) {

    path += "/" + this->name;

    

    for (std::filesystem::directory_entry const& entry : std::filesystem::directory_iterator(path)) {

        std::string file_name = entry.path().filename();

        uintmax_t file_size = 0;

        auto cftime = std::chrono::system_clock::to_time_t(std::chrono::file_clock::to_sys(entry.last_write_time()));

        std::string last_modified = std::asctime(std::localtime(&cftime));

        FileType file_type = FileType::file;

        if(entry.is_directory()) {
            
            file_type = FileType::directory;
        }else {
            file_size = entry.file_size();

            
        }

        FileStructure structure(file_name,file_type,last_modified,file_size, path); 

        this->add_child(structure);

        if(entry.is_directory()) {
            this->directory_count++;
            structure.add_children(path);
        }else {
            this->file_count++;
        }

    }
}