
Bash scripting
======

Basic commands 
------
### TLDR and notable features
Bash is the only shell scripting language permitted for executables. Executables must start with #!/bin/bash and a minimum number of flags. Use set to set shell options so that calling your script as bash script_name does not break its functionality. Executables should have no extension (strongly preferred) or a .sh extension. Libraries must have a .sh extension and should not be executable.

Some guidelines:

- If you’re mostly calling other utilities and are doing relatively little data manipulation, shell is an acceptable choice for the task.
- If performance matters, use something other than shell.
- If you are writing a script that is more than 100 lines long, or that uses non-straightforward control flow logic, you should rewrite it in a more structured language now. Bear in mind that scripts grow. Rewrite your script early to avoid a more time-consuming rewrite at a later date.
When assessing the complexity of your code (e.g. to decide whether to switch languages) consider whether the code is easily maintainable by people other than its author.

```
#!/bin/bash
#A script that says "Hello, AP World!"
echo "Hello, AP World!"
```
### Variables and variable expansion
Variables are not bounded to a transparent, solid data type. They are recognisable through the signature '$' and their capitalization.
```
#!/bin/bash
#A script that uses a variable
NAME="Nguyen"
echo "My name is $NAME"
echo "Again, my name is ${NAME}"

#Output:
#My name is Nguyen
#Again, my name is Nguyen

#^ Above is an example of our usage:  $<varname> or ${ <varname>} to indicate that a variable is in place and acting as a placholder for a value
```
