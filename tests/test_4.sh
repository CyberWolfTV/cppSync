#!/usr/bin/env bash


function test_4(){
    source "$1/functions/create_testing_env.sh"
    source "$1/configs.sh"


    # Test 4
    # bak=003 -> does it delete older files?
    create_testing_env $cppSync_binary $test_env
    #create_main
    #init_location main
}
