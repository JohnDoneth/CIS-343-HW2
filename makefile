build:
	gcc -Wall reverse.c file_utils.c -o reverse

test:
	./reverse.exe someFile newFile
	./reverse.exe newFile newFile2
	diff someFile newFile2
