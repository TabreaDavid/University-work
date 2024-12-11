class GradeRepository:
    def __init__(self):
        self.gradeList = []

    @property
    def grades(self):
        return self.gradeList

    def repositoryAddGrade(self, newGrade):
        self.gradeList.append(newGrade)

    def repositoryListGrades(self):
        for grade in self.gradeList:
            print(f'{grade.student.name} | {grade.discipline.name} | Grade: {grade.gradeValue}')

    def repositoryRemoveGradeByDiscipline(self, disciplineId):
        for grade in self.gradeList:
            if grade.discipline.id == disciplineId:
                self.gradeList.remove(grade)

    def repositoryRemoveGradeByStudent(self, studentId):
        for grade in self.gradeList:
            if grade.student.id == studentId:
                self.gradeList.remove(grade)

