package model.values;

import model.types.StringType;
import model.types.Type;

public class StringValue implements Value {
    private final String val;

    public StringValue(String v) {
        this.val = v;
    }

    public String getVal() {
        return val;
    }

    @Override
    public String toString() {
        return val;
    }

    @Override
    public Type getType() {
        return new StringType();
    }

    @Override
    public boolean equals(Object another) {
        return another instanceof StringValue && ((StringValue) another).getVal().equals(this.val);
    }
}
