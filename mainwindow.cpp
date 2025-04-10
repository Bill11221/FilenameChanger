#include "mainwindow.h"
#include <QPushButton>
#include <QLineEdit>
#include <QTextEdit>
#include <QFileDialog>
#include <QDir>
#include <QFileInfoList>
#include <QFileInfo>
#include <QMessageBox>
#include <QVBoxLayout>
#include <QFile>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent)
{
    // 创建中央部件和布局
    QWidget *centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);

    // 创建控件
    editFolderPath = new QLineEdit(centralWidget);
    editFolderPath->setPlaceholderText("选择文件夹路径...");

    btnChooseFolder = new QPushButton("选择文件夹", centralWidget);
    btnRename = new QPushButton("开始重命名", centralWidget);

    textLog = new QTextEdit(centralWidget);
    textLog->setReadOnly(true);

    // 设置垂直布局
    QVBoxLayout *layout = new QVBoxLayout(centralWidget);
    layout->addWidget(editFolderPath);
    layout->addWidget(btnChooseFolder);
    layout->addWidget(btnRename);
    layout->addWidget(textLog);

    setWindowTitle("文件重命名工具");
    resize(600, 400);

    // 信号和槽连接
    connect(btnChooseFolder, &QPushButton::clicked, this, &MainWindow::chooseFolder);
    connect(btnRename, &QPushButton::clicked, this, &MainWindow::renameFiles);
}

void MainWindow::chooseFolder()
{
    // 弹出选择文件夹对话框
    QString folder = QFileDialog::getExistingDirectory(this, "选择文件夹", "");
    if (!folder.isEmpty()) {
        editFolderPath->setText(folder);
        textLog->append("选中的文件夹: " + folder);
    }
}

void MainWindow::renameFiles()
{
    QString folderPath = editFolderPath->text();
    if (folderPath.isEmpty()) {
        QMessageBox::warning(this, "错误", "请选择一个文件夹!");
        return;
    }

    QDir dir(folderPath);
    if (!dir.exists()) {
        QMessageBox::warning(this, "错误", "文件夹路径不存在!");
        return;
    }

    // 设置图片文件过滤器
    QStringList filters;
    filters << "*.jpg" << "*.jpeg" << "*.png" << "*.bmp" << "*.gif";

    // 获取文件列表，按文件名排序
    QFileInfoList fileList = dir.entryInfoList(filters, QDir::Files, QDir::Name);
    if (fileList.isEmpty()) {
        textLog->append("没有找到图片文件.");
        return;
    }

    textLog->append(QString("找到 %1 个文件, 开始重命名...").arg(fileList.size()));
    int count = 1;
    bool overallSuccess = true;

    // 遍历文件列表依次重命名
    for (const QFileInfo &fileInfo : fileList) {
        QString newFileName = QString::number(count) + "." + fileInfo.suffix();
        QString newFilePath = dir.absoluteFilePath(newFileName);
        QString oldFilePath = fileInfo.absoluteFilePath();

        // 检查新文件是否已存在
        if (QFile::exists(newFilePath)) {
            textLog->append(QString("文件 %1 已存在，跳过重命名。").arg(newFileName));
            ++count;
            continue;
        }

        // 执行重命名
        if (!QFile::rename(oldFilePath, newFilePath)) {
            textLog->append(QString("重命名失败：%1").arg(oldFilePath));
            overallSuccess = false;
        } else {
            textLog->append(QString("重命名: %1 -> %2").arg(fileInfo.fileName(), newFileName));
        }
        ++count;
    }

    if (overallSuccess)
        textLog->append("重命名完成!");
    else
        textLog->append("部分文件重命名失败，请检查日志信息！");
}
