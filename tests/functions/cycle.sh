#!/bin/bash


function cycle(){
    main="$1"
    count="$2"
    file_number_to_edit="$3"

    mkdir ".tmp-$main-$count"
    cp -r "$main" ".tmp-$main-$count/$main"

    # change
    echo "change$file_number_to_edit" >> "$main/changed/changed_file$file_number_to_edit.txt"

    # delete
    for i in $(seq "$file_number_to_edit" 1 20)
    do
        if [ -f "$main/deleted/deleted_file$i.txt" ]; then
            rm "$main/deleted/deleted_file$i.txt"
            break
        fi
    done

    # move
    for i in $(seq "$file_number_to_edit" 1 20)
    do
        if [ -f "$main/moved_from/moved_file$i.txt" ]; then
            mv "$main/moved_from/moved_file$i.txt" "$main/moved_to/moved_file$i.txt"
            break
        fi
    done

    # create
    for i in $(seq "$file_number_to_edit" 1 20)
    do
        if [ ! -f "$main/created/created_file$i.txt" ]; then
            echo "This is a new file!" >> "$main/created/created_file$i.txt"
            break
        fi
    done

    # rename
    for i in $(seq "$file_number_to_edit" 1 20)
    do
        a=$((i+8))
        if [ -f "$main/renamed/renamed_file$i.txt" ]; then
            mv "$main/renamed/renamed_file$i.txt" "$main/renamed/renamed_file$a.txt"
            break
        fi
    done

    # back stuff up
    [ ! -d ".tmp-conf" ] && mkdir ".tmp-conf"
    mv "main/.cppSync" ".tmp-conf"
    find main -type f -exec sha256sum {} \; > check.sha256sum
    mv ".tmp-conf/.cppSync" "main"
    rm -r ".tmp-conf"
    ./cppSync --backup "$main" >> /dev/null
    sha256sum -c check.sha256sum >> /dev/null
}
export -f cycle
