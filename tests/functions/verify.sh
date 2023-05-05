#!/usr/bin/env bash


function verify(){
    # $1 = files should exist,
    # format: 'path/to/file?path/to/other/file' -> they get compared
    exist=$1
    # $2 = files that shouldn't exist
    doesnt_exist=$2
    call_num=$3

    for file in "${exist[@]}"
    do
        IFS="?" read -r -a files <<< "${file}"
        if ! cmp --silent "${files[0]}" "${files[1]}"; then
            echo "CALL_NUM = $call_num">&2
            echo "ERROR: ${files[0]}">&2
            echo "    is not the same as ${files[1]}">&2
            echo
        fi
    done

    for file in "${doesnt_exist[@]}"
    do
        if [ -f "$file" ]; then
            echo "CALL_NUM = $call_num">&2
            echo "ERROR: $file does exist">&2
            echo
        fi
    done
}
export -f verify
