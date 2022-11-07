# cppSync
cppSync is an easy to use command line delta-backup tool which has some nice features... Its written in C++ (obviously).   

## Installation
- Linux
    - install gcc (e.g. $ apt install gcc)
    - $ chmod +x install.sh
    - $ sudo ./install.sh
- Windows
    - coming soon...

## Usage
- $ cppsync --help

## Functionality
- Backup
    - it can backup files to locations u specified in the .config file, unplugged storage medias will just be ignored and work the next time fine like the ones with the newest backup
    - it saves as many (<=999) old versions of files
    - it sees .git folders and does not save old versions of files in git repositories -> dont version-control a version control
    - u can restore ur directory to a saved point (how old depends on how many old versions and how many states u want to save)
    - white- or blacklist files and directories for backup in the .config file
- Additional
    - compare to states of ur directory
    - find duplicate files
    - get checksums [sha256 or md5] of all files in a directory in json format
- What it does NOT do
    - its not very complex, it does not sync to clouds .... yet
    - it does not detect or save permissions, just the content of a file
    - it does not backup empty directories
    - it does not backup non-regular files (e.g. links)

## How it works
- creates checksums of all files