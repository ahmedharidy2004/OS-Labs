#!/bin/bash
rm -rf Lab1
mkdir Lab1
cp words.txt numbers.txt Lab1/
cd Lab1
touch MergedContent.txt
paste words.txt numbers.txt > MergedContent.txt
head -n 3 MergedContent.txt
touch SortedMergedContent.txt
sort MergedContent.txt > SortedMergedContent.txt
echo "The sorted file is:"
cat SortedMergedContent.txt
chmod a-r SortedMergedContent.txt
cat MergedContent.txt | sort | uniq
touch CapitalSortedMergedContent.txt
cat SortedMergedContent.txt | tr 'a-z' 'A-Z' > CapitalSortedMergedContent.txt
echo "Permission for SortedMergedContent.txt denied, this is because we removed read permissions for all users"
chmod u+r SortedMergedContent.txt
cat SortedMergedContent.txt | tr 'a-z' 'A-Z' > CapitalSortedMergedContent.txt
cat MergedContent.txt | grep -n "^w.*[0-9]$"
touch NewMergedContent.txt
cat MergedContent.txt | tr 'i' 'o' > NewMergedContent.txt
paste MergedContent.txt NewMergedContent.txt
