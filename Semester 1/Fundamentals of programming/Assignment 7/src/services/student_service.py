from src.domain.student import Student

class StudentService:
    def __init__(self, repository):
        self.repository = repository
        self.undoStack = []

    def addStudentService(self, studentId, studentName, studentGroup):
        student = Student(studentId, studentName, studentGroup)
        self.undoStack.append(self.repository.getAllStudents()[:])
        self.repository.addStudent(student)

    def listStudents(self):
        for student in self.repository.getAllStudents():
            print(student)
        print('\n')

    def undoService(self):
        if not self.undoStack:
            print("No operations to undo")
            return

        previousListState = self.undoStack.pop()
        self.repository.studentsList = previousListState

    def filterByGroup(self, group):
        self.undoStack.append(self.repository.getAllStudents()[:])
        self.repository.deleteStudentsByGroup(group)