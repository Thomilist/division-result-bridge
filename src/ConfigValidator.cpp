#include "ConfigValidator.hpp"


namespace divi
{
    ConfigValidator::ConfigValidator(Settings* a_settings)
        : Loggable(Helpers::loggableConfigValidator())
        , settings(a_settings)
    {
        attachLogging(Helpers::loggerFile());
        attachLogging(Helpers::loggerMain());
        
        disclaimer = QString()
        % "Reminder: "
        % "The configuration validator only checks if fields are meaningfully filled out, "
        % "and if file and directory paths lead to valid destinations. "
        % "It does not verify the contents of files, the validity of credentials, the status of network resources or the correctness of information. "
        % "Additionally, the address validation is not perfect, particularly for non-basic server configurations";
    }
    
    ConfigValidator::~ConfigValidator()
    { }
    
    int ConfigValidator::validate()
    {
        #ifdef Q_OS_WIN
        QNtfsPermissionCheckGuard ntfs_permissions;
        #endif
        
        int issues = 0;

        // Compatibility
        issues += validateResultSource();

        // Competition
        issues += validateCompetitionID();
        issues += validatePassword();
        issues += validateName();
        issues += validateOrganiser();
        issues += validateDate();
        issues += validateTimeZone();
        issues += validateVisibility();

        // Divisions
        issues += validateDivisions();

        // Online
        issues += validateWebserverAddress();
        issues += validateLiveresultsID();

        // Result source
        issues += validateDiviExePath();
        issues += validateMeosInfoServerAddress();
        issues += validateXmlResultPath();

        // Run
        issues += validateWorkingDir();
        issues += validateUpdateInterval();

        summarise(issues);

        return issues;
    }
    
    int ConfigValidator::validateResultSource()
    {
        int issues = 0;
        const auto result_source = settings->getResultSource();
        
        if (!std::ranges::contains(
            std::array{ResultSource::MeosDivi, ResultSource::Divi, ResultSource::XmlDivi}, 
            result_source))
        {
            warn("Result Source",
                QString()
                % "The result source compatibility setting is \""
                % Helpers::resultSource(result_source)
                % "\", but it must be either \""
                % Helpers::resultSource(ResultSource::MeosDivi)
                % "\", \""
                % Helpers::resultSource(ResultSource::Divi)
                % "\", or \""
                % Helpers::resultSource(ResultSource::XmlDivi)
                % "\"");
            ++issues;
        }

        return issues;
    }
    
    int ConfigValidator::validateCompetitionID()
    {
        int issues = 0;

        if (settings->getCompetition().getID() < 1)
        {
            warn("Competition ID", "The competition ID must be greater than 0");
            ++issues;
        }

        return issues;
    }
    
    int ConfigValidator::validatePassword()
    {
        int issues = 0;

        if (settings->getCompetition().getPassword().isEmpty())
        {
            warn("Password", "The password is empty");
            ++issues;
        }

        return issues;
    }
    
    int ConfigValidator::validateName()
    {
        int issues = 0;

        if (settings->getCompetition().getName().isEmpty())
        {
            warn("Competition Name", "No competition name specified");
            ++issues;
        }

        return issues;
    }
    
    int ConfigValidator::validateOrganiser()
    {
        int issues = 0;

        if (settings->getCompetition().getOrganiser().isEmpty())
        {
            warn("Organiser", "No organiser specified");
            ++issues;
        }

        return issues;
    }
    
    int ConfigValidator::validateDate()
    {
        int issues = 0;
        const auto date = settings->getCompetition().getDate();

        if (date.isEmpty())
        {
            warn("Date", "The date is empty");
            ++issues;
        }
        else if (!QDate::fromString(date, Helpers::dateFormat()).isValid())
        {
            warn("Date", "The date \"" % date % "\" is invalid");
            ++issues;
        }

        return issues;
    }
    
    int ConfigValidator::validateTimeZone()
    {
        int issues = 0;
        const auto time_zone_iana = settings->getCompetition().getTimeZone();
        
        if (time_zone_iana.isEmpty())
        {
            warn("Time Zone", "The time zone is empty");
            ++issues;
        }
        else if (!QTimeZone(time_zone_iana.toUtf8()).isValid())
        {
            warn("Time Zone", "\"" % time_zone_iana % "\" is not a valid IANA time zone ID");
            ++issues;
        }

        return issues;
    }
    
    int ConfigValidator::validateVisibility()
    {
        int issues = 0;
        const auto visibility_string = settings->getCompetition().getVisibility();
        const auto visibility = Helpers::visibility(visibility_string);
        
        if (!std::ranges::contains(
            std::array{Visibility::PUBLIC, Visibility::HIDDEN, Visibility::PRIVATE}, 
            visibility))
        {
            warn("Visibility",
                QString()
                % "The visibility setting is \""
                % visibility_string
                % "\", but it must be either \""
                % Helpers::visibility(Visibility::PUBLIC)
                % "\", \""
                % Helpers::visibility(Visibility::HIDDEN)
                % "\", or \""
                % Helpers::visibility(Visibility::PRIVATE)
                % "\"");
            ++issues;
        }

        return issues;
    }
    
    int ConfigValidator::validateDivisions()
    {
        int issues = 0;

        std::map<int, int> id_uses;
        std::map<QString, std::set<int>> name_uses;
        std::map<QString, std::set<int>> config_uses;
        std::map<QString, std::set<int>> address_uses;

        int id;
        QString name;
        QString config;
        QString address;

        // Collect usage information...
        if (const auto& divisions = settings->getDivisions(); divisions.size() > 0)
        {
            for (const auto& division : divisions)
            {
                id = division.getID();
                name = division.getName();
                config = division.getConfigPath();
                address = division.getInfoServerAddress();

                if (id_uses.contains(id))
                {
                    ++id_uses.at(id);
                }
                else
                {
                    id_uses.insert({id, 1});
                }

                if (name_uses.contains(name))
                {
                    name_uses.at(name).insert(id);
                }
                else
                {
                    name_uses.insert({name, {id}});
                }

                if (config_uses.contains(config))
                {
                    config_uses.at(config).insert(id);
                }
                else
                {
                    config_uses.insert({config, {id}});
                }

                if (address_uses.contains(address))
                {
                    address_uses.at(address).insert(id);
                }
                else
                {
                    address_uses.insert({address, {id}});
                }
            }
        
            issues += validateDivisionIDs(id_uses);
            issues += validateDivisionNames(name_uses);
            issues += validateDivisionConfigs(config_uses);
            issues += validateDivisionAddresses(address_uses);
        }
        // ... or note a lack of divisions
        else
        {
            warn("Divisions", "No divisions defined");
            ++issues;
        }

        return issues;
    }
    
    int ConfigValidator::validateDivisionIDs(const std::map<int, int>& a_id_uses)
    {
        int issues = 0;
        
        for (const auto& id : a_id_uses)
        {
            if (id.first < 1)
            {
                warn("Divisions / ID", "Divisions IDs must be greater than 0");
                issues += id.second;
            }

            if (id.second > 1)
            {
                warn("Divisions / ID",
                    QString()
                    % "Duplicate division IDs are not allowed. "
                    % "The ID ["
                    % QString::number(id.first)
                    % "] is used "
                    % QString::number(id.second)
                    % " times");
                issues += id.second - 1;
            }
        }

        return issues;
    }
    
    int ConfigValidator::validateDivisionNames(const std::map<QString, std::set<int>>& a_name_uses)
    {
        int issues = 0;

        for (const auto& name : a_name_uses)
        {
            if (name.first.isEmpty())
            {
                warn("Divisions / Name",
                    QString()
                    % "No name specified for "
                    % (name.second.size() == 1 ? "division " : "divisions ")
                    % humanDivisionIdList(name.second));
                issues += name.second.size();
            }
            else
            {
                if (name.first.length() > 32)
                {
                    warn("Divisions / Name",
                        QString()
                        % "The name \""
                        % name.first
                        % "\" is quite long, which may cause issues when viewing division results on mobile. "
                        % "It is used by "
                        % (name.second.size() == 1 ? "division " : "divisions ")
                        % humanDivisionIdList(name.second));
                    issues += name.second.size();
                }

                if (name.second.size() > 1)
                {
                    warn("Divisions / Name",
                        QString()
                        % "Duplicate division names are not recommended. "
                        % "The divisions "
                        % humanDivisionIdList(name.second)
                        % " are all named \""
                        % name.first
                        % "\"");
                    issues += name.second.size() - 1;
                }
            }
        }

        return issues;
    }
    
    int ConfigValidator::validateDivisionConfigs(const std::map<QString, std::set<int>>& a_config_uses)
    {
        switch (settings->getResultSource())
        {
            case ResultSource::MeosDivi:
            case ResultSource::XmlDivi:
            {
                break;
            }
            default:
            {
                return 0;
            }
        }
        
        int issues = 0;

        for (const auto& config : a_config_uses)
        {
            if (config.first.isEmpty())
            {
                warn("Divisions / Config Path",
                    QString()
                    % "No config path specified for "
                    % (config.second.size() == 1 ? "division " : "divisions ")
                    % humanDivisionIdList(config.second));
                issues += config.second.size();
            }
            else
            {
                if (config.second.size() > 1)
                {
                    warn("Divisions / Config Path",
                        QString()
                        % "Different divisions usually need different configurations. "
                        % "The divisions "
                        % humanDivisionIdList(config.second)
                        % (config.second.size() > 2 ? " all " : " both ")
                        % "use the config path \""
                        % config.first
                        % "\"");
                    issues += config.second.size() - 1;
                }
                
                QFileInfo file{config.first};
                
                if (!file.exists())
                {
                    warn("Divisions / Config Path",
                        QString()
                        % "No config file was found on the path \""
                        % config.first
                        % "\". It is used by "
                        % (config.second.size() == 1 ? "division " : "divisions ")
                        % humanDivisionIdList(config.second));
                    issues += config.second.size();
                }
                else if (!file.isReadable())
                {
                    warn("Divisions / Config Path",
                        QString()
                        % "The config file on the path \""
                        % config.first
                        % "\" is not readable. It is used by "
                        % (config.second.size() == 1 ? "division " : "divisions ")
                        % humanDivisionIdList(config.second));
                    issues += config.second.size();
                }
            }
        }

        return issues;
    }
    
    int ConfigValidator::validateDivisionAddresses(const std::map<QString, std::set<int>>& a_address_uses)
    {
        switch (settings->getResultSource())
        {
            case ResultSource::Divi:
            {
                break;
            }
            default:
            {
                return 0;
            }
        }
        
        int issues = 0;

        for (const auto& address : a_address_uses)
        {
            if (address.first.isEmpty())
            {
                warn("Divisions / Info Server Address",
                    QString()
                    % "No address specified for "
                    % (address.second.size() == 1 ? "division " : "divisions ")
                    % humanDivisionIdList(address.second));
                issues += address.second.size();
            }
            else
            {
                if (address.second.size() > 1)
                {
                    warn("Divisions / Info Server Address",
                        QString()
                        % "Different divisions usually need different configurations. "
                        % "The divisions "
                        % humanDivisionIdList(address.second)
                        % (address.second.size() > 2 ? " all " : " both ")
                        % "use the information server address \""
                        % address.first
                        % "\"");
                    issues += address.second.size() - 1;
                }

                QString mutable_address = address.first;
                
                if (int pos; address_validator.validate(mutable_address, pos) != QValidator::Acceptable)
                {
                    warn("Divisions / Info Server Address",
                        QString()
                        % "The information server address \""
                        % address.first
                        % "\" may not be valid"
                        % (address.first.indexOf("http") != 0 ? " - have you specified the protocol (http, https etc.)? " : ". ")
                        % "It is used by "
                        % (address.second.size() == 1 ? "division " : "divisions ")
                        % humanDivisionIdList(address.second));
                    issues += address.second.size();
                }
            }
        }

        return issues;
    }
    
    int ConfigValidator::validateWebserverAddress()
    {
        int issues = 0;
        auto address = settings->getWebserverAddress();

        if (address.isEmpty())
        {
            warn("Division Result Server Address", "No address specified");
            ++issues;
        }
        else if (int pos; address_validator.validate(address, pos) != QValidator::Acceptable)
        {
            warn("Division Result Server Address",
                QString()
                % "The address \""
                % address
                % "\" may not be valid"
                % (address.indexOf("http") != 0 ? " - have you specified the protocol (http, https etc.)?" : QString()));
            ++issues;
        }
        
        return issues;
    }
    
    int ConfigValidator::validateLiveresultsID()
    {
        int issues = 0;
        const auto liveresults_id = settings->getCompetition().getLiveresultsID();

        if (liveresults_id < 1)
        {
            warn("liveresultat.orientering.se ID",
                QString()
                % "The competition ID for liveresultat.orientering.se is not greater than 0, "
                % "so a link will not be added to the division result page. "
                % "If intentional, you can safely ignore this warning");
            ++issues;
        }

        return issues;
    }
    
    int ConfigValidator::validateDiviExePath()
    {
        switch (settings->getResultSource())
        {
            case ResultSource::MeosDivi:
            case ResultSource::XmlDivi:
            {
                break;
            }
            default:
            {
                return 0;
            }
        }
        
        int issues = 0;
        const auto path = settings->getDiviExePath();
        QFileInfo file{path};

        if (path.isEmpty())
        {
            warn(Helpers::diviExeName() % " Path", "The path to \"" % Helpers::diviExeName() % "\" is not specified");
            ++issues;
        }
        else if (!file.exists())
        {
            warn(Helpers::diviExeName() % " Path", "\"" % Helpers::diviExeName() % "\" was not found on the path \"" % path % "\"");
            ++issues;
        }
        else if (!file.isExecutable())
        {
            warn(Helpers::diviExeName() % " Path", "\"" % Helpers::diviExeName() % "\" on the path \"" % path % "\" is not executable");
            ++issues;
        }

        return issues;
    }
    
    int ConfigValidator::validateMeosInfoServerAddress()
    {
        switch (settings->getResultSource())
        {
            case ResultSource::MeosDivi:
            {
                break;
            }
            default:
            {
                return 0;
            }
        }
        
        int issues = 0;
        auto address = settings->getMeosAddress();

        if (address.isEmpty())
        {
            warn("MeOS Info Server Address", "No address specified");
            ++issues;
        }
        else if (int pos; address_validator.validate(address, pos) != QValidator::Acceptable)
        {
            warn("MeOS Info Server Address",
                QString()
                % "The address \""
                % address
                % "\" may not be valid"
                % (address.indexOf("http") != 0 ? " - have you specified the protocol (http, https etc.)?" : QString()));
            ++issues;
        }

        return issues;
    }
    
    int ConfigValidator::validateXmlResultPath()
    {
        switch (settings->getResultSource())
        {
            case ResultSource::XmlDivi:
            {
                break;
            }
            default:
            {
                return 0;
            }
        }
        
        int issues = 0;
        const auto path = settings->getXmlResultPath();
        QFileInfo file{path};

        if (path.isEmpty())
        {
            warn("IOF XML Results Path", "The path to the IOF XML 3.0 results file is not specified");
            ++issues;
        }
        else if (!file.exists())
        {
            warn("IOF XML Results Path", "The IOF XML 3.0 results file was not found on the path \"" % path % "\"");
            ++issues;
        }
        else if (!file.isReadable())
        {
            warn("IOF XML Results Path", "The IOF XML 3.0 results file on the path \"" % path % "\" is not readable");
            ++issues;
        }

        return issues;
    }
    
    int ConfigValidator::validateWorkingDir()
    {
        int issues = 0;
        const auto path = settings->getWorkingDir();
        QFileInfo working_dir = QFileInfo{path};

        if (path.isEmpty())
        {
            warn("Working Directory", "No working directory specified");
            ++issues;
        }
        else if (!working_dir.exists())
        {
            warn("Working Directory", "The path \"" % path % "\" does not exist");
            ++issues;
        }
        else if (!working_dir.isDir())
        {
            warn("Working Directory", "The path \"" % path % "\" does not point to directory");
            ++issues;
        }
        else if (!working_dir.isReadable())
        {
            warn("Working Directory", "The directory at \"" % path % "\" is not readable");
            ++issues;
        }
        else if (!working_dir.isWritable())
        {
            warn("Working Directory", "The directory at \"" % path % "\" is not writable");
            ++issues;
        }

        return issues;
    }
    
    int ConfigValidator::validateUpdateInterval()
    {
        int issues = 0;
        const auto interval = settings->getUpdateInterval();
        
        if (interval < 10)
        {
            warn("Update Interval",
                QString()
                % "Update intervals shorter than 10 seconds are not recommended "
                % "(and shouldn't be possible to specify - how did you do that?)");
            ++issues;
        }
        else if (interval > 600)
        {
            warn("Update Interval",
                QString()
                % "All this effort to set up live results, "
                % "and then you only want to update every "
                % QString::number(interval / 60)
                % " minutes? "
                % "To be clear, this is will not cause any (technical) problems, "
                % "but I will judge you");
            ++issues;
        }

        return issues;
    }
    
    void ConfigValidator::warn(const QString& a_subject, const QString& a_message)
    {
        log(MessageType::Warning, log_source_label, 0, a_subject, a_message);
        return;
    }
    
    void ConfigValidator::summarise(int a_issues)
    {
        const QString status_text = QString()
            % "Found "
            % QString::number(a_issues)
            % (a_issues > 0 ? " Potential" : QString())
            % (a_issues == 1 ? " Issue" : " Issues");
        
        log(MessageType::Info, log_source_label, 0, status_text, disclaimer);
        return;
    }
    
    const QString ConfigValidator::humanDivisionIdList(const std::set<int> a_ids)
    {
        if (a_ids.empty())
        {
            return QString();
        }
        else if (a_ids.size() == 1)
        {
            return "[" % QString::number(*a_ids.begin()) % "]";
        }

        QStringList id_strings;

        for (const auto& id : a_ids)
        {
            id_strings.push_back("[" % QString::number(id) % "]");
        }

        QString last_part = id_strings.back();
        id_strings.pop_back();
        QString first_part = id_strings.join(", ");
        QStringList both_parts{first_part, last_part};

        return both_parts.join(" and ");
    }
}