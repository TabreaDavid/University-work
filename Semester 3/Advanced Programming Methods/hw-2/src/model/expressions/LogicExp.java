package model.expressions;

import exceptions.MyException;
import model.adt.MyIDictionary;
import model.types.BoolType;
import model.values.BoolValue;
import model.values.Value;

public class LogicExp implements Exp {
    private final Exp e1;
    private final Exp e2;
    private final int op; // 1-and, 2-or

    public LogicExp(String op, Exp e1, Exp e2) {
        this.e1 = e1;
        this.e2 = e2;
        if (op.equals("and")) this.op = 1;
        else if (op.equals("or")) this.op = 2;
        else this.op = 0;
    }

    @Override
    public Value eval(MyIDictionary<String, Value> tbl) throws MyException {
        Value v1, v2;
        v1 = e1.eval(tbl);
        if (v1.getType().equals(new BoolType())) {
            v2 = e2.eval(tbl);
            if (v2.getType().equals(new BoolType())) {
                BoolValue b1 = (BoolValue) v1;
                BoolValue b2 = (BoolValue) v2;
                boolean n1, n2;
                n1 = b1.getVal();
                n2 = b2.getVal();
                if (op == 1) return new BoolValue(n1 && n2);
                if (op == 2) return new BoolValue(n1 || n2);
            } else {
                throw new MyException("second operand is not a boolean");
            }
        } else {
            throw new MyException("first operand is not a boolean");
        }
        return null; // Should not be reached
    }
    
    @Override
    public String toString() {
        String operation = (op == 1) ? "and" : "or";
        return e1.toString() + " " + operation + " " + e2.toString();
    }
}
