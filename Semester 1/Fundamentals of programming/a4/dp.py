# Given a set of integers A, determine if it can
# be partitioned into two subsets with equal sum.
# For example, set A = { 1, 1, 1, 1, 2, 3, 5 } can be
# partitioned into sets A1 = { 1, 1, 2, 3 } and A2 = { 1, 1, 5 },
# each of them having sum 7. Display one such possibility.

def equal_sum_partitions_dynamic_programming(checked_array):
    total_array_sum = 0
    for i in range(len(checked_array)):
        total_array_sum += checked_array[i]

    if total_array_sum % 2 == 1:
        return False

    half_of_total_sum = total_array_sum // 2
    checked_array_length = len(checked_array)
    dynamic_programming_sum = [False] * (half_of_total_sum + 1)
    dynamic_programming_sum[0] = True

    for i in checked_array:
        for j in range(half_of_total_sum, i - 1, -1):
            dynamic_programming_sum[j] = dynamic_programming_sum[j] or dynamic_programming_sum[j - i]

    if not dynamic_programming_sum[half_of_total_sum]:
        return False

    first_partition = []
    for i in range(checked_array_length - 1, -1, -1):
        if half_of_total_sum >= checked_array[i] and dynamic_programming_sum[half_of_total_sum - checked_array[i]]:
            first_partition.append(checked_array[i])
            half_of_total_sum -= checked_array[i]


    second_partition = checked_array.copy()
    for i in first_partition:
        second_partition.remove(i)

    return first_partition, second_partition


def descending_sort(arrayToSort):
    for i in range(len(arrayToSort)):
        for j in range(len(arrayToSort) - 1):
            if arrayToSort[j] < arrayToSort[j + 1]:
                copyForSwap = arrayToSort[j]
                arrayToSort[j] = arrayToSort[j + 1]
                arrayToSort[j + 1] = copyForSwap

def equal_sum_partitions_greedy_implementation(checked_array) :
    sequence_sum = 0
    for i in range(len(checked_array)):
        sequence_sum += checked_array[i]

    if sequence_sum % 2 != 0:
        return False

    first_partition = 0
    descending_sort(checked_array)
    valid_partition = []

    for i in range (len(checked_array)):
        if first_partition + checked_array[i] <=  sequence_sum // 2:
            first_partition += checked_array[i]
            valid_partition.append(checked_array[i])
            checked_array.pop(i)

        if first_partition == sequence_sum // 2:
            print("---NAIVE IMPLEMENTATION---")
            print(valid_partition, checked_array)
            return True

    return False


def main():

    sequence_for_greedy = list(map(int, input("Enter the sequence: ").split()))
    sequence_for_dynamic_programming = sequence_for_greedy.copy()

    gredy_implementation_result = equal_sum_partitions_greedy_implementation(sequence_for_greedy)

    if not gredy_implementation_result:
        print("Not possible to partition")
        return

    print("---DYNAMIC PROGRAMMING IMPLEMENTATION---")
    print(equal_sum_partitions_dynamic_programming(sequence_for_dynamic_programming))

main()