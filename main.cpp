#include <QApplication>
#include "mainwindow.h"
#include "teste.h"
#include "CarteRepoFile.h"
#include "validator.h"
#include "CarteService.h"

int main(int argc, char *argv[]) {

    testToate();


    QApplication a(argc, argv);


    CarteRepoFile repo("carti.txt");
    CarteValidator val;
    CarteService srv(repo, val);


    MainWindow w(srv);
    w.show();


    return a.exec();
}