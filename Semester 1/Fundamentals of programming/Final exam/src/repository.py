import os

class Repository:
    def __init__(self, fileName):
        self.fileName = fileName
        self.sentences = []
        self.load()

    def load(self):
        self.sentences = []
        if os.path.exists(self.fileName):
            with open(self.fileName, 'r') as file:
                for line in file:
                    line = line.strip()
                    if line:
                        self.sentences.append(line)

    def returnSentences(self):
        return self.sentences