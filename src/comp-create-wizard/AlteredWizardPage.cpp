#include "AlteredWizardPage.hpp"


namespace divi
{
    AlteredWizardPage::AlteredWizardPage(QWidget* a_parent)
        : QWizardPage(a_parent)
    { }
    
    AlteredWizardPage::~AlteredWizardPage()
    { }
    
    void AlteredWizardPage::registerField(
        const QString& a_name,
        QWidget* a_widget,
        const char* a_property,
        const char* a_changed_signal)
    {
        QWizardPage::registerField(
            a_name,
            a_widget,
            a_property,
            a_changed_signal);
        return;
    }
}