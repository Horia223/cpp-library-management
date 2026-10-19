#pragma once
#include <QWidget>
#include <QListWidget>
#include <QPushButton>
#include <QLabel>
#include <QVBoxLayout>
#include <QInputDialog>
#include <QMessageBox>
#include "CarteService.h"

class CosGUI : public QWidget, public Observer {
private:
    CarteService& srv;
    QListWidget* lstCos;
    QPushButton* btnGenereaza;
    QPushButton* btnGoleste;
    QPushButton* btnExport; 
    QLabel* lblDimensiune;

    void initGUI() {
        QVBoxLayout* layout = new QVBoxLayout;
        this->setLayout(layout);
        this->setWindowTitle("Fereastra Coș");
        this->resize(400, 300);

        lstCos = new QListWidget;
        layout->addWidget(lstCos);

        lblDimensiune = new QLabel("Numar carti in cos: 0");
        layout->addWidget(lblDimensiune);

        btnGenereaza = new QPushButton("Genereaza 3 Random");
        btnGoleste = new QPushButton("Goleste Cos");
        btnExport = new QPushButton("Export CSV");

        layout->addWidget(btnGenereaza);
        layout->addWidget(btnGoleste);
        layout->addWidget(btnExport);
    }

    void reloadCos() {
        lstCos->clear();
        for (const auto& c : srv.getAllCosService()) {
            lstCos->addItem(QString::fromStdString(c.getTitlu() + " - " + c.getAutor()));
        }
        lblDimensiune->setText("Numar carti in cos: " + QString::number(srv.dimensiuneCos()));
    }

    void connectSignals() {
        QObject::connect(btnGenereaza, &QPushButton::clicked, [&]() {
            srv.cosGenereaza(3);
            reloadCos();
            });

        QObject::connect(btnGoleste, &QPushButton::clicked, [&]() {
            srv.golesteCosService();
            reloadCos();
            });

        // Semnal pentru Export CSV
        QObject::connect(btnExport, &QPushButton::clicked, [&]() {
            // Cerem utilizatorului numele fisierului printr-un pop-up simplu
            QString numeFisier = QInputDialog::getText(this, "Export", "Introdu numele fisierului (fara extensie):");
            if (!numeFisier.isEmpty()) {
                try {
                    srv.exportCosCsvService(numeFisier.toStdString());
                    QMessageBox::information(this, "Succes", "Cosul a fost exportat in " + numeFisier + ".csv!");
                }
                catch (const RepoException& e) {
                    QMessageBox::warning(this, "Eroare", QString::fromStdString(e.getMesaj()));
                }
            }
            });
    }

public:
    CosGUI(CarteService& srv) : srv{ srv } {
        initGUI();
        connectSignals();
        reloadCos();
        srv.addObserverToCos(this);  
    }

    ~CosGUI() {
        srv.removeObserverFromCos(this);  
    }

    void update() override { 
        reloadCos();
    }
};