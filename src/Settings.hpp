#ifndef __SETTINGS_H__
#define __SETTINGS_H__

#include <vector>

#include <QDate>
#include <QJsonArray>
#include <QJsonObject>
#include <QMainWindow>
#include <QObject>
#include <QString>
#include <QStringBuilder>

#include "ForwardDeclarations.hpp"

#include "Competition.hpp"
#include "Division.hpp"

namespace divi
{
    class Settings
    {
        public:
            Settings(QMainWindow* a_main_window = nullptr);
            virtual ~Settings();

            const QJsonObject getMetadataAsJson() const;

            static const QString getWindowGeometryAlias();

            Competition& getCompetition();
            static const QString getCompetitionAlias();

            void setExternalConfigPath(const QString& a_path);
            const QString& getExternalConfigPath() const;
            static const QString getExternalConfigPathAlias();

            void setWorkingDir(const QString& a_dir);
            const QString& getWorkingDir() const;
            static const QString getWorkingDirAlias();
            const QString getXMLResultPath();
            const QString getDivisionResultPath(int a_division_id = 0);
            const QString getRawLogPath();
            const QString getHtmlLogPath();

            void setDiviExePath(const QString& a_path);
            const QString& getDiviExePath() const;
            static const QString getDiviExePathAlias();

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
            QMainWindow* main_window;

            // Competition
            Competition competition;

            // JSON configuration file paths for import and export of configuration
            QString external_config_path;

            // Working directory
            QString working_dir;

            // Divisionsmatch.exe path
            QString divi_exe_path;

            // MeOS information server IP address
            QString meos_address;

            // Web server IP address
            QString webserver_address;

            // Update interval in seconds
            int update_interval = 30;

            // Divisions
            std::vector<Division> divisions;

            // Save logs
            bool save_pretty_log = true;
            bool save_raw_log = false;
    };
}

#endif // __SETTINGS_H__