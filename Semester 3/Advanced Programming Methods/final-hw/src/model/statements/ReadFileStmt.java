package model.statements;

import exceptions.MyException;
import model.PrgState;
import model.adt.MyIDictionary;
import model.expressions.Exp;
import model.types.IntType;
import model.types.StringType;
import model.types.Type;
import model.values.IntValue;
import model.values.StringValue;
import model.values.Value;

import java.io.BufferedReader;
import java.io.IOException;

public class ReadFileStmt implements IStmt {
    private final Exp exp;
    private final String varName;

    public ReadFileStmt(Exp exp, String varName) {
        this.exp = exp;
        this.varName = varName;
    }

    @Override
    public PrgState execute(PrgState state) throws MyException {
        MyIDictionary<String, Value> symTable = state.getSymTable();
        MyIDictionary<String, BufferedReader> fileTable = state.getFileTable();
        
        if (!symTable.isDefined(varName)) {
            throw new MyException("ReadFile: variable " + varName + " is not defined");
        }
        
        Value varVal = symTable.lookup(varName);
        if (!varVal.getType().equals(new IntType())) {
            throw new MyException("ReadFile: variable " + varName + " is not an integer");
        }
        
        Value val = exp.eval(symTable, state.getHeap());
        if (!val.getType().equals(new StringType())) {
            throw new MyException("ReadFile: expression is not a string");
        }
        
        StringValue strVal = (StringValue) val;
        String filename = strVal.getVal();
        
        if (!fileTable.isDefined(filename)) {
            throw new MyException("ReadFile: file " + filename + " is not opened");
        }
        
        BufferedReader br = fileTable.lookup(filename);
        try {
            String line = br.readLine();
            IntValue intVal;
            if (line == null) {
                intVal = new IntValue(0);
            } else {
                intVal = new IntValue(Integer.parseInt(line));
            }
            symTable.update(varName, intVal);
        } catch (IOException e) {
            throw new MyException("ReadFile: could not read from file " + filename);
        }
        
        return null;
    }

    @Override
    public MyIDictionary<String, Type> typecheck(MyIDictionary<String, Type> typeEnv) throws MyException {
        Type typexp = exp.typecheck(typeEnv);
        if (!typexp.equals(new StringType())) {
            throw new MyException("ReadFile: expression is not a string type");
        }
        Type typevar = typeEnv.lookup(varName);
        if (!typevar.equals(new IntType())) {
            throw new MyException("ReadFile: variable is not an integer type");
        }
        return typeEnv;
    }

    @Override
    public String toString() {
        return "readFile(" + exp.toString() + ", " + varName + ")";
    }
}
