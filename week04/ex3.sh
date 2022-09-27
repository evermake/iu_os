clang ./ex3.c -o just-name-for-isy-grepping

# First run
echo "> 1st run : n=3"
echo "==============="
./just-name-for-isy-grepping 3 &

echo
echo "Sleep 1s zZ..."
echo
sleep 1
pstree | grep -B 2 -A 2 just-name-for-isy-grepping

echo
echo "Sleep 5s zZ..."
echo
sleep 5
pstree | grep -B 2 -A 2 just-name-for-isy-grepping

echo
echo "Sleep 5s zZ..."
echo
sleep 5
pstree | grep -B 2 -A 2 just-name-for-isy-grepping

echo
echo "Sleep 5s zZ..."
echo
sleep 5
pstree | grep -B 2 -A 2 just-name-for-isy-grepping

echo
echo "Sleep 5s zZ..."
echo
sleep 5
pstree | grep -B 2 -A 2 just-name-for-isy-grepping

echo
echo

# Second run
echo "> 2nd run : n=5"
echo "==============="

./just-name-for-isy-grepping 5 &
echo
echo "Sleep 1s zZ..."
echo
sleep 1
pstree | grep -B 2 -A 2 just-name-for-isy-grepping

echo
echo "Sleep 5s zZ..."
echo
sleep 5
pstree | grep -B 2 -A 2 just-name-for-isy-grepping

echo
echo "Sleep 5s zZ..."
echo
sleep 5
pstree | grep -B 2 -A 2 just-name-for-isy-grepping

echo
echo "Sleep 5s zZ..."
echo
sleep 5
pstree | grep -B 2 -A 2 just-name-for-isy-grepping

echo
echo "Sleep 5s zZ..."
echo
sleep 5
pstree | grep -B 2 -A 2 just-name-for-isy-grepping
