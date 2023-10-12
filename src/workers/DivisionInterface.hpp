#ifndef __DIVISIONINTERFACE_H__
#define __DIVISIONINTERFACE_H__

#include <unordered_map>
#include <vector>

#include <QFile>
#include <QFileInfo>
#include <QIODevice>
#include <QProcess>
#include <QString>
#include <QStringBuilder>
#include <QTextStream>

#include <cpr/cpr.h>

#include "../utils/ForwardDeclarations.hpp"

#include "../Division.hpp"
#include "../logging/Loggable.hpp"
#include "../utils/Helpers.hpp"
#include "ResultPackage.hpp"
#include "../Settings.hpp"

#include "../logging/MessageType.hpp"
#include "../ResultSource.hpp"

namespace divi
{
    class DivisionInterface : public Loggable
    {
        public:
            DivisionInterface(Settings* a_settings);
            ~DivisionInterface();

            static const QString resultsHtmlEndpoint();

            const std::vector<ResultPackage>* loadResults();
        
        private:
            // Info server
            int useInfoServer();
            int fetchResultsFromInfoServer(const Division& a_division);

            // Command line
            int useCommandLine();

            int runDivisionResultCommand(const Division& a_division);
            int fetchResultsFromFile(const Division& a_division);

            bool diviExeExists();
            bool isDivisionValid(const Division& a_division);

            // Shared
            void packageResults(const Division& a_division, QTextStream& a_result_stream);

            Settings* settings;
            QProcess divi_process;
            std::vector<ResultPackage> results;

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

#endif // __DIVISIONINTERFACE_H__