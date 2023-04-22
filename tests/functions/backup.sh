#!/usr/bin/env bash


function backup(){
    backup_location=$1
    test_env=$2

    echo "$test_env/$backup_location" >> "$test_env/main/.cppSync/configs/backup_locations.txt"

    ./cppSync --backup "main" >> /dev/null
    mkdir "tmp"
    mv "main/.cppSync" "tmp/.cppSync"

    hashes=$(find main -type f -exec sha256sum {} \;)

    mv "tmp/.cppSync" "main/.cppSync"
    rm -r "tmp"

    hashes="${hashes//main/"$backup_location"}"
    echo "$hashes"
}
export -f backup
