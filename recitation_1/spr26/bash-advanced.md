# Bash Scripting - Spring 2026 Recitation

This recitation covers intermediate bash topics. All code blocks can be copy-pasted directly into your terminal.

---

## VM Setup

### Windows - VirtualBox

### Mac - Multipass

[Multipass Setup Guide](https://courseworks2.columbia.edu/courses/237711/files/25781482?wrap=1)

---

## Expansion: `$()` vs `${}`

These look similar but do completely different things.

### `$()` - Command Substitution

Runs a command and substitutes its output.

```bash
# Run these one at a time
echo "Today is $(date +%A)"
echo "You are in $(pwd)"
echo "Files here: $(ls | wc -l)"
```

### `${}` - Variable Expansion

Access and manipulate variable values.

```bash
NAME="football"
echo "The sport is $NAME"
echo "The sport is ${NAME}"

# Why braces matter:
SPORT="foot"
echo "$SPORTball"      # Empty! Looks for variable SPORTball
echo "${SPORT}ball"    # Correct: football
```

### Parameter Expansion Tricks

```bash
FILE="document.tar.gz"

echo "${FILE%.gz}"        # Remove shortest match from end: document.tar
echo "${FILE%%.*}"        # Remove longest match from end: document
echo "${FILE#*.}"         # Remove shortest match from start: tar.gz
echo "${FILE##*.}"        # Remove longest match from start: gz

# Default values
echo "${UNSET_VAR:-default}"    # Use default if unset
echo "${UNSET_VAR:=default}"    # Set and use default if unset
```

---

## Loops

### For Loop

```bash
# Basic iteration
for item in apple banana cherry; do
    echo "Fruit: $item"
done

# Iterating over files
for file in *.txt; do
    echo "Found: $file"
done

# C-style loop
for ((i=1; i<=5; i++)); do
    echo "Count: $i"
done
```

### While Loop

```bash
count=1
while [ $count -le 5 ]; do
    echo "Count: $count"
    count=$((count + 1))
done
```

### Reading Lines from File

```bash
# Create a test file first
cat > names.txt << 'EOF'
Alice
Bob
Charlie
EOF

# Read line by line
while IFS= read -r line; do
    echo "Hello, $line!"
done < names.txt

rm names.txt
```

---

## Case Statements

Case provides pattern matching - cleaner than multiple if-elif chains.

```bash
read -p "Enter a fruit (apple/banana/other): " fruit

case "$fruit" in
    apple)
        echo "Red or green?"
        ;;
    banana)
        echo "Yellow and curved"
        ;;
    orange|lemon|lime)
        echo "It's a citrus!"
        ;;
    *)
        echo "Unknown fruit: $fruit"
        ;;
esac
```

### Pattern Matching in Case

```bash
read -p "Yes or No? " answer

case "$answer" in
    [yY] | [yY][eE][sS])
        echo "You said yes"
        ;;
    [nN] | [nN][oO])
        echo "You said no"
        ;;
    *)
        echo "Invalid response"
        ;;
esac
```

---

## getopts - Parsing Command Line Options

`getopts` is the standard way to parse flags like `-v`, `-f filename`, etc.

### Live Coding Demo

Create this script together:

```bash
cat > getopts_demo.sh << 'SCRIPT'
#!/bin/bash

# Default values
verbose=false
output_file=""
count=1

# Usage function
usage() {
    echo "Usage: $0 [-v] [-o output_file] [-n count] [args...]"
    echo "  -v            Verbose mode"
    echo "  -o <file>     Output file"
    echo "  -n <number>   Repeat count"
    exit 1
}

# Parse options
while getopts "vo:n:h" opt; do
    case "$opt" in
        v)
            verbose=true
            ;;
        o)
            output_file="$OPTARG"
            ;;
        n)
            count="$OPTARG"
            ;;
        h)
            usage
            ;;
        ?)
            usage
            ;;
    esac
done

# Shift past the options to get remaining arguments
shift $((OPTIND - 1))

# Demo the parsed values
echo "Verbose: $verbose"
echo "Output file: ${output_file:-<none>}"
echo "Count: $count"
echo "Remaining args: $@"

if $verbose; then
    echo "--- Verbose output ---"
    for ((i=1; i<=count; i++)); do
        echo "Iteration $i"
    done
fi
SCRIPT

chmod +x getopts_demo.sh
```

### Test the Script

```bash
./getopts_demo.sh -v -o results.txt -n 3 file1.txt file2.txt
./getopts_demo.sh -h
./getopts_demo.sh -o output.log
./getopts_demo.sh file1.txt file2.txt
```

### Key Points About getopts

- Options with arguments have `:` after them in the optstring (e.g., `o:`)
- `$OPTARG` contains the argument for the current option
- `$OPTIND` is the index of the next argument to process
- Leading `:` in optstring enables silent error handling

---

## Merge Conflict Demo with getopts Script

Let's simulate a merge conflict scenario.

```bash
# Setup: Create a git repo
mkdir merge_demo && cd merge_demo
git init

# Create initial version
cat > parser.sh << 'EOF'
#!/bin/bash
while getopts "vf:" opt; do
    case "$opt" in
        v) echo "verbose";;
        f) echo "file: $OPTARG";;
    esac
done
EOF

git add parser.sh
git commit -m "Initial parser script"

# Create and modify on branch A
git checkout -b feature-a
cat > parser.sh << 'EOF'
#!/bin/bash
while getopts "vf:o:" opt; do
    case "$opt" in
        v) echo "verbose mode on";;
        f) echo "input file: $OPTARG";;
        o) echo "output file: $OPTARG";;
    esac
done
EOF
git add parser.sh
git commit -m "Add output option"

# Go back to main and make conflicting change
git checkout main
cat > parser.sh << 'EOF'
#!/bin/bash
while getopts "vf:d" opt; do
    case "$opt" in
        v) echo "VERBOSE";;
        f) echo "file: $OPTARG";;
        d) echo "debug mode";;
    esac
done
EOF
git add parser.sh
git commit -m "Add debug option"

# Try to merge - this will conflict!
git merge feature-a
```

### Resolving the Conflict

```bash
# See the conflict markers
cat parser.sh

# Edit to resolve (keep both features)
cat > parser.sh << 'EOF'
#!/bin/bash
while getopts "vf:o:d" opt; do
    case "$opt" in
        v) echo "verbose mode on";;
        f) echo "input file: $OPTARG";;
        o) echo "output file: $OPTARG";;
        d) echo "debug mode";;
    esac
done
EOF

# Complete the merge
git add parser.sh
git commit -m "Merge feature-a: combine output and debug options"

# Cleanup
cd ..
rm -rf merge_demo
```

---

## Here Documents

Here docs allow multi-line input to commands.

### Basic Here Doc

```bash
cat << 'EOF'
This is a here document.
It preserves formatting and newlines.
Variables like $HOME are NOT expanded (because of quotes around EOF).
EOF
```

### Without Quotes - Variables Expand

```bash
cat << EOF
Your home directory is: $HOME
Current user: $USER
Today is: $(date +%A)
EOF
```

### Here Doc to File

```bash
cat > config.txt << 'EOF'
# Configuration file
server=localhost
port=8080
debug=false
EOF

cat config.txt
rm config.txt
```

### Here Doc with Indentation (<<-)

```bash
# Using <<- allows leading tabs to be stripped
if true; then
	cat <<- 'EOF'
	This text can be indented with tabs
	and the tabs will be removed from output
	EOF
fi
```

### Here String (<<<)

```bash
# Single line input to command
grep "hello" <<< "hello world"

# Useful with cut
name="John_Doe_123"
cut -d'_' -f2 <<< "$name"
```

---

## basename and cut

### basename - Extract Filename

```bash
# Remove directory path
basename /home/user/documents/report.pdf
# Output: report.pdf

# Remove directory AND suffix
basename /home/user/documents/report.pdf .pdf
# Output: report

# Process multiple files
basename -a /path/to/file1.txt /path/to/file2.txt
```

### dirname - Extract Directory

```bash
dirname /home/user/documents/report.pdf
# Output: /home/user/documents
```

### cut - Extract Fields

```bash
# By delimiter and field
echo "first:second:third" | cut -d':' -f2
# Output: second

# Multiple fields
echo "a,b,c,d,e" | cut -d',' -f1,3,5
# Output: a,c,e

# Range of fields
echo "one:two:three:four" | cut -d':' -f2-4
# Output: two:three:four

# By character position
echo "Hello World" | cut -c1-5
# Output: Hello
```

### Practical Example: Processing Filenames

```bash
# Simulating grade.sh pattern
filename="hw1_Smith_John_submission.zip"

# Extract parts using cut with here string
base="${filename%.*}"                    # Remove extension
last=$(cut -d'_' -f2 <<< "$base")
first=$(cut -d'_' -f3 <<< "$base")

echo "Student: $first $last"
echo "Directory: ${last}_${first}"
```

---

## readonly - Immutable Variables

`readonly` creates constants that cannot be changed.

### Basic Usage

```bash
readonly PI=3.14159
readonly APP_NAME="MyApp"

echo "PI is $PI"
echo "App: $APP_NAME"

# This will fail:
PI=3.14
# bash: PI: readonly variable
```

### Readonly in Scripts

```bash
cat > config_demo.sh << 'SCRIPT'
#!/bin/bash

# Configuration constants - cannot be accidentally modified
readonly CONFIG_FILE="/etc/myapp/config"
readonly MAX_RETRIES=3
readonly VERSION="1.0.0"

echo "Version: $VERSION"
echo "Config: $CONFIG_FILE"
echo "Max retries: $MAX_RETRIES"

# Attempting to change these will error
# VERSION="2.0.0"  # Would fail
SCRIPT

bash config_demo.sh
rm config_demo.sh
```

### Declaring Readonly Arrays

```bash
readonly -a COLORS=("red" "green" "blue")
echo "First color: ${COLORS[0]}"
echo "All colors: ${COLORS[@]}"

# Cannot modify
# COLORS[0]="yellow"  # Would fail
```

### List All Readonly Variables

```bash
readonly -p | head -10
```

---

## Cleanup

```bash
# Remove demo files created during this recitation
rm -f getopts_demo.sh
```

---

## Quick Reference

| Syntax             | Purpose                     |
| ------------------ | --------------------------- |
| `$()`              | Command substitution        |
| `${}`              | Variable expansion          |
| `${var:-default}`  | Use default if unset        |
| `${var%pattern}`   | Remove suffix (shortest)    |
| `${var##pattern}`  | Remove prefix (longest)     |
| `getopts "ab:c"`   | Parse options (b takes arg) |
| `$OPTARG`          | Current option's argument   |
| `<<EOF ... EOF`    | Here document               |
| `<<<`              | Here string                 |
| `readonly VAR=val` | Create constant             |

---

## Acknowledgements

Developed by Amit Aharoni and Veer Prasad, January 2026
