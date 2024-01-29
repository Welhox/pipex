#!/usr/bin/bash

./pipex "foo.txt" "wc" "cat" bar.txt
echo FT exit code = $?
echo "outfile"
cat bar.txt
rm bar.txt
echo

< foo.txt wc | cat > bar.txt
echo OG exit code = $?
echo "outfile"
cat bar.txt
rm bar.txt
echo

touch bar.txt
chmod 111 bar.txt
./pipex "foo.txt" "wc" "cat" bar.txt
echo FT exit code = $?
echo "outfile"
chmod 755 bar.txt
rm bar.txt
echo

touch bar.txt
chmod 111 bar.txt
< foo.txt wc | cat > bar.txt
echo OG exit code = $?
echo "outfile"
chmod 755 bar.txt
rm bar.txt
echo