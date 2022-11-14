mkdir -p week01
echo 'Hello, world!' > week01/file.txt
mkdir -p week10
ln week01/file.txt week10/_ex2.txt
innum=$(ls -i week01/file.txt | awk '{print $1}')
find . -inum $innum > ex2.txt
find . -inum $innum ! -name 'file.txt' -exec rm {} \; >> ex2.txt
