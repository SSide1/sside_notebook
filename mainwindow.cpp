#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QFont>
#include <QFontDialog>
#include <QColor>
#include <QList>
#include <QTextCursor>
#include <QDialog>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QGridLayout>
#include <QObject>
#include <QMouseEvent>
#include <QFile>
#include <QTextStream>
#include <QFileDialog>
#include <QMessageBox>
#include <QColorDialog>
#include <QPalette>
#include <QPixmap>
#include <QSettings>



MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    words = 0;
    setCentralWidget(ui->textEdit);
    action_font_Grey();
    on_action_view_LineState_triggered(true);
    connect(ui->textEdit,SIGNAL(cursorPositionChanged()), SLOT(on_actionStatus_triggered()));
    connect(ui->textEdit,SIGNAL(cursorPositionChanged()), SLOT(highlightline()));
    connect(ui->textEdit,SIGNAL(textChanged()), SLOT(titlechange()));
    connect(ui->textEdit,SIGNAL(textChanged()), SLOT(word_count()));

    titlechange();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::titlechange(){

    //qDebug() << saved;
    if(fname > 0 && saved == 1){
        saved = false;
        title = fname;
        setWindowTitle(title);
    }
    else if(fname > 0 && saved == 0){
        title = fname + "*";
        setWindowTitle(title);
    }
    else if(fname == 0 && saved == 1){
        saved = false;
        title = "New File*";
        setWindowTitle(title);
    }
    else if(fname == 0 && saved == 0){

        title = "New File*";
        setWindowTitle(title);
    }


}

void MainWindow::word_count(){
    words = ui->textEdit->toPlainText().split(QRegExp("(\\s|\\n|\\r)+")
                                              , QString::SkipEmptyParts).count();
}

void MainWindow::on_actionCancel_triggered()
{
    ui->textEdit->undo();
}

void MainWindow::on_actionReDo_triggered()
{
    ui->textEdit->redo();
}

void MainWindow::on_actionCopy_triggered()
{
    ui->textEdit->copy();
}

void MainWindow::on_actionCut_triggered()
{
    ui->textEdit->cut();
}

void MainWindow::on_actionPaste_triggered()
{
    ui->textEdit->paste();
}

void MainWindow::on_actionFind_triggered()
{
    on_action_edit_Find_triggered();
}

void MainWindow::on_action_menu_Exit_triggered()
{

    if(title.isEmpty()){
        QApplication::exit(0);
    }
    else if(title[title.size()-1] == '*'){
        QDialog *dialog = new QDialog(this,Qt::WindowTitleHint | Qt::WindowSystemMenuHint);
        dialog->resize(150,100);
        dialog->show();
        QLabel *label = new QLabel("Leave without saving?",dialog);
        label->show();
        QPushButton *yes = new QPushButton("&Yes",dialog);
        QPushButton *cancel = new QPushButton("&No",dialog);
        QObject::connect(yes,SIGNAL(clicked()),dialog,SLOT(accept()));
        QObject::connect(cancel, SIGNAL(clicked()),dialog, SLOT(reject()));
        QGridLayout* layout = new QGridLayout(dialog);
        layout->addWidget(label,0,0);
        layout->addWidget(yes,1,0);
        layout->addWidget(cancel,1,1);
        dialog->setLayout(layout);

        if(dialog->exec() == QDialog::Accepted){
            QApplication::exit(0);
        }
    }
    else
        QApplication::exit(0);
}

void MainWindow::on_action_edit_Cancel_triggered()
{
    ui->textEdit->undo();
}

void MainWindow::on_action_edit_ReDo_triggered()
{
    ui->textEdit->redo();
}

void MainWindow::on_action_edit_Copy_triggered()
{
    ui->textEdit->copy();
}

void MainWindow::on_action_edit_Cut_triggered()
{
    ui->textEdit->cut();
}

void MainWindow::on_action_edit_Paste_triggered()
{
    ui->textEdit->paste();
}

void MainWindow::on_action_edit_SelectAll_triggered()
{
    ui->textEdit->selectAll();
}

void MainWindow::on_action_format_WordWrap_toggled(bool arg1)
{
    if(arg1 == true){
        ui->textEdit->setLineWrapMode(QTextEdit::WidgetWidth);
    }
    else if(arg1 == false){
        ui->textEdit->setLineWrapMode(QTextEdit::NoWrap);
    }
}

void MainWindow::on_action_format_SelectFont_triggered()
{
    bool b0k;
    QFont fnt = QFontDialog::getFont(&b0k,this);
    if(b0k) {
        ui->textEdit->setFont(fnt);
    }
}

void MainWindow::on_action_view_ToolBar_toggled(bool arg1)
{
    if(!arg1){
        ui->mainToolBar->hide();
    }
    else
        ui->mainToolBar->show();
}

void MainWindow::highlightline(){
    QList<QTextEdit::ExtraSelection> extraSelections;
    if (!ui->textEdit->isReadOnly()) {

        QTextEdit::ExtraSelection selection;
        selection.format.setBackground(lineColor);
        selection.format.setProperty(QTextFormat::FullWidthSelection, true);
        selection.cursor = ui->textEdit->textCursor();
        selection.cursor.clearSelection();
        extraSelections.append(selection);


    }

    ui->textEdit->setExtraSelections(extraSelections);
}

void MainWindow::action_font_Grey(){
       if (!ui->textEdit->isReadOnly()) {
           lineColor = QColor(Qt::gray).lighter(140);
           highlightline();
       }
}

void MainWindow::on_action_edit_Find_triggered()
{
    QDialog *dialog = new QDialog(this,Qt::WindowTitleHint | Qt::WindowSystemMenuHint);
    dialog->resize(150,100);
    dialog->show();
    QLabel *label = new QLabel("&Type a word that you want find!",dialog);
    label->show();
    QLineEdit *line1;
    line1 = new QLineEdit(dialog);
    label->setBuddy(line1);
    QPushButton *find = new QPushButton("&Find",dialog);
    QPushButton *cancel = new QPushButton("&Cancel",dialog);
    QObject::connect(find,SIGNAL(clicked()),dialog,SLOT(accept()));
    QObject::connect(cancel, SIGNAL(clicked()),dialog, SLOT(reject()));
    QGridLayout* layout = new QGridLayout(dialog);
    layout->addWidget(label,0,0);
    layout->addWidget(line1,0,1);
    layout->addWidget(find,1,0);
    layout->addWidget(cancel,1,1);
    dialog->setLayout(layout);
    fin = true;
    if(dialog->exec() == QDialog::Accepted){
        QList<QTextEdit::ExtraSelection> extraSelections;
        if(!ui->textEdit->isReadOnly())
        {
            ui->textEdit->moveCursor(QTextCursor::Start);
            QColor color = QColor(Qt::green).lighter(130);

            while(ui->textEdit->find(line1->text()))
            {
                QTextEdit::ExtraSelection extra;
                extra.format.setBackground(color);

                extra.cursor = ui->textEdit->textCursor();
                extraSelections.append(extra);
            }
        }

        ui->textEdit->setExtraSelections(extraSelections);
    }

}

void MainWindow::mousePressEvent(QMouseEvent *event){
    //qDebug() << fin;
    if(event->button() == Qt::LeftButton && fin == true){
        highlightline();
        fin = false;
    }
}

void MainWindow::on_actionStatus_triggered()
{
    on_action_view_LineState_triggered(status);
}

void MainWindow::on_action_view_LineState_triggered(bool checked)
{
    if (!ui->textEdit->isReadOnly()){
    if(checked){
        //qDebug() << curr;
        status = true;
        ui->statusBar->show();
        int count = ui->textEdit->toPlainText().size();
        //qDebug() << count;
        int line = ui->textEdit->textCursor().blockNumber()+1;
        int pos = ui->textEdit->textCursor().columnNumber()+1;

        ui->statusBar->showMessage(QString("Ln %1, Col %2   |     Size in KB: %3    Words: %4   Symbols: %5  |    Last save: %6    Last read: %7").arg(line).arg(pos).arg(size).arg(words).arg(count).arg(last_mod.toString()).arg(last_read.toString()));
    }
    else{
        status = false;
        ui->statusBar->hide();
    }
    }
}


void MainWindow::on_actionFindAndChange_triggered()
{
    QDialog *dialog = new QDialog(this,Qt::WindowTitleHint | Qt::WindowSystemMenuHint);
    dialog->resize(150,100);
    dialog->show();
    //dialog->setModal(false);
    QLabel *label = new QLabel("&Type a word that you want replace",dialog);
    QLabel *label1 = new QLabel("&Type a replacing word",dialog);
    label->show();
    label1->show();
    QLineEdit *line1;
    QLineEdit *line2;
    line1 = new QLineEdit(dialog);
    line2 = new QLineEdit(dialog);
    label->setBuddy(line1);
    label1->setBuddy(line2);
    QPushButton *find = new QPushButton("&Find and Replace",dialog);
    QPushButton *cancel = new QPushButton("&Cancel",dialog);
    QObject::connect(find,SIGNAL(clicked()),dialog,SLOT(accept()));
    QObject::connect(cancel, SIGNAL(clicked()),dialog, SLOT(reject()));
    QGridLayout* layout = new QGridLayout(dialog);
    layout->addWidget(label,0,0);
    layout->addWidget(line1,0,1);
    layout->addWidget(label1,1,0);
    layout->addWidget(line2,1,1);
    layout->addWidget(find,2,0);
    layout->addWidget(cancel,2,1);
    dialog->setLayout(layout);
    fin = true;
    if(dialog->exec() == QDialog::Accepted){

        if(!ui->textEdit->isReadOnly())
        {
            ui->textEdit->moveCursor(QTextCursor::Start);

            while(ui->textEdit->find(line1->text()))
            {
                QTextEdit::ExtraSelection extra;

                extra.cursor = ui->textEdit->textCursor();
                extra.cursor.removeSelectedText();
                extra.cursor.insertText(line2->text());

            }
        }
    }
    highlightline();
}

void MainWindow::on_action_edit_FindAndChange_triggered()
{
    on_actionFindAndChange_triggered();
}

void MainWindow::on_actionOpen_triggered()
{
    saved = true;
    QString str = QFileDialog::getOpenFileName(this,"Open a file");
    QFile current(str);

    if(!current.open(QFile::ReadOnly | QFile::Text)){
        QMessageBox::warning(this, "Error","You didn't choose a file!");
        return;
    }
    QFileInfo file(str);
    last_read = file.lastRead();
    last_mod = file.lastModified();

    size = file.size() / 1024 + 1;
    fname = str;
    QTextStream ReadFile(&current);
    ui->textEdit->setText(ReadFile.readAll());
    current.close();
}

void MainWindow::on_action_menu_Open_triggered()
{
    on_actionOpen_triggered();
}

void MainWindow::on_actionNew_triggered()
{

    if(title.isEmpty()){

        fname = "";
        ui->textEdit->clear();
        titlechange();
    }
    else if(title[title.size()-1] == '*'){

        QDialog *dialog = new QDialog(this,Qt::WindowTitleHint | Qt::WindowSystemMenuHint);
        dialog->resize(150,100);
        dialog->show();
        QLabel *label = new QLabel("Create new file without save of previous?",dialog);
        label->show();
        QPushButton *yes = new QPushButton("&Yes",dialog);
        QPushButton *cancel = new QPushButton("&No",dialog);
        QObject::connect(yes,SIGNAL(clicked()),dialog,SLOT(accept()));
        QObject::connect(cancel, SIGNAL(clicked()),dialog, SLOT(reject()));
        QGridLayout* layout = new QGridLayout(dialog);
        layout->addWidget(label,0,0);
        layout->addWidget(yes,1,0);
        layout->addWidget(cancel,1,1);
        dialog->setLayout(layout);

        if(dialog->exec() == QDialog::Accepted){
//            QFile file(title);
//            QTextStream out(&file);
//            QStrin g text = ui->textEdit->toPlainText();
//            out << text;
//            file.flush();
//            file.close();
            fname = "";
            ui->textEdit->clear();
            titlechange();

        }
    }
    else{
        fname = "";
        ui->textEdit->clear();
        titlechange();
    }
//    fname = "";
//    ui->textEdit->clear();
//    titlechange();
}

void MainWindow::on_actionSave_triggered()
{
    QString str("New File*");
    saved = true;
    titlechange();

    //qDebug() << curr.toString();
    if(title == str){
        QString save = QFileDialog::getSaveFileName(this,"Save in file");
        QFile file(save);
        //file.open(QFile::WriteOnly | QFile::Text);

        if(!file.open(QFile::WriteOnly | QFile::Text)){

            return;
        }
        fname = save;
        titlechange();
        QTextStream out(&file);
        QString text = ui->textEdit->toPlainText();
        out << text;
        file.flush();
        file.close();
    }
    else{
        QFile file(title);
        file.open(QFile::WriteOnly | QFile::Text);

        QTextStream out(&file);
        QString text = ui->textEdit->toPlainText();
        out << text;
        file.flush();
        file.close();
        QFileInfo file1(title);
        last_read = file1.lastRead();
        last_mod = file1.lastModified();
        size = file1.size() / 1024 + 1;
    }

}

void MainWindow::on_action_menu_Save_triggered()
{
    on_actionSave_triggered();
}

void MainWindow::on_action_menu_Save_How_triggered()
{
    saved = true;
    titlechange();
    //curr = QTime::currentTime();

    QString save = QFileDialog::getSaveFileName(this,"Save in file");
    QFile file(save);

    if(!file.open(QFile::WriteOnly | QFile::Text)){
        QMessageBox::warning(this, "Error", "You didn't create or choose a file!!");
        return;
    }
    QFileInfo file1(save);
    last_read = file1.lastRead();
    last_mod = file1.lastModified();
    size = file1.size() / 1024 + 1;
    fname = save;
    titlechange();
    QTextStream out(&file);
    QString text = ui->textEdit->toPlainText();
    out << text;
    file.flush();
    file.close();

}

void MainWindow::on_action_view_Background_triggered()
{
    QColor color = QColorDialog::getColor(Qt::white,this,"Choose color!");
    QPalette pal;
    backColor = color;
    pal.setColor(QPalette::Base,color);
    if(color.isValid()) {
        ui->textEdit->setPalette(pal);
    }

}

void MainWindow::on_action_view_lineColor_triggered()
{
        //qDebug() << "s";
        QColor color = QColorDialog::getColor(Qt::white,this,"Choose color!");
        if(color.isValid()){
            lineColor = color;
        }
        highlightline();

}



void MainWindow::on_action_menu_New_triggered()
{
    on_actionNew_triggered();
}

void MainWindow::on_action_view_SintBacklight_triggered(bool checked)
{
    if(checked){
        highlighter = new Highlighter(ui->textEdit->document(),0);//c++98
        ui->action_98->setChecked(true);
    }
    else if(((ui->action_89->isChecked() || ui->action_98->isChecked() || ui->action_17->isChecked() || ui->action_11->isChecked())&& checked == false)){
        ui->action_89->setChecked(false);
        ui->action_98->setChecked(false);
        ui->action_17->setChecked(false);
        ui->action_11->setChecked(false);
        delete highlighter;
    }

}

void MainWindow::on_action_89_triggered(bool checked)
{
    if(checked && ui->action_view_SintBacklight->isChecked()){
        ui->action_98->setChecked(false);
        ui->action_11->setChecked(false);
        ui->action_17->setChecked(false);
        delete highlighter;
        highlighter = new Highlighter(ui->textEdit->document(),1);//c89
    }
    else if(!checked && ui->action_view_SintBacklight->isChecked())
        delete highlighter;
    else if(checked && !ui->action_view_SintBacklight->isChecked()){
        highlighter = new Highlighter(ui->textEdit->document(),1);//c89
        ui->action_view_SintBacklight->setChecked(true);
    }
}

void MainWindow::on_action_98_triggered(bool checked)
{
    if(checked && ui->action_view_SintBacklight->isChecked()){
        ui->action_89->setChecked(false);
        ui->action_11->setChecked(false);
        ui->action_17->setChecked(false);
        delete highlighter;
        highlighter = new Highlighter(ui->textEdit->document(),2);//c++98
    }
    else if(!checked && ui->action_view_SintBacklight->isChecked())
        delete highlighter;
    else if(checked && !ui->action_view_SintBacklight->isChecked()){
        highlighter = new Highlighter(ui->textEdit->document(),2);//c++98
        ui->action_view_SintBacklight->setChecked(true);
    }
}

void MainWindow::on_action_11_triggered(bool checked)
{
    if(checked && ui->action_view_SintBacklight->isChecked()){
        ui->action_89->setChecked(false);
        ui->action_98->setChecked(false);
        ui->action_17->setChecked(false);
        delete highlighter;
        highlighter = new Highlighter(ui->textEdit->document(),3);//c++11
    }
    else if(!checked && ui->action_view_SintBacklight->isChecked())
        delete highlighter;
    else if(checked && !ui->action_view_SintBacklight->isChecked()){
        highlighter = new Highlighter(ui->textEdit->document(),3);//c++11
        ui->action_view_SintBacklight->setChecked(true);
    }
}

void MainWindow::on_action_17_triggered(bool checked)
{
    if(checked && ui->action_view_SintBacklight->isChecked()){
        ui->action_89->setChecked(false);
        ui->action_98->setChecked(false);
        ui->action_11->setChecked(false);
        delete highlighter;
        highlighter = new Highlighter(ui->textEdit->document(),4);//c++20
    }
    else if(!checked && ui->action_view_SintBacklight->isChecked())
        delete highlighter;
    else if(checked && !ui->action_view_SintBacklight->isChecked()){
        highlighter = new Highlighter(ui->textEdit->document(),4);//c++20
        ui->action_view_SintBacklight->setChecked(true);
    }
}

void MainWindow::on_action_about_triggered()
{
    QDialog *dialog = new QDialog(this,Qt::WindowTitleHint | Qt::WindowSystemMenuHint);
    dialog->resize(150,500);
    dialog->show();
    QLabel *label = new QLabel(dialog);
    //QString str = QDir::currentPath();
    //qDebug() << str;
    QPixmap pic("photo.jpg");
    label->setPixmap(pic);
    label->setScaledContents( true );

    label->setSizePolicy( QSizePolicy::Ignored, QSizePolicy::Ignored );
    label->show();
    QPushButton *yes = new QPushButton("&OK",dialog);
    QObject::connect(yes,SIGNAL(clicked()),dialog,SLOT(accept()));
//    QDateTime d = QFileInfo(mainwindow.cpp).created();
//    qDebug() << d;
    QLabel *label1 = new QLabel("Programm created by Alexander Volkov, MIEM\n12.11.2020, MinGW 5.7.0, QT 5.3.0",dialog);
    //QLabel *label2 = new QLabel("12.11.2020, MinGW 5.7.0, Q 5.3.0",dialog);

    QGridLayout* layout = new QGridLayout(dialog);
    layout->addWidget(label,0,0);
    layout->addWidget(label1,1,0);
    //layout->addWidget(label2,2,0);
    layout->addWidget(yes,2,0);
    dialog->setLayout(layout);
}

void MainWindow::on_action_ini_triggered()
{
    QSettings *set = new QSettings("settings.ini",QSettings::IniFormat);
    set->setValue("Programm/size",ui->textEdit->size());
    set->setValue("Programm/font",ui->textEdit->font().toString());
    set->setValue("Programm/BackgroundLine",lineColor.name());
    set->setValue("Programm/Background",backColor.name());
    set->setValue("Programm/FileSizeKiloBytes",size);
    set->setValue("Programm/currentFile",title);
}
