from src.repository import Repository
from src.services import Services
from src.ui import ScrambleGameUi
from random import randint

def main():
    repo = Repository('input.txt')
    services = Services(repo)
    ui = ScrambleGameUi(services)
    ui.start()

main()