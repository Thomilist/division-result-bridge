#ifndef __CREATECOMPETITIONDIALOG_H__
#define __CREATECOMPETITIONDIALOG_H__

#include <QDialog>
#include <QDialogButtonBox>
#include <QGridLayout>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QRegularExpression>
#include <QRegularExpressionValidator>
#include <QString>
#include <QWidget>

#include "ForwardDeclarations.hpp"

#include "Helpers.hpp"

namespace divi
{
    class CreateCompetitionDialog : public QDialog
    {
        Q_OBJECT
        
        public:
            CreateCompetitionDialog(QWidget* a_parent = nullptr);
            ~CreateCompetitionDialog();
        
        public slots:
            void open();
        
        signals:
            void createCompetition(const QString& a_password);
        
        private slots:
            void submit();
        
        private:
            QGridLayout layout;
            QLabel intro_text;
            QLabel password_label{"Password:"};
            QLineEdit password_input;
            QRegularExpression password_regex;
            QRegularExpressionValidator password_validator;
            QLabel password_text;
            QDialogButtonBox buttons;
    };
}

#endif // __CREATECOMPETITIONDIALOG_H__