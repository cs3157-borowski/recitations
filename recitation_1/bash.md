
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
### Variables and expansion
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

#^ Above is an example of our usage:  $<varname> or ${ <varname>} to indicate that a variable is in place and acting as a placholder for a value.
```

#### When to quote a variable:
General rule: quote it if it can either be empty or contain spaces (or any whitespace really) or special characters (wildcards). Not quoting strings with spaces often leads to the shell breaking apart a single argument into many. 

```
List="one two three"

for a in $List     # Splits the variable in parts at whitespace.
do
  echo "$a"
done
# one
# two
# three

echo "---"

for a in "$List"   # Preserves whitespace in a single variable.
do #     ^     ^
  echo "$a"
done
# one two three
```
#### Differentiating expansions: $()  vs  ${} 
The expression $(command) is a modern synonym for `command` which stands for command substitution; it means run command and put its output here. So

```
echo "Today is $(date). A fine day."
```

will run the date command and include its output in the argument to echo. The parentheses are unrelated to the syntax for running a command in a subshell, although they have something in common (the command substitution also runs in a separate subshell).
By contrast, ${variable} is just a disambiguation mechanism, so you can say ${var}text when you mean the contents of the variable var, followed by text (as opposed to $vartext which means the contents of the variable vartext).

### If statements and case:
#### If statements:
The logic of `if statement` works the same as in another language. The difference lies in the syntax of the code. When you write script in bash, spacing MATTERS. ---- Always ensure that there's space between your conditions and your SQUARE brackets
- Always remember the 3-part structure of every control flow, in the case of `if statement`, it's: `if` - `then` - `fi`   
Take a look at the code below
```
#!/bin/bash

#Syntax structure
#if [ sthsth ]; then
#	sthsth
#else
#	sthsth
#fi

#Example
NUM1=3
NUM2=5
if [ "$NUM1" -gt "$NUM2" ]; then              #symmetric spacing is recommended
        echo "$NUM1 is bigger than $NUM2"
else
        echo "$NUM2 is bigger than $NUM1"
fi
```

#### Case:
Rules of thumb:
- 3-part syntax: **case** - **in** - **esac**
- conditions end each case with a **‘)’**
- actions ends with **;**

```
#!/bin/bash
read -p "Testing case condition: Are you 21 or over? y/n" ANSR        #  <- Here we save the user input into a variable called ANSR
case "$ANSR" in
        [yY] | [yY][eE][sS])                                          # **[nN]** means taking in both n or N ⇒ making our script case insensitive
                echo "here, have a beer";;
        [nN] | [nN][oO])
                echo "well, wait for a couple years";;
esac
```


