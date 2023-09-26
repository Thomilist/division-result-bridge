#ifndef __COORDINATOR_H__
#define __COORDINATOR_H__

#include <unordered_map>
#include <vector>

#include <QByteArray>
#include <QDir>
#include <QFile>
#include <QFileInfo>
#include <QIODevice>
#include <QJsonDocument>
#include <QJsonObject>
#include <QObject>
#include <QProcess>
#include <QStringList>
#include <QTextStream>

#include <cpr/cpr.h>

#include "ForwardDeclarations.hpp"

#include "Competition.hpp"
#include "Division.hpp"
#include "Helpers.hpp"
#include "Loggable.hpp"
#include "Logger.hpp"
#include "MeosInterface.hpp"
#include "ResultPackage.hpp"
#include "Settings.hpp"
#include "WebserverInterface.hpp"

namespace divi
{
    class Coordinator : public Loggable
    {
        Q_OBJECT
        
        public:
            Coordinator(
                Settings* a_settings,
                Logger* a_log,
                QObject* a_parent = nullptr);
            ~Coordinator();

        public slots:
            void pingWebserver();
            void createCompetition(const QString& a_password);
            void updateMetadata();
            void updateResults();
            void startFresh();
        
        signals:
            void competitionCreated(const Competition& a_competition);

        private:
            void updateCache();
            void prepareWorkingDir();
            int calculateDivisionResults(const Division& a_division);
            int loadResultFile(const Division& a_division);
            bool diviExeExists();

            Settings* settings;
            Settings settings_cache;
            MeosInterface meos;
            WebserverInterface webserver;
            std::vector<ResultPackage> results;
            QProcess divi_process;

            std::unordered_map<QString, QString> substitutions{
                {"<div class=\"matchgruppeHeader\">Klasse oversigt</div>", "<div class=\"matchgruppeHeader\">Klasseoversigt</div>"},
                {"<table", "<div class=\"table-wrapper\"><table"},
                {"/table>", "/table></div>"},
                {">LøbsPoint<", ">Løbspoint<"},
                {">MatchPoint<", ">Matchpoint<"},
                {"<td>Ialt:</td>", "<td>I alt:</td>"}
            };
    };
}

#endif // __COORDINATOR_H__