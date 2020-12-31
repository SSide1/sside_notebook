#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFile>
#include <highlighter.h>
#include <QFileInfo>
#include <QDateTime>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:

    bool fin = false;
    bool status = true;
    QColor lineColor;
    QColor backColor;
    QString fname;
    QString title;
    bool saved = false;
    Highlighter *highlighter;
    QFileInfo curr;
    QDateTime last_read;
    QDateTime last_mod;
    int words;
    qint64 size;

    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

protected:

    void mousePressEvent(QMouseEvent *event);

private slots:


    void on_actionCancel_triggered();

    void on_actionReDo_triggered();

    void on_actionCopy_triggered();

    void on_actionCut_triggered();

    void on_actionPaste_triggered();

    void on_actionFind_triggered();

    void on_action_menu_Exit_triggered();

    void on_action_edit_Cancel_triggered();

    void on_action_edit_ReDo_triggered();

    void on_action_edit_Copy_triggered();

    void on_action_edit_Cut_triggered();

    void on_action_edit_Paste_triggered();

    void on_action_edit_SelectAll_triggered();

    void on_action_format_WordWrap_toggled(bool arg1);

    void on_action_format_SelectFont_triggered();

    void on_action_view_ToolBar_toggled(bool arg1);

    void on_action_edit_Find_triggered();

    void on_actionStatus_triggered();

    void on_action_view_LineState_triggered(bool checked);

    void highlightline();

    void action_font_Grey();

    void on_actionFindAndChange_triggered();

    void on_action_edit_FindAndChange_triggered();

    void on_actionOpen_triggered();

    void on_action_menu_Open_triggered();

    void on_actionNew_triggered();

    void on_actionSave_triggered();

    void on_action_menu_Save_triggered();

    void on_action_menu_Save_How_triggered();

    void on_action_view_Background_triggered();

    void on_action_view_lineColor_triggered();

    void titlechange();

    void on_action_menu_New_triggered();

    void on_action_view_SintBacklight_triggered(bool checked);

    void on_action_89_triggered(bool checked);

    void on_action_98_triggered(bool checked);

    void on_action_11_triggered(bool checked);

    void on_action_17_triggered(bool checked);

    void on_action_about_triggered();

    void word_count();

    void on_action_ini_triggered();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
