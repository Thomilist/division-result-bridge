#include "Version.hpp"


namespace divi
{
    Version::Version(QString a_version_string)
    {
        setCurrentVersion(a_version_string);
        current_version_digits = toDigits(a_version_string.toStdString());
        load();
    }
    
    Version::~Version()
    {
        save();
    }
    
    VersionComparison Version::compare(const QString& a_baseline, const QString& a_other)
    {
        return compare(a_baseline.toStdString(), a_other.toStdString());
    }
    
    VersionComparison Version::compare(const std::string& a_baseline, const std::string& a_other)
    {
        auto baseline_digits = toDigits(a_baseline);
        auto other_digits = toDigits(a_other);

        if (baseline_digits.size() != 3 || baseline_digits.size() != other_digits.size())
        {
            return VersionComparison::Undefined;
        }

        const std::vector<VersionComparison> newer_version{
            VersionComparison::NewerMajor,
            VersionComparison::NewerMinor,
            VersionComparison::NewerPatch
        };

        const std::vector<VersionComparison> older_version{
            VersionComparison::OlderMajor,
            VersionComparison::OlderMinor,
            VersionComparison::OlderPatch
        };

        auto items = std::views::zip(baseline_digits, other_digits, newer_version, older_version);

        for (const auto& [baseline_digit, other_digit, newer, older] : items)
        {
            if (other_digit > baseline_digit)
            {
                return newer;
            }
            else if (other_digit < baseline_digit)
            {
                return older;
            }
        }

        return VersionComparison::Equal;
    }
    
    QString Version::getCurrentVersion()
    {
        return current_version;
    }
    
    void Version::setCurrentVersion(QString a_version)
    {
        current_version = a_version;
        return;
    }
    
    bool Version::checkedRecently()
    {
        QDateTime current_time = QDateTime::currentDateTime();
        bool checked_recently = last_checked.secsTo(current_time) < recency_threshold;
        last_checked = current_time;
        return checked_recently;
    }
    
    UpdateStatus Version::isUpdateAvailable()
    {
        try
        {
            std::string all_releases_json = fetchJSONFromGithub();
            std::optional<std::string> latest_release_tag = readVersionFromJSON(all_releases_json);

            if (!latest_release_tag.has_value())
            {
                return UpdateStatus::Inaccessible;
            }

            upstream_version = QString::fromStdString(latest_release_tag.value());

            if (isNewerThanCurrent(latest_release_tag.value()))
            {
                return UpdateStatus::NewerAvailable;
            }
            else
            {
                return UpdateStatus::UpToDate;
            }
        }
        catch(const std::exception& e)
        {
            return UpdateStatus::Inaccessible;
        }
    }
    
    QString Version::getUpstreamVersion()
    {
        return upstream_version;
    }
    
    void Version::load()
    {
        last_checked = value("version/last_checked", "1970-01-01T00:00:00").toDateTime();
        return;
    }
    
    void Version::save()
    {
        setValue("version/last_checked", last_checked);
        return;
    }
    
    std::string Version::fetchJSONFromGithub()
    {
        cpr::Response response = cpr::Get
        (
            cpr::Url{Helpers::gitHubReleaseApiUrl().toStdString()},
            cpr::Header
            {
                Helpers::userAgentHeaderField(),
                {"accept", "application/json"}
            }
        );

        return response.text;
    }
    
    std::optional<std::string> Version::readVersionFromJSON(std::string a_json_string)
    {
        nlohmann::json json = nlohmann::json::parse(a_json_string);

        if (!json.is_array() && !json[0].contains("tag_name"))
        {
            return std::nullopt;
        }

        return json[0]["tag_name"];
    }
    
    std::vector<int> Version::toDigits(std::string a_version)
    {
        std::vector<int> digits;
        std::istringstream stream{a_version};
        std::string number;

        while (std::getline(stream, number, '.'))
        {
            digits.push_back(std::stoi(number));
        }

        return digits;
    }
    
    bool Version::isNewerThanCurrent(std::string a_version)
    {
        std::vector<int> version_digits = toDigits(a_version);

        for (size_t index = 0; index < version_digits.size(); ++index)
        {
            if (version_digits[index] > current_version_digits[index])
            {
                return true;
            }
        }

        return false;
    }
}