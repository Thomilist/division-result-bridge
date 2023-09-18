#ifndef __COMPETITIONCREATEDDIALOG_H__
#define __COMPETITIONCREATEDDIALOG_H__

#include <QDialog>
#include <QDialogButtonBox>
#include <QGridLayout>
#include <QLabel>
#include <QTextEdit>
#include <QPushButton>
#include <QString>
#include <QWidget>

#include "ForwardDeclarations.hpp"

#include "Competition.hpp"

namespace divi
{
    class CompetitionCreatedDialog : public QDialog
    {
        Q_OBJECT
        
        public:
            CompetitionCreatedDialog(QWidget* a_parent = nullptr);
            ~CompetitionCreatedDialog();

        public slots:
            void open(const Competition& a_competition);
        
        signals:
            void useCompetitionNow(const Competition& a_competition);
        
        private:
            Competition new_competition;

            QGridLayout layout;
            QLabel success_text{"Competition successfully created. Make sure you don't lose the ID and password, as you will need these any time you wish to access the competition."};
            QTextEdit metadata_display;
            QLabel use_now_text{"Do you wish to use this competition now? This will erase competition and division settings."};
            QDialogButtonBox buttons;
    };
}
#endif // __COMPETITIONCREATEDDIALOG_H__