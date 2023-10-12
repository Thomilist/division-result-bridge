#ifndef __UPDATEDIALOG_H__
#define __UPDATEDIALOG_H__

#include <QDebug>

#include <QDialog>
#include <QDialogButtonBox>
#include <QGridLayout>
#include <QLabel>
#include <QStackedWidget>

#include "../utils/Helpers.hpp"
#include "Version.hpp"

#include "UpdateStatus.hpp"

namespace divi
{
    class UpdateDialog : public QDialog
    {
        public:
            UpdateDialog(Version* a_version, QWidget* a_parent);
            ~UpdateDialog();

            void open(UpdateStatus a_update_status, bool a_quiet);
        
        public slots:
            void manualUpdateCheck();
        
        private:
            void createYouHaveLatestVersion();
            void createNewVersionAvailable();
            void createInaccessible();
            void createUnknown();

            Version* version;
            QDialogButtonBox buttons;
            QGridLayout grid_layout;
            QLabel update_text;
    };
}

#endif // __UPDATEDIALOG_H__