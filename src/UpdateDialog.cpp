#include "UpdateDialog.hpp"


namespace divi
{
    UpdateDialog::UpdateDialog(Version* a_version, QWidget* a_parent)
        : QDialog(a_parent, QDialog().windowFlags() & ~Qt::WindowContextHelpButtonHint)
        , version(a_version)
        , buttons(QDialogButtonBox::Ok)
    {
        setModal(true);
        setWindowTitle("Check for updates");
        connect(&buttons, &QDialogButtonBox::accepted, this, &QDialog::accept);

        update_text.setTextFormat(Qt::RichText);
        update_text.setTextInteractionFlags(Qt::TextBrowserInteraction);
        update_text.setOpenExternalLinks(true);
        update_text.setAlignment(Qt::AlignCenter);

        grid_layout.addWidget(&update_text, 0, 0, Qt::AlignCenter);
        grid_layout.addWidget(&buttons, 1, 0, Qt::AlignCenter);
        setLayout(&grid_layout);
    }
    
    UpdateDialog::~UpdateDialog()
    { }
    
    void UpdateDialog::manualUpdateCheck()
    {
        open(version->isUpdateAvailable(), false);
        return;
    }
    
    void UpdateDialog::open(UpdateStatus a_update_status, bool a_quiet)
    {
        switch (a_update_status)
        {
            case UpdateStatus::NewerAvailable:
            {
                createNewVersionAvailable();
                break;
            }
            case UpdateStatus::UpToDate:
            {
                if (a_quiet)
                {
                    return;
                }

                createYouHaveLatestVersion();
                break;
            }
            case UpdateStatus::Inaccessible:
            {
                createInaccessible();
                break;
            }
            case UpdateStatus::Unknown:
            {
                createUnknown();
                break;
            }
        }

        QDialog::open();
        return;
    }
    
    void UpdateDialog::createYouHaveLatestVersion()
    {
        update_text.setText(
            QString()
            % "You have the latest version ("
            % version->getCurrentVersion()
            % ")."
        );

        return;
    }
    
    void UpdateDialog::createNewVersionAvailable()
    {
        update_text.setText(
            QString()
            % "There is a newer version available online.<br>"
            % "You have version "
            % version->getCurrentVersion()
            % ", but version "
            % version->getUpstreamVersion()
            % " is available for download "
            % "<a style=\"color:#1d99f3\" href=\""
            % Helpers::gitHubReleaseUrl()
            % "\">here</a>."
        );

        return;
    }
    
    void UpdateDialog::createInaccessible()
    {
        update_text.setText(
            QString()
            % "Unable to check for updates.<br>"
            % "Please try again later."
        );

        return;
    }
    
    void UpdateDialog::createUnknown()
    {
        update_text.setText(
            QString()
            % "This message should never be shown.<br>"
            % "Congratulations?"
        );

        return;
    }
}