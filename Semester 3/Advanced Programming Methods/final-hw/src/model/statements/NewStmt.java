package model.statements;

import exceptions.MyException;
import model.PrgState;
import model.adt.MyIDictionary;
import model.adt.MyIHeap;
import model.expressions.Exp;
import model.types.RefType;
import model.types.Type;
import model.values.RefValue;
import model.values.Value;

public class NewStmt implements IStmt {
    private final String varName;
    private final Exp expression;

    public NewStmt(String varName, Exp expression) {
        this.varName = varName;
        this.expression = expression;
    }

    @Override
    public PrgState execute(PrgState state) throws MyException {
        MyIDictionary<String, Value> symTable = state.getSymTable();
        MyIHeap heap = state.getHeap();
        
        // Check if var_name is defined in SymTable
        if (!symTable.isDefined(varName)) {
            throw new MyException("variable " + varName + " is not defined");
        }
        
        Value varValue = symTable.lookup(varName);
        
        // Check if var_name has RefType
        if (!(varValue.getType() instanceof RefType)) {
            throw new MyException("variable " + varName + " is not a RefType");
        }
        
        // Evaluate the expression
        Value expValue = expression.eval(symTable, heap);
        
        // Get the locationType from the RefType
        RefType refType = (RefType) varValue.getType();
        
        // Check if expression type matches locationType
        if (!expValue.getType().equals(refType.getInner())) {
            throw new MyException("expression type does not match the locationType of " + varName);
        }
        
        // Allocate in heap and get new address
        int newAddress = heap.allocate(expValue);
        
        // Update SymTable with new RefValue
        symTable.update(varName, new RefValue(newAddress, refType.getInner()));
        
        return null;
    }

    @Override
    public MyIDictionary<String, Type> typecheck(MyIDictionary<String, Type> typeEnv) throws MyException {
        Type typevar = typeEnv.lookup(varName);
        Type typexp = expression.typecheck(typeEnv);
        if (typevar.equals(new RefType(typexp))) {
            return typeEnv;
        } else {
            throw new MyException("NEW stmt: right hand side and left hand side have different types");
        }
    }

    @Override
    public String toString() {
        return "new(" + varName + "," + expression.toString() + ")";
    }
}
