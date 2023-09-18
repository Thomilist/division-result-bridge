#ifndef __VERSION_H__
#define __VERSION_H__

#include <iostream>

#include <optional>
#include <sstream>
#include <string>
#include <vector>

#include <QSettings>
#include <QString>
#include <QDateTime>

#include <cpr/cpr.h>
#include <nlohmann/json.hpp>

#include "ForwardDeclarations.hpp"

#include "Helpers.hpp"
#include "UpdateStatus.hpp"

namespace divi
{
    class Version : public QSettings
    {
        public:
            Version(QString a_version_string);
            ~Version();

            QString getCurrentVersion();
            void setCurrentVersion(QString a_version);
            bool checkedRecently();
            UpdateStatus isUpdateAvailable();
            QString getUpstreamVersion();
        
        private:
            void load();
            void save();
            std::string fetchJSONFromGithub();
            std::optional<std::string> readVersionFromJSON(std::string a_json_string);
            std::vector<int> toDigits(std::string a_version);
            bool isNewerThanCurrent(std::string a_version);

            QString current_version;
            QString upstream_version;
            std::vector<int> current_version_digits;
            QDateTime last_checked;
            // Last 24 hours considered "recent"
            const qint64 recency_threshold = 60 * 60 * 24;
    };
}

#endif // __VERSION_H__