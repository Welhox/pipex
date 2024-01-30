#!/usr/bin/bash

echo TEST WITH ALL VALID 
echo

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

echo TEST WITH NO WRITE PERMISSION AT OUTFILE
echo

touch bar.txt
chmod 111 bar.txt
./pipex "foo.txt" "wc" "cat" bar.txt
echo FT exit code = $?
echo "outfile"
chmod 755 bar.txt
rm bar.txt
echo
echo

touch bar.txt
chmod 111 bar.txt
< foo.txt wc | cat > bar.txt
echo OG exit code = $?
echo "outfile"
chmod 755 bar.txt
rm bar.txt
echo

echo TEST WITH NO READ PERMISSION AT INFILE
echo

touch foo2.txt
chmod 111 foo2.txt
./pipex "foo2.txt" "wc" "cat" bar.txt
echo FT exit code = $?
echo "outfile"
cat bar.txt
$rm bar.txt
chmod 755 foo2.txt
rm foo2.txt
echo

touch foo2.txt
chmod 111 foo2.txt
< foo2.txt wc | cat > bar.txt
echo OG exit code = $?
echo "outfile"
cat bar.txt
$rm bar.txt
chmod 755 foo2.txt
rm foo2.txt
echo

echo TEST WITH INVALID CMD1
echo

./pipex "foo.txt" "88" "cat" bar.txt
echo FT exit code = $?
echo "outfile"
cat bar.txt
rm bar.txt
echo

< foo.txt 88 | cat > bar.txt
echo OG exit code = $?
echo "outfile"
cat bar.txt
rm bar.txt
echo

echo TEST WITH INVALID CMD2
echo

./pipex "foo.txt" "wc" "88" bar.txt
echo FT exit code = $?
echo "outfile"
cat bar.txt
rm bar.txt
echo

< foo.txt wc | 88 > bar.txt
echo OG exit code = $?
echo "outfile"
cat bar.txt
rm bar.txt
echo