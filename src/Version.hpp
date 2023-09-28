#ifndef __VERSION_H__
#define __VERSION_H__

#include <optional>
#include <ranges>
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
#include "VersionComparison.hpp"

namespace divi
{
    class Version : public QSettings
    {
        public:
            Version(QString a_version_string);
            ~Version();

            static VersionComparison compare(const QString& a_baseline, const QString& a_other);
            static VersionComparison compare(const std::string& a_baseline, const std::string& a_other);

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
            static std::vector<int> toDigits(std::string a_version);
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