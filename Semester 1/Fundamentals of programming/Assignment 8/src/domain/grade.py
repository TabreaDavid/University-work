from src.domain.discipline import Discipline
from src.domain.student import Student

class Grade:
    def __init__(self, studentId: int, studentName, disciplineId: int, disciplineName, gradeValue: int):
        self.student = Student(studentId, studentName)
        self.discipline = Discipline(disciplineId, disciplineName)
        self.gradeValue = gradeValue


