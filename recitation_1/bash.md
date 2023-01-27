
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
### Loop:
Similar logic to conventional loops, Rules of thumb:
- 3-part syntax: 
                  1.  For - loops: **for** - **do** - **done**
                  2.  While - loops: **while** - **do** - **done**

```
#!/bin/bash
#Script to create 3 text files and append a prefix to their names using a for loop
touch 1.txt 2.txt 3.txt
FILES=$(ls *.txt)
PRE="2023_"
for FILE in $FILES
do
        mv $FILE $PRE$FILE
done
```

Some other usefuls commands
------
### Cut command:
Basically the cut command slices a line and extracts the text. It can be used to cut parts of a line, usually by byte position or character (using -b) and field (using -f). In this recitation, we are interested in using a delimiter to split the lines in the text into fields and we will acess those fields:
Syntax:
```
$cut -d "delimiter" -f (field number) file.txt
```
Lets's say we have a file called cut_demo.txt with some names in it;
```
$ cat cut_demo.txt
Dr. Borowski
Leslie Chang
Nguyen Tran
$ cut -d " " -f2 cut_demo.txt     # delimiter: " " means a space character => we will break 'Dr. Borowski' into field 1:  'Dr.' and field2: 'Borowski'. 
Borowski
Chang
Tran
```
### Basic pattern matching:
TBA

Exercise:
------
### Agenda:
- First, we will go through Dr.B's "grade.sh" script in class. We will apply what we just learnt above to see what and why the code is doing what it does. You can obtain a copy of the code on Coursework.
- Second, we will go through a smaller piece of code called "sum.sh" that takes in `$1` and `$2`. It will compute the running total of every integer between the 2 arguments. You can look through the code and recreate it from scratch for practice after the recitation, or you can just program it rightaway.

Here is the solution:

```
#!/bin/bash
declare -i return_val
compute_sum() {
    local sum=0
    for (( lower=$1; lower <= $2; lower++ )); do
        sum=$(( $sum + $lower ))
    done
    return_val=$sum
    return 0
}
if [ $# -ne 2 ]; then
    echo “Usage: $0 [lower bound] [upper bound]”
    exit 1
fi
compute_sum $1 $2
echo “sum[$1..$2] = $return_val”
```

Based on the script above, `$./sum.sh 1 5` will have an output of `15` 






