mkdir dir1
date && sleep 3
mkdir dir2
date && sleep 3

ls -tr / > ./dir1/root.txt
date && sleep 3
ls -tr ~ > ./dir2/home.txt

cat ./dir1/root.txt ./dir2/home.txt
ls ./dir1 ./dir2

