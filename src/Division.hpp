#ifndef __DIVISION_H__
#define __DIVISION_H__

#include <QFileInfo>
#include <QJsonObject>
#include <QString>

#include "utils/ForwardDeclarations.hpp"

#include "ResultSource.hpp"

namespace divi
{
    class Division
    {
        public:
            Division(
                int a_id = 0,
                const QString& a_name = "",
                const QString& a_divi_path = "",
                const QString& a_info_server_address = "");
            ~Division();

            bool operator<(const Division& a_other) const;

            static Division fromJson(const QJsonObject& a_json);
            QJsonObject toJson() const;

            bool isFullyDefined(ResultSource a_result_source) const;
            bool hasValidConfigPath() const;

            void setID(int a_id);
            int getID() const;
            static const QString getIDAlias();

            void setName(const QString& a_name);
            const QString& getName() const;
            static const QString getNameAlias();

            void setConfigPath(const QString& a_divi_path);
            const QString& getConfigPath() const;
            static const QString getConfigPathAlias();

            void setInfoServerAddress(const QString& a_address);
            const QString& getInfoServerAddress() const;
            static const QString getInfoServerAddressAlias();
        
        private:
            // ID 0 is an empty (invalid) division
            int id = 0;
            QString name = "";
            QString division_config_path = "";
            QString division_info_server_address = "";
    };
}

#endif // __DIVISION_H__