#include <QtCore/QFile>
#include <QtWidgets/QFrame>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMessageBox>
#include "ProfileGUI.hpp"

ProfileGUI::ProfileGUI(ProfileManager *manager) : ProfileUI(manager) {}

ProfileGUI::~ProfileGUI() {
    close();
}


void ProfileGUI::display() {
    QFile File("../../qt_ui/profile.qss");
    File.open(QFile::ReadOnly);
    QString styleSheet = QLatin1String(File.readAll());
    this->setStyleSheet(styleSheet);

    this->setFixedHeight(600);
    this->setFixedWidth(750);
    QPixmap bkgnd("../../qt_ui/game_pictures/backgrounds/americanBg");
    bkgnd = bkgnd.scaled(this->size(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
    QPalette palette;
    palette.setBrush(QPalette::Background, bkgnd);
    this->setPalette(palette);
    QFont police("calibri");

    QFrame *fields = new QFrame(this);
    QFormLayout *fieldsLayout = new QFormLayout(this);

    usernameL = new QLineEdit(fields);
    usernameL->setSelection(0, 10);

    QString usernameString = "Username";
    QString searchButtonString = "SEARCH";

    QLabel *label = new QLabel(fields);
    label->setText(usernameString);
    label->setFont(police);

    searchButton = new QPushButton(searchButtonString, fields);
    searchButton->setFixedSize(QSize(212, 45));

    QObject::connect(searchButton, SIGNAL(clicked()), this, SLOT(showUser()));
    QObject::connect(usernameL, SIGNAL(returnPressed()), searchButton, SIGNAL(clicked()));

    fieldsLayout->addRow(label, usernameL);
    fieldsLayout->addRow(searchButton);
    fields->setLayout(fieldsLayout);
    fields->move(this->size().width() / 2 - 125, this->size().height() / 2 + 105);

    // TODO: add profile data

    this->show();
}

void ProfileGUI::displayNoSuchProfileError() {
    QMessageBox::critical(this, "No such profile", "Error : There is no profile with that username");
}

void ProfileGUI::updateProfile() {
    // TODO
}

void ProfileGUI::showUser() {
    // TODO
}
