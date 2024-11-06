import math

def isPrime(n: int) ->bool:
    if n <= 1 or n % 2 == 0 and n != 2:
        return False
    for i in range(2,int(math.sqrt(n)) + 1):
        if n % i == 0:
            return False
    return True


def primeDivisorCount(n: int) -> int:
    div, count = 2, 0
    while n > 1:
        true = 0
        while n % div == 0:
            true = 1
            n //= div
        if true:
            count += 1
        div += 1

    return count

def neededPrimeDiv(n : int, step: int) -> int:
    div, k = 2, 0
    while n > 1:
        if n % div == 0:
            k += 1
            while n % div == 0:
                n //= div
            if k == step:
                return div
        div += 1


def sequence(n: int) -> int:
    if n == 1:
        return 1
    currentNumber = 1
    i = 1
    while i < n:
        currentNumber += 1
        if int(isPrime(currentNumber)):
            i+= 1
        else:
            pDiv = primeDivisorCount(currentNumber)
            if i + pDiv >= n:
                return neededPrimeDiv(currentNumber, n - i)
            i += pDiv
    return currentNumber

def main():

    # Solve the problem from the third set here
    # 13. Determine the n-th element of the sequence 1,2,3,2,5,2,3,7,2,3,2,5,...
    # obtained from the sequence of natural numbers by replacing composed numbers
    # with their prime divisors, without memorizing the elements of the sequence.

    n = int(input("Enter the element: "))
    print(sequence(n))

main()

