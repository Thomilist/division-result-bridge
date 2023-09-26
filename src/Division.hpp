#ifndef __DIVISION_H__
#define __DIVISION_H__

#include <QFileInfo>
#include <QJsonObject>
#include <QString>

#include "ForwardDeclarations.hpp"

namespace divi
{
    class Division
    {
        public:
            Division(
                int a_id = 0,
                const QString& a_divi_path = "",
                const QString& a_name = "");
            ~Division();

            bool operator<(const Division& a_other) const;

            static Division fromJson(const QJsonObject& a_json);
            QJsonObject toJson() const;

            bool isFullyDefined() const;
            bool hasValidConfigPath() const;

            void setID(int a_id);
            int getID() const;
            static const QString getIDAlias();

            void setDivisionConfigPath(const QString& a_divi_path);
            const QString& getDivisionConfigPath() const;
            static const QString getDivisionConfigPathAlias();

            void setName(const QString& a_name);
            const QString& getName() const;
            static const QString getNameAlias();
        
        private:
            // ID 0 is an empty (invalid) division
            int id;
            QString division_config_path;
            QString name;
    };
}

#endif // __DIVISION_H__