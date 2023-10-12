#ifndef __CONFIGVALIDATOR_H__
#define __CONFIGVALIDATOR_H__

#include <algorithm>
#include <array>
#include <map>
#include <set>

#include <QDir>
#include <QFileInfo>
#include <QRegularExpression>
#include <QRegularExpressionValidator>
#include <QString>
#include <QStringBuilder>
#include <QStringList>
#include <QTimeZone>
#include <QValidator>

#include "utils/ForwardDeclarations.hpp"

#include "Division.hpp"
#include "utils/Helpers.hpp"
#include "logging/Loggable.hpp"
#include "Settings.hpp"

#include "logging/MessageType.hpp"
#include "ResultSource.hpp"
#include "Visibility.hpp"

namespace divi
{
    class ConfigValidator : public Loggable
    {
        public:
            ConfigValidator(
                Settings* a_settings);
            ~ConfigValidator();

            int validate();
        
        private:
            // Compatibility
            int validateResultSource();

            // Competition
            int validateCompetitionID();
            int validatePassword();
            int validateName();
            int validateOrganiser();
            int validateDate();
            int validateTimeZone();
            int validateVisibility();

            // Divisions
            int validateDivisions();
            int validateDivisionIDs(const std::map<int, int>& a_id_uses);
            int validateDivisionNames(const std::map<QString, std::set<int>>& a_name_uses);
            int validateDivisionConfigs(const std::map<QString, std::set<int>>& a_config_uses);
            int validateDivisionAddresses(const std::map<QString, std::set<int>>& a_address_uses);

            // Online
            int validateWebserverAddress();
            int validateLiveresultsID();

            // Result source
            int validateDiviExePath();
            int validateMeosInfoServerAddress();
            int validateXmlResultPath();

            // Run
            int validateWorkingDir();
            int validateUpdateInterval();

            void warn(const QString& a_subject, const QString& a_message);
            void summarise(int a_issues);
            static const QString humanDivisionIdList(const std::set<int> a_ids);

            Settings* settings;
            QString disclaimer;
            const QString log_source_label{"Internal / Validate Config"};
            QRegularExpression address_regex{"^https?:\\/\\/(?:(?:localhost(?::\\d{0,5}))|(?:(?:\\d{1,3}\\.){3}\\d{1,3})|(?=(?:.{1,255}(?:\\/|$)))(?:[a-zA-Z0-9]{1}(?=.{1,62}\\.)(?:[a-zA-Z0-9-]*[a-zA-Z0-9]{1})\\.)*(?:[a-zA-Z0-9]{1}(?=.{1,62}(?:\\/|$))(?:[a-zA-Z0-9-]*[a-zA-Z0-9]{1})){1})(?:\\/(?:meos)?)?$"};
            QRegularExpressionValidator address_validator{address_regex};
    };
}

#endif // __CONFIGVALIDATOR_H__