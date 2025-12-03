#!/bin/bash

QSORT=./Bright_Caleb_QuickSort
OUTFILE=Bright_Caleb_executionTime.txt
AVGFILE=Bright_Caleb_averageExecutionTime.txt

rm -f $OUTFILE
rm -f $AVGFILE

echo "Input Size    Execution Time in Microseconds" >> $OUTFILE

sizes=(10 100 1000)

# ============================================================
# 1. RUN QUICKSORT ON ALL INPUT FILES (handles both 1 and 01 formats)
# ============================================================

for n in "${sizes[@]}"; do
    echo "Processing size $n..."

    for i in {1..25}; do

        # Try without leading zero
        in1="Bright_Caleb_input_${n}_${i}.txt"

        # Try with leading zero
        printf -v num "%02d" $i
        in2="Bright_Caleb_input_${n}_${num}.txt"

        # Pick whichever exists
        if [[ -f "$in1" ]]; then
            in="$in1"
        elif [[ -f "$in2" ]]; then
            in="$in2"
        else
            echo "Missing file: $in1 or $in2"
            exit 1
        fi

        # Output file (same basename)
        out=$(echo "$in" | sed 's/input/output/')

        # Run and capture time
        TIME_US=$($QSORT "$in" "$out")

        echo "$n    $TIME_US" >> $OUTFILE
    done
done

echo "Finished generating Bright_Caleb_executionTime.txt"


# ============================================================
# 2. COMPUTE AVERAGES
# ============================================================

echo "Input Size    Average Execution Time in Microseconds" >> $AVGFILE

for n in "${sizes[@]}"; do
    avg=$(awk -v s="$n" '$1 == s {sum += $2; count++} END {if(count>0) print sum/count;}' $OUTFILE)
    echo "$n    $avg" >> $AVGFILE
done

echo "Finished generating Bright_Caleb_averageExecutionTime.txt"
echo "Automation complete!"
