#!/bin/bash
###############################################################################
# Name: grade.sh
# Simple bash script that unzips a file containing zip files of student
# submissions and a single grading script.
# It parses the first and last names from the submission zip files,
# creates folders for each student with the name "last_first", and grades the
# submissions.
###############################################################################

readonly ARCHIVE="gcd_assignments.zip"
readonly TEST_SCRIPT="test_gcd.sh"

process_file() {
    # Function arguments are $1, $2, etc.
    echo "Processing $1."

    # Extract the name of the file without the extension.
    local base=${1%.*}

    # cut expects either file input or data on standard in
    # <<< places the value of the variable on standard in
    # and is called a 'here string'
    local first
    first="$(cut -d'_' -f3 <<<"$base")"
    local last
    last="$(cut -d'_' -f2 <<<"$base")"

    echo "Author: $first $last"
    local dirname="$last"_"$first"
    mkdir -p "$dirname"
    mv "$1" "$dirname"
    cp "$TEST_SCRIPT" "$dirname"
    cd "$dirname" || exit 1

    unzip -o "$1"
    rm "$1"

    bash "$TEST_SCRIPT" | tee grade.txt

    cd - > /dev/null || exit 1
}

unzip -o "$ARCHIVE"
for f in *.zip; do
    if [ "$f" != "$ARCHIVE" ]; then
        process_file "$f"
    fi
done