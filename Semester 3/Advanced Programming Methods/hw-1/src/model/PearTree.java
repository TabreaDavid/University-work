package model;

public class PearTree implements FruitTree {
    private int age;
    private String name;

    public PearTree(int age, String name) {
        this.age = age;
        this.name = name;
    }

    public int getAge() {
        return age;
    }

    public String getType() {
        return "Pear tree";
    }

    public String getName() {
        return name;
    }

    public boolean isOlderThan(int age) {
        return this.age > age;
    }

    public String toString() {
        String treeType = getType();
        return "Type: " + treeType + "; Name: " + this.name + "; Age: " + this.age;
    }
}
