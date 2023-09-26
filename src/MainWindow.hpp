#ifndef __MAINWINDOW_H__
#define __MAINWINDOW_H__

#include <array>
#include <limits>

#include <QAbstractItemView>
#include <QAction>
#include <QCheckBox>
#include <QComboBox>
#include <QDate>
#include <QDateTimeEdit>
#include <QDesktopServices>
#include <QFileDialog>
#include <QFileInfo>
#include <QFont>
#include <QGridLayout>
#include <QGroupBox>
#include <QHeaderView>
#include <QIcon>
#include <QItemSelectionModel>
#include <QKeySequence>
#include <QLabel>
#include <QLineEdit>
#include <QMainWindow>
#include <QMenu>
#include <QMenuBar>
#include <QMessageBox>
#include <QModelIndexList>
#include <QPushButton>
#include <QRegularExpression>
#include <QRegularExpressionValidator>
#include <QSizePolicy>
#include <QSpinBox>
#include <QString>
#include <QStringBuilder>
#include <QStringList>
#include <QTableView>
#include <QTextEdit>
#include <QThread>
#include <QTimer>
#include <QVBoxLayout>
#include <QWidget>

#include "ForwardDeclarations.hpp"

#include "AboutDialog.hpp"
#include "CompetitionCreatedDialog.hpp"
#include "ConfigValidator.hpp"
#include "CreateCompetitionDialog.hpp"
#include "Division.hpp"
#include "DivisionEditor.hpp"
#include "DivisionTableModel.hpp"
#include "Helpers.hpp"
#include "Logger.hpp"
#include "MeosInterface.hpp"
#include "Coordinator.hpp"
#include "PersistentSettings.hpp"
#include "UpdateDialog.hpp"
#include "Version.hpp"
#include "VersionNotifier.hpp"

#include "EditorMode.hpp"

namespace divi
{
    class MainWindow : public QMainWindow
    {
        Q_OBJECT
        
        public:
            MainWindow(Version* a_version);
            ~MainWindow();
        
        signals:
            void runOnce();

        private slots:
            void start();
            void stop();
            void importConfig();
            void exportConfig();
            void browseWorkingDir();
            void browseDiviExe();
            void updateInterfaceState();
            void editSelectedDivision();
            void deleteSelectedDivision();
            void updateCountdown();
            void loadNewCompetition(const Competition& a_competition);
        
        private:
            void createHeader();
            void createCompetitionGroup();
            void createConfigGroup();
            void createDivisionsGroup();
            void createWebserverGroup();
            void createRunGroup();
            void createLogGroup();
            void populate();
            void initaliseMenus();
            void initialiseConnections();
            void disableAllInputs(bool a_disable);
            const QString getCompetitionUrl();
            void clearCompetitionAndDivision();
            void loadCompetitionMetadata(const Competition& a_competition);
            void updateLiveresultsText();

            bool running = false;

            Version* version;
            PersistentSettings settings;
            QThread worker;
            Logger* log;
            VersionNotifier version_notifier;
            Coordinator coordinator;

            QMenu file_menu;
            QAction import_config_action;
            QAction export_config_action;
            ConfigValidator config_validator;

            QMenu help_menu;
            QAction view_help;
            QAction view_about;
            AboutDialog about_dialog;
            QAction check_for_updates;
            UpdateDialog update_dialog;
            QAction open_github;
            QAction report_issue;

            QWidget central_widget;
            QGridLayout grid_layout;
            std::array<QVBoxLayout, 3> ui_columns;
            QWidget spacer;

            QLabel header{"Division Result Bridge"};
            QFont header_font;
            
            QFileDialog import_config_dialog;
            QFileDialog export_config_dialog;

            std::vector<QWidget*> all_inputs;

            // Competition
            QGroupBox competition_group{"Competition"};
            QGridLayout competition_layout;
            QWidget competition_spacer;

            QGridLayout competition_id_layout;
            QLabel competition_id_label{"Competition ID:"};
            QSpinBox competition_id_input;

            QGridLayout password_layout;
            QLabel password_label{"Password:"};
            QLineEdit password_input;
            QRegularExpression password_regex;
            QRegularExpressionValidator password_validator;
            QLabel password_text;

            QGridLayout competition_name_layout;
            QLabel competition_name_label{"Name:"};
            QLineEdit competition_name_input;

            QGridLayout organiser_layout;
            QLabel organiser_label{"Organiser:"};
            QLineEdit organiser_input;

            QGridLayout competition_date_layout;
            QLabel competition_date_label{"Date (YYYY-MM-DD):"};
            QDateTimeEdit competition_date_input;
            QWidget competition_date_spacer;
            QLabel competition_visibility_label{"Visibility:"};
            QComboBox competition_visibility_input;

            // Configuration
            QGroupBox config_group{"Local Configuration"};
            QGridLayout config_layout;
            QWidget config_spacer;

            QGridLayout working_dir_layout;
            QLabel working_dir_label{"Working directory:"};
            QLineEdit working_dir_input;
            QPushButton working_dir_button{"..."};
            QLabel working_dir_text;
            QFileDialog working_dir_dialog;

            QGridLayout divi_exe_path_layout;
            QLabel divi_exe_path_label;
            QLineEdit divi_exe_path_input;
            QPushButton divi_exe_path_button{"..."};
            QLabel divi_exe_path_text;
            QFileDialog divi_exe_path_dialog;

            QGridLayout meos_address_layout;
            QLabel meos_address_label{"MeOS information server address:"};
            QLineEdit meos_address_input;
            QLabel meos_address_text;

            // Divisions
            QGroupBox divisions_group{"Divisions"};
            QGridLayout divisions_layout;
            QTableView division_table;
            DivisionTableModel division_table_model;
            DivisionEditor division_editor;

            QGridLayout division_button_layout;
            QPushButton new_division_button{"New"};
            QPushButton edit_division_button{"Edit"};
            QPushButton delete_division_button{"Delete"};
            QWidget left_division_button_spacer;
            QWidget right_division_button_spacer;

            QMessageBox delete_division_warning;
            QPushButton* delete_division_confirm_button;
            QPushButton* delete_division_cancel_button;

            // Web Server
            QGroupBox webserver_group{"Web Server"};
            QGridLayout webserver_layout;

            QGridLayout webserver_address_layout;
            QLabel webserver_address_label{"Web server address:"};
            QLineEdit webserver_address_input;

            QGridLayout webserver_manage_layout;
            QLabel webserver_manage_label{"Manage competition on server:"};
            QPushButton webserver_create_button{"Create New"};
            CreateCompetitionDialog create_competition_dialog;
            CompetitionCreatedDialog competition_created_dialog;
            QPushButton webserver_update_meta_button{"Update Metadata"};

            QGridLayout webserver_inspect_layout;
            QLabel webserver_inspect_label{"Inspect competition on server:"};
            QPushButton webserver_ping_button{"Test"};
            QPushButton webserver_view_button{"View In Browser"};

            QGridLayout liveresults_layout;
            QLabel liveresults_label;
            QSpinBox liveresults_input;

            // Run
            QGroupBox run_group{"Run"};
            QGridLayout run_layout;
            QWidget run_spacer;
            QTimer run_timer;
            QTimer countdown_timer;

            QGridLayout update_interval_layout;
            QLabel update_interval_label{"Update interval (seconds):"};
            QSpinBox update_interval_input;

            QGridLayout countdown_layout;
            QLabel countdown_label;
            QLabel countdown_time;

            QGridLayout run_buttons_layout;
            QPushButton start_button{"Start"};
            QPushButton stop_button{"Stop"};
            QPushButton run_once_button{"Run Once"};

            // Log
            QGroupBox log_group{"Log"};
            QGridLayout log_layout;
            QGridLayout save_logs_layout;
            QLabel save_logs_label{"Save logs:"};
            QWidget save_logs_spacer;
            QCheckBox save_pretty_log_input{"Pretty (HTML)"};
            QCheckBox save_raw_log_input{"Raw (plain text)"};
    };
}

#endif // __MAINWINDOW_H__