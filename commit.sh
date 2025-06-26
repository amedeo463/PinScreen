#! /bin/sh

# Script I use to commit and push

# Tidy up repo
make fullcleanup

# Commit and push (add repo first)
git add .
git commit
git push