from src.repository.repository import MemoryRepository
from src.services.student_service import StudentService
from src.ui.student_ui import StudentUi
from src.repository.binaryRepository import BinaryFileRepository
from src.repository.textFileRepo import TextFileRepository

if __name__ == "__main__":

    repository = TextFileRepository("students.txt")
    #repository = BinaryFileRepository("students.bin")
    # repository = MemoryRepository()

    studentService = StudentService(repository)

    StudentUi= StudentUi(studentService)

    initial_data = [
        (1, "David", 1), (2, "Iacob", 1), (3, "Valentin", 2),
        (4, "Marius", 3), (5, "Viorel", 3), (6, "Dragos", 4),
        (7, "Andrei", 4), (8, "Radu", 5), (9, "Marian", 5),
        (10, "Marcel", 6),
    ]
    for student_id, name, group in initial_data:
        studentService.addStudentService(student_id, name, group)

    StudentUi.runUi()