from load_from_file import load_data
from print_data import print_data
from alg_calc import AlgCalc

def main():

    for i in range(0,1):
        n_list, tw_list = load_data("./Dane/"+str(i))
        print_data(n_list, tw_list)
        alg = AlgCalc(n_list, tw_list)
        alg.permutacje(0, 0)
        print("cMin", alg.c_min)
        print("cMax", alg.c_max)

if __name__ == "__main__":
    main()