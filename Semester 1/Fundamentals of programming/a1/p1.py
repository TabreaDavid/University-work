
def largestNumber(n: int) -> int:
    digitFrequency = [0] * 10
    newNumber = 0
    while n:
        digitFrequency[n % 10] += 1
        n //= 10
    for i in range(9, -1, -1):
        while digitFrequency[i]:
            newNumber = newNumber * 10 + i
            digitFrequency[i] = digitFrequency[i] - 1
    return newNumber

def main():
    #For a given natural number n find the largest natural
    #number written with the same digits. (e.g. n=3658, m=8653).

    n = int(input("Insert the number:"))
    print("The largest number written with those digits is:",largestNumber(n))

main()
# pb 4 set 1