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

plt.scatter(x, y, c="r")
print(x)
x, y, solution = zip(*sorted(zip(x, y, solution), key=lambda s: s[2]))
print(x)
plt.plot(x, y, c="k")
plt.show()
