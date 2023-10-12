#include "ResponseWizardPage.hpp"


namespace divi
{
    ResponseWizardPage::ResponseWizardPage(Logger* a_logger, QWidget* a_parent)
        : QWizardPage(a_parent)
        , logger(a_logger)
    {
        layout.addWidget(logger, 0, 0);
        setLayout(&layout);
    }
    
    ResponseWizardPage::~ResponseWizardPage()
    { }
    
    void ResponseWizardPage::initializePage()
    {
        setCompetitionReceived(false);
        return;
    }
    
    bool ResponseWizardPage::isComplete() const 
    {
        return competition_received && QWizardPage::isComplete();
    }
    
    void ResponseWizardPage::setCompetitionReceived(bool a_state)
    {
        competition_received = a_state;
        emit completeChanged();
        return;
    }
}