package model.statements;

import exceptions.MyException;
import model.PrgState;
import model.adt.MyIDictionary;
import model.expressions.Exp;
import model.types.StringType;
import model.types.Type;
import model.values.StringValue;
import model.values.Value;

import java.io.BufferedReader;
import java.io.FileReader;
import java.io.IOException;

public class OpenRFileStmt implements IStmt {
    private final Exp exp;

    public OpenRFileStmt(Exp exp) {
        this.exp = exp;
    }

    @Override
    public PrgState execute(PrgState state) throws MyException {
        MyIDictionary<String, Value> symTable = state.getSymTable();
        MyIDictionary<String, BufferedReader> fileTable = state.getFileTable();
        
        Value val = exp.eval(symTable, state.getHeap());
        if (!val.getType().equals(new StringType())) {
            throw new MyException("OpenRFile: expression is not a string");
        }
        
        StringValue strVal = (StringValue) val;
        String filename = strVal.getVal();
        
        if (fileTable.isDefined(filename)) {
            throw new MyException("OpenRFile: file is already opened");
        }
        
        try {
            BufferedReader br = new BufferedReader(new FileReader(filename));
            fileTable.put(filename, br);
        } catch (IOException e) {
            throw new MyException("OpenRFile: could not open file " + filename);
        }
        
        return null;
    }

    @Override
    public MyIDictionary<String, Type> typecheck(MyIDictionary<String, Type> typeEnv) throws MyException {
        Type typexp = exp.typecheck(typeEnv);
        if (typexp.equals(new StringType())) {
            return typeEnv;
        } else {
            throw new MyException("OpenRFile: expression is not a string type");
        }
    }

    @Override
    public String toString() {
        return "openRFile(" + exp.toString() + ")";
    }
}
