Caleb Bright QuickSort Project

1. Run "make" in the Project directory
2. Run "./Bright_Caleb_InputFileGenerator" to create 25 files for sizes 10, 100, 1000
3. To QuickSort single files run "./Bright_Caleb_QuickSort Bright_Caleb_input_10_XX.txt Bright_Caleb_output_10_XX.txt"
    a. (Replace 10 with 100 or 1000 to run those files and replace XX with 01-25)
4. Run "./Bright_Caleb_automated" this QuickSorts all 75 files, and creates .txt files with their execution times and average execution times.
5. The plot is included in the project file "Bright_Caleb_plotAverageExecutionTime.jpg"
6. To reset and run again, run "make clean" to get rid of all input and output files
7. Then run "make wipe" to get rid of executionTime.txt files, or just run "make reset" to do both 6 & 7 at the same time
