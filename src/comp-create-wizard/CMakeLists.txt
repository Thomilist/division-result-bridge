add_library(AlteredWizardPage AlteredWizardPage.cpp)
target_link_libraries(
    AlteredWizardPage PRIVATE
    Qt::Widgets
)

add_library(CompatibilityWizardPage CompatibilityWizardPage.cpp)
target_link_libraries(
    CompatibilityWizardPage PRIVATE
    Qt::Widgets
    Settings
)

add_library(CompetitionCreationWizard CompetitionCreationWizard.cpp)
target_link_libraries(
    CompetitionCreationWizard PRIVATE
    Qt::Widgets
    AlteredWizardPage
    CompatibilityWizardPage
    Competition
    Helpers
    Loggable
    Logger
    ResponseWizardPage
    Settings
    SummaryTableModel
)

add_library(ResponseWizardPage ResponseWizardPage.cpp)
target_link_libraries(
    ResponseWizardPage PRIVATE
    Qt::Widgets
)

add_library(SummaryTableModel SummaryTableModel.cpp)
target_link_libraries(
    SummaryTableModel PRIVATE
    Qt::Widgets
    Settings
)