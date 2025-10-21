package model.expressions;

import exceptions.MyException;
import model.adt.MyIDictionary;
import model.values.Value;

public interface Exp {
    Value eval(MyIDictionary<String, Value> tbl) throws MyException;
}
