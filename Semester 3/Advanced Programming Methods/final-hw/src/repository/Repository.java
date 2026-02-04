package repository;
//stores program state objects
import exceptions.MyException;
import model.PrgState;
import java.io.BufferedWriter;
import java.io.FileWriter;
import java.io.IOException;
import java.io.PrintWriter;
import java.util.ArrayList;
import java.util.List;

public class Repository implements IRepository {
    private List<PrgState> prgList;
    private String logFilePath;

    public Repository(String logFilePath) {
        this.prgList = new ArrayList<>();
        this.logFilePath = logFilePath;
    }

    public Repository() {
        this.prgList = new ArrayList<>();
        this.logFilePath = null;
    }

    @Override
    public void addPrg(PrgState prg) {
        prgList.add(prg);
    }

    @Override
    public List<PrgState> getPrgList() {
        return prgList;
    }

    @Override
    public void setPrgList(List<PrgState> prgList) {
        this.prgList = prgList;
    }

    @Override
    public void logPrgStateExec(PrgState prg) throws MyException {
        if (logFilePath == null) {
            return;
        }
        
        try (PrintWriter logFile = new PrintWriter(new BufferedWriter(new FileWriter(logFilePath, true)))) {
            logFile.println(prg.toString());
            logFile.println("========================================");
        } catch (IOException e) {
            throw new MyException("Could not write to log file: " + e.getMessage());
        }
    }
}
