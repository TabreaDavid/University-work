class MemoryRepository:
    def __init__(self):
        self.studentsList = []

    def addStudent(self, student):
        self.studentsList.append(student)

    def getAllStudents(self):
        return self.studentsList

    def deleteStudentsByGroup(self, group):
        updatedStudentsList = []
        for student in self.studentsList:
            if student.group != group:
                updatedStudentsList.append(student)
        self.studentsList = updatedStudentsList