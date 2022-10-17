#include <iostream>
#include <experimental/filesystem>
#include <fstream>

namespace fs = std::experimental::filesystem;


namespace my{
    void init(std::string *name){

        std::string oldpath = fs::current_path();

        std::string path = *name +  "/.cppSync/";
        fs::create_directory(path);
        fs::current_path(path);

        fs::create_directory("hashes");
        fs::create_directory("what_changed");
        fs::create_directory("duplicates");
        std::ofstream touch_configfile(".config");
        touch_configfile.close();

        std::fstream config_file;
        config_file.open(".config",std::ios::out);
        if(config_file.is_open()){
            config_file << "# This is the configuration file.\n";
            config_file << "# Rules for editing:\n";
            config_file << "#    1. Comments only at the start of a new line.\n";
            config_file << "#    2. No spaces before and after a configuration (e.g. after a path).\n";
            config_file << "#    3. Just look at the examples, u will see how to configure this.\n#\n";
            
            config_file << "# Backup_Locations:\n";
            config_file << "# location=PATH_TO_BACKUP_DIRECTORY\n";
            config_file << "# U can have multiple backup locations, if some of em arent mounted\n# (e.g. usb-drives) it will still back it up to the other locations.\n#\n";
            
            config_file << "# It can keep old versions of a file.\n";
            config_file << "# They will be stored as hidden files with a .bak003 ending.\n";
            config_file << "# U can configure how many u want to keep.\n";
            config_file << "bak=003\n";
            config_file << "# always put 0's infront of it so thats 3 numbers, max is 999\n#\n";

            config_file << "# U can white- or blacklist subdirectories and files, choose\n# here which type of list ur using (default = blacklist)\n";
            config_file << "list_type=blacklist\n";
            config_file << "The possible opions are \"blacklist\" and \"whitelist\".\n#\n";

            config_file << "# Put paths on ur black-/whitelist:\n";
            config_file << "# listed_item=RELATIVE_PATH -> create as many entries as u want\n";
            config_file << "# This RELATIVE_PATH does not include the parent directory (the folder ur backing up)." << std::endl;
            config_file.close();
        } else{
            std::cerr << "FAILED TO OPEN THE .CONFIG FILE" << std::endl;
        }
       std::cout << "Configure backup-locations and other settings in the .config file." << std::endl;
       std::cout << "Disclaimer:" << std::endl;
       std::cout << "  cppSync does not backup empty directories." << std::endl;
       std::cout << "  cppSync is published under the GNU General Public License v3.0" << std::endl;

       fs::current_path(oldpath);
    }
}