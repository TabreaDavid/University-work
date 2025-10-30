package view;

import controller.Controller;
import exceptions.MyException;
import model.PrgState;
import model.adt.*;
import model.expressions.ArithExp;
import model.expressions.ValueExp;
import model.expressions.VarExp;
import model.statements.*;
import model.types.BoolType;
import model.types.IntType;
import model.values.BoolValue;
import model.values.IntValue;
import repository.IRepository;
import repository.Repository;

import java.util.Scanner;

public class View {

    public static void main(String[] args) {
        IStmt ex1 = new CompStmt(new VarDeclStmt("v", new IntType()),
                new CompStmt(new AssignStmt("v", new ValueExp(new IntValue(2))), new PrintStmt(new VarExp("v"))));

        IStmt ex2 = new CompStmt(new VarDeclStmt("a", new IntType()),
                new CompStmt(new VarDeclStmt("b", new IntType()),
                        new CompStmt(
                                new AssignStmt("a",
                                        new ArithExp('+', new ValueExp(new IntValue(2)),
                                                new ArithExp('*', new ValueExp(new IntValue(3)),
                                                        new ValueExp(new IntValue(5))))),
                                new CompStmt(
                                        new AssignStmt("b",
                                                new ArithExp('+', new VarExp("a"), new ValueExp(new IntValue(1)))),
                                        new PrintStmt(new VarExp("b"))))));

        IStmt ex3 = new CompStmt(new VarDeclStmt("a", new BoolType()),
                new CompStmt(new VarDeclStmt("v", new IntType()),
                        new CompStmt(new AssignStmt("a", new ValueExp(new BoolValue(true))),
                                new CompStmt(
                                        new IfStmt(new VarExp("a"), new AssignStmt("v", new ValueExp(new IntValue(2))),
                                                new AssignStmt("v", new ValueExp(new IntValue(3)))),
                                        new PrintStmt(new VarExp("v"))))));

        Scanner scanner = new Scanner(System.in);
        while (true) {
            printMenu();
            int option = scanner.nextInt();
            IStmt selectedExample = null;
            if (option == 1) {
                selectedExample = ex1;
            } else if (option == 2) {
                selectedExample = ex2;
            } else if (option == 3) {
                selectedExample = ex3;
            } else if (option == 0) {
                break;
            }

            if (selectedExample != null) {
                runProgram(selectedExample);
            }
        }
        scanner.close();
    }

    private static void runProgram(IStmt example) {
        try {
            MyIStack<IStmt> stk = new MyStack<>();
            MyIDictionary<String, model.values.Value> symtbl = new MyDictionary<>();
            MyIList<model.values.Value> out = new MyList<>();

            PrgState crtPrgState = new PrgState(stk, symtbl, out, example);

            IRepository repo = new Repository();
            repo.addPrg(crtPrgState);
            Controller ctrl = new Controller(repo);

            ctrl.allStep();
        } catch (MyException e) {
            System.out.println("Error: " + e.getMessage());
        }
    }


    //mkdir -p out && javac -d out $(find src -name '*.java') && java -cp out view.View
    private static void printMenu() {
        System.out.println("\nChoose an example to run:");
        System.out.println("1. int v; v=2; Print(v)");
        System.out.println("2. int a; int b; a=2+3*5; b=a+1; Print(b)");
        System.out.println("3. bool a; int v; a=true; (If a Then v=2 Else v=3); Print(v)");
        System.out.println("0. Exit");
        System.out.print("Your choice: ");
    }
}
