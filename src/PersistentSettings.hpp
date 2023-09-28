#ifndef __PERSISTENTSETTINGS_H__
#define __PERSISTENTSETTINGS_H__

#include <vector>

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

#include "ForwardDeclarations.hpp"

#include "Division.hpp"
#include "Loggable.hpp"
#include "Logger.hpp"
#include "Settings.hpp"
#include "Version.hpp"

#include "MessageType.hpp"

namespace divi
{
    class PersistentSettings : public QSettings, public Loggable, public Settings
    {
        Q_OBJECT
        
        public:
            PersistentSettings(QMainWindow* a_main_window, Logger* a_log = nullptr);
            ~PersistentSettings();

            static const QString getConfigMetadataAlias();
            static const QString getConfigSourceAlias();
            static const QString getConfigVersionAlias();

            void importConfig(const QString& a_path);
            void exportConfig(const QString& a_path);
        
        signals:
            void clearDivisions();
            void addDivision(const Division& a_division);
        
        private:
            void loadFromRegistry();
            void saveToRegistry();

            void loadFromConfig();
            void saveToConfig();
            bool isLoadedConfigValid(const QJsonObject& a_config_json);
    };
}

#endif // __PERSISTENTSETTINGS_H__