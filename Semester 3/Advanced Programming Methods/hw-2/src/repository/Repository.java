package repository;

import model.PrgState;
import java.util.ArrayList;
import java.util.List;

public class Repository implements IRepository {
    private final List<PrgState> prgList;

    public Repository() {
        this.prgList = new ArrayList<>();
    }

    @Override
    public PrgState getCrtPrg() {
        return prgList.get(0);
    }

    @Override
    public void addPrg(PrgState prg) {
        prgList.add(prg);
    }
}
