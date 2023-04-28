#!/usr/bin/env bash


function test_2(){
    home_dir=$1

    source "$home_dir/functions/create_testing_env.sh"
    source "$home_dir/functions/init_location.sh"
    source "$home_dir/functions/create_main.sh"
    source "$home_dir/functions/backup.sh"
    source "$home_dir/configs.sh"

    backup_loc="backup1"

    # Test 2
    # >= 2 renamed | moved, changed, created, deleted
    # + file in new directory
    # + file out of dir -> dir empty afterwards
    create_testing_env $cppSync_binary $test_env
    create_main
    init_location main 002
    mkdir "$backup_loc"
    init_location "$backup_loc" 002

    # create first backup
    echo "$test_env/$backup_loc" >> "$test_env/main/.cppSync/configs/backup_locations.txt"
    ./cppSync --backup "main" >> /dev/null
    mkdir "tmp"
    mv "main/.cppSync" "tmp/.cppSync"
    hashes=$(find main -type f -exec sha256sum {} \;)
    hashes="${hashes//main/"$backup_loc"}"
    echo "$hashes" >> check.sha256sum
    mv "tmp/.cppSync" "main/.cppSync"
    rm -r "tmp"
    sha256sum -c check.sha256sum | grep --invert-match "OK"

    # to have the files copy em to .tmp (from main)
    mkdir .tmp-main
    cp -r main .tmp-main/main

    # make changes in main
    echo "change1" >> "main/changed/changed_file1.txt"
    echo "change2" >> "main/changed/changed_file2.txt"
    echo "change3" >> "main/changed/changed_file3.txt"
    rm "main/deleted/deleted_file1.txt"
    rm "main/deleted/deleted_file2.txt"
    rm "main/deleted/deleted_file3.txt"
    mkdir "main/moved_to/dir" "main/renamed/dir"
    mv "main/moved_from/moved_file1.txt" "main/moved_to/moved_file1.txt"
    mv "main/moved_from/moved_file2.txt" "main/moved_to/dir/moved_file2.txt"
    mv "main/renamed/renamed_file1.txt" "main/renamed/dir/renamed_file4.txt"
    mkdir "main/created/dir"
    echo "I got created1" >> "main/created/created_file1.txt"
    echo "I got created2" >> "main/created/created_file2.txt"
    echo "I got created3" >> "main/created/dir/created_file3.txt"

    mkdir "tmp"
    mv "main/.cppSync" "tmp/.cppSync"
    rm check.sha256sum
    hashes=$(find main -type f -exec sha256sum {} \;)
    echo "$hashes" >> check.sha256sum
    mv "tmp/.cppSync" "main/.cppSync"
    rm -r "tmp"
    sha256sum -c check.sha256sum | grep --invert-match "OK"

    # back them up to backup1
    ./cppSync --backup main >> /dev/null

    # verify that the main location hasn't changed
    sha256sum -c check.sha256sum | grep --invert-match "OK"

    # make sure the newer versions have been backed up
    changed=("changed/changed_file1.txt" "changed/changed_file2.txt" "changed/changed_file3.txt")
    deleted=("deleted/deleted_file1.txt" "deleted/deleted_file2.txt" "deleted/deleted_file3.txt")
    moved=("moved_to/moved_file1.txt" "moved_to/dir/moved_file2.txt" "renamed/dir/renamed_file4.txt")
    created=("created/created_file1.txt" "created/created_file2.txt" "created/dir/created_file3.txt")
    for file in "${changed[@]}"; do
        cmp --silent "backup1/$file" "main/$file" || echo "ERROR: changed file \"$file\" had errors">&2
    done
    for file in "${moved[@]}"; do
        cmp --silent "backup1/$file" "main/$file" || echo "ERROR: moved file \"$file\" had errors">&2
    done
    for file in "${created[@]}"; do
        cmp --silent "backup1/$file" "main/$file" || echo "ERROR: created file \"$file\" had errors">&2
    done
    for file in "${deleted[@]}"; do
        if [ -f "backup1/$file" ] || [ -f "main/$file" ]; then
            echo "ERROR: deleted file \"$file\" had errors">&2
        fi
    done

    # make sure the old versions still exist (not for the moved/renamed ones)
    changed=("changed/changed_file1.txt" "changed/changed_file2.txt" "changed/changed_file3.txt")
    deleted=("deleted/deleted_file1.txt" "deleted/deleted_file2.txt" "deleted/deleted_file3.txt")
    moved=("main/moved_from/moved_file1.txt" "main/moved_from/moved_file2.txt" "main/renamed/renamed_file1.txt")
    created=("created/created_file1.txt" "created/created_file2.txt" "created/dir/created_file3.txt")
    for file in "${changed[@]}"; do
        bak_file="${file/"changed_file"/".changed_file"}"
        cmp --silent "backup1/$bak_file.bak-001" ".tmp-main/main/$file" || echo "ERROR: changed file \"backup1/$bak_file.bak-001\" had errors">&2
    done
    for file in "${deleted[@]}"; do
        bak_file="${file/"deleted_file"/".deleted_file"}"
        cmp --silent "backup1/$bak_file.bak-001" ".tmp-main/main/$file" || echo "ERROR: changed file \"backup1/$bak_file.bak-001\" had errors">&2
    done
    for file in "${moved[@]}"; do
        if [ -f "backup1/$file" ] || [ -f "main/$file" ]; then
            echo "ERROR: moved file is in one of the Locations still available \"$file\"">&2
        fi
    done
}
