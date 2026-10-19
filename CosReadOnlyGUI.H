#pragma once
#include <QWidget>
#include <QPainter>
#include <QPaintEvent>
#include <QRandomGenerator>
#include "CarteService.h"

class CosReadOnlyGUI : public QWidget, public Observer {
private:
    CarteService& srv;

protected:
    void paintEvent(QPaintEvent* ev) override {
        QPainter p(this);

        size_t nrCarti = srv.dimensiuneCos();

        for (size_t i = 0; i < nrCarti; i++) {
            int x = QRandomGenerator::global()->bounded(width());
            int y = QRandomGenerator::global()->bounded(height());
            p.drawEllipse(x, y, 30, 30);
        }
    }

public:
    CosReadOnlyGUI(CarteService& srv) : srv{ srv } {
        setWindowTitle("CosReadOnlyGUI");
        resize(300, 200);
        srv.addObserverToCos(this);
    }

    ~CosReadOnlyGUI() {
        srv.removeObserverFromCos(this);
    }

    void update() override {
        QWidget::update();
    }
};