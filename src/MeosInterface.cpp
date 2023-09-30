#include "MeosInterface.hpp"


namespace divi
{
    MeosInterface::MeosInterface(
        Settings* a_settings,
        Logger* a_log,
        QObject* a_parent)
        : Loggable(a_log, a_parent)
        , settings(a_settings)
    {
        resetDifference();
    }
    
    MeosInterface::~MeosInterface()
    { }
    
    const QString MeosInterface::statusEndpoint()
    {
        return "?get=status";
    }
    
    const QString MeosInterface::competitionEndpoint()
    {
        return "?get=competition";
    }
    
    const QString MeosInterface::changesEndpoint(const std::string& a_difference)
    {
        return QString()
            % "?difference="
            % QString::fromStdString(a_difference);
    }
    
    const QString MeosInterface::resultsEndpoint()
    {
        return "?get=iofresult";
    }
    
    const char* MeosInterface::MOPCompleteXmlTag()
    {
        return "MOPComplete";
    }
    
    const char* MeosInterface::MOPDiffXmlTag()
    {
        return "MOPDiff";
    }
    
    const char* MeosInterface::nextDifferenceXmlAttribute()
    {
        return "nextdifference";
    }
    
    const char* MeosInterface::competitionXmlTag()
    {
        return "competition";
    }
    
    const char* MeosInterface::dateXmlAttribute()
    {
        return "date";
    }
    
    const char* MeosInterface::organiserXmlAttribute()
    {
        return "organizer";
    }
    
    const char* MeosInterface::statusXmlTag()
    {
        return "status";
    }
    
    const char* MeosInterface::versionXmlAttribute()
    {
        return "version";
    }
    
    void MeosInterface::ping()
    {
        cpr::Response response = cpr::Get
        (
            cpr::Url{QString(settings->getMeosAddress() % statusEndpoint()).toStdString()},
            cpr::Header
            {
                Helpers::userAgentHeaderField(),
                {"Accept", "application/xml"}
            }
        );

        log("MeOS / Test", response);

        if (response.status_code == 200)
        {
            validatePingResponse(response);
        }

        return;
    }
    
    const std::optional<Competition> MeosInterface::fetchMetadata()
    {
        cpr::Response response = cpr::Get
        (
            cpr::Url{QString(settings->getMeosAddress() % competitionEndpoint()).toStdString()},
            cpr::Header
            {
                Helpers::userAgentHeaderField(),
                {"Accept", "application/xml"}
            }
        );

        log("MeOS / Fetch Metadata", response);

        if (response.status_code != 200)
        {
            return std::nullopt;
        }

        return extractCompetitionMetadata(response);
    }
    
    // Returns:
    // 0 on success
    // 1 when no changes found
    // 2 on results fetch error
    // 3 on results write error
    int MeosInterface::updateResults()
    {
        if (checkForChanges())
        {
            return 1;
        }
        
        if (fetchResults())
        {
            return 2;
        }

        if (writeResults())
        {
            return 3;
        }

        return 0;
    }
    
    void MeosInterface::resetDifference()
    {
        difference = "zero";
        return;
    }
    
    void MeosInterface::validatePingResponse(cpr::Response a_response)
    {
        bool success = true;
        pugi::xml_document status_xml;
        pugi::xml_parse_result parse_res = status_xml.load_string(a_response.text.c_str());

        if (!parse_res)
        {
            success = false;
            return;
        }
        else if (const QString meos_version = status_xml
            .child(MOPCompleteXmlTag())
            .child(statusXmlTag())
            .attribute(versionXmlAttribute())
            .as_string();
            !meos_version.isEmpty())
        {
            success = true;
            log(MessageType::Success, "Internal / Test", 0, "MeOS Available",
                QString()
                % "Found MeOS version "
                % meos_version);
        }
        else
        {
            success = false;
        }

        if (!success)
        {
            log(MessageType::Error, "Internal / Test", 0, "XML Parsing Error",
                "An error occured while parsing the status XML. Is this even a MeOS information server at all?");
        }

        return;
    }
    
    const std::optional<Competition> MeosInterface::extractCompetitionMetadata(cpr::Response a_response)
    {
        Competition competition;
        pugi::xml_document competition_xml;
        pugi::xml_parse_result parse_res = competition_xml.load_string(a_response.text.c_str());

        if (!parse_res)
        {
            log(MessageType::Error, "Internal / Fetch Metadata", 0, "XML Parsing Error",
                "An error occured while parsing the competition XML");
            return std::nullopt;
        }

        QStringList metadata_found;

        if (const QString competition_name = competition_xml
            .child(MOPCompleteXmlTag())
            .child(competitionXmlTag())
            .text()
            .as_string();
            !competition_name.isEmpty())
        {
            metadata_found.push_back(Competition::getNameAlias());
            competition.setName(competition_name);
        }

        if (const QString organiser = competition_xml
            .child(MOPCompleteXmlTag())
            .child(competitionXmlTag())
            .attribute(organiserXmlAttribute())
            .as_string();
            !organiser.isEmpty())
        {
            metadata_found.push_back(Competition::getOrganiserAlias());
            competition.setOrganiser(organiser);
        }

        if (const QString date = competition_xml
            .child(MOPCompleteXmlTag())
            .child(competitionXmlTag())
            .attribute(dateXmlAttribute())
            .as_string();
            !date.isEmpty())
        {
            metadata_found.push_back(Competition::getDateAlias());
            competition.setDate(date);
        }
        else
        {
            competition.setDate(QDate());
        }

        if (metadata_found.isEmpty())
        {
            log(MessageType::Info, "Internal / Fetch Metadata", 0, "No Metadata Found",
                "No values specified in MeOS for competition name, organiser or date");
            return std::nullopt;
        }
        else
        {
            log(MessageType::Success, "Internal / Fetch Metadata", 0, "Found Metadata",
                QString()
                % "Found: "
                % metadata_found.join(", "));
        }

        return competition;
    }
    
    // Returns:
    // 0 on success (changes found)
    // 1 on HTTP != 200
    // 2 on empty response text
    // 3 on XML parse error
    // 4 on identical text to previous (no update required)
    int MeosInterface::checkForChanges()
    {
        cpr::Response response = cpr::Get
        (
            cpr::Url{QString(settings->getMeosAddress() % changesEndpoint(difference)).toStdString()},
            cpr::Header
            {
                Helpers::userAgentHeaderField(),
                {"Accept", "application/xml"}
            }
        );

        log("MeOS / Check Results", response);

        if (response.status_code != 200)
        {
            resetDifference();
            return 1;
        }

        if (response.text.empty())
        {
            log(MessageType::Error, "Internal / Check Results", 0, "Empty Response",
                "MeOS successfully responded to the request, but no data was attached");
            resetDifference();
            return 2;
        }

        pugi::xml_document changes_xml;
        pugi::xml_parse_result parse_res = changes_xml.load_string(response.text.c_str());

        if (!parse_res)
        {
            log(MessageType::Error, "Internal / Check Results", 0, "XML Parsing Error",
                "An error occured while parsing the difference XML");
            resetDifference();
            return 3;
        }

        std::string element_name = difference == "zero" ? "MOPComplete" : "MOPDiff";
        std::string next_difference = changes_xml.child(element_name.c_str()).attribute("nextdifference").as_string();

        if (next_difference != difference)
        {
            log(MessageType::Success, "Internal / Check Results", 0, "Changes Found",
                QString()
                % "Difference tag: "
                % QString::fromStdString(difference)
                % " -> "
                % QString::fromStdString(next_difference));
            
            difference = next_difference;
            return 0;
        }

        log(MessageType::Success, "Internal / Check Results", 0, "Results Unchanged",
            "No changes detected since last fetch. Update skipped");

        return 4;
    }
    
    // Returns:
    // 0 on success
    // 1 on HTTP != 200
    // 2 on empty response text
    int MeosInterface::fetchResults()
    {
        cpr::Response response = cpr::Get
        (
            cpr::Url{QString(settings->getMeosAddress() % resultsEndpoint()).toStdString()},
            cpr::Header
            {
                Helpers::userAgentHeaderField(),
                {"Accept", "application/xml"}
            }
        );

        log("MeOS / Fetch Results", response);

        if (response.status_code != 200)
        {
            return 1;
        }

        if (response.text.empty())
        {
            log(MessageType::Error, "Internal / Fetch Results", 0, "Empty Response",
                "MeOS successfully responded to the request, but no data was attached");
            return 2;
        }

        results_xml = response.text;
        return 0;
    }
    
    // Returns true on success
    int MeosInterface::writeResults()
    {
        QFile results_xml_file{getOutputFile()};

        if (results_xml_file.open(QIODevice::WriteOnly | QIODevice::Text))
        {
            QTextStream results_xml_output{&results_xml_file};
            results_xml_output << QString::fromStdString(results_xml);

            log(MessageType::Success, "Internal / Write Results", 0, "Write Complete",
                "IOF XML results written successfully");
            return 0;
        }

        log(MessageType::Error, "Internal / Write Results", 0, "Write Error",
            "Unable to write IOF XML results");
        return 1;
    }
    
    const QString MeosInterface::getOutputFile()
    {
        return settings->getXMLResultPath();
    }
}