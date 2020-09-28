import re
import numpy as np
import pandas as pd
import matplotlib.pyplot as plt
from pprint import pprint

file = open("script_data/with_string_reserve.txt", 'r')

def parse_line(line: str):
    params = line.split(';')
    res = dict()
    for param in params:
        param = param.strip()
        name, value = (str.strip(s) for s in param.split(':'))
        res[name] = value
    return res

def parse_file(input):
    return list(map(parse_line, input))

def parse_data(data):
    res = []
    for item in data:
        d = list(map(int, re.match(r'(\d+)\s+(\d+)', item["info"]).groups()))
        res.append({
            "words_in_line": d[0],
            "words_to_replace": d[1],
            "time": float(item['time'][:-2])
        })
        
    return res

data = parse_data(parse_file(file))
df = pd.DataFrame(data, columns=["words_in_line", "words_to_replace", "time"])
print(df, end='\n\n')

############################################################################################

vals = [df.loc[df['words_to_replace'] == val] for val in df["words_to_replace"].unique()]
ys = [list(item['time']) for item in vals]
x = df["words_in_line"].unique()


ax = plt.subplot(1, 2, 1)
for y, label in zip(ys, (f"words_to_replace={v}" for v in df["words_to_replace"].unique())):
    ax.plot(x, y, label=label)
    
ax.set_ylabel('time')
ax.set_xlabel('words_in_line')
# ax.set_xscale('log')
ax.legend(loc='upper left')

############################################################################################

vals = [df.loc[df['words_in_line'] == val] for val in df["words_in_line"].unique()]
ys = [list(item['time']) for item in vals]
x = df["words_to_replace"].unique()


ax = plt.subplot(1, 2, 2)
for y, label in zip(ys, (f"words_in_line={v}" for v in df["words_in_line"].unique())):
    ax.plot(x, y, label=label)
    
ax.set_ylabel('time')
ax.set_xlabel('words_to_replace')
# ax.set_yscale('log')
ax.legend(loc='upper left')

plt.show()
