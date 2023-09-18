#include "Division.hpp"


namespace divi
{
    Division::Division(
        int a_id,
        const QString& a_divi_path,
        const QString& a_name)
        : id(a_id)
        , division_config_path(a_divi_path)
        , name(a_name)
    { }
    
    Division::~Division()
    { }
    
    bool Division::operator<(const Division& a_other) const
    {
        return getID() < a_other.getID();
    }

    Division Division::fromJson(const QJsonObject& a_json)
    {
        Division division;

        if (const QJsonValue value = a_json[getIDAlias()]; value.isDouble())
        {
            division.setID(value.toInt());
        }

        if (const QJsonValue value = a_json[getDivisionConfigPathAlias()]; value.isString())
        {
            division.setDivisionConfigPath(value.toString());
        }

        if (const QJsonValue value = a_json[getNameAlias()]; value.isString())
        {
            division.setName(value.toString());
        }

        return division;
    }
    
    QJsonObject Division::toJson() const
    {
        QJsonObject json;

        json[getIDAlias()] = id;
        json[getDivisionConfigPathAlias()] = division_config_path;
        json[getNameAlias()] = name;

        return json;
    }
    
    bool Division::isFullyDefined() const
    {
        return (id > 0) && !name.isEmpty() && !division_config_path.isEmpty();
    }
    
    void Division::setID(int a_id)
    {
        id = a_id;
        return;
    }
    
    int Division::getID() const
    {
        return id;
    }
    
    const QString Division::getIDAlias()
    {
        return "division_id";
    }
    
    void Division::setDivisionConfigPath(const QString& a_path)
    {
        division_config_path = a_path;
        return;
    }
    
    const QString& Division::getDivisionConfigPath() const
    {
        return division_config_path;
    }
    
    const QString Division::getDivisionConfigPathAlias()
    {
        return "division_config_path";
    }
    
    void Division::setName(const QString& a_name)
    {
        name = a_name;
        return;
    }
    
    const QString& Division::getName() const
    {
        return name;
    }
    
    const QString Division::getNameAlias()
    {
        return "division_name";
    }
}
