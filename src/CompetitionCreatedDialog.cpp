#include "CompetitionCreatedDialog.hpp"


namespace divi
{
    CompetitionCreatedDialog::CompetitionCreatedDialog(QWidget* a_parent)
        : QDialog(a_parent, QDialog().windowFlags() & ~Qt::WindowContextHelpButtonHint)
        , buttons(QDialogButtonBox::Ok | QDialogButtonBox::Cancel)
    {
        setModal(true);
        setWindowTitle("New Competition Created");

        metadata_display.setReadOnly(true);
        metadata_display.setFixedHeight(50);
        metadata_display.setMinimumWidth(300);
        metadata_display.setAcceptRichText(true);

        success_text.setWordWrap(true);
        use_now_text.setWordWrap(true);

        buttons.button(QDialogButtonBox::Ok)->setText("Use Now");
        buttons.button(QDialogButtonBox::Cancel)->setText("Close");

        connect(&buttons, &QDialogButtonBox::accepted, [this]{emit this->useCompetitionNow(this->new_competition);});
        connect(&buttons, &QDialogButtonBox::accepted, this, &QDialog::accept);
        connect(&buttons, &QDialogButtonBox::rejected, this, &QDialog::reject);

        int row = 0;

        layout.addWidget(&success_text, row++, 0);
        layout.addWidget(&metadata_display, row++, 0);
        layout.addWidget(&use_now_text, row++, 0);
        layout.addWidget(&buttons, row++, 0);

        setLayout(&layout);
    }
    
    CompetitionCreatedDialog::~CompetitionCreatedDialog()
    { }
    
    void CompetitionCreatedDialog::open(const Competition& a_competition)
    {
        new_competition = a_competition;

        QString metadata_text = QString()
            %   "<table>"
            %       "<tr>"
            %           "<td style=\"padding-right: 10px;\">"
            %               "Competition ID:"
            %           "</td>"
            %           "<td>"
            %               QString::number(new_competition.getID())
            %           "</td>"
            %       "</tr>"
            %       "<tr>"
            %           "<td style=\"padding-right: 10px;\">"
            %               "Password:"
            %           "</td>"
            %           "<td>"
            %               new_competition.getPassword()
            %           "</td>"
            %       "</tr>"
            %   "</table>";
        
        metadata_display.setText(metadata_text);

        QDialog::open();
        return;
    }
}