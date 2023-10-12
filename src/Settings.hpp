#ifndef __SETTINGS_H__
#define __SETTINGS_H__

#include <vector>

#include <QDate>
#include <QJsonArray>
#include <QJsonObject>
#include <QObject>
#include <QStandardPaths>
#include <QString>
#include <QStringBuilder>
#include <QTimeZone>

#include "utils/ForwardDeclarations.hpp"

#include "Competition.hpp"
#include "Division.hpp"

#include "ResultSource.hpp"

namespace divi
{
    class Settings
    {
        public:
            Settings();
            virtual ~Settings();

            const QJsonObject getMetadataAsJson() const;

            static const QString getWindowGeometryAlias();

            void setFirstTime(bool a_state);
            bool isFirstTime() const;
            static const QString getFirstTimeAlias();

            void setResultSource(const QString& a_result_source);
            void setResultSource(ResultSource a_result_source);
            ResultSource getResultSource() const;
            static const QString getResultSourceAlias();

            Competition& getCompetition();
            static const QString getCompetitionAlias();

            void setExternalConfigPath(const QString& a_path);
            const QString& getExternalConfigPath() const;
            static const QString getExternalConfigPathAlias();

            void setWorkingDir(const QString& a_dir);
            const QString& getWorkingDir() const;
            static const QString getWorkingDirAlias();
            const QString getDynamicXmlResultPath();
            const QString getDivisionResultPath(int a_division_id = 0);
            const QString getRawLogPath();
            const QString getHtmlLogPath();

            void setDiviExePath(const QString& a_path);
            const QString& getDiviExePath() const;
            static const QString getDiviExePathAlias();

            void setXmlResultPath(const QString& a_path);
            const QString& getXmlResultPath() const;
            static const QString getXmlResultPathAlias();

            void setMeosAddress(const QString& a_address);
            const QString& getMeosAddress() const;
            static const QString getMeosAddressAlias();

            void setWebserverAddress(const QString& a_address);
            const QString& getWebserverAddress() const;
            static const QString getWebserverAddressAlias();

            void setUpdateInterval(int a_interval);
            int getUpdateInterval() const;
            static const QString getUpdateIntervalAlias();

            std::vector<Division>& getDivisions();
            static const QString getDivisionsAlias();

            void setPrettyLogging(bool a_state);
            bool getPrettyLogging() const;
            static const QString getPrettyLoggingAlias();

            void setRawLogging(bool a_state);
            bool getRawLogging() const;
            static const QString getRawLoggingAlias();
        
        protected:
            // Is this the first launch on this machine?
            bool first_time = true;

            // Result source
            ResultSource result_source = ResultSource::_Undefined;

            // Competition
            Competition competition;

            // JSON configuration file paths for import and export of configuration
            QString external_config_path;

            // Working directory
            QString working_dir;

            // Divisionsmatch.exe path
            QString divi_exe_path = "";

            // XML result path
            QString xml_result_path = "";

            // MeOS information server IP address
            QString meos_address;

            // Web server IP address
            QString webserver_address;

            // Update interval in seconds
            int update_interval = 60;

            // Divisions
            std::vector<Division> divisions;

            // Save logs
            bool save_pretty_log = true;
            bool save_raw_log = true;
    };
}

#endif // __SETTINGS_H__