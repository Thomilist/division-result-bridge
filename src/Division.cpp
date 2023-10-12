#include "Division.hpp"


namespace divi
{
    Division::Division(
        int a_id,
        const QString& a_name,
        const QString& a_divi_path,
        const QString& a_info_server_address)
        : id(a_id)
        , name(a_name)
        , division_config_path(a_divi_path)
        , division_info_server_address(a_info_server_address)
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

        if (const QJsonValue value = a_json[getNameAlias()]; value.isString())
        {
            division.setName(value.toString());
        }

        if (const QJsonValue value = a_json[getConfigPathAlias()]; value.isString())
        {
            division.setConfigPath(value.toString());
        }

        if (const QJsonValue value = a_json[getInfoServerAddressAlias()]; value.isString())
        {
            division.setInfoServerAddress(value.toString());
        }

        return division;
    }
    
    QJsonObject Division::toJson() const
    {
        QJsonObject json;

        json[getIDAlias()] = id;
        json[getNameAlias()] = name;
        json[getConfigPathAlias()] = division_config_path;
        json[getInfoServerAddressAlias()] = division_info_server_address;

        return json;
    }
    
    bool Division::isFullyDefined(ResultSource a_result_source) const
    {
        bool fully_defined = (id > 0) && !name.isEmpty();

        switch (a_result_source)
        {
            case ResultSource::MeosDivi:
            case ResultSource::XmlDivi:
            {
                fully_defined &= !division_config_path.isEmpty();
                break;
            }
            case ResultSource::Divi:
            {
                fully_defined &= !division_info_server_address.isEmpty();
                break;
            }
            default:
            {
                fully_defined = false;
                break;
            }
        }
        
        return fully_defined;
    }
    
    bool Division::hasValidConfigPath() const
    {
        QFileInfo divi_file{division_config_path};
        return divi_file.exists() && divi_file.isReadable();
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
    
    void Division::setConfigPath(const QString& a_path)
    {
        division_config_path = a_path;
        return;
    }
    
    const QString& Division::getConfigPath() const
    {
        return division_config_path;
    }
    
    const QString Division::getConfigPathAlias()
    {
        return "division_config_path";
    }
    
    void Division::setInfoServerAddress(const QString& a_address)
    {
        division_info_server_address = a_address;
        return;
    }
    
    const QString& Division::getInfoServerAddress() const
    {
        return division_info_server_address;
    }
    
    const QString Division::getInfoServerAddressAlias()
    {
        return "division_info_server_address";
    }
}
