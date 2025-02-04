from random import randint

class Services:
    def __init__(self, repo):
        self.repo = repo

    def changeLetters(self, sentence, firstWordIndex, firstLetterIndex, secondWordIndex, secondLetterIndex):
        '''
        Changes the letters at the specified indices in the sentence
        Raises value error if indices are invalid
        :param sentence: The sentence to be changed
        :param firstWordIndex: The index of the first word in the sentence
        :param firstLetterIndex: The index of the first letter in the first word
        :param secondWordIndex: The index of the second word in the sentence
        :param secondLetterIndex: The index of the second letter in the second word
        :return: New sentence with swapped letters
        '''
        wordsList = sentence.split(" ")

        firstWordLength = len(wordsList[firstWordIndex])
        secondWordLength = len(wordsList[secondWordIndex])

        invalidIndices = {0, firstWordLength - 1, 0, secondWordLength - 1}

        if firstLetterIndex in invalidIndices or secondLetterIndex in invalidIndices:
            raise ValueError("Indexes can only be from the middle of words!")

        firstCharacter = wordsList[firstWordIndex][firstLetterIndex]
        secondCharacter = wordsList[secondWordIndex][secondLetterIndex]

        wordsList[firstWordIndex] = "".join([wordsList[firstWordIndex][:firstLetterIndex], secondCharacter, wordsList[firstWordIndex][firstLetterIndex + 1:]])
        wordsList[secondWordIndex] = "".join([wordsList[secondWordIndex][:secondLetterIndex], firstCharacter, wordsList[secondWordIndex][secondLetterIndex + 1:]])
        return " ".join(wordsList)

    def shuffleSentence(self, sentence):
        '''
        Randomly shuffles the letters in a sentence by keeping the first and last characters unchanged of each word
        :param sentence: The sentence to be shuffled
        :return: The shuffled sentence
        '''
        words = sentence.split(" ")
        shuffledWords = []

        for word in words:
            if len(word) > 3:
                firstCharacter = word[0]
                lastCharacter = word[-1]
                middleCharacters = list(word[1:-1])
                for i in range(len(middleCharacters)):
                    randomIndex = randint(0, len(middleCharacters) - 1)
                    middleCharacters[i], middleCharacters[randomIndex] = middleCharacters[randomIndex], middleCharacters[i]
                shuffledWord = firstCharacter + ''.join(middleCharacters) + lastCharacter
                shuffledWords.append(shuffledWord)
            else:
                shuffledWords.append(word)

        return " ".join(shuffledWords)

    def pickRandomSentence(self):
        sentences = self.repo.returnSentences()
        randomInde = randint(0, len(sentences) - 1)
        return sentences[randomInde]