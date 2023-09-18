#include "DivisionEditor.hpp"


namespace divi
{
    DivisionEditor::DivisionEditor(DivisionTableModel* a_division_table_model, QWidget* a_parent)
        : QDialog(a_parent, QDialog().windowFlags() & ~Qt::WindowContextHelpButtonHint)
        , buttons(QDialogButtonBox::Save | QDialogButtonBox::Discard)
        , division_table_model(a_division_table_model)
        , overwrite_warning(this)
    {
        setModal(true);
        setWindowTitle("Division Editor");
        createDialog();
        createOverwriteWarningDialog();
        initialiseConnections();
    }
    
    DivisionEditor::~DivisionEditor()
    { }
    
    Division& DivisionEditor::getDivision()
    {
        return division;
    }
    
    void DivisionEditor::launch(EditorMode a_mode, const Division& a_division)
    {
        setEditorMode(a_mode);
        setDivision(a_division);
        populate();
        
        QDialog::open();
        return;
    }
    
    void DivisionEditor::accept()
    {
        Division* existing_division = division_table_model->getDivision(division.getID());

        // Prompt for overwrite unless in edit mode and about to overwrite the one chosen for editing
        if (existing_division != nullptr
        && !(mode == EditorMode::EditExisting && existing_division->getID() == original_division.getID()))
        {
            overwrite_warning.setText
            (
                QString()
                % "Are you sure you wish to overwrite \""
                % existing_division->getName()
                % "\" with \""
                % division.getName()
                % "\"?"
            );

            overwrite_warning.setInformativeText
            (
                QString()
                % "The chosen division ID ("
                % QString::number(division.getID())
                % ") is already in use by the division \""
                % existing_division->getName()
                % "\"."
            );
            
            overwrite_warning.exec();

            if (overwrite_warning.clickedButton() != overwrite_confirm_button)
            {
                return;
            }
        }

        // If in edit mode, delete the original before saving if the ID has been changed (effectively changing the ID)
        if (mode == EditorMode::EditExisting && original_division.getID() != division.getID())
        {
            division_table_model->deleteDivision(original_division.getID());
        }

        division_table_model->addOrOverwriteDivision(division);
        QDialog::accept();
        return;
    }
    
    void DivisionEditor::reject()
    {
        QDialog::reject();
        return;
    }
    
    void DivisionEditor::browseDivi()
    {
        if (divi_path_dialog.exec())
        {
            QString file = divi_path_dialog.selectedFiles().front();
            divi_path_input.setText(file);
            divi_path_dialog.setDirectory(QFileInfo{file}.absoluteDir());
        }

        return;
    }
    
    void DivisionEditor::setEditorMode(EditorMode a_mode)
    {
        mode = a_mode;
        
        switch (mode)
        {
            case EditorMode::CreateNew:
            {
                header.setText("Create New Division");
                break;
            }
            case EditorMode::EditExisting:
            {
                header.setText("Edit Division");
                break;
            }
        }

        return;
    }
    
    void DivisionEditor::setDivision(const Division& a_division)
    {
        division = a_division;
        original_division = a_division;

        return;
    }
    
    void DivisionEditor::populate()
    {
        switch (mode)
        {
            case EditorMode::CreateNew:
            {
                id_input.setValue(division_table_model->getAvailableID());
                divi_path_input.clear();
                name_input.clear();
                break;
            }
            case EditorMode::EditExisting:
            {
                id_input.setValue(division.getID());
                divi_path_input.setText(division.getDivisionConfigPath());
                name_input.setText(division.getName());
                break;
            }
        }

        return;
    }
    
    void DivisionEditor::createDialog()
    {
        header_font.setPixelSize(20);
        header.setFont(header_font);
        header.setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Maximum);

        id_input.setMinimum(1);
        id_input.setMaximum(std::numeric_limits<int>::max());

        id_text.setTextFormat(Qt::RichText);
        id_text.setText
        (
            QString()
            % "<i>"
            % "The division ID must be unique within the competition."
            % "<br>"
            % "Divisions are sorted in order of ascending ID."
            % "</i>"
        );

        divi_path_input.setReadOnly(true);
        divi_path_button.setMaximumWidth(25);

        divi_path_dialog.setFileMode(QFileDialog::ExistingFile);
        divi_path_dialog.setNameFilter("Division config (*.divi)");
        
        int row = 0;

        layout.addWidget(&header, row++, 0);

        id_layout.addWidget(&id_label, 0, 0);
        id_layout.addWidget(&id_input, 1, 0);
        id_layout.addWidget(&id_text, 2, 0);
        layout.addLayout(&id_layout, row++, 0);
        layout.setRowMinimumHeight(row++, 10);

        name_layout.addWidget(&name_label, 0, 0);
        name_layout.addWidget(&name_input, 1, 0);
        layout.addLayout(&name_layout, row++, 0);
        layout.setRowMinimumHeight(row++, 10);

        divi_path_layout.addWidget(&divi_path_label, 0, 0);
        divi_path_layout.addWidget(&divi_path_input, 1, 0);
        divi_path_layout.addWidget(&divi_path_button, 1, 1);
        layout.addLayout(&divi_path_layout, row++, 0);
        layout.setRowMinimumHeight(row++, 10);

        left_button_spacer.setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::Maximum);
        right_button_spacer.setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::Maximum);
        button_layout.addWidget(&left_button_spacer, 0, 0);
        button_layout.addWidget(&buttons, 0, 1);
        button_layout.addWidget(&right_button_spacer, 0, 2);
        layout.addLayout(&button_layout, row++, 0);

        layout.setSizeConstraint(QLayout::SetFixedSize);
        setLayout(&layout);
        return;
    }
    
    void DivisionEditor::createOverwriteWarningDialog()
    {
        overwrite_warning.setWindowTitle("Overwrite Division");
        overwrite_warning.setIcon(QMessageBox::Warning);

        overwrite_confirm_button = overwrite_warning.addButton("Overwrite", QMessageBox::AcceptRole);
        overwrite_cancel_button = overwrite_warning.addButton("Cancel", QMessageBox::RejectRole);

        return;
    }
    
    void DivisionEditor::initialiseConnections()
    {
        // Buttons
        connect(&divi_path_button, &QPushButton::clicked, this, &DivisionEditor::browseDivi);
        connect(buttons.button(QDialogButtonBox::Discard), &QPushButton::clicked, this, &DivisionEditor::reject);
        connect(&buttons, &QDialogButtonBox::rejected, this, &DivisionEditor::reject);
        connect(&buttons, &QDialogButtonBox::accepted, this, &DivisionEditor::accept);

        // Inputs
        connect(&id_input, &QSpinBox::valueChanged, this, [this](int a_value){this->getDivision().setID(a_value);});
        connect(&name_input, &QLineEdit::textChanged, this, [this](const QString& a_text){this->getDivision().setName(a_text);});
        connect(&divi_path_input, &QLineEdit::textChanged, this, [this](const QString& a_text){this->getDivision().setDivisionConfigPath(a_text);});

        return;
    }
}