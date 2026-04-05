all:
	gcc fork_exec.c -o fe
	gcc waitpid.c -o wait
	gcc shell.c -o shell

fe:
	gcc fork_exec.c -o fe

waitpid:
	gcc waitpid.c -o wait

shell:
	gcc shell.c -o shell

clean:
	rm -rf fe wait shell

rebuild: clean all
	