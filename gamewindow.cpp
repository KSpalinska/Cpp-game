#include "gamewindow.h"
#include "startwindow.h"
#include "importdata.h"
#include "questionanswer.h"

#include <QPushButton>
#include <QApplication>
#include <QLabel>
#include <QVBoxLayout>
#include <QGroupBox>
#include <QRadioButton>
#include <QProcess>

#include <QFile>
#include <QTextStream>
#include <QMessageBox>

#include <fstream>
#include <sstream>
#include <boost/archive/binary_iarchive.hpp>
#include <boost/archive/binary_oarchive.hpp>
#include <boost/serialization/string.hpp>
#include <boost/serialization/export.hpp>
#include <boost/serialization/vector.hpp>
#include <boost/serialization/list.hpp>
#include "qstringserializer.h"


GameWindow::GameWindow(bool isNewGame, QWidget *parent) :
 QWidget(parent)
{

 if(isNewGame==true) {
    importDataObject = ImportData::getInstance();
    //myData = importDataObject->get_dataToLearn();
    chosenWord = generateNextWord();

    if(importDataObject->dataToLearn.empty()) {
        QMessageBox msgBox;
        msgBox.setWindowTitle("cos poszlo nie tak");
        msgBox.setInformativeText("z importem");
        msgBox.setDefaultButton(QMessageBox::Ok);
        msgBox.exec();
    }
 }

 if(isNewGame==false) {

     //import wektora myData z pliku
 }

 createGUI();
 setLayout(windowLayout);
 setSignals();

}

void GameWindow::setSignals() {
    connect(mainButton, SIGNAL (clicked(bool)), this, SLOT (slotMainButtonClicked(bool)));
    connect(radio0, SIGNAL (clicked(bool)), this, SLOT (slotNumberChosen0(bool)));
    connect(radio1, SIGNAL (clicked(bool)), this, SLOT (slotNumberChosen1(bool)));
    connect(radio2, SIGNAL (clicked(bool)), this, SLOT (slotNumberChosen2(bool)));
    connect(radio3, SIGNAL (clicked(bool)), this, SLOT (slotNumberChosen3(bool)));
    connect(radio4, SIGNAL (clicked(bool)), this, SLOT (slotNumberChosen4(bool)));
    connect(radio5, SIGNAL (clicked(bool)), this, SLOT (slotNumberChosen5(bool)));
    connect(this, &GameWindow::destroyed, this, &GameWindow::refreshProgress);
}

int GameWindow::generateNextWord(){

    return 6;
}

void GameWindow::refreshWindow(int chosenValue) {

    importDataObject->dataToLearn[chosenWord].setQualityOfResponse(chosenValue);
    chosenWord = generateNextWord();

    delete label;
    delete mainButton;
    delete groupBox;
    delete windowLayout;

    createGUI();
    setLayout(windowLayout);
    setSignals();
}

void GameWindow::refreshProgress() {

    //std::cout << "Hello world";

    //std::ofstream ofs;
    //ofs.open("/new/prefix1/dataProgress.txt", std::ofstream::out | std::ofstream::trunc);
    //ofs.close();

    std::string filename = "/new/prefix1/dataProgress.txt";
    std::ofstream out(filename.c_str());
    std::stringstream ss;
    boost::archive::binary_oarchive oa(ss);
    oa << myData;
    out << ss.str();
    out.close();

}

void GameWindow::slotMainButtonClicked(bool checked)
{
 if (checked) {
    mainButton->setText(QString::fromStdString(importDataObject->dataToLearn[chosenWord].getAnswer()));
    windowLayout->addWidget(groupBox);
 }
}

void GameWindow::slotNumberChosen0(bool checked)
{
 if(checked) {
     refreshWindow(0);
 }
}
 void GameWindow::slotNumberChosen1(bool checked)
 {
  if(checked) {
      refreshWindow(1);
  }
 }
 void GameWindow::slotNumberChosen2(bool checked)
 {
  if(checked) {
      refreshWindow(2);
  }
 }
 void GameWindow::slotNumberChosen3(bool checked)
 {
  if(checked) {
      refreshWindow(3);
  }
 }
 void GameWindow::slotNumberChosen4(bool checked)
 {
  if(checked) {
      refreshWindow(4);
  }
 }
 void GameWindow::slotNumberChosen5(bool checked)
 {
  if(checked) {
      refreshWindow(5);
  }
 }

 void GameWindow::createGUI() {

     windowLayout = new QVBoxLayout;

     label = new QLabel(this);
     label->setText("Oto pierwsze pytanie\nOdpowiedz na nie w głowie\nNaciśnij kiedy będziesz chciał poznać odpowiedź");
     label->setGeometry(30,30,300,50);


     mainButton = new QPushButton(QString::fromStdString(importDataObject->dataToLearn[chosenWord].getQuestion()), this);

     mainButton->setGeometry(0, 100, 200, 200);
     mainButton->setCheckable(true);

     groupBox = new QGroupBox(tr("Odpowiedz na ile dobrze pamietałes tą odpowiedź:"));

     radio0 = new QRadioButton(tr("0"));
     radio1 = new QRadioButton(tr("1"));
     radio2 = new QRadioButton(tr("2"));
     radio3 = new QRadioButton(tr("3"));
     radio4 = new QRadioButton(tr("4"));
     radio5 = new QRadioButton(tr("5"));

     QHBoxLayout *buttonsLayout = new QHBoxLayout;
     buttonsLayout->addWidget(radio0);
     buttonsLayout->addWidget(radio1);
     buttonsLayout->addWidget(radio2);
     buttonsLayout->addWidget(radio3);
     buttonsLayout->addWidget(radio4);
     buttonsLayout->addWidget(radio5);
     groupBox->setLayout(buttonsLayout);

     windowLayout->addWidget(label);
     windowLayout->addWidget(mainButton);

     setFixedSize(500, 500);
     setWindowTitle("Graj - supermemo");

 }
