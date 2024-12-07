#!/usr/bin/env bash
cmake -B build ./
cmake --build build
repos=$(find ../config/ -name *.repos)
for repo in $repos; do
  echo "repos is $repo"
  ./build/update_repos $repo
done
rm -rf build
