from random import randint

APARTMENT_NUMBER_INDEX = 0
UTILITY_INDEX = 1
BILL_AMOUNT_INDEX = 2

def generate_10_random_transactions():
    random_generated_transactions = []
    valid_utilities_list = ["water", "heating", "electricity", "gas", "other"]

    for i in range(10):
        random_generated_apartment_number = randint(1, 100)
        random_generated_utility = valid_utilities_list[randint(0, len(valid_utilities_list) - 1)]
        random_generated_bill_amount = randint(1, 1000)
        random_generated_transactions.append([random_generated_apartment_number, random_generated_utility, random_generated_bill_amount])

    return random_generated_transactions


def add_transaction(apartment_transactions_list, apartment_number, chosen_utility, billed_amount):
    if chosen_utility not in ["water", "heating", "electricity", "gas", "other"]:
        chosen_utility = "other"
    apartment_transactions_list.append([apartment_number, chosen_utility, billed_amount])


def remove_expenses_by_apartment_range(apartment_transactions_list, first_apartment_numebr, second_apartment_number):
    for transaction in apartment_transactions_list:
        if first_apartment_numebr <= transaction[APARTMENT_NUMBER_INDEX] <= second_apartment_number:
            transaction[BILL_AMOUNT_INDEX] = 0


def modify_expense(apartment_transactions_list, apartment_number, chosen_utility, new_bill):
    for transaction in apartment_transactions_list:
        if transaction[APARTMENT_NUMBER_INDEX] == apartment_number and transaction[UTILITY_INDEX] == chosen_utility:
            transaction[BILL_AMOUNT_INDEX] = new_bill
            return


def filter_by_utility(apartment_transactions_list, chosen_utility):
    i = 0
    while i < len(apartment_transactions_list):
        if apartment_transactions_list[i][UTILITY_INDEX] != chosen_utility:
            apartment_transactions_list.pop(i)
        else:
            i += 1


def filter_by_bill_amount(apartment_transactions_list, max_bill):
    i = 0
    while i < len(apartment_transactions_list):
        if apartment_transactions_list[i][BILL_AMOUNT_INDEX] >= max_bill:
            apartment_transactions_list.pop(i)
        else:
            i += 1


def undo_command(apartment_transactions_list, transaction_list_change_history):
    if transaction_list_change_history:
        return transaction_list_change_history.pop()
    else:
        print("Nothing to undo!")
        return apartment_transactions_list