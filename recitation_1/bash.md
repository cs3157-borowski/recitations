So what is bash ?
BASH is an acronym for Bourne Again Shell. It is based on the Bourne shell and is mostly compatible with its features.

Shells are command interpreters. They are applications that provide users with the ability to give commands to their operating system interactively, or to execute batches of commands quickly. In no way are they required for the execution of programs; they are merely a layer between system function calls and the user.

Think of a shell as a way for you to speak to your system. Your system doesn't need it for most of its work, but it is an excellent interface between you and what your system can offer. It allows you to perform basic math, run basic tests and execute applications. More importantly, it allows you to combine these operations and connect applications to each other to perform complex and automated tasks. We identify bash files by their .sh extension.

Digging deeper in the command line:
You should make yourself familiar with the man and apropos commands on the shell. They will be vital to your self-tutoring.

$ man man
$ man apropos

In this guide, the $ at the beginning of a line represents your BASH prompt. Traditionally, a shell prompt either ends with $, % or #. If it ends with $, this indicates a shell that's compatible with the Bourne shell (such as a POSIX shell, or a Korn shell, or Bash). If it ends with %, this indicates a C shell (csh or tcsh); this guide does not cover C shell. If it ends with #, this indicates that the shell is running as the system's superuser account (root), and that you should be extra careful.

The man command stands for "manual"; it opens documentation (so-called "man pages") on various topics. You use it by running the command man [topic] at the BASH prompt, where [topic] is the name of the "page" you wish to read. Note that many of these "pages" are considerably longer than one printed page; nevertheless, the name persists. Each command (application) on your system is likely to have a man page. There are pages for other things too, such as system calls or specific configuration files. In this guide, we will only be covering commands.
