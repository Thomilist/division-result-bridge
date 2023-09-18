#include "MeosInterface.hpp"


namespace divi
{
    MeosInterface::MeosInterface(
        Settings* a_settings,
        Logger* a_log,
        QObject* a_parent)
        : Loggable(a_log, a_parent)
        , settings(a_settings)
    { }
    
    MeosInterface::~MeosInterface()
    { }
    
    int MeosInterface::updateResults()
    {
        if (fetchResults())
        {
            return 1;
        }

        if (writeResults())
        {
            return 2;
        }

        return 0;
    }
    
    // Returns 0 on success
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

        if (response.text.empty())
        {
            return 1;
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
            emit log("File", 0, "Write Complete", "IOF XML results written successfully.");
            return 0;
        }

        emit log("File", 0, "Write Error", "Unable to write IOF XML results.");
        return 1;
    }
    
    const std::string MeosInterface::getResultsEndpoint()
    {
        QString endpoint = settings->getMeosAddress() % "?get=iofresult";
        return endpoint.toStdString();
    }
    
    const std::string MeosInterface::getOutputFile()
    {
        return settings->getXMLResultPath().toStdString();
    }
}