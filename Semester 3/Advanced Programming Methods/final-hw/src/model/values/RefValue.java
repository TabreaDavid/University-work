package model.values;

import model.types.RefType;
import model.types.Type;

public class RefValue implements Value {
    private int address;
    private Type locationType;

    public RefValue(int address, Type locationType) {
        this.address = address;
        this.locationType = locationType;
    }

    public int getAddr() {
        return address;
    }

    public Type getLocationType() {
        return locationType;
    }

    @Override
    public Type getType() {
        return new RefType(locationType);
    }

    @Override
    public String toString() {
        return "(" + address + "," + locationType.toString() + ")";
    }

    @Override
    public boolean equals(Object another) {
        if (another instanceof RefValue) {
            RefValue other = (RefValue) another;
            return address == other.address && locationType.equals(other.locationType);
        }
        return false;
    }
}
