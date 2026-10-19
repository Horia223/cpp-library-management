#include "mainwindow.h"
#include "CosGUI.h"
#include "CosReadOnlyGUI.h"
//#include <Windows.h>
MainWindow::MainWindow(CarteService& srv) : srv{ srv } {
    initGUI();
    connectSignals();
    reloadList(srv.getAll());
}

void MainWindow::initGUI() {
    this->setWindowTitle("Gestiune Biblioteca");
    this->resize(800, 500);

    QHBoxLayout* mainLayout = new QHBoxLayout;
    this->setLayout(mainLayout);

    //Partea din stanga
    QWidget* leftWidget = new QWidget;
    QVBoxLayout* leftLayout = new QVBoxLayout;
    leftWidget->setLayout(leftLayout);

    lst = new QTableView;
    tableModel = new CarteTableModel(&srv.getAll(), this);
    lst->setModel(tableModel);
    lst->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    leftLayout->addWidget(lst);
    leftLayout->addWidget(lst);

    // butoane cu actiuni pentru cartea selectata
    QHBoxLayout* layoutActiuniLista = new QHBoxLayout;
    btnDelete = new QPushButton("Sterge");
    btnUpdate = new QPushButton("Modifica");
    btnCosAdauga = new QPushButton("Pune in Cos");

    layoutActiuniLista->addWidget(btnDelete);
    layoutActiuniLista->addWidget(btnUpdate);
    layoutActiuniLista->addWidget(btnCosAdauga);
    leftLayout->addLayout(layoutActiuniLista);

    mainLayout->addWidget(leftWidget);


    // partea din dreapta
    QWidget* rightWidget = new QWidget;
    QVBoxLayout* rightLayout = new QVBoxLayout;
    rightWidget->setLayout(rightLayout);

    //Undo
    btnUndo = new QPushButton("Undo (Anulare)");
    rightLayout->addWidget(btnUndo);

    //form adaugare afisare
    QFormLayout* formLayout = new QFormLayout;
    txtTitlu = new QLineEdit;
    txtAutor = new QLineEdit;
    txtGen = new QLineEdit;
    txtAn = new QLineEdit;
    formLayout->addRow("Titlu:", txtTitlu);
    formLayout->addRow("Autor:", txtAutor);
    formLayout->addRow("Gen:", txtGen);
    formLayout->addRow("An:", txtAn);
    rightLayout->addLayout(formLayout);

    btnAdd = new QPushButton("Adauga Carte");
    rightLayout->addWidget(btnAdd);

    //partea de sortare
    QHBoxLayout* layoutSort = new QHBoxLayout;
    btnSortTitlu = new QPushButton("Sort Titlu");
    btnSortAutor = new QPushButton("Sort Autor");
    btnSortAnGen = new QPushButton("Sort An+Gen");
    layoutSort->addWidget(btnSortTitlu);
    layoutSort->addWidget(btnSortAutor);
    layoutSort->addWidget(btnSortAnGen);
    rightLayout->addLayout(layoutSort);

    //zona filtru
    QHBoxLayout* layoutFilter = new QHBoxLayout;
    btnFiltruTitlu = new QPushButton("Filtru Titlu");
    btnFiltruAn = new QPushButton("Filtru An");
    btnReset = new QPushButton("Toate Cartile");
    layoutFilter->addWidget(btnFiltruTitlu);
    layoutFilter->addWidget(btnFiltruAn);
    layoutFilter->addWidget(btnReset);
    rightLayout->addLayout(layoutFilter);

    //a doua fereastra pentru cos
    btnCosOpen = new QPushButton("Deschide Fereastra Coș");
    //btnOpenCRUD = new QPushButton("Deschide Coș CRUD");
    btnOpenReadOnly = new QPushButton("Deschide Coș Grafic");

    rightLayout->addWidget(btnCosOpen);
    //rightLayout->addWidget(btnOpenCRUD);      // pentru CosGUI-ul existent
    rightLayout->addWidget(btnOpenReadOnly);

    // butoane dinamice statistici
    panelButoaneDinamice = new QWidget;
    layoutButoaneDinamice = new QVBoxLayout;
    panelButoaneDinamice->setLayout(layoutButoaneDinamice);
    rightLayout->addWidget(panelButoaneDinamice);

    mainLayout->addWidget(rightWidget);
}

void MainWindow::incarcaButoaneDinamice() {
    //scoatem butoanele vechi
    QLayoutItem* item;
    while ((item = layoutButoaneDinamice->takeAt(0)) != nullptr) {
        delete item->widget();
        delete item;
    }

    //preluam din dto statisticile
    map<string, dto> dictionar = srv.getGenDto();

    for (const auto& pereche : dictionar) {
        string genCurent = pereche.first;
        int numarCarti = pereche.second.getcount();

        QPushButton* btn = new QPushButton(QString::fromStdString("Gen: " + genCurent));
        layoutButoaneDinamice->addWidget(btn);

        QObject::connect(btn, &QPushButton::clicked, [this, genCurent, numarCarti]() {
            QString mesaj = "In biblioteca exista " + QString::number(numarCarti) + " carti din genul " + QString::fromStdString(genCurent);
            QMessageBox::information(this, "Statistici Gen", mesaj);
            });
    }
}

void MainWindow::reloadList(const std::vector<Carte>& carti) {
    tableModel->layoutChanged();
    incarcaButoaneDinamice();
}

void MainWindow::connectSignals() {
    //adaugare
    QObject::connect(btnAdd, &QPushButton::clicked, [&]() {
        try {
            srv.adaugaCarte(txtTitlu->text().toStdString(),
                txtAutor->text().toStdString(),
                txtGen->text().toStdString(),
                txtAn->text().toInt());
            reloadList(srv.getAll());
        }
        catch (const RepoException& e) {
            QMessageBox::warning(this, "Eroare Repo", QString::fromStdString(e.getMesaj()));
        }
        catch (const ValidareException& e) {
            QMessageBox::warning(this, "Eroare Validare", QString::fromStdString(e.getMesaj()));
        }
        });

    //selectare item automplcetare form
    QObject::connect(lst->selectionModel(), &QItemSelectionModel::currentChanged,
        [&](const QModelIndex& current, const QModelIndex&) {
            if (!current.isValid()) {
                txtTitlu->setText(""); txtAutor->setText("");
                txtGen->setText(""); txtAn->setText("");
                return;
            }
            int selRow = current.row();
            auto c = srv.getCarte(selRow + 1);
            txtTitlu->setText(QString::fromStdString(c.getTitlu()));
            txtAutor->setText(QString::fromStdString(c.getAutor()));
            txtGen->setText(QString::fromStdString(c.getGen()));
            txtAn->setText(QString::number(c.getAn()));
        });;

    // stergere
    QObject::connect(btnDelete, &QPushButton::clicked, [&]() {
        int selRow = lst->currentIndex().row();
        if (selRow < 0) {
            QMessageBox::warning(this, "Avertisment", "Selectati o carte!");
            return;
        }
        try {
            srv.stergeCarte(selRow + 1);
            reloadList(srv.getAll());
        }
        catch (const RepoException& e) {
            QMessageBox::warning(this, "Eroare", QString::fromStdString(e.getMesaj()));
        }
        });

    // modificare
    QObject::connect(btnUpdate, &QPushButton::clicked, [&]() {
        int selRow = lst->currentIndex().row();
        if (selRow < 0) {
            QMessageBox::warning(this, "Avertisment", "Selectati o carte din lista pentru a o modifica!");
            return;
        }
        try {
            // Modificam folosind datele curente din LineEdit-uri
            srv.modificaTitlu(selRow + 1, txtTitlu->text().toStdString());
            srv.modificaAutor(selRow + 1, txtAutor->text().toStdString());
            srv.modificaGen(selRow + 1, txtGen->text().toStdString());
            srv.modificaAn(selRow + 1, txtAn->text().toInt());
            reloadList(srv.getAll());
        }
        catch (const RepoException& e) {
            QMessageBox::warning(this, "Eroare", "Eroare la modificare!");
        }
        });

    // undo
    QObject::connect(btnUndo, &QPushButton::clicked, [&]() {
        try {
            srv.undo();
            reloadList(srv.getAll());
        }
        catch (const RepoException& e) {
            QMessageBox::warning(this, "Eroare", QString::fromStdString(e.getMesaj()));
        }
        });

    // sortari
    QObject::connect(btnSortTitlu, &QPushButton::clicked, [&]() {
        reloadList(srv.sorteaza(CarteService::comparaTiltu)); // Folosesc typo-ul tau (Tiltu) ca in backend!
        });
    QObject::connect(btnSortAutor, &QPushButton::clicked, [&]() {
        reloadList(srv.sorteaza(CarteService::comparaAutor));
        });
    QObject::connect(btnSortAnGen, &QPushButton::clicked, [&]() {
        reloadList(srv.sorteaza(CarteService::comparaAnGen));
        });

    // filtrari
    QObject::connect(btnFiltruTitlu, &QPushButton::clicked, [&]() {
        QString text = QInputDialog::getText(this, "Filtrare", "Introduceti titlul:");
        if (!text.isEmpty()) {
            reloadList(srv.filtrare_titlu(text.toStdString()));
        }
        });

    QObject::connect(btnFiltruAn, &QPushButton::clicked, [&]() {
        QString text = QInputDialog::getText(this, "Filtrare", "Introduceti anul:");
        if (!text.isEmpty()) {
            reloadList(srv.filtrare_an(text.toInt()));
        }
        });

    //resetare lista arata tot
    QObject::connect(btnReset, &QPushButton::clicked, [&]() {
        reloadList(srv.getAll());
        });

    //actiuni cos
    QObject::connect(btnCosAdauga, &QPushButton::clicked, [&]() {
        int selRow = lst->currentIndex().row();
        if (selRow < 0) {
            QMessageBox::warning(this, "Avertisment", "Selectati o carte din lista!");
            return;
        }
        auto c = srv.getCarte(selRow + 1);
        try {
            srv.cosAdauga(c.getTitlu());
            QMessageBox::information(this, "Succes", "Carte adaugata in cos!");
        }
        catch (const RepoException& e) {
            QMessageBox::warning(this, "Eroare", QString::fromStdString(e.getMesaj()));
        }
        });

    QObject::connect(btnCosOpen, &QPushButton::clicked, [&]() {
        CosGUI* cosWindow = new CosGUI(srv);
        cosWindow->show();
        });

    //QObject::connect(btnOpenCRUD, &QPushButton::clicked, [&]() {
    //    CosGUI* cosWindow = new CosGUI(srv);
    //    cosWindow->show();
    //    });

    QObject::connect(btnOpenReadOnly, &QPushButton::clicked, [&]() {
        CosReadOnlyGUI* cosReadWindow = new CosReadOnlyGUI(srv);
        cosReadWindow->show();
        });
}


