#pragma once
#include <QWidget>
#include <QListWidget>
#include <QPushButton>
#include <QLineEdit>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QFormLayout>
#include <QMessageBox>
#include <QInputDialog>
#include "CarteService.h"
#include "CarteTableModel.h"
#include <QTableView>
#include <QHeaderView>

class MainWindow : public QWidget {
private:
    CarteService& srv;

    // Elemente stanga (lista + butoane actiuni directe pe carte)
    QTableView* lst;
    CarteTableModel* tableModel;
    QPushButton* btnDelete;
    QPushButton* btnUpdate;
    QPushButton* btnCosAdauga; 

    // Elemente dreapta (formular +adaugare +undo)
    QLineEdit* txtTitlu;
    QLineEdit* txtAutor;
    QLineEdit* txtGen;
    QLineEdit* txtAn;
    QPushButton* btnAdd;
    QPushButton* btnUndo;

    // Butoane Sortare
    QPushButton* btnSortTitlu;
    QPushButton* btnSortAutor;
    QPushButton* btnSortAnGen;

    // Butoane Filtrare
    QPushButton* btnFiltruTitlu;
    QPushButton* btnFiltruAn;
    QPushButton* btnReset; // Reseteaza lista la forma initiala

    // Buton deschidere fereastra Cos
    QPushButton* btnCosOpen;

    // Zona Butoane Dinamice (Statistici / DTO)
    QWidget* panelButoaneDinamice;
    QVBoxLayout* layoutButoaneDinamice;


    //QPushButton* btnOpenCRUD;
    QPushButton* btnOpenReadOnly;

    // Functii interne
    void initGUI();
    void connectSignals();
    void reloadList(const std::vector<Carte>& carti);
    void incarcaButoaneDinamice();

public:
    MainWindow(CarteService& srv);
};