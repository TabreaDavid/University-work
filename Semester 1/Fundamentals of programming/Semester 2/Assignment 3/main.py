import timeit
import random
from texttable import Texttable


# INSERTION SORT
# Complexity: Best case --- Average case ---  Worst case
#              O(n)        O(n^2)        O(n^2)

def insertionSort(arrayToSort: list):
    for i in range(1, len(arrayToSort)):
        for j in range(i, 0, -1):
            if arrayToSort[j] < arrayToSort[j - 1]:
                copyForSwap = arrayToSort[j]
                arrayToSort[j] = arrayToSort[j - 1]
                arrayToSort[j - 1] = copyForSwap



def shellSortWhichReturns(arrayToSort: list):
    GAP_REDUCTION_FACTOR  = 2
    valueGap = len(arrayToSort) // GAP_REDUCTION_FACTOR
    while valueGap:
        for i in range(valueGap, len(arrayToSort)):
            copyForSwap = arrayToSort[i]
            j = i
            while j >= valueGap and arrayToSort[j - valueGap] > copyForSwap:
                arrayToSort[j] = arrayToSort[j - valueGap]
                j = j - valueGap
            arrayToSort[j] = copyForSwap
        valueGap //= GAP_REDUCTION_FACTOR
        return arrayToSort

# SHELL SORT
# Complexity: Best case --- Average case ---  Worst case
#            O(n * log n)     O(n^4/3)        O(n^3/2)

def shellSortForTesting(arrayToSort: list):
    GAP_REDUCTION_FACTOR = 2
    valueGap = len(arrayToSort) // GAP_REDUCTION_FACTOR
    while valueGap:
        for i in range(valueGap, len(arrayToSort)):
            copyForSwap = arrayToSort[i]
            j = i
            while j >= valueGap and arrayToSort[j - valueGap] > copyForSwap:
                arrayToSort[j] = arrayToSort[j - valueGap]
                j = j - valueGap
            arrayToSort[j] = copyForSwap
        valueGap //= GAP_REDUCTION_FACTOR



def binarySearch(searchedArray, leftIndex, rightIndex, searchedValue):
    while leftIndex <= rightIndex:
        middleIndex = (leftIndex + rightIndex) // 2
        if searchedArray[middleIndex] == searchedValue:
            return middleIndex
        elif searchedArray[middleIndex] > searchedValue:
            rightIndex = middleIndex - 1
        else:
            leftIndex = middleIndex + 1


# EXPONENTIAL SEARCH
# Complexity: Best case --- Average case ---  Worst case
#               O(1)         O(log n)    O(log n)

def exponentialSearch(searchedArray: list, value: int):
    if len(searchedArray) == 0:
        return -1
    if searchedArray[0] == value:
        return 0
    i = 1
    EXPONENT = 2
    while i < len(searchedArray) and searchedArray[i] <= value:
        i *= EXPONENT
    return binarySearch(searchedArray, i // EXPONENT, min(i, len(searchedArray) - 1), value)


def randomListGenerator(generatedList, listSize):
    generatedList = []
    for i in range(listSize):
        generatedList.append(random.randint(0, 1000))
    return generatedList


def descendingSort(arrayToSort):
    for i in range(len(arrayToSort) - 1):
        for j in range(len(arrayToSort) - 1):
            if arrayToSort[j] < arrayToSort[j + 1]:
                copyForSwap = arrayToSort[j]
                arrayToSort[j] = arrayToSort[j + 1]
                arrayToSort[j + 1] = copyForSwap


def generateListOfLists():
    finalList = []
    finalList.append(randomListGenerator([], 500))
    finalList.append(randomListGenerator([], 1000))
    finalList.append(randomListGenerator([], 2000))
    finalList.append(randomListGenerator([], 4000))
    finalList.append(randomListGenerator([], 8000))
    return finalList


def buildComplexityTable(complexityTestArray, searchComplexityCase):
    complexityTable = Texttable()
    arrayOfSizes = [500, 1000, 2000, 4000, 8000]
    complexityTable.add_row(['Number', 'Size', 'Insertion Sort', 'Shell Sort', 'Exponential Search'])

    for i in range(len(complexityTestArray)):
        VALUE_OUTSIDE_THE_LIST = 1001
        arrayCopyForShellsort = complexityTestArray[i][:]
        arrayCopyForExponentialSearch = shellSortWhichReturns(complexityTestArray[i])

        #INSERTION SORT TESTING
        insertionStart = timeit.default_timer()
        insertionSort(complexityTestArray[i])
        insertionEnd = timeit.default_timer()

        #SHELLSORT TESTING
        shellStart = timeit.default_timer()
        shellSortForTesting(arrayCopyForShellsort)
        shellEnd = timeit.default_timer()

        #EXPONENTIAL SEARCH TESTING
        if searchComplexityCase == 'worst':
            search_value = VALUE_OUTSIDE_THE_LIST
        elif searchComplexityCase == "best":
            search_value = complexityTestArray[i][0]
        else:
            search_value = random.choice(arrayCopyForExponentialSearch)

        searchStart = timeit.default_timer()
        for j in range(1000):
            exponentialSearch(arrayCopyForExponentialSearch, search_value)
        searchEnd = timeit.default_timer()

        complexityTable.add_row([i + 1, arrayOfSizes[i], insertionEnd - insertionStart, shellEnd - shellStart, searchEnd - searchStart])

    return complexityTable


def complexityChecker(whichCase):
    listOfLists = generateListOfLists()
    if whichCase == "worst":
        for i in listOfLists:
            descendingSort(i)

    elif whichCase == "best":
        for i in listOfLists:
            insertionSort(i)

    table = buildComplexityTable(listOfLists, whichCase)
    print(table.draw())


def isSorted(checkedArray):
    for i in range(len(checkedArray) - 1):
        if checkedArray[i] > checkedArray[i + 1]:
            return False
    return True

def printMenu():
    print("'''''''''''''''''''''''''''''''''''''''''''")
    print("1. Generate a new list")
    print("2. Search for a value in the list using exponential search")
    print("3. Sort the list using the insertion sort algorithm")
    print("4. Sort the list using the shellsort algorithm")
    print("5. Best case complexity for all algorithms")
    print("6. Average case complexity for all algorithms")
    print("7. Worst case complexity for all algorithms")
    print("8. Exit")
    print("'''''''''''''''''''''''''''''''''''''''''''")


def searchSortMenu():
    searchSortArray = []

    while True:
        printMenu()

        CREATE_ARRAY_OPTION = 1
        ARRAY_SEARCH_OPTION = 2
        INSERTION_SORT_OPTION = 3
        SHELL_SORT_OPTION = 4
        BEST_COMPLEXITY_OPTION = 5
        AVERAGE_COMPLEXITY_OPTION = 6
        WORST_COMPLEXITY_OPTION = 7
        EXIT = 8


        userOption = int(input("Choose an option: "))
        try:
            if userOption == CREATE_ARRAY_OPTION:
                length = int(input("Enter the length of the array: "))
                searchSortArray = randomListGenerator([], length)
                print('Your array is: ', searchSortArray)

            elif userOption == ARRAY_SEARCH_OPTION:
                if not len(searchSortArray):
                    print("You didn't generate the array!")
                    continue

                if isSorted(searchSortArray):
                    valueToSearch = int(input("Then enter the value you want to search in the array: "))
                    print("The position of the element is:", exponentialSearch(searchSortArray, valueToSearch))
                else:
                    print("Array is not sorted! Sorting with Insertion Sort first...")
                    insertionSort(searchSortArray)

            elif userOption == INSERTION_SORT_OPTION:
                if not len(searchSortArray):
                    print("You didn't generate the array!")
                    continue
                insertionSort(searchSortArray)

            elif userOption == SHELL_SORT_OPTION:
                if not len(searchSortArray):
                    print("You didn't generate the array!")
                    continue
                shellSortForTesting(searchSortArray)

            elif userOption == BEST_COMPLEXITY_OPTION:
                complexityChecker("best")

            elif userOption == AVERAGE_COMPLEXITY_OPTION:
                complexityChecker("average")

            elif userOption == WORST_COMPLEXITY_OPTION:
                complexityChecker("worst")

            elif userOption == EXIT:
                print("Goodbye!")
                break

            else:
                print("Your value is not on the menu!")

        except ValueError:
            print("You didn't enter a number!")


def main():
    searchSortMenu()

main()