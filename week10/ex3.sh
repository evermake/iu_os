echo 'Foobarbazz' > _ex3.txt
chmod a-x _ex3.txt > ex3.txt
chmod uo+rwx _ex3.txt >> ex3.txt
chmod g=u _ex3.txt >> ex3.txt
echo '660 = 400+200+40+20 that is read and write permissions for the owner and group, and no permissions for others' >> ex3.txt
echo '775 = 400+200+100+40+20+10+4+1 that is read, write and execute permissions for the owner and group, and read and execute permissions for others' >> ex3.txt
echo '777 = 400+200+100+40+20+10+4+2+1 that is read, write and execute permissions for everyone' >> ex3.txt
