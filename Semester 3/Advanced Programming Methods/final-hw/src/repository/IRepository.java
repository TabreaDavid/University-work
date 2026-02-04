package repository;

import exceptions.MyException;
import model.PrgState;
import java.util.List;

public interface IRepository {
    void addPrg(PrgState prg);
    
    void logPrgStateExec(PrgState prg) throws MyException;
    
    List<PrgState> getPrgList();
    
    void setPrgList(List<PrgState> prgList);
}
