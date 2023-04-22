#!/usr/bin/env bash


function test_2(){
    source "$1/functions/create_test_envs.sh"
    source "$1/configs.sh"


    # Test 2
    # 1 renamed
    create_testing_env $cppSync_binary $test_env
}
