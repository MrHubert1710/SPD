import numpy as np

def load_data(filename):
    file = open(filename, 'r')

    tmp_list = file.read().split('\n')

    n_list = list()

    for a in tmp_list[0]:
        if a.isdigit():
            n_list.append(a)

    tw_list = list()
    for i in range(0, int(n_list[1])):
        tw_list.append(list())

    for b in tmp_list[1:]:
        i=0
        for c in b:
            if c.isdigit():
                tw_list[i].append(int(c))
                i+=1
    return n_list, tw_list
