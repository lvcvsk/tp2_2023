import random
import numpy as np
import os
from collections import namedtuple

np.random.seed(420)

Coordinate = namedtuple('Coordinate', ['x', 'y'])

x = []
directory = input("Enter the directory to save the test case: ")
if not os.path.exists(directory):
    os.makedirs(directory)

for power in range(6,15):
    x.append(2**power)

for n in x:

    def generate_test_case(n):
        x = []
        y = []
        for _ in range(n):
            temp = random.randint(0, n)  # Adjust the range of x coordinates as per your requirements
            temp2 = random.randint(0, n)  # Adjust the range of y coordinates as per your requirements
            x.append(temp)
            y.append(temp2)
        return x, y

    x, y = generate_test_case(n)

    w = random.randint(1, n)
    u = 1
    v = 1
    r = 1
    filename = f"testcase_{n}.txt"
    filepath = os.path.join(directory, filename)
    with open(filepath, "w") as f:
        f.write(str(u) + "\n")
        f.write(f"{n}")
        f.write(" " + str(r) + " " + str(w) + " " + str(u) + " "+ str(v) + "\n") 
        for start, end in zip(x, y):
            f.write(f"{start} {end}\n")

    print(f"Test case written to {filepath}")

