package model.statements;

import exceptions.MyException;
import model.PrgState;
import model.adt.MyIDictionary;
import model.types.Type;
import model.values.Value;

public class VarDeclStmt implements IStmt {
    private final String name;
    private final Type typ;

    public VarDeclStmt(String name, Type typ) {
        this.name = name;
        this.typ = typ;
    }

    @Override
    public PrgState execute(PrgState state) throws MyException {
        MyIDictionary<String, Value> symTbl = state.getSymTable();
        if (symTbl.isDefined(name)) {
            throw new MyException("Variable " + name + " is already declared.");
        } else {
            symTbl.put(name, typ.defaultValue());
        }
        return state;
    }

    @Override
    public String toString() {
        return typ.toString() + " " + name;
    }
}
