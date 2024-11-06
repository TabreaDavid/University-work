def hasCommonDigit(firstNumber, secondNumber):
    digitPresenceOf1stNumber, digitPresenceOf2ndNumber = [0] * 10, [0] * 10

    while firstNumber:
        lastDigit = firstNumber % 10
        digitPresenceOf1stNumber[lastDigit] = True
        firstNumber //= 10

    while secondNumber:
        lastDigit = secondNumber % 10
        digitPresenceOf2ndNumber[lastDigit] = True
        secondNumber //= 10

    for i in range(10):
        if True == digitPresenceOf1stNumber[i] == digitPresenceOf2ndNumber[i]:
            return True
    return False

def recursiveBacktrack(inputtedSequence, startingPosition, currentSubsequence, validSubsequences):
    VALID_SUBSEQUENCE_LENGTH = 2
    if len(currentSubsequence) >= VALID_SUBSEQUENCE_LENGTH:
        validSubsequences.append(currentSubsequence[:])

    for i in range(startingPosition, len(inputtedSequence)):
        if not currentSubsequence or (
                inputtedSequence[i] > currentSubsequence[-1] and hasCommonDigit(inputtedSequence[i], currentSubsequence[-1])):

            currentSubsequence.append(inputtedSequence[i])
            recursiveBacktrack(inputtedSequence, i + 1, currentSubsequence, validSubsequences)
            currentSubsequence.pop()

def iterativeBacktrack(inputtedSequence):
    VALID_SUBSEQUENCE_LENGTH = 2
    validSubsequences = []

    for i in range(len(inputtedSequence)):
        currentSubsequence = [inputtedSequence[i]]

        for j in range(i + 1, len(inputtedSequence)):
            if inputtedSequence[j] > currentSubsequence[-1] and hasCommonDigit(inputtedSequence[j], currentSubsequence[-1]):
                currentSubsequence.append(inputtedSequence[j])

                if len(currentSubsequence) >= VALID_SUBSEQUENCE_LENGTH:
                    validSubsequences.append(currentSubsequence[:])

        for k in range(j + 1, len(inputtedSequence)):
            if inputtedSequence[k] > currentSubsequence[-1] and hasCommonDigit(inputtedSequence[k], currentSubsequence[-1]):
                currentSubsequence.append(inputtedSequence[k])

                if len(currentSubsequence) >= VALID_SUBSEQUENCE_LENGTH:
                    validSubsequences.append(currentSubsequence[:])

    return validSubsequences

def main():

    # 9. The sequence a = a1, ..., an with distinct integer elements is given.
    # Determine all subsets of at least two elements with the property:
    # - The elements in the subset are in increasing order
    # - Any two consecutive elements in the subsequence have at least one common digit

    inputtedSequence = list(map(int, input("Enter the values you want in the sequence: ").split()))

    #Recursive Version
    print("--- Recursive version ---")
    validSubsequencesRecursive = []
    recursiveBacktrack(inputtedSequence, 0, [], validSubsequencesRecursive)

    print("Valid subsequences:")
    for i in validSubsequencesRecursive:
        print(i)


    # Iterative Version
    print("--- Iterative version ---")
    validSubsequencesIterative = iterativeBacktrack(inputtedSequence)
    for i in validSubsequencesIterative:
        print(i)

main()


