# FILE I/O
### 3 channels

By convention, every C program is given 3 channels for input/output operations, often called I/O. I/O refers to anything that involves data coming into the program from outside (such as getting user input with  `scanf`) and writing data to the outside (such as printing data to the console with  `printf`).

The 3 basic channels (often called "streams") as well as their corresponding integer representations are:

-   **(0) stdin (standard input)**  This stream is for incoming data, which often comes from the keyboard but can also be from other sources (e.g. through piping & redirection)
-   **(1) stdout (standard output)**  This stream is for outgoing data, and normally goes to the terminal screen but does not necessarily have to. This stream is buffered which means it is not sent to the terminal until a new line character is sent. This means if you use  `printf("hello")`  you likely will not see it until the end of your program is reached.
-   **(2) stderr (standard error)**  This stream is for error messages and is not buffered, meaning any characters written to it will immediately be flushed to their destination. This destination is often the terminal screen, but can be other locations as well.

If you wish to interact with these buffers you will need to  `#include <stdio.h>`. This library defines standard functions such as  `printf()`  `scanf()`  and others which you may or may not have already used.

### Redirection and Piping

Lots of input and output to/from programs is visible in the shell (your terminal screen). That being said, it's possible to redirect the source of stdin or the destination of stderr and stdout.

There are several kinds of redirection possible from the console:

-   `>`  redirects the standard output of the left argument to the right argument. For example  `echo "hello world" > hi.txt`  will write the words 'hello world' to a file called  `hi.txt`, and 'hello world' will not appear on the terminal screen. 
-   `2>`  is similar, except that it takes the standard error and redirects it, rather than the standard output.
-   `<`  does 'input redirection', meaning that the contents of the file on the right of the operator serves as the standard input of the left argument. For example, after running the example above,  `cat < hi.txt`  will print "hello world" to the console.
-   `2>&1`  will redirect stderr to the same location as stdout.
-   `>>`  will also redirect the standard output of the left argument to the right (destination), but instead of overwriting data that may already be in the destination, '>>' will append.
-  `|`  will pipe the output from the program on the left as input to the program on the right. For example the `head -n` command will print as output the first n number of data of its input. Running `ls | head -3` will print up to 3 files in your working directory. 

#### Remark: We use redirection in C to redirect input and output to and from the standard/default streams. So, redirection is between programs and streams/files. Whereas piping deals with only programs.

### Formatting

printf and scanf both use format strings to specify what how to format their output. They also both accept variable arguments. All arguments to scanf  **must**  be pointers whereas arguments to printf should be values (in the case of numbers) or  `char *`  in the case of strings. Pages 153-154 in the K&R explain how to format your format strings for  `printf()`  and 157-158 explain formatting for  `scanf()`. Make sure you can identify the following two format strings:

	printf("%-15.10s", "hello, world");
	sscanf("25 Dec 1988", "%d %s %d", &day, month, &year);


### FILE Pointers

`FILE`  is a typedef'ed structure in  `stdio.h`. Whenever you use it, you'll use a  `FILE *`  though because you'll always be getting a value back from/passing it to common file operating functions. Why a pointer? Because these functions will modify the internal values of the  `FILE`  value. So while you could copy them because it's a struct and C would be fine with passing it by value, things like your place in the file would not be maintained. A  `FILE *`  is given as an  _opaque type_, meaning you should never be accessing it's internals directly.

### File Descriptors

Among other things, a FILE * wraps a file descriptor, an integer used by the operating system to keep track of open files. As you'll see below, a FILE pointer provides a nicer interface than a file descriptor for interacting with files. You can use function like  `fopen`  and  `fclose`  instead of the more low-level  `open`  and  `close`.

### fopen and fclose

`fopen()`  is how you'll open files. It takes two arguments, both strings. The first is a string representing the path to the file you want to open, and the second is the mode with which you will open it. The mode tells whether or not you are going to be reading, writing, or appending to the file and also how you want to read the file in. The list of different modes and their uses are listed below. If  `fopen()`  fails it will return a NULL pointer. This can happen because a file doesn't exist (in the case of r's) or because you don't have permissions to access the file. If you fopen a non-existent file with the 'a' or 'w' option, the file will, however, be created.  `fclose()`  will close the file when you're done.

	FILE *fopen(char *name, char *mode);
	int fclose(FILE *fp);

The above structure should look a tiny bit familiar. Knowing what we know about  `FILE *`s you might see the likeness here to:

	void *malloc(size_t size);
	int free(void *p);

That's because fopen and fclose create a new  `FILE`  structure on the heap so that the status of the open file can be maintained. This means that  **if you don't  `fclose`  your  `FILE *`s, you'll have memory leaks**. Be careful about this.

**Modes**

-   `"r"`  read only (file must already exist)
-   `"w"`  write only. Creates new text file and discards previous contents if file already exists
-   `"a"`  append only; opens text file or creates file, all writes go to end of the file
-   `"r+"`  read and write. Opens file for update (file must already exist)
-   `"w+"`  read and write. Creates new text file and discards previous contents if file already exists
-   `"a+"`  append; can read and append. Adds to end in the same behavior as  `"a"`  **regardless**  of file position
-   `"rb"`,  `"wb"`,  `"ab"`,  `"rb+"`,  `"wb+"`,  `"ab+"`  indicates binary file. If using Windows OS, these modes suppresse the Windows addition of  `"\r"`  to  `"\n"`. The order of "b" and "+" does not matter (i.e.`"rb+"`  and  `"r+b"`  are equivalent).

### fgets and fputs

**IMPORTANT: THESE FUNCTIONS ARE FOR LINE INPUT AND LINE OUTPUT**

What's that you ask? It means they're really good at reading in strings, but bad for everything else. Only use these functions if lines are a logical way to delimit chunks of the file you're reading.

	char *fgets(char *line, int maxline, FILE *fp);
	int fputs(char *line, FILE *fp);

`fgets`  reads the next  _line_  from the input file in  `fp`  into the memory location pointed to by  `line`. If all is successful, it reads at most  `maxline-1`  characters out of the file, and returns  `line`  as well. If something goes wrong (on end of file, or error) it returns  `NULL`. It will keep the newline character it reads if it gets to one before it reaches  `maxline-1`  characters. It also ALWAYS appends the null character to the end of the string.  `fgets`  will advance the file position after each read by the space read into  `line`.

`fputs`  returns EOF if there's an error and 0 otherwise. This will not append a newline to the file, nor does your string need to contain a newline character. It will write the null-terminated string pointed to by `line` to the stream pointed to by `fp`.  The terminating null byte will not be written.

**Watch out!**  `gets`  and  `puts`  work very similarly for  `stdin`  and  `stdout`  but  `gets`  will not give you the newline character. But you shouldn't have to worry about that because you should NEVER use  `gets`. It does not perform any bounds checking on the input, so you're just asking for memory errors.

### fread and fwrite

	size_t fread(void *ptr, size_t size, size_t nmemb, FILE *stream);
	size_t fwrite(const void *ptr, size_t size, size_t nmemb, FILE *stream);

Each of these functions accept pointers of type  `void`. So if you want each item to be read into the right size memory space, you'll need to tell it the  `size`  of each item, and the number of items  `nmemb`  to read/write from/to the  `stream`.  `fwrite`  promises not to modify the data that  `ptr`  references as well. These return the number of items succesfully read/written. If it's anything less than what you expected, you should check what happened using  `ferror`  or  `feof`.  `fread`  and  `fwrite`  advances the position of the file to the end of the space read or written. These functions are more helpful than `fgets` and `fputs` when working with arbitrary binary data. 

### fseek

	int fseek(FILE *stream, long offset, int origin);

This handy dandy function lets you hop through a file without doing anything other than changing the position in the  `FILE`  structure. You can use any  `stream`  of your choosing, but pay attention to whether or not it's a binary stream. If it's a binary stream,  `offset`  can be any number of bytes/characters from  `origin`  which should be set to either  `SEEK_SET`  (a constant representing the beginning of the file),  `SEEK_CUR`  (a constant representing the current position), or  `SEEK_END`  (the end of the file).

If you're reading a text stream,  `offset`  must either be zero or the current position as returned by a call to  `ftell` . In this case, always set origin to  `SEEK_SET`.

	FILE *text = fopen("myfile", "r");
	FILE *binary = fopen("myfile", "rb");

	fseek(text, ftell(text), SEEK_SET);
	fseek(binary, -100, SEEK_END);

### feof and ferror

	int feof(FILE *stream);
	int ferror(FILE *stream);

So you didn't get what you were expecting from one of the above functions. What do you do? You call  `feof`  or  `ferror`. These two functions let you know what happened.  `feof`  returns true if the end of the  `stream`  has been reached, and  `ferror`  returns true if there was an error reading the  `stream`.

### fprintf and fscanf

These functions work just like their counterparts  `printf`  and  `scanf`, respectively, except you specify which FILE to write to, rather than defaulting to  `stdout`  and  `stdin`, respectively.

	int fprintf(FILE *stream,  const  char  *format,  ...);
	int fscanf(FILE *stream,  const  char  *format,  ...);

### What's Buffering?

Buffering determines how often the contents of a stream are sent to their destination. There's some low level stuff going on at this point, but just understand that its not very efficient to send data one character at a time, so buffering happens. Unbuffered streams are constantly flushed to their destination. Line-buffered streams are only flushed to its destination after a newline character is written. Block-buffered streams are flushed when they reach a certain size. You can use  `fflush(fp)`  to manually flush the buffer for any file pointer.

-   stderr is unbuffered (why?)
-   stdout is line-buffered when it's connected to terminal
-   everything else is block-buffered

### Exercise
In this exercise, we will use two programs,  `decho`  and  `dcat`, to experiment with FILE I/O functions provided by the C standard library.

`decho`  takes decimal integers as command-line arguments, and writes those decimal values as individual bytes to stdout:

```
// decho.c
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

int main(int argc, char **argv) {
    for (int i = 1; i < argc; i++) {
        unsigned char d = atoi(argv[i]);
        fwrite(&d, 1, 1, stdout);
    }
}
```
The C library function **int atoi(const char \*str)** converts the string argument **str** to an integer (type int). 

Say you type `./decho 20 15` into the command line, `decho` will go through each command-line argument and convert it into an integer using `atoi()` and store it in a *single-byte char*. It then writes the singular byte of *binary data* to stdout. (Which is why if you run the above, the program will not print out "20 15" to the terminal.) 

`dcat`  receives bytes from its stdin, and prints them as comma-separated decimal integers to its stdout:
```
// dcat.c
#include <stdio.h>

int main(void) {

    unsigned char d;
    while (fread(&d, 1, 1, stdin))
        printf("%d, ", d);

    printf("\n");
}
```
Notice that `dcat` reads in one byte at a time and prints to its stdout, using the `%d` format specifier, the decimal value of the binary data stored in unsigned char `d`.  Say, `dcat` receives one byte `[0000 1010]`from its stdin, it will print out the decimal value of this byte with a comma: `"10, "`.

We can use these programs together to construct and inspect file streams at a byte-by-byte level:

```
$ gcc -o decho decho.c && gcc -o dcat dcat.c

$ ./decho 0 1 2 5 10 | ./dcat
0, 1, 2, 5, 10,
```

Now, let us consider the following program, named `cats`:

```
// cats.c: cats play with strings!
#include <stdio.h>

int main(void) {
	assert(atoi("10") == '\n'); // Important!
    char buf[8];

    fgets(buf, 8, stdin);
    fputs(buf, stdout);

    return 0;
}
```
We build and run it as follows, with the output of `decho` piped to the input of `cats` and the output of cats piped to the input of `dcat`:
```
$ gcc -o cats cats.c

$ ./decho  1  2  3  4  5  6  7  8 | ./cats | ./dcat

    (1.1)

$ ./decho  9 10 11 12 13 14 15 16 | ./cats | ./dcat

    (1.2)

$ ./decho  1  1  0  1  0          | ./cats | ./dcat

    (1.3)
```

What is the output shown at 1.1–1.3? 
*It's helpful to think about when fgets stops reading and when fputs stops writing. How much can they read/write? How do they know when to stop?* 

### Solutions

For (1.1), it's important to look at the function declaration of fgets **(char \*fgets(char \*line, int maxline, FILE \*fp))** and remember that it reads up to `maxline - 1`bytes and then appends the null character after the last byte it reads. So because we passed in 8, it will only read 7 bytes from `cats`'s stdin. So, `cats` receives 7 bytes from `decho`  and stores it into a buffer and send those 7 bytes using fputs(), which  `dcat` will then read, one byte at a time, and print the decimal value of each of those 7 bytes. 


```
$ ./decho  1  2  3  4  5  6  7  8 | ./cats | ./dcat

    1, 2, 3, 4, 5, 6, 7, 

```
For (1.2), it's important to recognize that the integer value of 10 also represents the newline character (**assert(atoi("10") == '\n')**) and that `fgets()` reads one line at a time, so it will stop after it reads in the newline character.
```
$ ./decho  9 10 11 12 13 14 15 16 | ./cats | ./dcat

    9, 10, 
```
For (1.3), the trick here is noticing that `fputs()` writes to its output stream until it encounters a null-terminator (which is equivalent in this case to integer value '0'). And fputs does not write the null byte, so only "1, 1, " will be written.
```
$ ./decho  1  1  0  1  0          | ./cats | ./dcat

    1, 1,
```

### Acknowledgements
This recitation was originally developed by Jae Woo Lee and John Hui. Markus Tran adapted it in Spring 2023.

