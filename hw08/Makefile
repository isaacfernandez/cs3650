FILE=semaphore_hw8

run: ${FILE}
	./${FILE}

# We include -lpthread here, for a program that uses POSIX threads.
# Newer versions of gcc allow you to simply invoke '-pthread' instead
#   of '-lpthread'
${FILE}: ${FILE}.c
	gcc -g -O0 -o ${FILE} ${FILE}.c -std=c99 -lpthread

gdb: ${FILE}
	gdb ${FILE}

vi: ${FILE}.c
	vi ${FILE}.c

emacs: ${FILE}.c
	emacs ${FILE}.c
