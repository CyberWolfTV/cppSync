#!/usr/bin/env bash


# 1 file changed/deleted/moved/renamed/created
function test_1(){
    home_dir=$1

    source "$home_dir/functions/create_testing_env.sh"
    source "$home_dir/functions/init_location.sh"
    source "$home_dir/functions/create_main.sh"
    source "$home_dir/functions/backup.sh"
    source "$home_dir/configs.sh"

    # changed/deleted/moved/created
    create_testing_env "$cppSync_binary" "$test_env"
    create_main
    init_location main 002
    mkdir backup1
    init_location backup1
    hashes=$(backup backup1 $test_env)

    # changed
    echo "change" >> main/changed/changed_file1.txt
    new_hash=$(sha256sum main/changed/changed_file1.txt)
    new_hash="${new_hash/"main"/"backup1"}"
    printf -v hashes "$hashes\n$new_hash"
    hashes="${hashes/"00546b1cd319725c3bb0ef15deef457549f7d008b5b42c02d85b0e78caadcd59  main/changed/changed_file1.txt"/"$new_hash"}"

    # deleted
    rm main/deleted/deleted_file1.txt

    # moved
    mv "main/moved_from/moved_file1.txt" "main/moved_to/moved_file1.txt"
    hashes="${hashes/"backup1/moved_from/moved_file1.txt"/"backup1/moved_to/moved_file1.txt"}"

    # created
    touch main/created/created_file1.txt
    echo "I got created" >> main/created/created_file1.txt
    new_hash=$(sha256sum main/created/created_file1.txt)
    printf -v hashes "$hashes\n$new_hash"
    new_hash="${new_hash//"main"/"backup1"}"
    printf -v hashes "$hashes\n$new_hash"

    echo "$hashes" >> check.sha256sum

    t=$(./cppSync --backup main)



    if [ -f backup1/deleted/deleted_file1.txt ]; then
            echo "ERROR test_1"
            echo "backup1/deleted/deleted_file1.txt did not got deleted."
    fi
    if [ ! -f backup1/deleted/.deleted_file1.txt.bak-001 ]; then
            echo "ERROR test_1"
            echo "backup1/deleted/.deleted_file1.txt.bak-001"
            echo "Didnt backed up the deleted file."
    fi
    sed -i "/main\/deleted\/deleted_file1.txt/d" check.sha256sum
    sed -i "/backup1\/deleted\/deleted_file1.txt/d" check.sha256sum
    sed -i "/main\/moved_from\/moved_file1.txt/d" check.sha256sum
    echo "1efee7bb87c6a9f67cab0b2fbdc977fe4fe6339d89f1980d26885904217261c2  backup1/deleted/.deleted_file1.txt.bak-001" >> check.sha256sum
    echo "57220e1e21c09e518e9921ad63efba03d6edcbe5812a92941899f444c3a4e715  main/moved_to/moved_file1.txt" >> check.sha256sum

    hashes=$(cat check.sha256sum)
    new_hash=$(sha256sum main/changed/changed_file1.txt)
    new_hash="${new_hash/"  main/changed/changed_file1.txt"/""}"
    hashes="${hashes//"00546b1cd319725c3bb0ef15deef457549f7d008b5b42c02d85b0e78caadcd59"/"$new_hash"}"
    echo "$hashes" > check.sha256sum

    cat check.sha256sum
    sha256sum -c "$test_env/check.sha256sum" | grep --invert-match OK

    # renamed
}


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