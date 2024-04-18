import matplotlib.pyplot as plt
import pandas as pd

towns = pd.read_csv("towns.csv")
x = towns["x"]
y = towns["y"]


file = open("solution.txt", "r")
line = file.readline()
solution = []
while line != "":
    solution.append(int(line))
    line = file.readline()

plt.figure(figsize=(12, 8))
plt.title("Best path found")
plt.xlabel("X town coordinate")
plt.ylabel("Y town coordinate")

plt.scatter(x, y, c="r", label="town")

x_new = [x[solution[i]] for i in range(len(x))]
y_new = [y[solution[i]] for i in range(len(y))]

plt.plot(x_new, y_new, c="k", label="path")

plt.legend()
plt.show()
