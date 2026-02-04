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

public class WriteHeapStmt implements IStmt {
    private final String varName;
    private final Exp expression;

    public WriteHeapStmt(String varName, Exp expression) {
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
        
        RefValue refValue = (RefValue) varValue;
        int address = refValue.getAddr();
        
        // Check if address is defined in heap
        if (!heap.isDefined(address)) {
            throw new MyException("address " + address + " is not defined in heap");
        }
        
        // Evaluate the expression
        Value expValue = expression.eval(symTable, heap);
        
        // Check if expression type matches locationType
        if (!expValue.getType().equals(refValue.getLocationType())) {
            throw new MyException("expression type does not match the locationType of " + varName);
        }
        
        // Update heap at the address
        heap.update(address, expValue);
        
        return null;
    }

    @Override
    public MyIDictionary<String, Type> typecheck(MyIDictionary<String, Type> typeEnv) throws MyException {
        Type typevar = typeEnv.lookup(varName);
        Type typexp = expression.typecheck(typeEnv);
        if (typevar instanceof RefType) {
            RefType refType = (RefType) typevar;
            if (refType.getInner().equals(typexp)) {
                return typeEnv;
            } else {
                throw new MyException("WriteHeap: right hand side and left hand side have different types");
            }
        } else {
            throw new MyException("WriteHeap: variable is not a RefType");
        }
    }

    @Override
    public String toString() {
        return "wH(" + varName + "," + expression.toString() + ")";
    }
}
