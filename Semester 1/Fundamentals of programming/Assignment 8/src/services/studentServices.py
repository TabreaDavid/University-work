from src.domain.student import Student


class StudentServices:
    def __init__(self, studentRepository):
        self.studentRepository = studentRepository

    def addStudentService(self, studentId, studentName):
        newStudent = Student(studentId, studentName)
        self.studentRepository.repositoryAddStudent(newStudent)

    def removeStudentService(self, studentId):
        self.studentRepository.repositoryRemoveStudent(studentId)

    def listStudents(self):
        self.studentRepository.listStudents()

    @property
    def students(self):
        return self.studentRepository.students
