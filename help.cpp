#include <iostream>

namespace my{
    
    void help(){
        std::cout << "backup [Option/-s] $Name \n\nOptions:" << std::endl;
        std::cout << "--hash                  -> Just hashes all the files and saves the hashes in the .change/hashes directory." << std::endl;
        std::cout << "-i  / --init            -> Creates the .changes directory in the target directory. In this" << std::endl;
        std::cout << "                           directory will informations, outputs and configurations be stored." << std::endl;
        std::cout << "-c  / --compare         -> Compares the hashes of 2 .change files of ur choice." << std::endl;
        std::cout << "-cd / --compare-default -> Compares the current state with the last one." << std::endl;
        std::cout << "-fd / --find-duplicates -> Shows u all files in the directory which exists more than once." << std::endl;
        std::cout << "-nq / --no-questions    -> Does not ask any questions, u can use the script in scripts then." << std::endl;
        std::cout << "                           This will force compare-default." << std::endl;
        std::cout << "-b  / --backup          -> Creates a backup on the selected location." << std::endl;
        std::cout << "--configure             -> Pops up vim with the config file.." << std::endl;
        std::cout << "-h  / --help            -> Shows this information." << std::endl;
        exit(EXIT_SUCCESS);
        return;
    }
}