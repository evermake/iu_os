# Compile the program
gcc -pthread ./ex3.c -o ex3

# Run the program with n = 10, 000, 000 and m in (1, 2, 4, 10, 100)
# Time it, and store 5 time results to ex3.txt
for m in 1 2 4 10 100
do
    echo "m = $m"
    echo "m = $m" >> ex3.txt
    { time ./ex3 10000000 $m; } >> ex3.txt 2>&1
    echo "============" >> ex3.txt
done