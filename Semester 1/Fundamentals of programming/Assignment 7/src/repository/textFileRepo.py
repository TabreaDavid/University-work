from src.domain.student import Student
from src.repository.repository import MemoryRepository

ID_INDEX = 0
NAME_INDEX = 1
GROUP_INDEX = 2

class TextFileRepository(MemoryRepository):
    def __init__(self, file_path):
        super().__init__()
        self.filePath = file_path
        self.loadStudentsFromFile()

    def addStudent(self, student):
        super().addStudent(student)
        self.saveStudentsToFile()

    def deleteStudentsByGroup(self, group):
        super().deleteStudentsByGroup(group)
        self.saveStudentsToFile()

    def loadStudentsFromFile(self):
        with open(self.filePath, 'r') as file:
            self.studentsList = []
            for line in file:
                studentAttributes = line.strip().split(',')
                if len(studentAttributes) == 3:
                    student_id, name, group = int(studentAttributes[ID_INDEX]), studentAttributes[NAME_INDEX], int(studentAttributes[GROUP_INDEX])
                    self.studentsList.append(Student(student_id, name, group))

    def saveStudentsToFile(self):
        with open(self.filePath, 'w') as file:
            for student in self.studentsList:
                file.write(f"{student.id},{student.name},{student.group}\n")