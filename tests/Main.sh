#!/usr/bin/env bash


source configs.sh

source test_1.sh
source test_2.sh
source test_3.sh
source test_4.sh

# 1 file changed/deleted/moved/renamed/created
test_1 "$home_dir"

exit
#
test_2 "$home_dir"
test_3 "$home_dir"
test_4 "$home_dir"

# position-edge-cases [./file | ./dir/dir/dir/file]
test_5 "$home_dir"
