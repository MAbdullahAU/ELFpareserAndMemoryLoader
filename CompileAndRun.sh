#clear
rm GoElf
gcc -Wall -g -c ParseElf.c 
gcc -Wall -g ParseElf.o MyElf.h -o GoElf

./GoElf

#echo "Done Compling and Linking"

