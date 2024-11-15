text.exe:main.o tea_f.o stu_f.o
	gcc *.o -o $@

%.o:%.c
	gcc -c $< -o $@

clean:
	rm -f *.o text.exe
