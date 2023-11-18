#ifndef __FORWARDDECLARATIONS_H__
#define __FORWARDDECLARATIONS_H__

namespace divi
{
    class AboutDialog;
    class AlteredWizardPage;
    class CompatibilityWizardPage;
    class Competition;
    class CompetitionCreationWizard;
    class ConfigValidator;
    class Coordinator;
    class Division;
    class DivisionEditor;
    class DivisionInterface;
    class DivisionTableModel;
    class Helpers;
    class Loggable;
    class Logger;
    class LoggerProxy;
    class LoggerRegistry;
    class MainWindow;
    class MeosInterface;
    class PersistentSettings;
    class ResponseWizardPage;
    class Settings;
    class SummaryTableModel;
    class UpdateDialog;
    class Version;
    class VersionNotifier;
    class WebserverInterface;

    template<typename ... Parameters> class SignalDebouncer;

    struct ResultPackage;

    enum class EditorMode;
    enum class LoggerMode;
    enum class MessageType;
    enum class PrintMode;
    enum class ResultSource;
    enum class UpdateStatus;
    enum class VersionComparison;
    enum class Visibility;
}

#endif // __FORWARDDECLARATIONS_H__