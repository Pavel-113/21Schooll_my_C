declare -a arr=("-b" "-e" "-n" "-t" "-e" "-u")
gcc s21_cat.c -o s21_cat.o
gcc test_cat.c -o test_cat.o

for i in "${arr[@]}"
do
cat "$i" file >> file1
./s21_cat.o "$i" file >> file2
echo "$i file"
./test_cat.o
rm file1 file2
done

for i in "${arr[@]}"
do
cat "$i" microfile file >> file1
./s21_cat.o "$i" microfile file >> file2
echo "$i microfile file"
./test_cat.o
rm file1 file2
done