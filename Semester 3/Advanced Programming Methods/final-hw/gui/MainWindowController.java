package gui;

import controller.Controller;
import exceptions.MyException;
import javafx.beans.property.SimpleIntegerProperty;
import javafx.beans.property.SimpleStringProperty;
import javafx.collections.FXCollections;
import javafx.fxml.FXML;
import javafx.scene.control.*;
import model.PrgState;
import model.statements.IStmt;
import model.values.Value;

import java.util.ArrayList;
import java.util.List;
import java.util.Map;

public class MainWindowController {
    
    @FXML private TextField nrPrgStatesTextField;
    @FXML private TableView<Map.Entry<Integer, Value>> heapTableView;
    @FXML private TableColumn<Map.Entry<Integer, Value>, Integer> heapAddressColumn;
    @FXML private TableColumn<Map.Entry<Integer, Value>, String> heapValueColumn;
    @FXML private ListView<String> outListView;
    @FXML private ListView<String> fileTableListView;
    @FXML private ListView<Integer> prgStateListView;
    @FXML private TableView<Map.Entry<String, Value>> symTableView;
    @FXML private TableColumn<Map.Entry<String, Value>, String> symVarNameColumn;
    @FXML private TableColumn<Map.Entry<String, Value>, String> symValueColumn;
    @FXML private ListView<String> exeStackListView;
    
    private Controller controller;
    private PrgState initialPrgState;
    
    @FXML
    public void initialize() {
        heapAddressColumn.setCellValueFactory(p -> 
            new SimpleIntegerProperty(p.getValue().getKey()).asObject());
        heapValueColumn.setCellValueFactory(p -> 
            new SimpleStringProperty(p.getValue().getValue().toString()));
        symVarNameColumn.setCellValueFactory(p -> 
            new SimpleStringProperty(p.getValue().getKey()));
        symValueColumn.setCellValueFactory(p -> 
            new SimpleStringProperty(p.getValue().getValue().toString()));
        
        prgStateListView.getSelectionModel().selectedItemProperty().addListener(
            (obs, oldVal, newVal) -> { if (newVal != null) updatePrgStateDetails(newVal); }
        );
    }
    
    public void setController(Controller controller) {
        this.controller = controller;
        this.initialPrgState = controller.getRepository().getPrgList().get(0);
        populateAll();
    }
    
    private void populateAll() {
        List<PrgState> prgList = controller.getRepository().getPrgList();
        
        nrPrgStatesTextField.setText(String.valueOf(prgList.size()));
        
        heapTableView.getItems().clear();
        heapTableView.setItems(FXCollections.observableArrayList(
            new ArrayList<>(initialPrgState.getHeap().getContent().entrySet())));
        heapTableView.refresh();
        
        List<String> outList = new ArrayList<>();
        for (Value v : initialPrgState.getOut().getList()) {
            outList.add(v.toString());
        }
        outListView.setItems(FXCollections.observableArrayList(outList));
        
        fileTableListView.setItems(FXCollections.observableArrayList(
            new ArrayList<>(initialPrgState.getFileTable().getContent().keySet())));
        
        List<Integer> prgIds = new ArrayList<>();
        for (PrgState prg : prgList) {
            prgIds.add(prg.getId());
        }
        prgStateListView.setItems(FXCollections.observableArrayList(prgIds));
        
        if (!prgIds.isEmpty()) {
            prgStateListView.getSelectionModel().selectFirst();
        } else {
            symTableView.setItems(FXCollections.observableArrayList());
            exeStackListView.setItems(FXCollections.observableArrayList());
        }
    }
    
    private void updatePrgStateDetails(int prgStateId) {
        PrgState selectedPrg = null;
        for (PrgState prg : controller.getRepository().getPrgList()) {
            if (prg.getId() == prgStateId) {
                selectedPrg = prg;
                break;
            }
        }
        
        if (selectedPrg == null) {
            symTableView.setItems(FXCollections.observableArrayList());
            exeStackListView.setItems(FXCollections.observableArrayList());
            return;
        }
        
        symTableView.getItems().clear();
        symTableView.setItems(FXCollections.observableArrayList(
            new ArrayList<>(selectedPrg.getSymTable().getContent().entrySet())));
        symTableView.refresh();
        
        List<String> exeStackList = new ArrayList<>();
        for (IStmt stmt : selectedPrg.getStk().getReversed()) {
            exeStackList.add(stmt.toString());
        }
        exeStackListView.setItems(FXCollections.observableArrayList(exeStackList));
    }
    
    @FXML
    private void handleRunOneStep() {
        if (controller.getRepository().getPrgList().isEmpty()) {
            Alert alert = new Alert(Alert.AlertType.INFORMATION);
            alert.setTitle("Finished");
            alert.setContentText("Program execution completed.");
            alert.showAndWait();
            return;
        }
        
        try {
            controller.oneStepForAllPrg(controller.getRepository().getPrgList());
            populateAll();
        } catch (MyException | InterruptedException e) {
            Alert alert = new Alert(Alert.AlertType.ERROR);
            alert.setTitle("Error");
            alert.setContentText(e.getMessage());
            alert.showAndWait();
        }
    }
}
