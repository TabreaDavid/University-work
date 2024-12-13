class Student:
    def __init__(self, studentId, studentName, studentGroup):
        self.id = studentId
        self.name = studentName
        self.group = studentGroup


    def getStudentId(self):
        return self.id

    def getStudentName(self):
        return self.name

    def getStudentGroup(self):
        return self.name

    def setStudentId(self, newId):
        self.id = newId

    def setStudentName(self, newName):
        self.name = newName

    def setStudentGroup(self, newGroup):
        self.group = newGroup

    def __repr__(self):
        return f"Id = {self.id}, Name = {self.name}, Group = {self.group}"