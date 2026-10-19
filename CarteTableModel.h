#pragma once
#include <QAbstractTableModel>
#include <vector>
#include "carte.h"

class CarteTableModel : public QAbstractTableModel {
private:
    const std::vector<Carte>* carti;

public:
    CarteTableModel(const std::vector<Carte>* data, QObject* parent = nullptr)
        : QAbstractTableModel(parent), carti(data) {
    }

    int rowCount(const QModelIndex& parent = QModelIndex()) const override {
        return carti ? (int)carti->size() : 0;
    }

    int columnCount(const QModelIndex& parent = QModelIndex()) const override {
        return 4;
    }

    QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override {
        if (!index.isValid() || !carti || index.row() >= carti->size())
            return QVariant();

        const Carte& c = (*carti)[index.row()];

        if (role == Qt::DisplayRole) {
            switch (index.column()) {
            case 0: return QString::fromStdString(c.getTitlu());
            case 1: return QString::fromStdString(c.getAutor());
            case 2: return QString::fromStdString(c.getGen());
            case 3: return c.getAn();
            default: return QVariant();
            }
        }
        return QVariant();
    }

    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override {
        if (role != Qt::DisplayRole) return QVariant();
        if (orientation == Qt::Horizontal) {
            switch (section) {
            case 0: return "Titlu";
            case 1: return "Autor";
            case 2: return "Gen";
            case 3: return "An";
            default: return QVariant();
            }
        }
        return QString::number(section + 1);
    }
};