#!/usr/bin/env bash


function cycle_verify(){
    cycle "main" "$1" 1

    mkdir "tmp"
    mv "main/.cppSync" "tmp"
    hashes=$(find main -type f -exec sha256sum {} \;)
    echo "${hashes//"main"/"$backup_loc1"}" > check.sha256sum
    echo "${hashes//"main"/"$backup_loc2"}" >> check.sha256sum
    sha256sum -c check.sha256sum >> /dev/null
    mv "tmp/.cppSync" "main"
    rm -r "tmp"
    hashes=$(find "$backup_loc1" -type f -exec sha256sum {} \;)
    echo "${hashes//"$backup_loc1"/"$backup_loc2"}" >> check.sha256sum
}


function verify_backup(){
    # changed
    cmp --silent "$1/changed/.changed_file1.txt.bak-002" ".tmp-main-1/main/changed/changed_file1.txt" || echo "ERROR \"$1\": changed file \".tmp-main-1/main/changed/changed_file1.txt\" had errors">&2
    cmp --silent "$1/changed/.changed_file1.txt.bak-001" ".tmp-main-2/main/changed/changed_file1.txt" || echo "ERROR \"$1\": changed file \".tmp-main-2/main/changed/changed_file1.txt\" had errors">&2

    # created
    cmp --silent "$1/created/created_file1.txt" "main/created/created_file1.txt" || echo "ERROR \"$1\": created file \"main/created/created_file1.txt\" had errors">&2
    cmp --silent "$1/created/created_file2.txt" "main/created/created_file2.txt" || echo "ERROR \"$1\": created file \"main/created/created_file2.txt\" had errors">&2

    # moved
    cmp --silent ".tmp-main-1/main/moved_from/moved_file1.txt" "$1/moved_to/moved_file1.txt" || echo "ERROR \"$1\": moved file \"$1/moved_to/moved_file1.txt\" had errors">&2
    cmp --silent ".tmp-main-1/main/moved_from/moved_file2.txt" "$1/moved_to/moved_file2.txt" || echo "ERROR \"$1\": moved file \"$1/moved_to/moved_file2.txt\" had errors">&2

    # renamed
    cmp --silent ".tmp-main-1/main/renamed/renamed_file1.txt" "$1/renamed/renamed_file9.txt" || echo "ERROR \"$1\": renamed file \".tmp-main-1/main/renamed/renamed_file1.txt\" had errors">&2
    cmp --silent ".tmp-main-1/main/renamed/renamed_file2.txt" "$1/renamed/renamed_file10.txt" || echo "ERROR \"$1\": renamed file \".tmp-main-1/main/renamed/renamed_file2.txt\" had errors">&2

    # deleted
    cmp --silent ".tmp-main-1/main/deleted/deleted_file1.txt" "$1/deleted/.deleted_file1.txt.bak-001" || echo "ERROR \"$1\": deleted file \".tmp-main-1/main/deleted/deleted_file1.txt\" had errors">&2
    cmp --silent ".tmp-main-1/main/deleted/deleted_file2.txt" "$1/deleted/.deleted_file2.txt.bak-001" || echo "ERROR \"$1\": deleted file \".tmp-main-1/main/deleted/deleted_file2.txt\" had errors">&2
}


# Test 3
# multiple backups to multiple locations
function test_3(){
    source "$1/functions/create_testing_env.sh"
    source "$1/functions/init_location.sh"
    source "$1/functions/create_main.sh"
    source "$1/functions/backup.sh"
    source "$1/functions/cycle.sh"
    source "$1/configs.sh"


    create_testing_env $cppSync_binary $test_env
    create_main
    init_location main 005

    backup_loc1="backup1"
    mkdir "$backup_loc1"
    init_location "$backup_loc1" 005
    echo "$test_env/$backup_loc1" >> "$test_env/main/.cppSync/configs/backup_locations.txt"

    backup_loc2="backup2"
    mkdir "$backup_loc2"
    init_location "$backup_loc2" 005
    echo "$test_env/$backup_loc2" >> "$test_env/main/.cppSync/configs/backup_locations.txt"

    ./cppSync --backup main >> /dev/null

    cycle_verify 1
    cycle_verify 2

    verify_backup "$backup_loc1"
    verify_backup "$backup_loc2"
}
