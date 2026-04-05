all:
	gcc cat.c input.c main.c -o cat
	gcc cp.c -o cp

cat:
	gcc -Wall -Werror -Wextra -std=c11 cat.c input.c main.c -o cat

cp:
	gcc cp.c -o cp

clean:
	rm -rf cat cp

rebuild: clean all
