#ifndef __RESPONSEWIZARDPAGE_H__
#define __RESPONSEWIZARDPAGE_H__

#include <QGridLayout>
#include <QLabel>
#include <QWidget>
#include <QWizardPage>

#include "../utils/ForwardDeclarations.hpp"

#include "../logging/Logger.hpp"

namespace divi
{
    class ResponseWizardPage : public QWizardPage
    {
        public:
            ResponseWizardPage(Logger* a_logger, QWidget* a_parent = nullptr);
            ~ResponseWizardPage();

            void initializePage() override;
            bool isComplete() const override;

            void setCompetitionReceived(bool a_state);
        
        private:
            bool competition_received = false;

            QGridLayout layout;
            Logger* logger;
    };
}

#endif // __RESPONSEWIZARDPAGE_H__