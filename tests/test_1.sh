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

    ./cppSync --backup main >> /dev/null



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
    echo "00546b1cd319725c3bb0ef15deef457549f7d008b5b42c02d85b0e78caadcd59  backup1/changed/.changed_file1.txt.bak-001" >> check.sha256sum
    echo "$hashes" > check.sha256sum
    sha256sum -c "$test_env/check.sha256sum" | grep --invert-match OK

    # renamed
    mv main/renamed/renamed_file1.txt main/renamed/renamed_file4.txt
    ./cppSync --backup main >> /dev/null

    hashes=$(cat check.sha256sum)
    hashes="${hashes//"renamed_file1.txt"/"renamed_file4.txt"}"
    echo "$hashes" > check.sha256sum
    sha256sum -c "$test_env/check.sha256sum" | grep --invert-match OK
}
