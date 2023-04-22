#!/usr/bin/env bash


function create_testing_env(){
    # init testing directory
    cppSync_binary=$1
    test_env=$2

    [ -d "$test_env" ]  && rm -rf "$test_env"
    mkdir "$test_env"
    cp "$cppSync_binary" "$test_env"
    cd "$test_env" || exit
    touch check.sha256sum
}
export -f create_testing_env
