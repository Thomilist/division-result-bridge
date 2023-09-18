#ifndef __WEBSERVERINTERFACE_H__
#define __WEBSERVERINTERFACE_H__

#include <vector>

#include <QByteArray>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QObject>

#include <cpr/cpr.h>

#include "ForwardDeclarations.hpp"

#include "Competition.hpp"
#include "Division.hpp"
#include "Helpers.hpp"
#include "ResultPackage.hpp"
#include "Settings.hpp"

namespace divi
{
    class WebserverInterface : public QObject
    {
        Q_OBJECT
        
        public:
            WebserverInterface(Settings* a_settings, QObject* a_parent = nullptr);
            ~WebserverInterface();

            static const QString getMetadataAlias();
            static const QString getResultsAlias();
            static const QString getHtmlAlias();

            cpr::Response ping();
            cpr::Response create(const QString& a_password);
            cpr::Response updateMetadata();
            cpr::Response updateResults(std::vector<ResultPackage>& a_results);
        
        private:
            const QString getMetadataAsBase64String() const;
            Settings* settings;
    };
}

#endif // __WEBSERVERINTERFACE_H__