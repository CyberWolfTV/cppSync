#include "helper_functions.hpp"

#include <string>
#include <iostream>


bool ask(const std::string& question, char default_answer){
    std::cout << question;
    std::string answer;
    while(std::getline(std::cin, answer)){
        std::cout << question << std::endl;
        if(answer.empty()) {
            answer = default_answer;
        }
        if(answer == "n" or answer == "N"){
            return false;
        }
        if(answer == "y" or answer == "Y"){
            return true;
        }
        std::cout << "Possible answers are y [yes] and n [no]." << std::endl;
    }
    // g++ won't compile it, cuz it doesn't understand that it
    // definitely returns a bool or actually returns at all.
    // So if the user is able to break it somehow he will get an error.
    std::cout << "Error - occurred in the ask function." << std::endl;
    exit(EXIT_FAILURE);
}


int get_int(const std::string& question){
    std::string input;
    while(std::getline(std::cin, input)){
        std::cout << question << std::endl;
        std::cin >> input;
        try {
            int number = std::stoi(input);
            return number;
        } catch(std::invalid_argument const& e){
            std::cout << "Please enter a number." << std::endl;
        }
    }
    exit(EXIT_FAILURE);
}
