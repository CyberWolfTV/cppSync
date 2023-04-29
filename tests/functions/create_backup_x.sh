#!/usr/bin/env bash


function create_backup_x(){
    num="$1"
    bak="$2"
    test_env="$3"

    backup_loc="backup$num"
    mkdir "$backup_loc"
    init_location "$backup_loc" "$bak"
    echo "$test_env/$backup_loc" >> "$test_env/main/.cppSync/configs/backup_locations.txt"
}
export -f create_backup_x
