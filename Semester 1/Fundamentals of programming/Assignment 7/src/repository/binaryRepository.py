import pickle
from src.domain.student import Student
from src.repository.repository import MemoryRepository

class BinaryFileRepository(MemoryRepository):
    def __init__(self, filePath):
        super().__init__()
        self.filePath = filePath
        self.loadStudentsFromFile()

    def addStudent(self, student):
        super().addStudent(student)
        self.saveStudentsToFile()

    def deleteStudentsByGroup(self, group):
        super().deleteStudentsByGroup(group)
        self.saveStudentsToFile()

    def loadStudentsFromFile(self):
        with open(self.filePath, 'rb') as file:
            self.studentsList = pickle.load(file)

    def saveStudentsToFile(self):
        with open(self.filePath, 'wb') as file:
            pickle.dump(self.studentsList, file)