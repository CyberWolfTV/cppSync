#!/usr/bin/env bash


function create_5(){
    source "$1/functions/create_testing_env.sh"
    source "$1/functions/init_location.sh"
    source "$1/functions/create_main.sh"
    source "$1/configs.sh"

    create_testing_env "$cppSync_binary" "$test_env"
    mkdir "$test_env/main"
    init_location "main" 000
    create_backup_x 1 000 "$test_env"

    dir="main/dir"
    dir1="main/dir1"
    dir2="main/dir/dir"
    mkdir "$dir" "$dir1" "$dir2"

    echo "This is the Main-Location!" >> main/test.txt
    echo "This is the file in $dir!" >> "$dir/file.txt"
    echo "This is the file in $dir1!" >> "$dir1/file.txt"
    echo "This is file 1 in $dir2!" >> "$dir2/file1.txt"
    echo "This is file 2 in $dir2!" >> "$dir2/file2.txt"
    echo "This is file 3 in $dir2!" >> "$dir2/file3.txt"
}


# TEST 5
# test the is_in_scope() function, black- and whitelists
# 1. Test if Blacklist works
# 2. Test if whitelisted dir in blacklist still gets backed up

# Cases:
# 1: BL: ./           ---   WL: ./dir
# 2: BL: ./dir        ---   WL: ./dir/dir
# 3: BL: ./dir        ---   WL: ./dir/file
# 4: BL: ./dir/dir    ---   WL: ./dir
# 5: BL: ./dir/file   ---   WL: ./dir
function test_5(){
    source "$1/functions/verify.sh"

    dir="main/dir"
    dir1="main/dir1"
    dir2="main/dir/dir"

    # 1: BL: ./           ---   WL: ./dir
    create_5 "$1"
    echo "./dir" >> main/.cppSync/configs/whitelist.txt
    echo "./" >> main/.cppSync/configs/blacklist.txt
    declare -a exist
    exist[0]="$dir/file.txt?backup1/dir/file.txt"
    exist[1]="$dir2/file1.txt?backup1/dir/dir/file1.txt"
    exist[2]="$dir2/file2.txt?backup1/dir/dir/file2.txt"
    exist[3]="$dir2/file3.txt?backup1/dir/dir/file3.txt"
    declare -a doesnt_exist
    doesnt_exist[0]="backup1/dir1/file.txt"
    doesnt_exist[1]="backup1/test.txt"
    ./cppSync --backup main >> /dev/null
    # shellcheck disable=SC2128
    verify "$exist" "$doesnt_exist" 1
    unset exist
    unset doesnt_exist

    # 2: BL: ./dir        ---   WL: ./dir/dir
    create_5 "$1"
    echo "./dir/dir" >> main/.cppSync/configs/whitelist.txt
    echo "./dir" >> main/.cppSync/configs/blacklist.txt
    declare -a exist
    exist[0]="$dir2/file1.txt?backup1/dir/dir/file1.txt"
    exist[1]="$dir2/file2.txt?backup1/dir/dir/file2.txt"
    exist[2]="$dir2/file3.txt?backup1/dir/dir/file3.txt"
    exist[3]="$dir1/file.txt?backup1/dir1/file.txt"
    exist[4]="main/test.txt?backup1/test.txt"
    declare -a doesnt_exist
    doesnt_exist[0]="backup1/dir/file.txt"
    ./cppSync --backup main >> /dev/null
    # shellcheck disable=SC2128
    verify "$exist" "$doesnt_exist" 2
    unset exist
    unset doesnt_exist

    # 3: BL: ./dir        ---   WL: ./dir/file
    create_5 "$1"
    echo "./dir/file.txt" >> main/.cppSync/configs/whitelist.txt
    echo "./dir" >> main/.cppSync/configs/blacklist.txt
    declare -a exist
    exist[0]="$dir/file.txt?backup1/dir/file.txt"
    exist[1]="$dir1/file.txt?backup1/dir1/file.txt"
    exist[2]="main/test.txt?backup1/test.txt"
    declare -a doesnt_exist
    doesnt_exist[0]="backup1/dir/dir/file1.txt"
    doesnt_exist[1]="backup1/dir/dir/file2.txt"
    doesnt_exist[2]="backup1/dir/dir/file3.txt"
    ./cppSync --backup main >> /dev/null
    # shellcheck disable=SC2128
    verify "$exist" "$doesnt_exist" 3
    unset exist
    unset doesnt_exist

    # 4: BL: ./dir/dir    ---   WL: ./dir
    create_5 "$1"
    echo "./dir" >> main/.cppSync/configs/whitelist.txt
    echo "./dir/dir" >> main/.cppSync/configs/blacklist.txt
    declare -a exist
    exist[0]="$dir/file.txt?backup1/dir/file.txt"
    exist[1]="main/test.txt?backup1/test.txt"
    exist[2]="$dir1/file.txt?backup1/dir1/file.txt"
    declare -a doesnt_exist
    doesnt_exist[0]="backup1/dir/dir/file1.txt"
    doesnt_exist[1]="backup1/dir/dir/file2.txt"
    doesnt_exist[2]="backup1/dir/dir/file3.txt"
    ./cppSync --backup main >> /dev/null
    # shellcheck disable=SC2128
    verify "$exist" "$doesnt_exist" 3
    unset exist
    unset doesnt_exist

    # 5: BL: ./dir/file   ---   WL: ./dir
    create_5 "$1"
    echo "./dir" >> main/.cppSync/configs/whitelist.txt
    echo "./dir/file.txt" >> main/.cppSync/configs/blacklist.txt
    declare -a exist
    exist[0]="main/test.txt?backup1/test.txt"
    exist[1]="$dir2/file1.txt?backup1/dir/dir/file1.txt"
    exist[2]="$dir2/file2.txt?backup1/dir/dir/file2.txt"
    exist[3]="$dir2/file3.txt?backup1/dir/dir/file3.txt"
    exist[4]="$dir1/file.txt?backup1/dir1/file.txt"
    declare -a doesnt_exist
    doesnt_exist[0]="backup1/dir/file.txt"
    ./cppSync --backup main >> /dev/null
    # shellcheck disable=SC2128
    verify "$exist" "$doesnt_exist" 3
    unset exist
    unset doesnt_exist
}
export -f test_5
