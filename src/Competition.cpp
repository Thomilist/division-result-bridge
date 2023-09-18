#include "Competition.hpp"


namespace divi
{
    Competition::Competition()
    {
        setDate(QDate::currentDate());
        setVisibility(Visibility::PRIVATE);
    }
    
    Competition::~Competition()
    { }
    
    Competition Competition::fromJson(const QJsonObject& a_json)
    {
        Competition competition;

        if (const QJsonValue value = a_json[getIDAlias()]; value.isDouble())
        {
            competition.setID(value.toInt());
        }

        if (const QJsonValue value = a_json[getPasswordAlias()]; value.isString())
        {
            competition.setPassword(value.toString());
        }

        if (const QJsonValue value = a_json[getNameAlias()]; value.isString())
        {
            competition.setName(value.toString());
        }

        if (const QJsonValue value = a_json[getOrganiserAlias()]; value.isString())
        {
            competition.setOrganiser(value.toString());
        }

        if (const QJsonValue value = a_json[getDateAlias()]; value.isString())
        {
            competition.setDate(value.toString());
        }

        if (const QJsonValue value = a_json[getVisibilityAlias()]; value.isString())
        {
            competition.setVisibility(value.toString());
        }

        return competition;
    }
    
    QJsonObject Competition::toJson() const
    {
        QJsonObject json;

        json[getIDAlias()] = id;
        json[getPasswordAlias()] = password;
        json[getNameAlias()] = name;
        json[getOrganiserAlias()] = organiser;
        json[getDateAlias()] = date;
        json[getVisibilityAlias()] = visibility;

        return json;
    }
    
    void Competition::setID(int a_id)
    {
        id = a_id;
        return;
    }
    
    int Competition::getID() const
    {
        return id;
    }
    
    const QString Competition::getIDAlias()
    {
        return "id";
    }
    
    void Competition::setPassword(const QString& a_password)
    {
        password = a_password;
        return;
    }
    
    const QString& Competition::getPassword() const
    {
        return password;
    }
    
    const QString Competition::getPasswordAlias()
    {
        return "password";
    }
    
    void Competition::setName(const QString& a_name)
    {
        name = a_name;
        return;
    }
    
    const QString& Competition::getName() const
    {
        return name;
    }
    
    const QString Competition::getNameAlias()
    {
        return "competition_name";
    }
    
    void Competition::setOrganiser(const QString& a_organiser)
    {
        organiser = a_organiser;
        return;
    }
    
    const QString& Competition::getOrganiser() const
    {
        return organiser;
    }
    
    const QString Competition::getOrganiserAlias()
    {
        return "organiser";
    }
    
    void Competition::setDate(const QString& a_date)
    {
        date = a_date;
        return;
    }
    
    void Competition::setDate(const QDate& a_date)
    {
        date = a_date.toString(Helpers::dateFormat());
        return;
    }
    
    const QString& Competition::getDate() const
    {
        return date;
    }
    
    const QString Competition::getDateAlias()
    {
        return "competition_date";
    }
    
    void Competition::setVisibility(const QString& a_visibility)
    {
        visibility = a_visibility;
        return;
    }
    
    void Competition::setVisibility(Visibility a_visibility)
    {
        visibility = Helpers::visibility(a_visibility);
        return;
    }
    
    const QString& Competition::getVisibility() const
    {
        return visibility;
    }
    
    const QString Competition::getVisibilityAlias()
    {
        return "visibility";
    }
}