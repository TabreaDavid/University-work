#
# Write the implementation for A5 in this file
#

import math

#
# Write below this comment
# Functions to deal with complex numbers -- list representation
# -> There should be no print or input statements in this section
# -> Each function should do one thing only
# -> Functions communicate using input parameters and their return values
#


REAL_PART_INDEX = 0
IMAGINARY_PART_INDEX = 1

def create_complex_number_list(real_part, imaginary_part):
    return [real_part, imaginary_part]

def get_real_part_list(complex_number):
    return complex_number[REAL_PART_INDEX]

def set_real_part_list(complex_number, real_part):
    complex_number[REAL_PART_INDEX] = real_part

def get_imaginary_part_list(complex_number):
    return complex_number[IMAGINARY_PART_INDEX]

def set_imaginary_part_list(complex_number, imaginary_part):
    complex_number[IMAGINARY_PART_INDEX] = imaginary_part

def to_string_complex_list(complex_number):
    return str(complex_number[REAL_PART_INDEX]) + " + " + str(complex_number[IMAGINARY_PART_INDEX]) + "i"

def modulus_list(complex_number):
    return math.sqrt(complex_number[REAL_PART_INDEX] ** 2 + complex_number[IMAGINARY_PART_INDEX] ** 2)

#
# Write below this comment
# Functions to deal with complex numbers -- dict representation
# -> There should be no print or input statements in this section
# -> Each function should do one thing only
# -> Functions communicate using input parameters and their return values
#

def create_complex_number_dictionary(real_part, imaginary_part):
    return {'real': real_part, 'imaginary': imaginary_part}

def get_real_part_dictionary(complex_number):
    return complex_number['real']

def set_real_part_dictionary(complex_number, real_part):
    complex_number['real'] = real_part

def get_imaginary_part_dictionary(complex_number):
    return complex_number['imaginary']

def set_imaginary_part_dictionary(complex_number, imaginary_part):
    complex_number['imaginary'] = imaginary_part

def to_string_complex_dictionary(complex_number):
    return str(complex_number['real']) + " + " + str(complex_number['imaginary']) + "i"

def modulus_dictionary(complex_number):
    return math.sqrt(complex_number['real'] * complex_number['real'] + complex_number['imaginary'] * complex_number['imaginary'])

#
# Write below this comment
# Functions that deal with subarray/subsequence properties
# -> There should be no print or input statements in this section
# -> Each function should do one thing only
# -> Functions communicate using input parameters and their return values
#

def longest_subarray_distinct(numbers):
    maximum_length = 0
    start_index = 0
    visited_numbers = {}
    maximum_subarray = []
    end_index = 0
    while end_index < len(numbers):
        complex_number = numbers[end_index]
        complex_number_tuple = tuple(complex_number)

        if complex_number_tuple in visited_numbers and visited_numbers[complex_number_tuple] >= start_index:
            start_index = visited_numbers[complex_number_tuple] + 1

        visited_numbers[complex_number_tuple] = end_index
        current_length = end_index - start_index + 1

        if current_length > maximum_length:
            maximum_length = current_length
            maximum_subarray = numbers[start_index:end_index + 1]

        end_index += 1

    return maximum_subarray


#sqrt(a^2 + b^2)
def longest_subarray_same_modulus(numbers):
    maximum_length = 1
    current_length = 1
    maximum_subarray_same_modulus = numbers[:1]

    for i in range(1, len(numbers)):
        if modulus_list(numbers[i]) == modulus_list(numbers[i - 1]):
            current_length += 1
        else:
            if current_length > maximum_length:
                maximum_length = current_length
                maximum_subarray_same_modulus = numbers[i - current_length:i]
            current_length = 1

    if current_length > maximum_length:
        maximum_subarray_same_modulus = numbers[len(numbers) - current_length:]

    return maximum_subarray_same_modulus

#
# Write below this comment
# UI section
# Write all functions that have input or print statements here
# Ideally, this section should not contain any calculations relevant to program functionalities
#

def read_complex_number():
    print("Enter a complex number")
    real_part = int(input("  Real part: "))
    imaginary_part = int(input("  Imaginary part: "))
    return create_complex_number_list(real_part, imaginary_part)

def display_complex_number(complex_number):
    print("Complex number:", to_string_complex_list(complex_number))

def display_complex_numbers(complex_numbers):
    for complex_number in complex_numbers:
        print(to_string_complex_list(complex_number))

def display_menu():
    print("\nMenu:")
    print("1. Read a new complex number")
    print("2. Display all complex numbers")
    print("3. Show longest subarray of distinct numbers")
    print("4. Show longest subarray with the same modulus")
    print("5. Exit")

def main():
    complex_numbers = []

    while True:
        display_menu()
        option = int(input("Choose an option: "))

        READ_COMPLEX_NUMBER = 1
        DISPLAY_COMPLEX_NUMBERS = 2
        LONGEST_DISTINCT_SUBARRAY = 3
        LONGEST_SUBARRAY_SAME_MODULUS = 4
        EXIT = 5

        if option == READ_COMPLEX_NUMBER:
            complex_numbers.append(read_complex_number())

        elif option == DISPLAY_COMPLEX_NUMBERS:
            print("\nAll complex numbers:")
            display_complex_numbers(complex_numbers)

        elif option == LONGEST_DISTINCT_SUBARRAY:
            subarray_distinct = longest_subarray_distinct(complex_numbers)
            print("\nLongest subarray of distinct numbers:")
            display_complex_numbers(subarray_distinct)

        elif option == LONGEST_SUBARRAY_SAME_MODULUS:
            subarray_same_modulus = longest_subarray_same_modulus(complex_numbers)
            print("\nLongest subarray with the same modulus:")
            display_complex_numbers(subarray_same_modulus)

        elif option == EXIT:
            print("Goodbye!")
            break
        else:
            print("Invalid option. Try again.")


if __name__ == "__main__":
    main()