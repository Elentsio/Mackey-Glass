import pandas as pd
import matplotlib.pyplot as plt
import glob
import os

plt.rcParams.update({'font.size': 18})
filename = "simulation_MackeyGlass.csv"


data = pd.read_csv(filename)
time_range = ((data["Time"]>=100) & (data["Time"]<=900))
data = data[time_range]
t = data["Time"]
x = data["x"]
y = data["y"]

fig = plt.figure(figsize=(6, 6))

ax = fig.add_subplot()

ax.plot(x, y, color="blue", lw=0.5)

ax.set_title("Phase Portrait Mackey-Glass")
ax.set_xlabel("x")
ax.set_ylabel("y")

ax.grid(True)

plt.show()