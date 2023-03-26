# Working with Directories and Files

### DIR Pointers

`DIR`  is a typedef'ed structure in  `dirent.h`. As it was the case with the `FILE` struct, `DIR` is an _opaque type_ so its contents are never to be directly accesed. Rather, there is a series of function that we can use to operate on a `DIR *` in a very recognizable and similar manner to the functions we used to operate on `FILE *`. Since directories are a special case of files, the `DIR` structure also wraps a file descriptor.

### opendir and closedir

`opendir()`  is how you'll open directories. It takes a single, string, argument, representing the path to the directory you want to open. If  `opendir()` fails it will return a NULL pointer. In contrast from `fopen()`, `opendir()` only opens directory for reading purposes, therefore, calling it on a non-existent directory would result in failure, as opposed to creating the directory like it would be the case when calling `fopen()` on a file with `a` or `w` mode.

	DIR *opendir(const char *name);
	int closedir(DIR *dirp);

As it was the case with files, `opendir()` will create a new structure on the heap, so failing to call `closedir()` will inevitably result in memory leaks. Be careful about this.

### readdir

	struct dirent *readdir(DIR *dirp);
   
`readdir()` can be thought of as the directory version of `fgets` though it has a much simpler interface. It simply reads the next _directory entry_ in the input directory in `dirp` and *returns* it. There is no guarantees on the ordering of the directory entries returned by `readdir()`. On end of the file or if an error occurs, then `NULL` will be returned. To distinguish between an error and the end of the directory, one may look at the value of errno, which only gets set on error. `readdir()` will advance the directory position, so that a subsequent call to it returns the next directory entry. 

### struct dirent

So you know you can use `readdir()` to read the entries within a directory, but what is a directory entry? It simply is a struct with information about anything contained within a directory, that being a regular file, another directory, itself (.), its parent (..), a symbolic link... Contrary to the `DIR` structure, the contents of the `dirent` structure are to be accessed directly, so the structure is as shown below:

	struct dirent {
       ino_t          d_ino;       /* Inode number */
       off_t          d_off;       /* Not an offset; see below */
       unsigned short d_reclen;    /* Length of this record */
       unsigned char  d_type;      /* Type of file; not supported
                                      by all filesystem types */
       char           d_name[256]; /* Null-terminated filename */
	};
   
### stat

`stat()` is used to return information about a file ("a file" here is used as an umbrella term for all types of files -- directories, symbolic links, devices, etc -- and not just regular files.) It takes two arguments, a string representing the path to the file which we want to obtain the information of, and a pointer to a statbuf, which fill be filled with the information obtained. `stat()` will return 0 on success, and -1 on error.

   int stat(const char *restrict pathname,
            struct stat *restrict statbuf);
            
One key thing to note is that in order to stat a file within a directory, the user needs to have `execute` permissions on all directories in `pathname`
            
## struct statbuf

In a similar fashion to `readdir()`, despite the interface of `stat()` being simply, it provides a considerable amount of information, stored in a struct with the following attributes:

    struct stat {
       dev_t     st_dev;         /* ID of device containing file */
       ino_t     st_ino;         /* Inode number */
       mode_t    st_mode;        /* File type and mode */
       nlink_t   st_nlink;       /* Number of hard links */
       uid_t     st_uid;         /* User ID of owner */
       gid_t     st_gid;         /* Group ID of owner */
       dev_t     st_rdev;        /* Device ID (if special file) */
       off_t     st_size;        /* Total size, in bytes */
       blksize_t st_blksize;     /* Block size for filesystem I/O */
       blkcnt_t  st_blocks;      /* Number of 512B blocks allocated */

       struct timespec st_atim;  /* Time of last access */
       struct timespec st_mtim;  /* Time of last modification */
       struct timespec st_ctim;  /* Time of last status change */
     }

One of the key elements is `st_mode`, which despite its `mode_t` type is just a 16-bit bitfield. 7 bits are used to store the file type, and 9 bits are used to store the permissions. The 7 bits storing the file type, can be easily conveniently accessed by the following macros:

    S_ISREG() // regular file
    S_ISDIR() // directory file
    S_ISCHR() // character special file
    S_ISBLK() // block special file
    S_ISFIFO() // pipe or FIFO
    S_ISLNK() // symbolic link
    S_ISSOCK() // socket
           
The remaining 9 bits, require some additional manipulation and the usage of the following 9 macros:

    S_IRUSR // user-read
    S_IWUSR // user-write
    S_IXUSR // user-execute
    S_IRGRP // group-read
    S_IWGRP // group-write
    S_IXGRP // group-execute
    S_IROTH // other-read
    S_IWOTH // other-write
    S_IXOTH // other-execute
    
The macros simply represent [one-hot encoded values](https://en.wikipedia.org/wiki/One-hot) which can be tested for using bitwise and (&) or combined using bitwise (or).

Using one-hot encoded values is a very common pattern in systems programming because it allows for efficient usage of resources while preserving the readability of the code. For example, let's suppose we wanted to write a function to create a file with some permissions, one option would be for the prototype of the function to be as follows:

	int create_file(char *filename, int user-read, int user-write, int user-execute, ...);
  
which would result in the function being called as `create_file("dummyfile", 1, 1, 0, ...)` 

If instead we relied on the one-hot encoded macros, our function could simply have the prototype:

	int create_file(char *filename, int mode);
  
and could be called as `create_file("dummyfile", S_IRUSR | S_IWUSR)` and it would carry the same information while using considerably less space and mantain sufficient readability.

## lstat

int lstat(const char *restrict pathname,
                struct stat *restrict statbuf);

`lstat` performs an identical function to `stat()` with the only diference being that if `pathname` refers to a symbolic link, the information on `statbuf` will represent information about the link itself, and not the file pointed to by the link.

In the following scenario:

	$ ls -l
	drwxrwx---  2 xurxo xurxo        3 Mar 25 17:38 dir/
	lrwxrwxrwx  1 xurxo xurxo        3 Mar 25 17:39 dirlink -> dir/
  
`stat("dir", statbuf)` would be equivalent to `stat("dirlink", statbuf)` but not equivalent to `lstat("dirlink", statbuf)`


### Exercises

(1.1) Using the permission macros, write an expression using bitwise OR to represent the following permission string `rw-rw-r--`

(1.2) Using the permission macros, write an expression to verify that a given mode does not have write permissions for any group.

(1.3) T/F We can modify the parameters to readdir to prevent it from returning the directory entries for "." and ".."

(1.4) Does the following code contain any memory leaks? If so, how would you fix it?

	int main(int argc, char **argv){
	    DIR *dir = opendir(argv[1]);
	    if (dir != NULL)
	        printf("Opened directory\n");
	     else
	        printf("Could not open directory\n");
	}

(1.5) How many times will `readdir()` execute in the following directory before it returns `NULL`. You may assume it never fails

	$ ls -l
	-rw-rw----  1 xurxo xurxo   0 Mar 25 17:58 file1.txt
	-rw-rw----  1 xurxo xurxo   0 Mar 25 17:58 file2.txt
	lrwxrwxrwx  1 xurxo xurxo   4 Mar 25 17:38 link -> link
	drwxrwx---  2 xurxo xurxo   2 Mar 25 17:58 subdir/

Check the additional, `permstat.c` exercise on CourseWorks for more hands-on coding practice. 

### Solutions
<details><summary>Click Here for Solutions</summary>

(1.1) `(S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH)`

(1.2) `(mode & (S_IWUSR | S_IWGRP | S_IWOTH)) == 0`

(1.3) False.

(1.4) Yes, it can be prevented calling `closedir()`

(1.5) 6
</details>

### Acknowledgements
This recitation was originally developed by Xurxo Riesco for Spring 2023.

