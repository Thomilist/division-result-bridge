#include "SummaryTableModel.hpp"


namespace divi
{
    SummaryTableModel::SummaryTableModel(QObject* a_parent)
        : QAbstractTableModel(a_parent)
    {
        items[0][0] = "Server address:";
        items[1][0] = "Competition ID:";
        items[2][0] = "Password:";
    }
    
    SummaryTableModel::~SummaryTableModel()
    { }
    
    int SummaryTableModel::rowCount(const QModelIndex&) const 
    {
        return 3;
    }
    
    int SummaryTableModel::columnCount(const QModelIndex&) const 
    {
        return 2;
    }
    
    QVariant SummaryTableModel::data(const QModelIndex& a_index, int a_role) const 
    {
        switch (a_role)
        {
            case Qt::DisplayRole:
            {
                return items[a_index.row()][a_index.column()];
            }
            case Qt::TextAlignmentRole:
            {
                switch (a_index.column())
                {
                    case 0:
                    {
                        return {Qt::AlignLeft | Qt::AlignVCenter};
                    }
                    default:
                    {
                        return Qt::AlignCenter;
                    }
                }
            }
        }

        return QVariant();
    }
    
    QVariant SummaryTableModel::headerData(int, Qt::Orientation, int) const 
    {
        return QVariant();
    }
    
    void SummaryTableModel::updateData(Settings& a_settings)
    {
        items[0][1] = a_settings.getWebserverAddress();
        items[1][1] = QString::number(a_settings.getCompetition().getID());
        items[2][1] = a_settings.getCompetition().getPassword();
        emit dataChanged(createIndex(0, 0), createIndex(rowCount() - 1, columnCount() - 1), {Qt::DisplayRole});
        return;
    }
}