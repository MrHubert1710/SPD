import numpy as np


class AlgCalc:
    def __init__(self, n_list, tw_list):
        self.n_list = n_list
        self.tw_list = tw_list
        self.c_max = -1
        self.c_min = 9999
        self.c_tmp = -1

    def propability(self, c_1, c_2, Temp):
        if c_2 >= c_1:
            ret_val = np.exp((c_1 - c_2)/Temp)
        elif c_2 < c_1:
            ret_val = 1
        return ret_val

    def new_move(self):
        

    def c_calculate(self):
        time = list()
        for i in range(0, int(self.n_list[1])):
            time.append(0)

        for i in range(0, int(self.n_list[0])):
            for j in range(0, int(self.n_list[1])-1):
                if j == 0:
                    time[j] += self.tw_list[j][i]
                if time[j] >= time[j+1]:
                    time[j+1] = time[j]
                    time[j+1] += self.tw_list[j+1][i]
                else: time[j+1] += self.tw_list[j+1][i]

        if self.c_max < time[int(self.n_list[1])-1]:
            self.c_max = time[int(self.n_list[1])-1]

        if self.c_min > time[int(self.n_list[1])-1]:
            self.c_min = time[int(self.n_list[1]) - 1]

        if self.c_tmp < time[int(self.n_list[1])-1]:
            self.c_tmp = time[int(self.n_list[1])-1]

    def swap(self, a, poziom, i, ix):

        a[poziom][ix], a[poziom][i] = a[poziom][i], a[poziom][ix]

    def permutacje(self, ix, poziom):
        if ix < int(self.n_list[0])-1:
            for i in range(ix, int(self.n_list[0])):
                self.swap(self.tw_list, poziom, i, ix)
                self.permutacje(ix+1, poziom)
                self.swap(self.tw_list, poziom, i, ix)
        else:
            poziom += 1
            if poziom == 1:
                self.c_tmp = 0
                for i in range(0, int(self.n_list[0])):
                    print(self.tw_list[0][i], end=' ')

            if int(self.n_list[1]) > poziom:
                self.permutacje(0, poziom)
            else:
                self.c_calculate()
            if poziom == 1:
                print("C:", self.c_tmp)
