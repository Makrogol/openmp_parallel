#!/bin/bash
echo "" > out/output.txt

max_count_threads=$(awk '/^MAX_COUNT_THREADS/ {print substr($0, length($0) , 1)}' input_data/variabels.txt)
count_iterations=$(awk '/^COUNT_ITERATIONS/ {print substr($0, length($0) , 1)}' input_data/variabels.txt)

for (( i=1; i <= $max_count_threads; i++ ))
do
    echo $i > input_data/current_count_threads.txt
    python change_count_threads.py
    g++ -fopenmp main.cpp -o out/main

    while IFS= read -r line; do

        echo $line > input_data/input.txt
        echo "" > out/intermediate_output.txt
        for (( j=1; j <= $count_iterations; j++ ))
        do
            ./out/main >> out/intermediate_output.txt
        done
        python create_results.py
        
    done < input_data/sizes.txt

    echo "" > out/intermediate_output.txt
done

python create_table.py
python work_with_excel.py
echo "" > input_data/input.txt
echo "" > out/output.txt
