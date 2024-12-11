#
# This is the program's UI module. The user interface and all interaction with the user (print and input statements) are found here
#

from functions import generate_10_random_transactions,add_transaction,remove_expenses_by_apartment_range,modify_expense,filter_by_utility,filter_by_bill_amount,undo_command

def print_transactions_menu():
    print("\nCommands:")
    print("1. add <apartment_number> <utility> <bill> - Add a new transaction.")
    print("2. remove <start> to <end> - Remove transactions for apartments in a range.")
    print("3. modify <apartment_number> <utility> with <new_bill> - Modify a transaction.")
    print("4. filter <utility> - Keep only transactions of a specific utility.")
    print("5. filter <max_bill> - Keep only transactions with bills below a certain amount.")
    print("6. undo - Undo the last operation.")
    print("7. show - Display all transactions.")
    print("8. exit - Exit the program.")


def activate_apartment_transaction_ui():
    transactions_list = generate_10_random_transactions()
    transaction_list_change_history = []

    while True:
        print_transactions_menu()
        user_command = input("Enter a command: ")

        try:
            if user_command.startswith("add "):
                splitted_user_commands_list = user_command.split()
                apartment_number = int(splitted_user_commands_list[1])
                chosen_utility = splitted_user_commands_list[2]
                billed_amount = int(splitted_user_commands_list[3])

                transaction_list_change_history.append(transactions_list[:])
                add_transaction(transactions_list, apartment_number, chosen_utility, billed_amount)
                print("Transaction added successfully")

            elif user_command.startswith("remove "):
                splitted_user_commands_list = user_command.split()
                if "to" in splitted_user_commands_list:
                    start = int(splitted_user_commands_list[1])
                    end = int(splitted_user_commands_list[3])

                    transaction_list_change_history.append(transactions_list[:])
                    remove_expenses_by_apartment_range(transactions_list, start, end)
                    print("Transactions removed successfully")

            elif user_command.startswith("modify "):
                splitted_user_commands_list = user_command.split()
                apartment_number = int(splitted_user_commands_list[1])
                chosen_utility = splitted_user_commands_list[2]
                new_bill = int(splitted_user_commands_list[4])

                transaction_list_change_history.append(transactions_list[:])
                modify_expense(transactions_list, apartment_number, chosen_utility, new_bill)
                print("Transaction modified successfully.")

            elif user_command.startswith("filter "):
                splitted_user_commands_list = user_command.split()

                if splitted_user_commands_list[1].isdigit():
                    max_bill = int(splitted_user_commands_list[1])

                    transaction_list_change_history.append(transactions_list[:])
                    filter_by_bill_amount(transactions_list, max_bill)

                    print("Transactions filtered by bill amount")
                else:
                    chosen_utility = splitted_user_commands_list[1]

                    transaction_list_change_history.append(transactions_list[:])
                    filter_by_utility(transactions_list, chosen_utility)
                    print("Transactions filtered by utility")

            elif user_command == "undo":
                transactions_list = undo_command(transactions_list, transaction_list_change_history)
                print("Undo successful")

            elif user_command == "show":
                if not transactions_list:
                    print("No transactions to display")
                else:
                    print("\nCurrent Transactions:")
                    for transaction in transactions_list:
                        print(f"Apartment {transaction[0]} | {transaction[1]} | {transaction[2]} RON")

            elif user_command == "exit":
                print("Goodbye!")
                break

            else:
                print("Invalid command. Please try again.")

        except ValueError as error:
            print(f"Error: {error}")