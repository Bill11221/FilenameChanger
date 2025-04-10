#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

class QPushButton;
class QLineEdit;
class QTextEdit;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);

private slots:
    void chooseFolder();
    void renameFiles();

private:
    QPushButton *btnChooseFolder;
    QPushButton *btnRename;
    QLineEdit   *editFolderPath;
    QTextEdit   *textLog;
};

#endif // MAINWINDOW_H
