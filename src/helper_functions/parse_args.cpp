#include "helper_functions.hpp"


void parse_args(int argc, char *argv[], struct arguments *args){
    for(int i = 1; i < argc; i++){
        std::string argument = argv[i];
        if(argument == "-c" || argument == "--compare"){
            args->compare = true;
            continue;
        }
        if(argument == "-cd" || argument == "--compare-default"){
            args->compare = true;
            args->compare_default = true;
            continue;
        }
        if(argument == "-h" || argument == "--help"){
            cppSync_help();
        }
        if(argument == "-nq" || argument == "--no-questions"){
            // TODO make the script running in other scripts)
            args->no_questions = true;
            args->compare_default = true;
            continue;
        }
        if(argument == "-b" || argument == "--backup"){
            // TODO write backup function(-s)
            args->backup = true;
            continue;
        }
        if(argument == "-fd" || argument == "--find-duplicates"){
            // TODO write function(-s)
            args->find_duplicates = true;
            continue;
        }
        if(argument == "--hash"){
            // TODO write function(-s)
            args->hash = true;
            continue;
        }
        if(argument == "--configure"){
            // TODO write function(-s)
            args->configure = true;
            continue;
        }
        args->name = argument;
    }
    args->name = get_name(args->name);
}
