#include "CompatibilityWizardPage.hpp"


namespace divi
{
    CompatibilityWizardPage::CompatibilityWizardPage(Settings* a_creation_settings, QWidget* a_parent)
        : QWizardPage(a_parent)
        , creation_settings(a_creation_settings)
    {
        label.setWordWrap(true);
        label.setText(
            QString()
            % "Results can be fetched in three different ways. "
            % "Choose the method that best fits your setup. "
            % "You can always change this later with no data loss. ");

        meos_divi_button.setText(Helpers::meosName() % " + " % Helpers::diviNameLong());
        divi_button.setText(Helpers::diviNameLong());
        xml_divi_button.setText("IOF XML 3.0 file + " % Helpers::diviNameLong());

        for (const auto& button_value :
        {
            std::pair{&meos_divi_button, ResultSource::MeosDivi},
            std::pair{&divi_button, ResultSource::Divi},
            std::pair{&xml_divi_button, ResultSource::XmlDivi}
        })
        {
            button_values.insert(button_value);
        }

        button_group.addButton(&meos_divi_button);
        button_group.addButton(&divi_button);
        button_group.addButton(&xml_divi_button);

        description.setWordWrap(true);
        description.setTextFormat(Qt::RichText);

        int layout_row = 0;

        layout.addWidget(&label, layout_row++, 0);

        layout.setRowMinimumHeight(layout_row++, 10);

        layout.addWidget(&meos_divi_button, layout_row++, 0);
        layout.addWidget(&divi_button, layout_row++, 0);
        layout.addWidget(&xml_divi_button, layout_row++, 0);

        layout.setRowMinimumHeight(layout_row++, 10);

        layout.addWidget(&description, layout_row++, 0);

        setLayout(&layout);

        connect(&button_group, &QButtonGroup::buttonClicked, this, &CompatibilityWizardPage::updateSelection);
    }
    
    CompatibilityWizardPage::~CompatibilityWizardPage()
    { }
    
    bool CompatibilityWizardPage::isComplete() const 
    {
        for (auto button : button_group.buttons())
        {
            if (button->isChecked())
            {
                return true;
            }
        }
        
        return false;
    }
    
    void CompatibilityWizardPage::populate()
    {
        for (auto& [button, source] : button_values)
        {
            if (creation_settings->getResultSource() == source)
            {
                button->setChecked(true);
                updateSelection(button);
                break;
            }
        }

        updateDescription();
        return;
    }
    
    void CompatibilityWizardPage::updateDescription()
    {
        switch (creation_settings->getResultSource())
        {
            case ResultSource::MeosDivi:
            {
                description.setText(
                    QString()
                    % "<i>"
                    % "Metadata can be fetched directly from "
                    % Helpers::meosName()
                    % ", and results are uploaded on a timer, "
                    % "but only when they have changed. "
                    % Helpers::diviNameLong()
                    % " is run automatically from the command line."
                    % "</i>");
                break;
            }
            case ResultSource::Divi:
            {
                description.setText(
                    QString()
                    % "<i>"
                    % "Results are fetched on a timer directly from "
                    % Helpers::diviNameLong()
                    % " through its information server. "
                    % "One instance per division must be kept open. "
                    % "This is independent of the underlying timing setup and has great performance, "
                    % "but it does not check for changes before uploading."
                    % "</i>");
                break;
            }
            case ResultSource::XmlDivi:
            {
                description.setText(
                    QString()
                    % "<i>"
                    % "Results are loaded from an IOF XML 3.0 file whenever it changes, "
                    % "independent of its source. "
                    % Helpers::diviNameLong()
                    % " is run automatically from the command line."
                    % "</i>");
                break;
            }
            default:
            {
                description.setText(
                    QString()
                    % "<i>"
                    % "Choose an option to see more details."
                    % "</i>");
                break;
            }
        }

        return;
    }
    
    void CompatibilityWizardPage::updateSelection(QAbstractButton* a_button)
    {
        if (button_values.contains(a_button))
        {
            creation_settings->setResultSource(button_values[a_button]);
        }
        else
        {
            creation_settings->setResultSource(ResultSource::_Undefined);
        }

        updateDescription();
        emit completeChanged();
        return;
    }
}