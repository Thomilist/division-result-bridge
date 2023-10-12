#ifndef __WEBSERVERINTERFACE_H__
#define __WEBSERVERINTERFACE_H__

#include <vector>

#include <QByteArray>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QString>

#include <cpr/cpr.h>

#include "../utils/ForwardDeclarations.hpp"

#include "../Competition.hpp"
#include "../Division.hpp"
#include "../utils/Helpers.hpp"
#include "../logging/Loggable.hpp"
#include "ResultPackage.hpp"
#include "../Settings.hpp"

namespace divi
{
    class WebserverInterface : public Loggable
    {
        public:
            WebserverInterface(Settings* a_settings);
            ~WebserverInterface();

            static const QString getMetadataAlias();
            static const QString getResultsAlias();
            static const QString getHtmlAlias();

            cpr::Response ping();
            cpr::Response create();
            cpr::Response updateMetadata();
            cpr::Response updateResults(const std::vector<ResultPackage>* a_results);
            cpr::Response deleteResults();
            cpr::Response fetchAnalytics();
        
        private:
            const QString getMetadataAsBase64String() const;
            Settings* settings;
    };
}

#endif // __WEBSERVERINTERFACE_H__