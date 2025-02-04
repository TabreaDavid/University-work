class ScrambleGameUi:
    SWAP_COMMAND_LENGTH = 6
    INDEX = 3
    FIRST_WORD_INDEX = 1
    FIRST_LETTER_INDEX = 2
    SECOND_WORD_INDEX = 4
    SECOND_LETTER_INDEX = 5
    PLAY_OPTION = 1
    EXIT_OPTION = 0
    SCORE_PENALTY = 1

    def __init__(self, services):
        self.services = services

    def startGameplay(self):
        try:
            targetSentence = self.services.pickRandomSentence()
        except ValueError as error:
            print(f"Error: {error}")
            return

        scrambledSentence = self.services.shuffleSentence(targetSentence)
        score = self.calculateScore(targetSentence)
        self.displayStatus(scrambledSentence, score)

        while score > 0:
            userInput = input("Enter your command: ")
            commandParts = userInput.split(" ")

            if self.isValidSwap(commandParts):
                try:
                    firstWord, firstLetter, secondWord, secondLetter = map(int, [
                        commandParts[self.FIRST_WORD_INDEX],
                        commandParts[self.FIRST_LETTER_INDEX],
                        commandParts[self.SECOND_WORD_INDEX],
                        commandParts[self.SECOND_LETTER_INDEX]
                    ])
                    scrambledSentence = self.services.changeLetters(scrambledSentence, firstWord, firstLetter, secondWord, secondLetter)
                    score -= self.SCORE_PENALTY
                    self.displayStatus(scrambledSentence, score)

                    if scrambledSentence == targetSentence:
                        print("You have won the game!")
                        return
                except (ValueError, IndexError):
                    print(f"Invalid command, try again!")
                    continue

            elif commandParts[0] == "undo":
                scrambledSentence = targetSentence
                self.displayStatus(scrambledSentence, score)

            elif commandParts[0] == 'exit':
                print("Exiting...")
                return
            else:
                print("Invalid input, try again!")

        print("You have lost the game :(")
        return

    def start(self):
        while True:
            try:
                userChoice = int(input("Choose an option:  " + '\n' + '0. exit' + '\n' + '1. play' + '\n'))
                if userChoice == self.PLAY_OPTION:
                    self.startGameplay()
                elif userChoice == self.EXIT_OPTION:
                    print("Exiting...")
                    break
                else:
                    print("Invalid input! Enter 0 or 1")
            except ValueError:
                print("Invalid input! Enter 0 or 1")

    def calculateScore(self, sentence):
        score = 0
        for char in sentence:
            if char.isalpha():
                score += 1
        return score

    def displayStatus(self, sentence, score):
        print(f"{sentence} [score is: {score}]")

    def isValidSwap(self, commandParts):
        return commandParts[0] == "swap" and len(commandParts) == self.SWAP_COMMAND_LENGTH and commandParts[self.INDEX] == "-"
