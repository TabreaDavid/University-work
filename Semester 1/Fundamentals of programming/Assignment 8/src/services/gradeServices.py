from src.domain.grade import Grade

class GradeServices:
    def __init__(self, studentRepository, disciplineRepository, gradeRepository):
        self.gradeRepository = gradeRepository
        self.studentRepository = studentRepository
        self.disciplineRepository = disciplineRepository

    def addGradeService(self, studentId: int, disciplineId: int, gradeValue: int):
        chosenStudent = None
        chosenDiscipline = None
        for student in self.studentRepository.students:
            if student.id == studentId:
                chosenStudent = student

        for discipline in self.disciplineRepository.disciplines:
            if discipline.id == disciplineId:
                chosenDiscipline = discipline

        if not chosenDiscipline or not chosenStudent:
            raise ValueError("Student or discipline ID invalid! ")

        newGrade = Grade(studentId, chosenStudent, disciplineId, chosenDiscipline, gradeValue)
        self.gradeRepository.repositoryAddGrade(newGrade)

    def listGradesService(self):
        self.gradeRepository.repositoryListGrades()






