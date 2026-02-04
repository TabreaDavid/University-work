package view;

import controller.Controller;
import exceptions.MyException;
import model.PrgState;
import model.adt.*;
import model.expressions.*;
import model.statements.*;
import model.types.*;
import model.values.*;
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

        // Example 4: Relational expressions
        // int a; int b; a=5; b=10; if(a<b) then print(100) else print(200)
        IStmt ex4 = new CompStmt(new VarDeclStmt("a", new IntType()),
                new CompStmt(new VarDeclStmt("b", new IntType()),
                        new CompStmt(new AssignStmt("a", new ValueExp(new IntValue(5))),
                                new CompStmt(new AssignStmt("b", new ValueExp(new IntValue(10))),
                                        new IfStmt(new RelationalExp("<", new VarExp("a"), new VarExp("b")),
                                                new PrintStmt(new ValueExp(new IntValue(100))),
                                                new PrintStmt(new ValueExp(new IntValue(200))))))));

        // Example 5: File operations
        // string filename; int v; filename="test.txt"; openRFile(filename); readFile(filename,v); print(v); closeRFile(filename)
        IStmt ex5 = new CompStmt(new VarDeclStmt("filename", new StringType()),
                new CompStmt(new VarDeclStmt("v", new IntType()),
                        new CompStmt(new AssignStmt("filename", new ValueExp(new StringValue("test.txt"))),
                                new CompStmt(new OpenRFileStmt(new VarExp("filename")),
                                        new CompStmt(new ReadFileStmt(new VarExp("filename"), "v"),
                                                new CompStmt(new PrintStmt(new VarExp("v")),
                                                        new CompStmt(new ReadFileStmt(new VarExp("filename"), "v"),
                                                                new CompStmt(new PrintStmt(new VarExp("v")),
                                                                        new CloseRFileStmt(new VarExp("filename"))))))))));

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
            } else if (option == 4) {
                selectedExample = ex4;
            } else if (option == 5) {
                selectedExample = ex5;
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
            MyIDictionary<String, java.io.BufferedReader> filetbl = new MyDictionary<>();
            MyIHeap heap = new MyHeap();

            PrgState crtPrgState = new PrgState(stk, symtbl, out, filetbl, heap, example);

            IRepository repo = new Repository("log.txt");
            repo.addPrg(crtPrgState);
            Controller ctrl = new Controller(repo);

            ctrl.allStep();
        } catch (MyException | InterruptedException e) {
            System.out.println("Error: " + e.getMessage());
        }
    }



    private static void printMenu() {
        System.out.println("\nChoose an example to run:");
        System.out.println("1. int v; v=2; Print(v)");
        System.out.println("2. int a; int b; a=2+3*5; b=a+1; Print(b)");
        System.out.println("3. bool a; int v; a=true; (If a Then v=2 Else v=3); Print(v)");
        System.out.println("4. int a,b; a=5; b=10; if(a<b) then print(100) else print(200)");
        System.out.println("5. File operations: openRFile, readFile (twice), print, closeRFile");
        System.out.println("0. Exit");
        System.out.print("Your choice: ");
    }
}
//javac -d out src/model/types/*.java src/model/values/*.java src/model/adt/*.java src/exceptions/*.java src/model/expressions/*.java src/model/statements/*.java src/model/*.java src/repository/*.java src/controller/*.java src/view/*.java && java -cp out view.Interpreter