#!/bin/bash

# You can use this program to test your submisison against multiple configurations, and get an idea of
# how your submission will perform. The mastermind board configurations tested here are identical
# to the ones that will be used to grade your submission.

# Do not modify this file.

function test_submission() 
{
    echo "Output from using $1 peg(s) and $2 color(s)" >> submissionOutput/SubmissionOutput_$1peg_$2color.txt
    results=$(java -jar Grader.jar -python3 -trials=10 -pegs=$1 -colors=$2 ./ 2> submissionOutput/SubmissionOutput_$1peg_$2color.txt)
    totalScore=$(echo ${results} | awk '{ printf "%d", $1 + $2 + $3 + $4 + $5 + $6 + $7 + $8 + $9 + $10 }')
    average=$(echo "$totalScore" | awk '{ printf "%f", $1 / 10 }')
    echo "Results of using $1 peg(s) and $2 color(s)"
    echo "Guesses per trial:"
    echo ${results}
    echo "Total Score: ${totalScore}"
    echo "Average: ${average}"
    echo ""
}

mkdir -p submissionOutput

echo "Your java submission will now be tested."
echo "Any output from your program will be stored in the directory \"submissionOutput\" which is in this level."
echo ""

# If you wish, you can add more test scenarios by following this format:
#   test_submission <NUMBER_OF_PEGS> <NUMBER_OF_COLORS>
# And pasting that command below all of the test_submission commands you see here.

test_submission 1 1
test_submission 1 4
test_submission 2 3
test_submission 3 3
test_submission 3 5
test_submission 9 1
test_submission 1 9
test_submission 2 9
test_submission 9 2
test_submission 4 4
test_submission 4 6
test_submission 4 8
test_submission 6 4
test_submission 6 8
test_submission 7 4
test_submission 7 5
test_submission 7 6
test_submission 7 7
test_submission 8 2
test_submission 8 3
test_submission 8 4
test_submission 8 5
test_submission 8 6
