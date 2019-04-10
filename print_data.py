
def print_data(n_list, tw_list):
    print("Liczba zadan:", n_list[0])
    print("Liczba maszyn:", n_list[1])
    print(" ")

    for i in range(0, int(n_list[1])):
        print("Zadania maszyny",i,"->", tw_list[i])
    print("_______________")