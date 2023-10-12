#ifndef __MEOSINTERFACE_H__
#define __MEOSINTERFACE_H__

#include <optional>
#include <string>

#include <QFile>
#include <QIODevice>
#include <QString>
#include <QStringBuilder>
#include <QStringList>
#include <QTextStream>

#include <cpr/cpr.h>
#include <pugixml.hpp>

#include "../utils/ForwardDeclarations.hpp"

#include "../Competition.hpp"
#include "../utils/Helpers.hpp"
#include "../logging/Loggable.hpp"
#include "../Settings.hpp"

#include "../logging/MessageType.hpp"

namespace divi
{
    class MeosInterface : public Loggable
    {
        public:
            MeosInterface(Settings* a_settings);
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