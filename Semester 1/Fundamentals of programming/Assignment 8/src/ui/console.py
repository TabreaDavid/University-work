EXIT = 0
ADD_STUDENT = 1
REMOVE_STUDENT = 2
DISPLAY_STUDENTS = 3
ADD_DISCIPLINE = 4
REMOVE_DISCIPLINE = 5
DISPLAY_DISCIPLINES = 6
GRADE_STUDENT = 7
DISPLAY_GRADES = 8
SEARCH_STUDENT = 9
SEARCH_DISCIPLINE = 10

class Console:
    def __init__(self, studentServices, disciplineServices, gradeServices):
        self.studentServices = studentServices
        self.disciplineServices = disciplineServices
        self.gradeServices = gradeServices

    @staticmethod
    def printMenu():
        print("\n1. Add student")
        print("2. Remove student by ID")
        print("3. Display students")
        print("4. Add discipline")
        print("5. Remove discipline by ID")
        print("6. Display disciplines")
        print("7. Grade student by ID's")
        print("8. Display grades")
        print("9. Search student by ID")
        print("10. Search discipline by ID")
        print(f"0. Exit\n")

    def addStudentUi(self, studentId, studentName):
        self.studentServices.addStudentService(studentId,studentName)

    def removeStudentUi(self, removedStudendId):
        self.studentServices.removeStudentService(removedStudendId)

    def displayStudents(self):
        self.studentServices.listStudents()

    def addDisciplineUi(self, disciplineId, disciplineName):
        self.disciplineServices.addDisciplineService(disciplineId, disciplineName)

    def removeDisciplineUi(self, disciplineId):
        self.disciplineServices.removeDisciplineService(disciplineId)

    def displayDisciplines(self):
        self.disciplineServices.listDisciplinesService()

    def gradeStudentUi(self, studentId, disciplineId, gradeValue):
        self.gradeServices.addGradeService(studentId, disciplineId, gradeValue)

    def displayGrades(self):
        self.gradeServices.listGradesService()

    def searchStudentUi(self, studentId):
        print(self.studentServices.searchStudentService(studentId))

    def searchDisciplineUi(self, disciplineId):
        print(self.disciplineServices.searchDisciplineService(disciplineId))

    def removeGradeByDisciplineUi(self, disciplineId):
        self.gradeServices.removeGradeByDisciplineService(disciplineId)

    def removeGradeByStudentUi(self, studentId):
        self.gradeServices.removeGradeByStudentService(studentId)

    def runUi(self):
        while True:
            Console.printMenu()
            userChoice = int(input("Your choice: "))

            if userChoice == ADD_STUDENT:
                studentId = int(input("Enter student ID: "))
                studentName= input("Enter student name: ")
                self.addStudentUi(studentId, studentName)

            elif userChoice == REMOVE_STUDENT:
                removedStudentId = int(input("Enter student ID: "))
                self.removeStudentUi(removedStudentId)
                self.removeGradeByStudentUi(removedStudentId)

            elif userChoice == DISPLAY_STUDENTS:
                self.displayStudents()

            elif userChoice == ADD_DISCIPLINE:
                disciplineId = int(input("Enter discipline id: "))
                disciplineName = input("Enter discipline name: ")
                self.addDisciplineUi(disciplineId, disciplineName)

            elif userChoice == REMOVE_DISCIPLINE:
                removedDisciplineId = int(input("Enter discipline id: "))
                self.removeDisciplineUi(removedDisciplineId)
                self.removeGradeByDisciplineUi(removedDisciplineId)

            elif userChoice == DISPLAY_DISCIPLINES:
                self.displayDisciplines()

            elif userChoice == GRADE_STUDENT:
                studentId = int(input("Enter student id: "))
                disciplineId = int(input("Enter discipline id: "))
                gradeValue = int(input("Enter the grade: "))
                self.gradeStudentUi(studentId, disciplineId, gradeValue)

            elif userChoice == DISPLAY_GRADES:
                self.displayGrades()

            elif userChoice == SEARCH_STUDENT:
                studentId = int(input("Enter student ID: "))
                self.searchStudentUi(studentId)

            elif userChoice == SEARCH_DISCIPLINE:
                disciplineId = int(input('Enter discipline ID: '))
                self.searchDisciplineUi(disciplineId)

            elif userChoice == EXIT:
                break

            else: print("\nYour option is not in the menu!\n")



