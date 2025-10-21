package model.expressions;

import exceptions.MyException;
import model.adt.MyIDictionary;
import model.values.Value;

public class ValueExp implements Exp {
    private final Value e;

    public ValueExp(Value e) {
        this.e = e;
    }

    @Override
    public Value eval(MyIDictionary<String, Value> tbl) throws MyException {
        return e;
    }
    
    @Override
    public String toString() {
        return e.toString();
    }
}
