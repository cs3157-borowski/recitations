#!/bin/bash
###############################################################################
# getopts_demo.sh - Demonstrates parsing command line options
# Usage: ./getopts_demo.sh [-v] [-o output_file] [-n count] [args...]
###############################################################################

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
