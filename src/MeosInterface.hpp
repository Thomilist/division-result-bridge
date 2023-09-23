#ifndef __MEOSINTERFACE_H__
#define __MEOSINTERFACE_H__

#include <iostream>

#include <fstream>
#include <string>

#include <QObject>
#include <QString>
#include <QStringBuilder>

#include <cpr/cpr.h>
#include <pugixml.hpp>

#include "ForwardDeclarations.hpp"

#include "Helpers.hpp"
#include "Loggable.hpp"
#include "Logger.hpp"
#include "Settings.hpp"

#include "MessageType.hpp"

namespace divi
{
    class MeosInterface : public Loggable
    {
        Q_OBJECT

        public:
            MeosInterface(
                Settings* a_settings,
                Logger* a_log,
                QObject* a_parent = nullptr);
            ~MeosInterface();

            int updateResults();
            void resetDifference();
        
        private:
            int checkForChanges();
            int fetchResults();
            int writeResults();

            const std::string getChangesEndpoint();
            const std::string getResultsEndpoint();
            const std::string getOutputFile();

            Settings* settings;
            std::string results_xml;
            std::string difference;
    };
}

#endif // __MEOSINTERFACE_H__