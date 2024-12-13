ADD_STUDENT = 1
DISPLAY_STUDENTS = 2
FILTER_BY_GROUP = 3
UNDO_CHOICE = 4
EXIT = 5
class StudentUi:
    def __init__(self, service):
        self.service = service

    def printStudentMenu(self):
        print("1. Add student")
        print("2. Display students")
        print("3. Filter students by group")
        print("4. Undo")
        print("5. Exit\n")

    def runUi(self):
        while True:
            self.printStudentMenu()
            userChoice = int(input("Enter your choice: "))

            if userChoice == ADD_STUDENT:
                self.addStudentUi()
            if userChoice == DISPLAY_STUDENTS:
                self.displayStudents()
            if userChoice == FILTER_BY_GROUP:
                self.filterStudents()
            if userChoice == UNDO_CHOICE:
                self.undoChoice()
            if userChoice == EXIT:
                break

    def addStudentUi(self):
        studentId = input("ID: ")
        studentName = input("Name: ")
        studentGroup = input("Group: ")

        self.service.addStudentService(studentId, studentName, studentGroup)

    def displayStudents(self):
        self.service.listStudents()

    def undoChoice(self):
        self.service.undoService()

    def filterStudents(self):
        filteredGroup = int(input("Enter the group: "))  # Convert input to integer
        self.service.filterByGroup(filteredGroup)