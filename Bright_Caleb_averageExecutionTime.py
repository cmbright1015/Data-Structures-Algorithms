#Caleb Bright
import matplotlib.pyplot as plt

sizes = []
times = []

# read the .txt file, if it doesn't have 2 values ignore
# convert to int and floats then store the values in their own list
with open("Bright_Caleb_averageExecutionTime.txt") as f:
    next(f)
    for line in f:
        parts = line.split()
        if len(parts) != 2:
            continue
        n = int(parts[0])
        t = float(parts[1])
        sizes.append(n)
        times.append(t)

plt.plot(sizes, times, marker="o")
plt.xlabel("Input Size")
plt.ylabel("Average Execution Time in microseconds")
plt.title("QuickSort Average Execution time vs Input time")
plt.grid(True)
plt.savefig("Bright_Caleb_plotAverageExecutionTime.jpg", dpi=300, bbox_inches="tight")