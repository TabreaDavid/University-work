# Solve the problem from the second set here

def Property(n1: int, n2: int) -> int:
    digits1, digits2 = [0] * 10, [0] * 10
    while n1:
        digits1[n1 % 10] += 1
        n1 //= 10
    while n2:
        digits2[n2 % 10] += 1
        n2 //= 10
    for i in range(10):
        if digits1[i] > 0 and digits2[i] == 0 or digits1[i] == 0 and digits2[i] > 0:
            return False
    return True


def main():

    # The numbers n1 and n2 have the property P if their
    # writing in base 10 uses the same digits (e.g. 2113 and 323121).
    # Determine whether two given natural numbers have property P.

    n1 = int(input("Enter the first number:"))
    n2 = int(input("Enter the second number:"))
    print(Property(n1, n2))

main()
