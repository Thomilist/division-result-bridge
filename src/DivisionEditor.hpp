#ifndef __DIVISIONEDITOR_H__
#define __DIVISIONEDITOR_H__

#include <limits>

#include <QDialog>
#include <QDialogButtonBox>
#include <QFileDialog>
#include <QFont>
#include <QGridLayout>
#include <QLabel>
#include <QLayout>
#include <QLineEdit>
#include <QMessageBox>
#include <QPushButton>
#include <QSpinBox>
#include <QString>
#include <QStringBuilder>
#include <QWidget>

#include "ForwardDeclarations.hpp"

#include "Division.hpp"
#include "DivisionTableModel.hpp"

#include "EditorMode.hpp"

namespace divi
{
    class DivisionEditor : public QDialog
    {
        Q_OBJECT
        
        public:
            DivisionEditor(DivisionTableModel* a_division_table_model, QWidget* a_parent = nullptr);
            ~DivisionEditor();

            Division& getDivision();
        
        public slots:
            void launch(EditorMode a_mode, const Division& a_division);

        private slots:
            void accept() override;
            void reject() override;
            void browseDivi();
        
        private:
            void setEditorMode(EditorMode a_mode);
            void setDivision(const Division& a_division);
            void populate();
            void createDialog();
            void createOverwriteWarningDialog();
            void initialiseConnections();
            void setToolTips();

            QGridLayout layout;
            QGridLayout button_layout;
            QDialogButtonBox buttons;
            QWidget left_button_spacer;
            QWidget right_button_spacer;
            EditorMode mode;
            Division division;
            Division original_division;
            DivisionTableModel* division_table_model;

            QMessageBox overwrite_warning;
            QPushButton* overwrite_confirm_button;
            QPushButton* overwrite_cancel_button;

            QLabel header;
            QFont header_font;

            QGridLayout id_layout;
            QLabel id_label{"Division ID:"};
            QSpinBox id_input;
            QLabel id_text;

            QGridLayout name_layout;
            QLabel name_label{"Name:"};
            QLineEdit name_input;

            QGridLayout divi_path_layout;
            QLabel divi_path_label{"Path to division config file (.divi):"};
            QLineEdit divi_path_input;
            QPushButton divi_path_button{"..."};
            QFileDialog divi_path_dialog;
    };
}

#endif // __DIVISIONEDITOR_H__