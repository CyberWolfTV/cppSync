#!/usr/bin/env bash


function init_location(){
    location=$1
    bak=$2

    [ -d "$location/.cppSync" ]  && echo "init_location() failed" && exit

    base_dir="$location/.cppSync"
    configs_folder="$base_dir/configs"

    mkdir "$location/.cppSync"

    mkdir "$base_dir/hashes"
    mkdir "$base_dir/what_changed"
    mkdir "$base_dir/duplicates"
    mkdir "$base_dir/configs"

    touch "$configs_folder/whitelist.txt"
    touch "$configs_folder/blacklist.txt"
    touch "$configs_folder/backup_locations.txt"
    touch "$configs_folder/.config"
    echo "{\"bak\": \"$bak\", \"per_file\": \"true\"}" >> "$configs_folder/.config"
}
export -f init_location
