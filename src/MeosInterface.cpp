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
            cpr::Url{getChangesEndpoint()},
            cpr::Header
            {
                Helpers::userAgentHeaderField(),
                {"Accept", "application/xml"}
            }
        );

        emit log("MeOS", response);

        if (response.status_code != 200)
        {
            resetDifference();
            return 1;
        }

        if (response.text.empty())
        {
            emit log(
                MessageType::Error,
                "Internal", 0, "Empty Response",
                "MeOS successfully responded to the request, but no data was attached.");
            resetDifference();
            return 2;
        }

        pugi::xml_document changes_xml;
        pugi::xml_parse_result parse_res = changes_xml.load_string(response.text.c_str());

        if (!parse_res)
        {
            emit log(
                MessageType::Error,
                "Internal", 0, "XML Parsing Error",
                "An error occured while parsing the difference XML.");
            resetDifference();
            return 3;
        }

        std::string element_name = difference == "zero" ? "MOPComplete" : "MOPDiff";
        std::string next_difference = changes_xml.child(element_name.c_str()).attribute("nextdifference").as_string();

        if (next_difference != difference)
        {
            emit log(
                MessageType::Info,
                "Internal", 0, "Changes Found",
                QString()
                % "Difference tag: "
                % QString::fromStdString(difference)
                % " -> "
                % QString::fromStdString(next_difference));
            
            difference = next_difference;
            return 0;
        }

        emit log(
            MessageType::Info,
            "Internal", 0, "Results Unchanged",
            "No changes detected since last fetch. Update skipped.");

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
            cpr::Url{getResultsEndpoint()},
            cpr::Header
            {
                Helpers::userAgentHeaderField(),
                {"Accept", "application/xml"}
            }
        );

        emit log("MeOS", response);

        if (response.status_code != 200)
        {
            return 1;
        }

        if (response.text.empty())
        {
            emit log(
                MessageType::Error,
                "Internal", 0, "Empty Response",
                "MeOS successfully responded to the request, but no data was attached.");
            return 2;
        }

        results_xml = response.text;
        return 0;
    }
    
    // Returns true on success
    int MeosInterface::writeResults()
    {
        std::ofstream results_xml_file{getOutputFile()};

        if (results_xml_file.is_open())
        {
            results_xml_file << results_xml;
            emit log(
                MessageType::Info,
                "Internal", 0, "Write Complete",
                "IOF XML results written successfully.");
            return 0;
        }

        emit log(
            MessageType::Error,
            "Internal", 0, "Write Error",
            "Unable to write IOF XML results.");
        return 1;
    }
    
    const std::string MeosInterface::getChangesEndpoint()
    {
        QString endpoint
            = settings->getMeosAddress()
            % "?difference="
            % QString::fromStdString(difference);
        return endpoint.toStdString();
    }
    
    void MeosInterface::resetDifference()
    {
        difference = "zero";
        return;
    }
    
    const std::string MeosInterface::getResultsEndpoint()
    {
        QString endpoint
            = settings->getMeosAddress()
            % "?get=iofresult";
        return endpoint.toStdString();
    }
    
    const std::string MeosInterface::getOutputFile()
    {
        return settings->getXMLResultPath().toStdString();
    }
}