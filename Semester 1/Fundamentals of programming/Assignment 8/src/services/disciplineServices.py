from src.domain.discipline import Discipline

class DisciplineServices:
    def __init__(self, disciplineRepository):
        self.disciplineRepository = disciplineRepository

    def addDisciplineService(self, disciplineId, disciplineName):
        newDiscipline = Discipline(disciplineId, disciplineName)
        self.disciplineRepository.repositoryAddDiscipline(newDiscipline)

    def removeDisciplineService(self, disciplineId):
        self.disciplineRepository.repositoryRemoveDiscipline(disciplineId)

    def listDisciplinesService(self):
        self.disciplineRepository.repositoryListDisciplines()

    def searchDisciplineService(self, disciplineId):
        for discipline in self.disciplineRepository.disciplines:
            if discipline.id == disciplineId:
                return discipline.name

        return 'Discipline not found'
