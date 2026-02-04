package model.statements;

import exceptions.MyException;
import model.PrgState;
import model.adt.MyIDictionary;
import model.adt.MyIHeap;
import model.adt.MyIStack;
import model.expressions.Exp;
import model.types.BoolType;
import model.types.Type;
import model.values.BoolValue;
import model.values.Value;

public class WhileStmt implements IStmt {
    private final Exp expression;
    private final IStmt statement;

    public WhileStmt(Exp expression, IStmt statement) {
        this.expression = expression;
        this.statement = statement;
    }

    @Override
    public PrgState execute(PrgState state) throws MyException {
        MyIDictionary<String, Value> symTable = state.getSymTable();
        MyIHeap heap = state.getHeap();
        MyIStack<IStmt> stack = state.getStk();
        
        Value value = expression.eval(symTable, heap);
        
        if (!value.getType().equals(new BoolType())) {
            throw new MyException("condition expression is not a boolean");
        }
        
        BoolValue boolValue = (BoolValue) value;
        
        if (boolValue.getVal()) {
            // If condition is true, push the while statement back and then the body
            stack.push(this);
            stack.push(statement);
        }
        // If condition is false, do nothing (while ends)
        
        return null;
    }

    @Override
    public MyIDictionary<String, Type> typecheck(MyIDictionary<String, Type> typeEnv) throws MyException {
        Type typexp = expression.typecheck(typeEnv);
        if (typexp.equals(new BoolType())) {
            statement.typecheck(typeEnv.clone());
            return typeEnv;
        } else {
            throw new MyException("The condition of WHILE has not the type bool");
        }
    }

    @Override
    public String toString() {
        return "while(" + expression.toString() + ") " + statement.toString();
    }
}
