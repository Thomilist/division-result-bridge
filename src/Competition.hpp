#ifndef __COMPETITION_H__
#define __COMPETITION_H__

#include <QDate>
#include <QDateTime>
#include <QJsonObject>
#include <QString>
#include <QTime>
#include <QTimeZone>

#include "utils/ForwardDeclarations.hpp"

#include "utils/Helpers.hpp"

#include "Visibility.hpp"

namespace divi
{
    class Competition
    {
        public:
            Competition();
            ~Competition();

            static Competition fromJson(const QJsonObject& a_json);
            QJsonObject toJson() const;

            void setID(int a_id);
            int getID() const;
            static const QString getIDAlias();

            void setPassword(const QString& a_password);
            const QString& getPassword() const;
            static const QString getPasswordAlias();

            void setName(const QString& a_name);
            const QString& getName() const;
            static const QString getNameAlias();

            void setOrganiser(const QString& a_organiser);
            const QString& getOrganiser() const;
            static const QString getOrganiserAlias();

            void setDate(const QString& a_date);
            void setDate(QDate a_date);
            const QString& getDate() const;
            static const QString getDateAlias();

            void setTimeZone(const QString& a_time_zone);
            const QString& getTimeZone() const;
            static const QString getTimeZoneAlias();

            void updateDateTime();
            const QString& getDateTime() const;
            static const QString getDateTimeAlias();

            void setVisibility(const QString& a_visibility);
            void setVisibility(Visibility a_visibility);
            const QString& getVisibility() const;
            static const QString getVisibilityAlias();

            void setLiveresultsID(int a_id);
            int getLiveresultsID() const;
            static const QString getLiveresultsIDAlias();
        
        private:
            // Competition ID
            int id = 0;

            // Password (in plain text; no security; just to avoid accidental access)
            QString password = "";

            // Name
            QString name = "";

            // Organiser
            QString organiser = "";

            // Date
            QString date;

            // Time zone
            QString time_zone;

            // Full ISO8601 date-time string
            QString date_time_string;

            // Visibility
            QString visibility;

            // liveresultat.orientering.se competition ID
            int liveresults_id = 0;
    };
}

#endif // __COMPETITION_H__