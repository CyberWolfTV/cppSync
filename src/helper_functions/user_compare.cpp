#include "helper_functions.hpp"

#include <iostream>
#include <fstream>
#include <string>
#include <vector>


#define PAIR std::pair<const std::string, std::string>


void user_compare(Location location){
    std::cout << "Which state do u want to compare?"        << std::endl;
    std::cout << "First state (usually the older one): "    << std::endl;
    std::string target = ".cppSync/hashes/" + get_choice(&location.path);

    std::cout                                               << std::endl;
    std::cout << "Second state (usually the newer one): "   << std::endl;
    std::string source = ".cppSync/hashes/" + get_choice(&location.path);

    location.compare(source, target);

    print_compared(&location.changes);
}


void print_compared(struct Location::comp_changes *changes){
    std::string filename = ".cppSync/what_changed/";
    filename += Location::DATE_TIME;
    std::fstream output_file;
    output_file.open(filename,std::ios::out);

    std::cout   << "These Files have been created:"  << std::endl;
    output_file << "These Files have been created:"  << std::endl;
    if(changes->created.empty()){
        std::cout   << "No Files have been created." << std::endl;
        output_file << "No Files have been created." << std::endl;
    } else{
        for(std::string& i : changes->created){
            std::cout   << i                         << std::endl;
            output_file << i                         << std::endl;
        }
    }
    output_file << std::endl;
    std::cout   << std::endl;

    std::cout   << "These Files have been changed:"  << std::endl;
    output_file << "These Files have been changed:"  << std::endl;
    if(changes->created.empty()){
        std::cout   << "No Files have been changed." << std::endl;
        output_file << "No Files have been changed." << std::endl;
    } else{
        for(std::string& i : changes->changed){
            std::cout   << i                         << std::endl;
            output_file << i                         << std::endl;
        }
    }
    output_file << std::endl;
    std::cout   << std::endl;

    std::cout   << "These Files have been deleted:"  << std::endl;
    output_file << "These Files have been deleted:"  << std::endl;
    if(changes->deleted.empty()){
        std::cout   << "No Files have been deleted." << std::endl;
        output_file << "No Files have been deleted." << std::endl;
    } else{
        for(std::string &i: changes->deleted){
            std::cout   << i                         << std::endl;
            output_file << i                         << std::endl;
        }
    }
    output_file << std::endl;
    std::cout   << std::endl;

    std::cout   << "These Files have been moved:"    << std::endl;
    output_file << "These Files have been moved:"    << std::endl;
    if(changes->moved.empty()){
        std::cout   << "No Files have been moved."   << std::endl;
        output_file << "No Files have been moved."   << std::endl;
    } else{
        for(PAIR &i: changes->moved){
            std::cout   << "from "   << i.second     << std::endl;
            std::cout   << "    -> " << i.first      << std::endl;
            output_file << "from "   << i.second     << std::endl;
            output_file << "    -> " << i.first      << std::endl;
        }
    }
}
