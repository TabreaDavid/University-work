import random

def insertionSort(arr: list, step: int):
    k = 1
    for i in range(1, len(arr)):
        k = 1
        for j in range(i, 0, -1):
            if arr[j] < arr[j - 1]:
                aux = arr[j]
                arr[j] = arr[j - 1]
                arr[j - 1] = aux
                k += 1
            if k == step:
                print(arr)
                k = 1
    print("The array has been sorted: ", arr)

def shellSort(arr: list, step: int):
    l = len(arr) // 2
    k = 1
    while l:
        for i in range(l, len(arr)):
            aux = arr[i]
            j = i
            k = 1
            while j >= l and arr[j - l] > aux:
                arr[j] = arr[j - l]
                j = j - l
                k += 1
            arr[j] = aux
            if k == step:
                print(arr)
                k = 1
        l //= 2
    print("The array has been sorted: ", arr)

def binarySearch(arr: list, st, dr,  value: int):
    while st <= dr:
        mij = (st + dr) // 2
        if arr[mij] == value:
            return mij
        elif arr[mij] > value:
            dr = mij - 1
        else:
            st = mij + 1

def exponentialSearch(arr : list, value : int):
    if len(arr) == 0:
        return -1
    if arr[0] == value:
        return 0
    i = 1
    while i < len(arr) and arr[i] <= value:
        i *= 2
    return binarySearch(arr, i // 2, min(i, len(arr) - 1), value)


def generateList(arr):
    n = int(input('Enter the length of the list: '))
    arr = []
    for i in range(n):
        arr.append(random.randint(0, 1000))
    return arr

def isSorted(arr):
    for i in range(len(arr) - 1):
        if arr[i] > arr[i + 1]:
            return False
    return True

def printMenu():
    print("'''''''''''''''''''''''''''''''''''''''''''")
    print("1. Generate a new list")
    print("2. Search for a value in the list using exponential search")
    print("3. Sort the list using the insertion sort algorithm")
    print("4. Sort the list using the shellsort algorithm")
    print("5. Exit")
    print("'''''''''''''''''''''''''''''''''''''''''''")

def searchSortMenu():
    arr = []
    while True:
        printMenu()
        option = int(input("Choose an option: "))
        try:
            if option == 1:
                arr = generateList(arr)
                print('Your array is: ',arr)

            elif option == 2:
                if not len(arr):
                    print("You didn't generate the array!")
                    continue

                if isSorted(arr):
                    value = int(input("Enter the value you want to search in the array: "))
                    print("The position of the element is:", exponentialSearch(arr, value))
                else:
                    step = int(input("The array is not sorted. At how many sorting steps do you want the array to display? "))
                    insertionSort(arr, step)
            elif option == 3:
                if not len(arr):
                    print("You didn't generate the array!")
                    continue
                step = int(input("At how many sorting steps do you want the array to display? "))
                insertionSort(arr, step)
            elif option == 4:
                if not len(arr):
                    print("You didn't generate the array!")
                    continue
                step = int(input("At how many sorting steps do you want the array to display? "))
                shellSort(arr, step)
            elif option == 5:
                print("Goodbye!")
                break
            elif option > 5:
                print("Your value is not on the menu!")
        except ValueError:
            print("You didn't enter a number!")


def main():

    searchSortMenu()

main()