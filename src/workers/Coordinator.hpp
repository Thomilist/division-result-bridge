#ifndef __COORDINATOR_H__
#define __COORDINATOR_H__

#include <optional>
#include <vector>

#include <QDir>
#include <QIODevice>
#include <QJsonDocument>
#include <QJsonObject>
#include <QObject>
#include <QString>
#include <QStringList>

#include <cpr/cpr.h>

#include "../utils/ForwardDeclarations.hpp"

#include "../Competition.hpp"
#include "DivisionInterface.hpp"
#include "../utils/Helpers.hpp"
#include "../logging/Loggable.hpp"
#include "MeosInterface.hpp"
#include "ResultPackage.hpp"
#include "../Settings.hpp"
#include "WebserverInterface.hpp"

namespace divi
{
    class Coordinator : public QObject, public Loggable
    {
        Q_OBJECT
        
        public:
            Coordinator(QObject* a_parent = nullptr);
            ~Coordinator();

        public slots:
            void updateCache(Settings a_settings);
            void pingWebserver();
            void createCompetition(const Settings& a_request_settings);
            void updateMetadata();
            void updateResults(bool a_fresh_start);
            void deleteResults();
            void fetchAnalytics();
            void pingMeos();
            void fetchMetadataFromMeos();
        
        signals:
            void competitionCreated(std::optional<Settings> a_response_settings);
            void activelyProcessing(bool a_state);
            void metadataFetched(const Competition& a_competition);

        private:
            void updateWithMeosDivi(bool a_fresh_start);
            void updateWithDivi();
            void updateWithXmlDivi();
            void prepareWorkingDir();
            bool divisionResultsValid(const std::vector<ResultPackage>* a_results);

            Settings settings_cache;
            MeosInterface meos;
            DivisionInterface divisionsmatch;
            WebserverInterface webserver;
    };
}

#endif // __COORDINATOR_H__