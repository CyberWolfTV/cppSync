#!/usr/bin/env bash


function test_3(){
    source "$1/functions/create_test_envs.sh"
    source "$1/configs.sh"


    # Test 3
    # >= 2 renamed | moved, changed, created, deleted
    # + file in new directory
    # + file out of dir -> dir empty afterwards
    create_testing_env $cppSync_binary $test_env
}
