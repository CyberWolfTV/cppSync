#!/usr/bin/env bash


source configs.sh

source test_1.sh
source test_2.sh
source test_3.sh
source test_4.sh


# 1 file changed/deleted/moved/renamed/created
echo "TEST 1"
test_1 "$home_dir"
echo ""

# >= 2 renamed | moved, changed, created, deleted
echo "TEST 2"
test_2 "$home_dir"
echo ""

# multiple backups to multiple locations
echo "TEST 3"
test_3 "$home_dir"
echo ""

# position-edge-cases [./file | ./dir/dir/dir/file]
echo "TEST 4"
test_4 "$home_dir"
echo ""
