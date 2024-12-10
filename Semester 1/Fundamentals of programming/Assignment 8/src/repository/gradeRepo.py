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
            print(grade)