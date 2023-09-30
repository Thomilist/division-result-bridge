#include "CreateCompetitionDialog.hpp"


namespace divi
{
    CreateCompetitionDialog::CreateCompetitionDialog(QWidget* a_parent)
        : QDialog(a_parent, QDialog().windowFlags() & ~Qt::WindowContextHelpButtonHint)
        , buttons(QDialogButtonBox::Ok | QDialogButtonBox::Cancel)
    {
        setModal(true);
        setWindowTitle("Create New Competition");

        connect(&buttons, &QDialogButtonBox::accepted, this, &CreateCompetitionDialog::submit);
        connect(&buttons, &QDialogButtonBox::accepted, this, &QDialog::accept);
        connect(&buttons, &QDialogButtonBox::rejected, this, &QDialog::reject);
        connect(&password_input, &QLineEdit::textChanged, this, [this]
        {
            this->buttons.button(QDialogButtonBox::Ok)->setDisabled(this->password_input.text().isEmpty());
        });

        auto request_button = buttons.button(QDialogButtonBox::Ok);

        request_button->setDisabled(true);
        request_button->setText("Request");

        intro_text.setWordWrap(true);
        intro_text.setText
        (
            QString()
            % "To create a new competition on the server, first ensure that the correct web server address is specified in the main window. "
            % "Then, enter a password in this dialog, which will be used to access the competition. "
            % "The password cannot be changed later, so choose carefully. "
            % "Finally, submit the request. The web server should respond with the competition ID of the newly-created competition."
        );

        password_regex.setPattern(Helpers::passwordRegex());
        password_validator.setRegularExpression(password_regex);
        password_input.setValidator(&password_validator);
        password_input.setToolTip(
            "Not secure. Seriously, don't reuse a password from another service. Act as if the whole world can see it, because, well, it can");

        password_text.setTextFormat(Qt::RichText);
        password_text.setWordWrap(true);
        password_text.setText(Helpers::passwordDisclaimer());

        int row = 0;

        layout.addWidget(&intro_text, row++, 0);
        layout.addWidget(&password_label, row++, 0);
        layout.addWidget(&password_input, row++, 0);
        layout.addWidget(&password_text, row++, 0);
        layout.addWidget(&buttons, row++, 0);

        setLayout(&layout);
    }
    
    CreateCompetitionDialog::~CreateCompetitionDialog()
    { }
    
    void CreateCompetitionDialog::open()
    {
        password_input.clear();

        QDialog::open();
        return;
    }
    
    void CreateCompetitionDialog::submit()
    {
        emit createCompetition(password_input.text());
        return;
    }
}