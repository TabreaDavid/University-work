from faker.proxy import Faker
from random import randint
from src.domain.student import Student

class StudentRepository:
    def __init__(self):
        self.studentList = []
        self.generateStudents()

    @property
    def students(self):
        return self.studentList

    def repositoryAddStudent(self, addedStudent):
        self.studentList.append(addedStudent)

    def repositoryRemoveStudent(self, removedStudentId):
        for student in self.studentList:
            if student.id == removedStudentId:
                self.studentList.remove(student)

    def isIdAvailable(self, checkedId):
        for student in self.studentList:
            if student.id == checkedId:
                return False
        return True

    def generateStudents(self):
        faker = Faker()
        for i in range(20):
            studentId = randint(1,300)
            while not self.isIdAvailable(studentId):
                studentId = randint(1, 300)

            studentName = faker.name()
            newStudent = Student(studentId, studentName)
            self.repositoryAddStudent(newStudent)

    def listStudents(self):
        for student in self.studentList:
            print(student)
