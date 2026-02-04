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
import java.io.IOException;

public class CloseRFileStmt implements IStmt {
    private final Exp exp;

    public CloseRFileStmt(Exp exp) {
        this.exp = exp;
    }

    @Override
    public PrgState execute(PrgState state) throws MyException {
        MyIDictionary<String, Value> symTable = state.getSymTable();
        MyIDictionary<String, BufferedReader> fileTable = state.getFileTable();
        
        Value val = exp.eval(symTable, state.getHeap());
        if (!val.getType().equals(new StringType())) {
            throw new MyException("CloseRFile: expression is not a string");
        }
        
        StringValue strVal = (StringValue) val;
        String filename = strVal.getVal();
        
        if (!fileTable.isDefined(filename)) {
            throw new MyException("CloseRFile: file " + filename + " is not opened");
        }
        
        BufferedReader br = fileTable.lookup(filename);
        try {
            br.close();
        } catch (IOException e) {
            throw new MyException("CloseRFile: could not close file " + filename);
        }
        
        fileTable.getContent().remove(filename);
        
        return null;
    }

    @Override
    public MyIDictionary<String, Type> typecheck(MyIDictionary<String, Type> typeEnv) throws MyException {
        Type typexp = exp.typecheck(typeEnv);
        if (typexp.equals(new StringType())) {
            return typeEnv;
        } else {
            throw new MyException("CloseRFile: expression is not a string type");
        }
    }

    @Override
    public String toString() {
        return "closeRFile(" + exp.toString() + ")";
    }
}
