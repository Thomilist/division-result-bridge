#include "Competition.hpp"


namespace divi
{
    Competition::Competition()
    {
        setDate(QDate::currentDate());
        setTimeZone(QTimeZone::systemTimeZoneId());
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

        if (const QJsonValue value = a_json[getTimeZoneAlias()]; value.isString())
        {
            competition.setTimeZone(value.toString());
        }

        if (const QJsonValue value = a_json[getVisibilityAlias()]; value.isString())
        {
            competition.setVisibility(value.toString());
        }

        if (const QJsonValue value = a_json[getLiveresultsIDAlias()]; value.isDouble())
        {
            competition.setLiveresultsID(value.toInt());
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
        json[getTimeZoneAlias()] = time_zone;
        json[getDateTimeAlias()] = date_time_string;
        json[getVisibilityAlias()] = visibility;
        json[getLiveresultsIDAlias()] = liveresults_id;

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
        QDate date_check = QDate::fromString(a_date, Helpers::dateFormat());

        if (!date_check.isValid())
        {
            date = QDate::currentDate().toString(Helpers::dateFormat());
            return;
        }
        
        date = a_date;
        updateDateTime();
        return;
    }
    
    void Competition::setDate(QDate a_date)
    {
        if (a_date.isValid())
        {
            date = a_date.toString(Helpers::dateFormat());
        }
        else
        {
            date = QDate::currentDate().toString(Helpers::dateFormat());
        }
        
        updateDateTime();
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
    
    void Competition::setTimeZone(const QString& a_time_zone)
    {
        time_zone = a_time_zone;
        updateDateTime();
        return;
    }
    
    const QString& Competition::getTimeZone() const
    {
        return time_zone;
    }
    
    const QString Competition::getTimeZoneAlias()
    {
        return "time_zone_iana";
    }
    
    void Competition::updateDateTime()
    {
        if (date.isEmpty() || time_zone.isEmpty())
        {
            return;
        }
        
        auto datetime = QDateTime{QDate::fromString(date, Helpers::dateFormat()), QTime(), QTimeZone{time_zone.toUtf8()}};
        date_time_string = datetime.toString(Qt::ISODateWithMs);
        return;
    }
    
    const QString& Competition::getDateTime() const
    {
        return date_time_string;
    }
    
    const QString Competition::getDateTimeAlias()
    {
        return "date_time_string";
    }
    
    void Competition::setVisibility(const QString& a_visibility)
    {
        visibility = a_visibility;
        return;
    }
    
    void Competition::setVisibility(Visibility a_visibility)
    {
        if (const QString new_visibility = Helpers::visibility(a_visibility); !new_visibility.isEmpty())
        {
            visibility = new_visibility;
        }
        
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
    
    void Competition::setLiveresultsID(int a_id)
    {
        liveresults_id = a_id;
        return;
    }
    
    int Competition::getLiveresultsID() const
    {
        return liveresults_id;
    }
    
    const QString Competition::getLiveresultsIDAlias()
    {
        return "liveresults_id";
    }
}