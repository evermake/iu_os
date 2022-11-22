echo Vlad > lofsdisk/file1
echo Deryabkin > lofsdisk/file2

gcc ex2.c -o lofsdisk/ex2.out

sudo mount --bind /bin lofsdisk/bin
sudo mount --bind /lib lofsdisk/lib

sudo chroot lofsdisk/
./ex2.out > ex2.txt
./ex2.out >> ex2.txt
