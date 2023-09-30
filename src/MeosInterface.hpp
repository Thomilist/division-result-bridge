#ifndef __MEOSINTERFACE_H__
#define __MEOSINTERFACE_H__

#include <optional>
#include <string>

#include <QFile>
#include <QIODevice>
#include <QObject>
#include <QString>
#include <QStringBuilder>
#include <QStringList>
#include <QTextStream>

#include <cpr/cpr.h>
#include <pugixml.hpp>

#include "ForwardDeclarations.hpp"

#include "Competition.hpp"
#include "Helpers.hpp"
#include "Loggable.hpp"
#include "Logger.hpp"
#include "Settings.hpp"

#include "MessageType.hpp"

namespace divi
{
    class MeosInterface : public Loggable
    {
        public:
            MeosInterface(
                Settings* a_settings,
                Logger* a_log,
                QObject* a_parent = nullptr);
            ~MeosInterface();

            static const QString statusEndpoint();
            static const QString competitionEndpoint();
            static const QString changesEndpoint(const std::string& a_difference = "zero");
            static const QString resultsEndpoint();

            static const char* MOPCompleteXmlTag();
            static const char* MOPDiffXmlTag();
            static const char* nextDifferenceXmlAttribute();
            static const char* competitionXmlTag();
            static const char* dateXmlAttribute();
            static const char* organiserXmlAttribute();
            static const char* statusXmlTag();
            static const char* versionXmlAttribute();

            void ping();
            const std::optional<Competition> fetchMetadata();
            int updateResults();
            void resetDifference();
        
        private:
            void validatePingResponse(cpr::Response a_response);
            const std::optional<Competition> extractCompetitionMetadata(cpr::Response a_response);
            int checkForChanges();
            int fetchResults();
            int writeResults();
            const QString getOutputFile();

            Settings* settings;
            std::string results_xml;
            std::string difference;
    };
}

#endif // __MEOSINTERFACE_H__