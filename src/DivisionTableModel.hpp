#ifndef __DIVISIONTABLEMODEL_H__
#define __DIVISIONTABLEMODEL_H__

#include <algorithm>
#include <set>
#include <vector>

#include <QAbstractTableModel>
#include <QModelIndex>
#include <QObject>
#include <QVariant>

#include "ForwardDeclarations.hpp"

#include "Division.hpp"
#include "Settings.hpp"

namespace divi
{
    class DivisionTableModel : public QAbstractTableModel
    {
        Q_OBJECT
        
        public:
            DivisionTableModel(Settings* a_settings, QObject* a_parent = nullptr);
            ~DivisionTableModel();

            int rowCount(const QModelIndex& a_parent = QModelIndex()) const override;
            int columnCount(const QModelIndex& a_parent = QModelIndex()) const override;
            bool insertRows(int a_row, int a_count, const QModelIndex& a_parent = QModelIndex()) override;
            bool removeRows(int a_row, int a_count, const QModelIndex& a_parent = QModelIndex()) override;
            QVariant data(const QModelIndex& a_index, int a_role = Qt::DisplayRole) const override;
            QVariant headerData(int a_section, Qt::Orientation a_orientation, int a_role = Qt::DisplayRole) const override;

            bool isIDAvailable(int a_id) const;
            int getAvailableID() const;
            Division* getDivision(int a_id);
        
        public slots:
            void addOrOverwriteDivision(const Division& a_division);
            void deleteDivision(int a_id);
            void clear();
        
        private:
            Settings* settings;
            std::set<int> used_ids;
    };
}

#endif // __DIVISIONTABLEMODEL_H__