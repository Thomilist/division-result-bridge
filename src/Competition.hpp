#ifndef __COMPETITION_H__
#define __COMPETITION_H__

#include <QJsonObject>
#include <QString>
#include <QDate>

#include "ForwardDeclarations.hpp"

#include "Helpers.hpp"

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
            void setDate(const QDate& a_date);
            const QString& getDate() const;
            static const QString getDateAlias();

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

            // Password (in plain text; minimal security; just to avoid accidental access)
            QString password = "";

            // Name
            QString name = "";

            // Organiser
            QString organiser = "";

            // Date
            QString date;

            // Visibility
            QString visibility;

            // liveresultat.orientering.se competition ID
            int liveresults_id = 0;
    };
}

#endif // __COMPETITION_H__