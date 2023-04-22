#!/usr/bin/env bash


function create_main(){
    main="main"
    created="$main/created"
    deleted="$main/deleted"
    changed="$main/changed"
    moved_from="$main/moved_from"
    moved_to="$main/moved_to"
    renamed="$main/renamed"

    mkdir "$main"
    mkdir "$created"
    mkdir "$deleted"
    mkdir "$changed"
    mkdir "$moved_from"
    mkdir "$moved_to"
    mkdir "$renamed"

    touch "$main/text.txt"

    touch "$deleted/deleted_file1.txt"
    touch "$deleted/deleted_file2.txt"
    touch "$deleted/deleted_file3.txt"
    echo "deleted_file1.txt" >> "$deleted/deleted_file1.txt"
    echo "deleted_file2.txt" >> "$deleted/deleted_file2.txt"
    echo "deleted_file3.txt" >> "$deleted/deleted_file3.txt"

    touch "$changed/changed_file1.txt"
    touch "$changed/changed_file2.txt"
    touch "$changed/changed_file3.txt"
    echo "changed_file1.txt" >> "$changed/changed_file1.txt"
    echo "changed_file2.txt" >> "$changed/changed_file2.txt"
    echo "changed_file3.txt" >> "$changed/changed_file3.txt"

    touch "$moved_from/moved_file1.txt"
    touch "$moved_from/moved_file2.txt"
    touch "$moved_from/moved_file3.txt"
    echo "moved_file1.txt" >> "$moved_from/moved_file1.txt"
    echo "moved_file2.txt" >> "$moved_from/moved_file2.txt"
    echo "moved_file3.txt" >> "$moved_from/moved_file3.txt"

    touch "$renamed/renamed_file1.txt"
    touch "$renamed/renamed_file2.txt"
    touch "$renamed/renamed_file3.txt"
    echo "renamed_file1.txt" >> "$renamed/renamed_file1.txt"
    echo "renamed_file2.txt" >> "$renamed/renamed_file2.txt"
    echo "renamed_file3.txt" >> "$renamed/renamed_file3.txt"

    echo "1efee7bb87c6a9f67cab0b2fbdc977fe4fe6339d89f1980d26885904217261c2  $deleted/deleted_file1.txt
58d3da5588c15d02cdd451dd6ad643215634619c8bbd8cad16936624765422c1  $deleted/deleted_file2.txt
da3e63888ee1136a6b9931a56fda7bd15070892862b10a4a074972fa92320a39  $deleted/deleted_file3.txt
00546b1cd319725c3bb0ef15deef457549f7d008b5b42c02d85b0e78caadcd59  $changed/changed_file1.txt
8e4b3a106504cb910e3304b1c5f5091605d72edf84371c865e956969230f05bb  $changed/changed_file2.txt
64db03b7d9fa5c8c5b9dc258e2895a301f2787b6ea2b57da443592ea44fbe3e7  $changed/changed_file3.txt
57220e1e21c09e518e9921ad63efba03d6edcbe5812a92941899f444c3a4e715  $moved_from/moved_file1.txt
1ed2d68f7ecca40680138ccbfbe4a2636b97dfff9669f5d36d9f205dda0796da  $moved_from/moved_file2.txt
8e010f44b246c4b4bc30f598df67b7b429012414529550c24f493cee86db2337  $moved_from/moved_file3.txt
20e4df9ec97c777dbeb46c656d459d23162a57148f75d58e65f7e31a8622a26b  $renamed/renamed_file1.txt
84993e2d5b35d4d487d5e1fd1f76ccdde3a01e47ea667eb5a4c1dc02c888d623  $renamed/renamed_file2.txt
771079346c3b4f287353866ac57a7bfb268234433ec7d92ad577a3e4e1e436e1  $renamed/renamed_file3.txt" >> check.sha256sum
}
export -f create_main
