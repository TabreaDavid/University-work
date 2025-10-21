package model.statements;

import exceptions.MyException;
import model.PrgState;
import model.adt.MyIDictionary;
import model.adt.MyIList;
import model.expressions.Exp;
import model.values.Value;

public class PrintStmt implements IStmt {
    private final Exp exp;

    public PrintStmt(Exp exp) {
        this.exp = exp;
    }

    @Override
    public String toString() {
        return "print(" + exp.toString() + ")";
    }

    @Override
    public PrgState execute(PrgState state) throws MyException {
        MyIList<Value> out = state.getOut();
        MyIDictionary<String, Value> symTbl = state.getSymTable();
        out.add(exp.eval(symTbl));
        return state;
    }
}
