#! /bin/sh

# Script I use to commit and push, please ignore

# Tidy up repo
make fullcleanup

# Commit and push (add repo first)
git add .
git commit
git push