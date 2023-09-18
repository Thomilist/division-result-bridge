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
#include <QString>
#include <QTextStream>

#include "ForwardDeclarations.hpp"

#include "Division.hpp"
#include "Settings.hpp"

namespace divi
{
    class PersistentSettings : public QSettings, public Settings
    {
        Q_OBJECT
        
        public:
            PersistentSettings(QMainWindow* a_main_window);
            ~PersistentSettings();

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
    };
}

#endif // __PERSISTENTSETTINGS_H__