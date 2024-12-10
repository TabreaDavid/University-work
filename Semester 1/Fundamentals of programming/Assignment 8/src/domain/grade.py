from src.domain.discipline import Discipline
from src.domain.student import Student

class Grade:
    def __init__(self, studentId: int, studentName, disciplineId: int, disciplineName, gradeValue: int):
        self.student = Student(studentId, studentName)
        self.discipline = Discipline(disciplineId, disciplineName)
        self.gradeValue = gradeValue

    def __str__(self):
        # return f"{self.gradeValue}"
         return f'{self.student} | {self.discipline} | Grade: {self.gradeValue}'
        # return f'Student ID: {self.student.id}| Student name: {self.student.name} | Discipline ID: {self.discipline.id} | Discipline name: {self.discipline.name} | Grade: {self.gradeValue}'

