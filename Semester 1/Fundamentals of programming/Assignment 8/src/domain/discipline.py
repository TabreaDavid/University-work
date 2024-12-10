class Discipline:
    def __init__(self, disciplineId: int, disciplineName):
        self.disciplineName = disciplineName
        self.disciplineId = disciplineId

    @property
    def id(self):
        return self.disciplineId

    @property
    def name(self):
        return self.disciplineName

    def __str__(self):
        return f'Discipline ID: {self.id} | Discipline name: {self.name}'
