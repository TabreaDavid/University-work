from src.domain.discipline import Discipline

class DisciplineRepository:
    def __init__(self):
        self.disciplineList = []
        self.generateDisciplines()

    @property
    def disciplines(self):
        return self.disciplineList

    def repositoryAddDiscipline(self, addedDiscipline):
        self.disciplineList.append(addedDiscipline)

    def repositoryRemoveDiscipline(self, disciplineId):
        for discipline in self.disciplineList:
            if discipline.id == disciplineId:
                self.disciplineList.remove(discipline)

    def isIdAvailable(self, checkedId):
        for discipline in self.disciplineList:
            if discipline.id == checkedId:
                return False
        return True

    def generateDisciplines(self):
        disciplines = [
            'Math', 'Computer Science', 'Physics', 'Biology', 'Physical education',
            'Chemistry', 'History', 'Geography', 'Economics', 'Literature',
            'Philosophy', 'Art', 'Music', 'Drama', 'Psychology',
            'Sociology', 'Political Science', 'Environmental Science',
            'Statistics', 'Astronomy'
        ]
        for disciplineId in range(20):
            newDiscipline = Discipline(disciplineId, disciplines[disciplineId])
            self.repositoryAddDiscipline(newDiscipline)


    def repositoryListDisciplines(self):
        for discipline in self.disciplineList:
            print(discipline)