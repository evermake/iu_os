echo 'Goodbye, world!' > _ex1.txt
ln _ex1.txt _ex1_1.txt
ln _ex1.txt _ex1_2.txt
ls -i | grep '.txt' | grep -v ' ex1.txt' > ex1.txt
