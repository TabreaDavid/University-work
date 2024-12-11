from src.repository.studentRepo import StudentRepository
from src.repository.disciplineRepo import DisciplineRepository
from src.repository.gradeRepo import GradeRepository
from src.services.studentServices import StudentServices
from src.services.disciplineServices import DisciplineServices
from src.services.gradeServices import GradeServices
from src.ui.console import Console

def main():
    studentRepository = StudentRepository()
    disciplineRepository = DisciplineRepository()
    gradeRepository = GradeRepository()

    studentServices = StudentServices(studentRepository)
    disciplineServices = DisciplineServices(disciplineRepository)
    gradeServices = GradeServices(studentRepository, disciplineRepository, gradeRepository)

    console = Console(studentServices,disciplineServices,gradeServices)

    console.runUi()

main()