#!/usr/bin/env bash


# README:
# When passing an array created with "declare -a" to a function it will bug when u write ${arr[@]}.

source configs.sh

source test_1.sh
source test_2.sh
source test_3.sh
source test_4.sh
source test_5.sh


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

# test whether the bak parameter is working correctly
echo "TEST 4"
test_4 "$home_dir"
echo ""

# test the is_in_scope() function, black- and whitelists
echo "TEST 5"
test_5 "$home_dir"
echo ""
