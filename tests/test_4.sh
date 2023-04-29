#!/usr/bin/env bash


function verify_backup4(){
    # every $x is for a file that should be there or not
    # $x = 1 --> the file .changed_file1.txt.bak-00x exists
    location=$1

    should_exist=0
    does_exist=0
    [ "$2" == "1" ] && should_exist=1
    [ -f "$location/changed/.changed_file1.txt.bak-001" ] && does_exist=1
    if [ $should_exist != $does_exist ]; then
        echo "$location: .changed_file1.txt.bak-001">&2
    elif [ $should_exist == 1 ]; then
      cmp --silent ".tmp-main-4/main/changed/changed_file1.txt" "$location/changed/.changed_file1.txt.bak-001" || echo "ERROR: $location/changed/.changed_file1.txt.bak-001">&2
    fi

    should_exist=0
    does_exist=0
    [ "$3" == "1" ] && should_exist=1
    [ -f "$location/changed/.changed_file1.txt.bak-002" ] && does_exist=1
    if [ $should_exist != $does_exist ]; then
        echo "$location: .changed_file1.txt.bak-002">&2
    elif [ $should_exist == 1 ]; then
        cmp --silent ".tmp-main-3/main/changed/changed_file1.txt" "$location/changed/.changed_file1.txt.bak-002" || echo "ERROR: $location/changed/.changed_file1.txt.bak-002">&2
    fi

    should_exist=0
    does_exist=0
    [ "$4" == "1" ] && should_exist=1
    [ -f "$location/changed/.changed_file1.txt.bak-003" ] && does_exist=1
    if [ $should_exist != $does_exist ]; then
        echo "$location: .changed_file1.txt.bak-003">&2
    elif [ $should_exist == 1 ]; then
        cmp --silent ".tmp-main-2/main/changed/changed_file1.txt" "$location/changed/.changed_file1.txt.bak-003" || echo "ERROR: $location/changed/.changed_file1.txt.bak-003">&2
    fi

    should_exist=0
    does_exist=0
    [ "$5" == "1" ] && should_exist=1
    [ -f "$location/changed/.changed_file1.txt.bak-004" ] && does_exist=1
    if [ $should_exist != $does_exist ]; then
        echo "$location: .changed_file1.txt.bak-004">&2
    elif [ $should_exist == 1 ]; then
        cmp --silent ".tmp-main-1/main/changed/changed_file1.txt" "$location/changed/.changed_file1.txt.bak-004" || echo "ERROR: $location/changed/.changed_file1.txt.bak-004">&2
    fi

    should_exist=0
    does_exist=0
    [ "$2" == "1" ] && should_exist=1
    [ -f "$location/deleted/.deleted_file1.txt.bak-001" ] && does_exist=1
    if [ $should_exist != $does_exist ]; then
        echo "$location: .deleted_file1.txt.bak-001">&2
    elif [ $should_exist == 1 ]; then
        cmp --silent ".tmp-main-1/main/deleted/deleted_file1.txt" "$location/deleted/.deleted_file1.txt.bak-001" || echo "ERROR: $location/deleted/.deleted_file1.txt.bak-001">&2
    fi
}


# Test 4
# test whether the bak parameter is working correctly
# 1. do they get removed when >bak
# 2. does bak goes up (001, 002, 003)
function test_4(){
    source "$1/functions/create_testing_env.sh"
    source "$1/functions/create_backup_x.sh"
    source "$1/functions/init_location.sh"
    source "$1/functions/create_main.sh"
    source "$1/functions/backup.sh"
    source "$1/functions/cycle.sh"
    source "$1/configs.sh"

    create_testing_env $cppSync_binary $test_env
    create_main
    init_location main 000

    create_backup_x 1 000 "$test_env"
    create_backup_x 2 001 "$test_env"
    create_backup_x 3 002 "$test_env"
    create_backup_x 4 020 "$test_env"

    ./cppSync --backup main >> /dev/null

    cycle "main" 1 1
    cycle "main" 2 1
    cycle "main" 3 1
    cycle "main" 4 1

    verify_backup4 backup1 0 0 0 0
    verify_backup4 backup2 1 0 0 0
    verify_backup4 backup3 1 1 0 0
    verify_backup4 backup4 1 1 1 1
}
