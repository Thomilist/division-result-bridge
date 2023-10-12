#ifndef __PERSISTENTSETTINGS_H__
#define __PERSISTENTSETTINGS_H__

#include <algorithm>
#include <array>

#include <QByteArray>
#include <QDir>
#include <QFile>
#include <QIODevice>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonValue>
#include <QMainWindow>
#include <QObject>
#include <QSettings>
#include <QStandardPaths>
#include <QString>
#include <QTextStream>
#include <QTimeZone>

#include "utils/ForwardDeclarations.hpp"

#include "Division.hpp"
#include "logging/Loggable.hpp"
#include "Settings.hpp"
#include "version/Version.hpp"

#include "logging/MessageType.hpp"

namespace divi
{
    class PersistentSettings : public QSettings, public Loggable, public Settings
    {
        Q_OBJECT
        
        public:
            PersistentSettings(QMainWindow* a_main_window);
            ~PersistentSettings();

            static const QString getConfigMetadataAlias();
            static const QString getConfigSourceAlias();
            static const QString getConfigVersionAlias();

            int importConfig(const QString& a_path);
            int exportConfig(const QString& a_path);
        
        signals:
            void clearDivisions();
            void addDivision(const Division& a_division);
        
        private:
            void loadFromRegistry();
            void saveToRegistry();

            int loadFromConfig();
            int saveToConfig();
            bool isLoadedConfigValid(const QJsonObject& a_config_json);

            QMainWindow* main_window;
    };
}

#endif // __PERSISTENTSETTINGS_H__