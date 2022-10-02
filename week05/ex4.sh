# Compile the program
gcc -pthread ./ex4.c -o ex4

# Run the program with n = 10, 000, 000 and m in (1, 2, 4, 10, 100)
# Time it, and store 5 time results to ex4.txt
for m in 1 2 4 10 100
do
    echo "m = $m"
    echo "m = $m" >> ex4.txt
    { time ./ex4 10000000 $m; } >> ex4.txt 2>&1
    echo "============" >> ex4.txt
done