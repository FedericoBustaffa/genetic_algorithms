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

x_new = [x[solution[i]] for i in range(len(x))]
y_new = [y[solution[i]] for i in range(len(y))]

plt.figure(figsize=(10, 6))

plt.scatter(x, y, c="r", label="town")
plt.plot(x_new, y_new, c="k", label="path")

plt.title("Best path found")
plt.xlabel("X town coordinate")
plt.ylabel("Y town coordinate")
plt.legend()
plt.show()
