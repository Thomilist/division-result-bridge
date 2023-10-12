#ifndef __SUMMARYTABLEMODEL_H__
#define __SUMMARYTABLEMODEL_H__

#include <array>

#include <QAbstractTableModel>
#include <QModelIndex>
#include <QObject>
#include <QString>
#include <QStringBuilder>
#include <QVariant>

#include "../utils/ForwardDeclarations.hpp"

#include "../Settings.hpp"

namespace divi
{
    class SummaryTableModel : public QAbstractTableModel
    {
        public:
            SummaryTableModel(QObject* a_parent = nullptr);
            ~SummaryTableModel();

            int rowCount(const QModelIndex& a_parent = QModelIndex()) const override;
            int columnCount(const QModelIndex& a_parent = QModelIndex()) const override;
        
            QVariant data(const QModelIndex& a_index, int a_role = Qt::DisplayRole) const override;
            QVariant headerData(int a_section, Qt::Orientation a_orientation, int a_role = Qt::DisplayRole) const override;

            void updateData(Settings& a_settings);

        private:
            std::array<std::array<QString, 2>, 3> items;
    };
}

#endif // __SUMMARYTABLEMODEL_H__