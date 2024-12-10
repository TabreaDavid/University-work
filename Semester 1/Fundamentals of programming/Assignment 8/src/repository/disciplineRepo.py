from faker.proxy import Faker
from random import randint
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

    def randomDisciplineNameGenerator(self):
        disciplines = ['Math', 'Computer Science', 'Physics', 'Biology', 'Physical education', 'Chemistry']
        disciplineIndex = randint(0, 5)
        return disciplines[disciplineIndex]

    def isIdAvailable(self, checkedId):
        for discipline in self.disciplineList:
            if discipline.id == checkedId:
                return False
        return True

    def generateDisciplines(self):
        faker = Faker()
        for i in range(20):
            disciplineId = randint(1,300)
            while not self.isIdAvailable(disciplineId):
                disciplineId = randint(1, 300)

            disciplineName = self.randomDisciplineNameGenerator()

            newDiscipline = Discipline(disciplineId, disciplineName)
            self.repositoryAddDiscipline(newDiscipline)

    def repositoryListDisciplines(self):
        for discipline in self.disciplineList:
            print(discipline)