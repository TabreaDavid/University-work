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

public class Interpreter {
    public static void main(String[] args) {
        Controller ctr1 = null, ctr2 = null, ctr3 = null, ctr4 = null, ctr5 = null, ctr6 = null;
        Controller ctr7 = null, ctr8 = null, ctr9 = null, ctr10 = null, ctr11 = null, ctr12 = null;
        Controller ctr13 = null;

        // Example 1: int v; v=2; Print(v)
        IStmt ex1 = new CompStmt(new VarDeclStmt("v", new IntType()),
                new CompStmt(new AssignStmt("v", new ValueExp(new IntValue(322))), 
                        new PrintStmt(new VarExp("v"))));

        try {
            ex1.typecheck(new MyDictionary<>());
            MyIStack<IStmt> stk1 = new MyStack<>();
            MyIDictionary<String, Value> symtbl1 = new MyDictionary<>();
            MyIList<Value> out1 = new MyList<>();
            MyIDictionary<String, java.io.BufferedReader> filetbl1 = new MyDictionary<>();
            MyIHeap heap1 = new MyHeap();
            PrgState prg1 = new PrgState(stk1, symtbl1, out1, filetbl1, heap1, ex1);
            IRepository repo1 = new Repository("log1.txt");
            repo1.addPrg(prg1);
            ctr1 = new Controller(repo1);
        } catch (MyException e) {
            System.out.println("Example 1 failed typechecking: " + e.getMessage());
        }

        // Example 2: int a; int b; a=2+3*5; b=a+1; Print(b)
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

        try {
            ex2.typecheck(new MyDictionary<>());
            MyIStack<IStmt> stk2 = new MyStack<>();
            MyIDictionary<String, Value> symtbl2 = new MyDictionary<>();
            MyIList<Value> out2 = new MyList<>();
            MyIDictionary<String, java.io.BufferedReader> filetbl2 = new MyDictionary<>();
            MyIHeap heap2 = new MyHeap();
            PrgState prg2 = new PrgState(stk2, symtbl2, out2, filetbl2, heap2, ex2);
            IRepository repo2 = new Repository("log2.txt");
            repo2.addPrg(prg2);
            ctr2 = new Controller(repo2);
        } catch (MyException e) {
            System.out.println("Example 2 failed typechecking: " + e.getMessage());
        }

        // Example 3: bool a; int v; a=true; (If a Then v=2 Else v=3); Print(v)
        IStmt ex3 = new CompStmt(new VarDeclStmt("a", new BoolType()),
                new CompStmt(new VarDeclStmt("v", new IntType()),
                        new CompStmt(new AssignStmt("a", new ValueExp(new BoolValue(true))),
                                new CompStmt(
                                        new IfStmt(new VarExp("a"), new AssignStmt("v", new ValueExp(new IntValue(2))),
                                                new AssignStmt("v", new ValueExp(new IntValue(3)))),
                                        new PrintStmt(new VarExp("v"))))));

        try {
            ex3.typecheck(new MyDictionary<>());
            MyIStack<IStmt> stk3 = new MyStack<>();
            MyIDictionary<String, Value> symtbl3 = new MyDictionary<>();
            MyIList<Value> out3 = new MyList<>();
            MyIDictionary<String, java.io.BufferedReader> filetbl3 = new MyDictionary<>();
            MyIHeap heap3 = new MyHeap();
            PrgState prg3 = new PrgState(stk3, symtbl3, out3, filetbl3, heap3, ex3);
            IRepository repo3 = new Repository("log3.txt");
            repo3.addPrg(prg3);
            ctr3 = new Controller(repo3);
        } catch (MyException e) {
            System.out.println("Example 3 failed typechecking: " + e.getMessage());
        }

        // Example 4: Relational expressions - int a,b; a=5; b=10; if(a<b) then print(100) else print(200)
        IStmt ex4 = new CompStmt(new VarDeclStmt("a", new IntType()),
                new CompStmt(new VarDeclStmt("b", new IntType()),
                        new CompStmt(new AssignStmt("a", new ValueExp(new IntValue(5))),
                                new CompStmt(new AssignStmt("b", new ValueExp(new IntValue(10))),
                                        new IfStmt(new RelationalExp("<", new VarExp("a"), new VarExp("b")),
                                                new PrintStmt(new ValueExp(new IntValue(100))),
                                                new PrintStmt(new ValueExp(new IntValue(200))))))));

        try {
            ex4.typecheck(new MyDictionary<>());
            MyIStack<IStmt> stk4 = new MyStack<>();
            MyIDictionary<String, Value> symtbl4 = new MyDictionary<>();
            MyIList<Value> out4 = new MyList<>();
            MyIDictionary<String, java.io.BufferedReader> filetbl4 = new MyDictionary<>();
            MyIHeap heap4 = new MyHeap();
            PrgState prg4 = new PrgState(stk4, symtbl4, out4, filetbl4, heap4, ex4);
            IRepository repo4 = new Repository("log4.txt");
            repo4.addPrg(prg4);
            ctr4 = new Controller(repo4);
        } catch (MyException e) {
            System.out.println("Example 4 failed typechecking: " + e.getMessage());
        }

        // Example 5: File operations
        // string varf; varf="test.in"; openRFile(varf); int varc; 
        // readFile(varf,varc);print(varc); readFile(varf,varc);print(varc); closeRFile(varf)
        IStmt ex5 = new CompStmt(new VarDeclStmt("varf", new StringType()),
                new CompStmt(new AssignStmt("varf", new ValueExp(new StringValue("test.in"))),
                        new CompStmt(new OpenRFileStmt(new VarExp("varf")),
                                new CompStmt(new VarDeclStmt("varc", new IntType()),
                                        new CompStmt(new ReadFileStmt(new VarExp("varf"), "varc"),
                                                new CompStmt(new PrintStmt(new VarExp("varc")),
                                                        new CompStmt(new ReadFileStmt(new VarExp("varf"), "varc"),
                                                                new CompStmt(new PrintStmt(new VarExp("varc")),
                                                                        new CloseRFileStmt(new VarExp("varf"))))))))));

        try {
            ex5.typecheck(new MyDictionary<>());
            MyIStack<IStmt> stk5 = new MyStack<>();
            MyIDictionary<String, Value> symtbl5 = new MyDictionary<>();
            MyIList<Value> out5 = new MyList<>();
            MyIDictionary<String, java.io.BufferedReader> filetbl5 = new MyDictionary<>();
            MyIHeap heap5 = new MyHeap();
            PrgState prg5 = new PrgState(stk5, symtbl5, out5, filetbl5, heap5, ex5);
            IRepository repo5 = new Repository("log5.txt");
            repo5.addPrg(prg5);
            ctr5 = new Controller(repo5);
        } catch (MyException e) {
            System.out.println("Example 5 failed typechecking: " + e.getMessage());
        }

        // Example 6: While Statement - int v; v=4; (while (v>0) print(v);v=v-1);print(v)
        IStmt ex6 = new CompStmt(new VarDeclStmt("v", new IntType()),
                new CompStmt(new AssignStmt("v", new ValueExp(new IntValue(4))),
                        new CompStmt(new WhileStmt(
                                new RelationalExp(">", new VarExp("v"), new ValueExp(new IntValue(0))),
                                new CompStmt(new PrintStmt(new VarExp("v")),
                                        new AssignStmt("v", new ArithExp('-', new VarExp("v"), new ValueExp(new IntValue(1)))))),
                                new PrintStmt(new VarExp("v")))));

        try {
            ex6.typecheck(new MyDictionary<>());
            MyIStack<IStmt> stk6 = new MyStack<>();
            MyIDictionary<String, Value> symtbl6 = new MyDictionary<>();
            MyIList<Value> out6 = new MyList<>();
            MyIDictionary<String, java.io.BufferedReader> filetbl6 = new MyDictionary<>();
            MyIHeap heap6 = new MyHeap();
            PrgState prg6 = new PrgState(stk6, symtbl6, out6, filetbl6, heap6, ex6);
            IRepository repo6 = new Repository("log6.txt");
            repo6.addPrg(prg6);
            ctr6 = new Controller(repo6);
        } catch (MyException e) {
            System.out.println("Example 6 failed typechecking: " + e.getMessage());
        }

        // Example 7: Heap Allocation - Ref int v;new(v,20);print(rH(v))
        IStmt ex7 = new CompStmt(new VarDeclStmt("v", new RefType(new IntType())),
                new CompStmt(new NewStmt("v", new ValueExp(new IntValue(20))),
                        new PrintStmt(new ReadHeapExp(new VarExp("v")))));

        try {
            ex7.typecheck(new MyDictionary<>());
            MyIStack<IStmt> stk7 = new MyStack<>();
            MyIDictionary<String, Value> symtbl7 = new MyDictionary<>();
            MyIList<Value> out7 = new MyList<>();
            MyIDictionary<String, java.io.BufferedReader> filetbl7 = new MyDictionary<>();
            MyIHeap heap7 = new MyHeap();
            PrgState prg7 = new PrgState(stk7, symtbl7, out7, filetbl7, heap7, ex7);
            IRepository repo7 = new Repository("log7.txt");
            repo7.addPrg(prg7);
            ctr7 = new Controller(repo7);
        } catch (MyException e) {
            System.out.println("Example 7 failed typechecking: " + e.getMessage());
        }

        // Example 8: Heap Writing - Ref int v;new(v,20);print(rH(v)); wH(v,30);print(rH(v)+5)
        IStmt ex8 = new CompStmt(new VarDeclStmt("v", new RefType(new IntType())),
                new CompStmt(new NewStmt("v", new ValueExp(new IntValue(20))),
                        new CompStmt(new PrintStmt(new ReadHeapExp(new VarExp("v"))),
                                new CompStmt(new WriteHeapStmt("v", new ValueExp(new IntValue(30))),
                                        new PrintStmt(new ArithExp('+', new ReadHeapExp(new VarExp("v")),
                                                new ValueExp(new IntValue(5))))))));

        try {
            ex8.typecheck(new MyDictionary<>());
            MyIStack<IStmt> stk8 = new MyStack<>();
            MyIDictionary<String, Value> symtbl8 = new MyDictionary<>();
            MyIList<Value> out8 = new MyList<>();
            MyIDictionary<String, java.io.BufferedReader> filetbl8 = new MyDictionary<>();
            MyIHeap heap8 = new MyHeap();
            PrgState prg8 = new PrgState(stk8, symtbl8, out8, filetbl8, heap8, ex8);
            IRepository repo8 = new Repository("log8.txt");
            repo8.addPrg(prg8);
            ctr8 = new Controller(repo8);
        } catch (MyException e) {
            System.out.println("Example 8 failed typechecking: " + e.getMessage());
        }

        // Example 9: Nested References - Ref int v;new(v,20);Ref Ref int a; new(a,v);print(v);print(a)
        IStmt ex9 = new CompStmt(new VarDeclStmt("v", new RefType(new IntType())),
                new CompStmt(new NewStmt("v", new ValueExp(new IntValue(20))),
                        new CompStmt(new VarDeclStmt("a", new RefType(new RefType(new IntType()))),
                                new CompStmt(new NewStmt("a", new VarExp("v")),
                                        new CompStmt(new PrintStmt(new VarExp("v")),
                                                new PrintStmt(new VarExp("a")))))));

        try {
            ex9.typecheck(new MyDictionary<>());
            MyIStack<IStmt> stk9 = new MyStack<>();
            MyIDictionary<String, Value> symtbl9 = new MyDictionary<>();
            MyIList<Value> out9 = new MyList<>();
            MyIDictionary<String, java.io.BufferedReader> filetbl9 = new MyDictionary<>();
            MyIHeap heap9 = new MyHeap();
            PrgState prg9 = new PrgState(stk9, symtbl9, out9, filetbl9, heap9, ex9);
            IRepository repo9 = new Repository("log9.txt");
            repo9.addPrg(prg9);
            ctr9 = new Controller(repo9);
        } catch (MyException e) {
            System.out.println("Example 9 failed typechecking: " + e.getMessage());
        }

        // Example 10: Heap Reading Nested - Ref int v;new(v,20);Ref Ref int a; new(a,v);print(rH(v));print(rH(rH(a))+5)
        IStmt ex10 = new CompStmt(new VarDeclStmt("v", new RefType(new IntType())),
                new CompStmt(new NewStmt("v", new ValueExp(new IntValue(20))),
                        new CompStmt(new VarDeclStmt("a", new RefType(new RefType(new IntType()))),
                                new CompStmt(new NewStmt("a", new VarExp("v")),
                                        new CompStmt(new PrintStmt(new ReadHeapExp(new VarExp("v"))),
                                                new PrintStmt(new ArithExp('+',
                                                        new ReadHeapExp(new ReadHeapExp(new VarExp("a"))),
                                                        new ValueExp(new IntValue(5)))))))));

        try {
            ex10.typecheck(new MyDictionary<>());
            MyIStack<IStmt> stk10 = new MyStack<>();
            MyIDictionary<String, Value> symtbl10 = new MyDictionary<>();
            MyIList<Value> out10 = new MyList<>();
            MyIDictionary<String, java.io.BufferedReader> filetbl10 = new MyDictionary<>();
            MyIHeap heap10 = new MyHeap();
            PrgState prg10 = new PrgState(stk10, symtbl10, out10, filetbl10, heap10, ex10);
            IRepository repo10 = new Repository("log10.txt");
            repo10.addPrg(prg10);
            ctr10 = new Controller(repo10);
        } catch (MyException e) {
            System.out.println("Example 10 failed typechecking: " + e.getMessage());
        }

        // Example 11: Garbage Collector Test - Ref int v;new(v,20);Ref Ref int a; new(a,v); new(v,30);print(rH(rH(a)))
        IStmt ex11 = new CompStmt(new VarDeclStmt("v", new RefType(new IntType())),
                new CompStmt(new NewStmt("v", new ValueExp(new IntValue(20))),
                        new CompStmt(new VarDeclStmt("a", new RefType(new RefType(new IntType()))),
                                new CompStmt(new NewStmt("a", new VarExp("v")),
                                        new CompStmt(new NewStmt("v", new ValueExp(new IntValue(30))),
                                                new PrintStmt(new ReadHeapExp(new ReadHeapExp(new VarExp("a")))))))));

        try {
            ex11.typecheck(new MyDictionary<>());
            MyIStack<IStmt> stk11 = new MyStack<>();
            MyIDictionary<String, Value> symtbl11 = new MyDictionary<>();
            MyIList<Value> out11 = new MyList<>();
            MyIDictionary<String, java.io.BufferedReader> filetbl11 = new MyDictionary<>();
            MyIHeap heap11 = new MyHeap();
            PrgState prg11 = new PrgState(stk11, symtbl11, out11, filetbl11, heap11, ex11);
            IRepository repo11 = new Repository("log11.txt");
            repo11.addPrg(prg11);
            ctr11 = new Controller(repo11);
        } catch (MyException e) {
            System.out.println("Example 11 failed typechecking: " + e.getMessage());
        }

        // Example 12: Fork Statement - int v; Ref int a; v=10;new(a,22);fork(wH(a,30);v=32;print(v);print(rH(a)));print(v);print(rH(a))
        IStmt ex12 = new CompStmt(new VarDeclStmt("v", new IntType()),
                new CompStmt(new VarDeclStmt("a", new RefType(new IntType())),
                        new CompStmt(new AssignStmt("v", new ValueExp(new IntValue(10))),
                                new CompStmt(new NewStmt("a", new ValueExp(new IntValue(22))),
                                        new CompStmt(
                                                new ForkStmt(
                                                        new CompStmt(new WriteHeapStmt("a", new ValueExp(new IntValue(30))),
                                                                new CompStmt(new AssignStmt("v", new ValueExp(new IntValue(32))),
                                                                        new CompStmt(new PrintStmt(new VarExp("v")),
                                                                                new PrintStmt(new ReadHeapExp(new VarExp("a"))))))),
                                                new CompStmt(new PrintStmt(new VarExp("v")),
                                                        new PrintStmt(new ReadHeapExp(new VarExp("a")))))))));

        try {
            ex12.typecheck(new MyDictionary<>());
            MyIStack<IStmt> stk12 = new MyStack<>();
            MyIDictionary<String, Value> symtbl12 = new MyDictionary<>();
            MyIList<Value> out12 = new MyList<>();
            MyIDictionary<String, java.io.BufferedReader> filetbl12 = new MyDictionary<>();
            MyIHeap heap12 = new MyHeap();
            PrgState prg12 = new PrgState(stk12, symtbl12, out12, filetbl12, heap12, ex12);
            IRepository repo12 = new Repository("log12.txt");
            repo12.addPrg(prg12);
            ctr12 = new Controller(repo12);
        } catch (MyException e) {
            System.out.println("Example 12 failed typechecking: " + e.getMessage());
        }

        // Example 13: TYPECHECKER TEST (should fail) - int v; v = true;
        // This example assigns a boolean value to an integer variable, which should fail typechecking
        IStmt ex13 = new CompStmt(new VarDeclStmt("v", new IntType()),
                new AssignStmt("v", new ValueExp(new BoolValue(true))));

        try {
            ex13.typecheck(new MyDictionary<>());
            MyIStack<IStmt> stk13 = new MyStack<>();
            MyIDictionary<String, Value> symtbl13 = new MyDictionary<>();
            MyIList<Value> out13 = new MyList<>();
            MyIDictionary<String, java.io.BufferedReader> filetbl13 = new MyDictionary<>();
            MyIHeap heap13 = new MyHeap();
            PrgState prg13 = new PrgState(stk13, symtbl13, out13, filetbl13, heap13, ex13);
            IRepository repo13 = new Repository("log13.txt");
            repo13.addPrg(prg13);
            ctr13 = new Controller(repo13);
        } catch (MyException e) {
            System.out.println("Example 13 failed typechecking: " + e.getMessage());
        }

        TextMenu menu = new TextMenu();
        menu.addCommand(new ExitCommand("0", "exit"));
        if (ctr1 != null) menu.addCommand(new RunExample("1", ex1.toString(), ctr1));
        if (ctr2 != null) menu.addCommand(new RunExample("2", ex2.toString(), ctr2));
        if (ctr3 != null) menu.addCommand(new RunExample("3", ex3.toString(), ctr3));
        if (ctr4 != null) menu.addCommand(new RunExample("4", ex4.toString(), ctr4));
        if (ctr5 != null) menu.addCommand(new RunExample("5", ex5.toString(), ctr5));
        if (ctr6 != null) menu.addCommand(new RunExample("6", ex6.toString(), ctr6));
        if (ctr7 != null) menu.addCommand(new RunExample("7", ex7.toString(), ctr7));
        if (ctr8 != null) menu.addCommand(new RunExample("8", ex8.toString(), ctr8));
        if (ctr9 != null) menu.addCommand(new RunExample("9", ex9.toString(), ctr9));
        if (ctr10 != null) menu.addCommand(new RunExample("10", ex10.toString(), ctr10));
        if (ctr11 != null) menu.addCommand(new RunExample("11", ex11.toString(), ctr11));
        if (ctr12 != null) menu.addCommand(new RunExample("12", ex12.toString(), ctr12));
        if (ctr13 != null) menu.addCommand(new RunExample("13", ex13.toString(), ctr13));
        menu.show();
        // javac -d out src/**/*.java
        // java -cp out view.Interpreter
    }
}
