class Student:
    def __init__(self, studentId: int, studentName):
        self.studentName = studentName
        self.studentId = studentId

    @property
    def id(self):
        return self.studentId
    
    @property
    def name(self):
        return self.studentName
    
    def __str__(self):
        return f'Student ID: {self.id} | Student name: {self.name}'
