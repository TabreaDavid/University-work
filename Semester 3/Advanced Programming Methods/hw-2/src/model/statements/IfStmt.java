package model.statements;

import exceptions.MyException;
import model.PrgState;
import model.adt.MyIDictionary;
import model.adt.MyIStack;
import model.expressions.Exp;
import model.types.BoolType;
import model.values.BoolValue;
import model.values.Value;

public class IfStmt implements IStmt {
    private final Exp exp;
    private final IStmt thenS;
    private final IStmt elseS;

    public IfStmt(Exp e, IStmt t, IStmt el) {
        exp = e;
        thenS = t;
        elseS = el;
    }

    @Override
    public String toString() {
        return "(IF(" + exp.toString() + ") THEN(" + thenS.toString() + ")ELSE(" + elseS.toString() + "))";
    }

    @Override
    public PrgState execute(PrgState state) throws MyException {
        MyIDictionary<String, Value> symTbl = state.getSymTable();
        Value cond = exp.eval(symTbl);

        if (!cond.getType().equals(new BoolType())) {
            throw new MyException("conditional expr is not a boolean");
        }

        MyIStack<IStmt> stk = state.getStk();
        if (((BoolValue) cond).getVal()) {
            stk.push(thenS);
        } else {
            stk.push(elseS);
        }
        return state;
    }
}
