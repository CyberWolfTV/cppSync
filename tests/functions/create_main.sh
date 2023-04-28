#!/usr/bin/env bash


function create_main(){
    main="main"
    created="$main/created"
    deleted="$main/deleted"
    changed="$main/changed"
    moved_from="$main/moved_from"
    moved_to="$main/moved_to"
    renamed="$main/renamed"

    mkdir "$main" "$created" "$deleted" "$changed" "$moved_from" "$moved_to" "$renamed"

    echo "This is the main location." >> "$main/text.txt"

    echo "deleted_file1.txt" >> "$deleted/deleted_file1.txt"
    echo "deleted_file2.txt" >> "$deleted/deleted_file2.txt"
    echo "deleted_file3.txt" >> "$deleted/deleted_file3.txt"

    echo "changed_file1.txt" >> "$changed/changed_file1.txt"
    echo "changed_file2.txt" >> "$changed/changed_file2.txt"
    echo "changed_file3.txt" >> "$changed/changed_file3.txt"

    echo "moved_file1.txt" >> "$moved_from/moved_file1.txt"
    echo "moved_file2.txt" >> "$moved_from/moved_file2.txt"
    echo "moved_file3.txt" >> "$moved_from/moved_file3.txt"

    echo "renamed_file1.txt" >> "$renamed/renamed_file1.txt"
    echo "renamed_file2.txt" >> "$renamed/renamed_file2.txt"
    echo "renamed_file3.txt" >> "$renamed/renamed_file3.txt"

    find main -type f -exec sha256sum {} \; >> check.sha256sum
}
export -f create_main
