declare -a arr=("-i" "-v" "-l" "-c" "-n" "-h" "-o" "-s" "-ivcnh")
gcc s21_grep.c -lpcre -o s21_grep.o
gcc test_grep.c -o test_grep.o
for i in "${arr[@]}"
do
grep "$i" Hello file >> file1
./s21_grep.o "$i" Hello file >> file2
echo "$i"
./test_grep.o
rm file1 file2
done

grep -e hello -e world file >> file1
./s21_grep.o -e hello -e world file >> file2
echo -e
./test_grep.o
rm file1 file2

grep -f microfile file >> file1
./s21_grep.o -f microfile file >> file2
echo -f
./test_grep.o
rm file1 file2