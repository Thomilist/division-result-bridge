#include "DivisionTableModel.hpp"


namespace divi
{
    DivisionTableModel::DivisionTableModel(Settings* a_settings, QObject* a_parent)
        : QAbstractTableModel(a_parent)
        , settings(a_settings)
    {
        if (settings != nullptr)
        {
            for (const auto& division : settings->getDivisions())
            {
                used_ids.insert(division.getID());
            }
        }
    }
    
    DivisionTableModel::~DivisionTableModel()
    { }
    
    int DivisionTableModel::rowCount(const QModelIndex&) const 
    {
        if (settings == nullptr)
        {
            return 0;
        }
        else
        {
            return settings->getDivisions().size();
        }
    }
    
    int DivisionTableModel::columnCount(const QModelIndex&) const 
    {
        return Column::_Count;
    }
    
    bool DivisionTableModel::insertRows(int a_row, int a_count, const QModelIndex& a_parent)
    {
        beginInsertRows(a_parent, a_row, a_row + a_count - 1);
        settings->getDivisions().insert(settings->getDivisions().begin() + a_row, a_count, Division());
        endInsertRows();
        return true;
    }
    
    bool DivisionTableModel::removeRows(int a_row, int a_count, const QModelIndex& a_parent)
    {
        beginRemoveRows(a_parent, a_row, a_row + a_count - 1);
        settings->getDivisions().erase(settings->getDivisions().begin() + a_row, settings->getDivisions().begin() + a_row + a_count);
        endRemoveRows();
        return true;
    }
    
    QVariant DivisionTableModel::data(const QModelIndex& a_index, int a_role) const 
    {
        if (settings == nullptr)
        {
            return QVariant();
        }
        
        switch (a_role)
        {
            case Qt::DisplayRole:
            {
                switch (a_index.column())
                {
                    case Column::ID:
                    {
                        return settings->getDivisions().at(a_index.row()).getID();
                    }
                    case Column::Name:
                    {
                        return settings->getDivisions().at(a_index.row()).getName();
                    }
                    case Column::ConfigPath:
                    {
                        return settings->getDivisions().at(a_index.row()).getConfigPath();
                    }
                    case Column::InfoServerAddress:
                    {
                        return settings->getDivisions().at(a_index.row()).getInfoServerAddress();
                    }
                }

                break;
            }
            case Qt::TextAlignmentRole:
            {
                switch (a_index.column())
                {
                    case Column::ID:
                    {
                        return Qt::AlignCenter;
                    }
                    default:
                    {
                        return {Qt::AlignLeft | Qt::AlignVCenter};
                    }
                }

                break;
            }
            default:
            {
                break;
            }
        }

        return QVariant();
    }
    
    QVariant DivisionTableModel::headerData(int a_section, Qt::Orientation a_orientation, int a_role) const 
    {
        switch (a_orientation)
        {
            case Qt::Orientation::Vertical:
            {
                return QVariant();
            }
            case Qt::Orientation::Horizontal:
            {
                switch (a_role)
                {
                    case Qt::DisplayRole:
                    {
                        switch (a_section)
                        {
                            case Column::ID:
                            {
                                return QString("ID");
                            }
                            case Column::Name:
                            {
                                return QString("Name");
                            }
                            case Column::ConfigPath:
                            {
                                return QString("Config Path");
                            }
                            case Column::InfoServerAddress:
                            {
                                return QString("Info Server Address");
                            }
                        }

                        break;
                    }
                    case Qt::TextAlignmentRole:
                    {
                        switch (a_section)
                        {
                            case Column::ID:
                            {
                                return Qt::AlignCenter;
                            }
                            default:
                            {
                                return {Qt::AlignLeft | Qt::AlignVCenter};
                            }
                        }

                        break;
                    }
                    default:
                    {
                        break;
                    }
                }
            }
        }

        return QVariant();
    }
    
    bool DivisionTableModel::isIDAvailable(int a_id) const
    {
        return !used_ids.contains(a_id);
    }
    
    int DivisionTableModel::getAvailableID() const
    {
        int id = 1;

        while (!isIDAvailable(id))
        {
            ++id;
        }

        return id;
    }
    
    Division* DivisionTableModel::getDivision(int a_id)
    {
        for (auto& division : settings->getDivisions())
        {
            if (division.getID() == a_id)
            {
                return &division;
            }
        }

        return nullptr;
    }
    
    void DivisionTableModel::addOrOverwriteDivision(const Division& a_division)
    {
        if (isIDAvailable(a_division.getID()))
        {
            insertRow(rowCount());
            settings->getDivisions().back() = a_division;
            used_ids.insert(a_division.getID());
            std::sort(settings->getDivisions().begin(), settings->getDivisions().end());
            emit dataChanged(createIndex(0, 0), createIndex(rowCount() - 1, columnCount() - 1), {Qt::DisplayRole});
        }
        else
        {
            int row = 0;
            
            for (auto& division : settings->getDivisions())
            {
                if (a_division.getID() == division.getID())
                {
                    division = a_division;
                    used_ids.insert(a_division.getID());
                    emit dataChanged(createIndex(row, 0), createIndex(row, columnCount() - 1), {Qt::DisplayRole});
                    break;
                }

                ++row;
            }
        }

        return;
    }
    
    void DivisionTableModel::deleteDivision(int a_id)
    {
        for (size_t row = 0; row < settings->getDivisions().size(); ++row)
        {
            if (settings->getDivisions().at(row).getID() == a_id)
            {
                removeRow(row);
                used_ids.erase(a_id);
                emit dataChanged(createIndex(row, 0), createIndex(rowCount() - 1, columnCount() - 1), {Qt::DisplayRole});
                return;
            }
        }
    }
    
    void DivisionTableModel::clear()
    {
        const auto ids = used_ids;
        
        for (const auto& id : ids)
        {
            deleteDivision(id);
        }

        return;
    }
}