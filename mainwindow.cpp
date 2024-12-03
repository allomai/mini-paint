#include "mainwindow.h"
#include "canvas.h"
#include "./ui_mainwindow.h"
#include <QTextEdit>
#include <QToolBar>

#include <QFileDialog>
#include <QtGlobal>
#include <QDir>
#include <QFile>
#include <QMessageBox>
#include <QPushButton>
#include <QCloseEvent>
#include <QPainter>
#include <QButtonGroup>
#include <QGroupBox>
#include <QHBoxLayout>
#include <QActionGroup>
#include <QToolButton>
#include <QAbstractButton>
#include <QPalette>
#include <QDebug>
#include <QSlider>



MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{

    Canvas* canvas = new Canvas(600, 400);
    this->setCentralWidget(canvas);

    QPalette pal = QPalette();
    pal.setColor(QPalette::Window, Qt::white);
    canvas->setAutoFillBackground(true);
    canvas->setPalette(pal);

    QToolButton *black = new QToolButton;
    QToolButton *blue = new QToolButton;
    QToolButton *green = new QToolButton;
    QToolButton *orange = new QToolButton;
    QToolButton *pink = new QToolButton;
    QToolButton *purple = new QToolButton;
    QToolButton *line = new QToolButton;
    QToolButton *rect = new QToolButton;
    QToolButton *elps = new QToolButton;
    QToolButton *solid = new QToolButton;
    QToolButton *dashed = new QToolButton;
    QToolButton *dotted = new QToolButton;
    QToolButton *draw = new QToolButton;
    QToolButton *select = new QToolButton;
    QToolButton *resize = new QToolButton;

    black -> setIcon(QIcon(":/images/black.png"));
    blue -> setIcon(QIcon(":/images/blue.png"));
    green -> setIcon(QIcon(":/images/green.png"));
    orange -> setIcon(QIcon(":/images/orange.png"));
    pink -> setIcon(QIcon(":/images/pink.png"));
    purple -> setIcon(QIcon(":/images/purple.png"));
    line->setIcon(QIcon(":/images/diagonal-line.png"));
    rect->setIcon(QIcon(":/images/rectangle.png"));
    elps->setIcon(QIcon(":/images/ellipse.png"));
    solid->setIcon(QIcon(":/images/straight-line.png"));
    dashed->setIcon(QIcon(":/images/dashed-line.png"));
    dotted->setIcon(QIcon(":/images/dotted-line.png"));
    select->setIcon(QIcon(":/images/selection.png"));
    draw->setIcon(QIcon(":/images/drawing.png"));
    resize->setIcon(QIcon(":/images/resize.png"));

    black->setCheckable(true);
    blue->setCheckable(true);
    green->setCheckable(true);
    orange->setCheckable(true);
    pink->setCheckable(true);
    purple->setCheckable(true);
    line->setCheckable(true);
    rect->setCheckable(true);
    elps->setCheckable(true);
    solid->setCheckable(true);
    dashed->setCheckable(true);
    dotted->setCheckable(true);
    select->setCheckable(true);
    draw->setCheckable(true);
    resize->setCheckable(true);

    //select->setAutoExclusive(true);

    QButtonGroup *colors = new QButtonGroup(this);
    QButtonGroup *shapes = new QButtonGroup(this);
    QButtonGroup *styles = new QButtonGroup(this);
    QButtonGroup *interactions = new QButtonGroup(this);

    connect(colors, &QButtonGroup::idClicked, canvas, &Canvas::setColor);
    connect(shapes, &QButtonGroup::idClicked, canvas, &Canvas::setShape);
    connect(styles, &QButtonGroup::idClicked, canvas, &Canvas::setStyle);
    connect(interactions, &QButtonGroup::idClicked, canvas, &Canvas::setInteraction);

    /*connect(colors, QOverload<QAbstractButton *>::of(&QButtonGroup::buttonClicked), this, &MainWindow::uncheckSelectIfOtherClicked);
    connect(shapes, QOverload<QAbstractButton *>::of(&QButtonGroup::buttonClicked), this, &MainWindow::uncheckSelectIfOtherClicked);
    connect(styles, QOverload<QAbstractButton *>::of(&QButtonGroup::buttonClicked), this, &MainWindow::uncheckSelectIfOtherClicked);*/

    colors->addButton(black);
    colors->addButton(blue);
    colors->addButton(green);
    colors->addButton(orange);
    colors->addButton(pink);
    colors->addButton(purple);
    shapes->addButton(line);
    shapes->addButton(rect);
    shapes->addButton(elps);
    styles->addButton(solid);
    styles->addButton(dashed);
    styles->addButton(dotted);
    interactions->addButton(draw);
    interactions->addButton(select);
    interactions->addButton(resize);

    black->setChecked(true);
    line->setChecked(true);
    solid->setChecked(true);
    draw->setChecked(true);

    colors->setId(black, 1);
    colors->setId(blue, 2);
    colors->setId(green, 3);
    colors->setId(orange, 4);
    colors->setId(pink, 5);
    colors->setId(purple, 6);
    shapes->setId(line, 1);
    shapes->setId(rect, 2);
    shapes->setId(elps, 3);
    styles->setId(solid, 1);
    styles->setId(dashed, 2);
    styles->setId(dotted, 3);
    interactions->setId(draw,1);
    interactions->setId(select,2);
    interactions->setId(resize,3);

    QHBoxLayout *hbox_lines = new QHBoxLayout;
    QHBoxLayout *hbox_shapes = new QHBoxLayout;
    QHBoxLayout *hbox_styles = new QHBoxLayout;
    QHBoxLayout *hbox_interactions = new QHBoxLayout;
    QGroupBox *colorGroupBox = new QGroupBox("");
    QGroupBox *shapeGroupBox = new QGroupBox("");
    QGroupBox *styleGroupBox = new QGroupBox("");
    QGroupBox *interactionGroupBox = new QGroupBox("");
    hbox_lines->addWidget(black);
    hbox_lines->addWidget(blue);
    hbox_lines->addWidget(green);
    hbox_lines->addWidget(orange);
    hbox_lines->addWidget(pink);
    hbox_lines->addWidget(purple);
    hbox_shapes->addWidget(line);
    hbox_shapes->addWidget(rect);
    hbox_shapes->addWidget(elps);
    hbox_styles->addWidget(solid);
    hbox_styles->addWidget(dashed);
    hbox_styles->addWidget(dotted);
    hbox_interactions->addWidget(draw);
    hbox_interactions->addWidget(select);
    hbox_interactions->addWidget(resize);
    colorGroupBox->setLayout(hbox_lines);
    shapeGroupBox->setLayout(hbox_shapes);
    styleGroupBox->setLayout(hbox_styles);
    interactionGroupBox->setLayout(hbox_interactions);

    colorGroupBox->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Fixed);
    shapeGroupBox->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Fixed);
    styleGroupBox->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Fixed);
    interactionGroupBox->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Fixed);

    QSlider* strokeSlider = new QSlider(Qt::Horizontal);
    strokeSlider->setRange(1, 50);  // Set the range of stroke size, e.g., from 1 to 50
    strokeSlider->setValue(5);      // Default stroke size is 5
    strokeSlider->setTickInterval(1);
    strokeSlider->setTickPosition(QSlider::TicksBelow);
    connect(strokeSlider, &QSlider::valueChanged, canvas, &Canvas::setStrokeSize);

    QToolBar* toolbar = this->addToolBar(tr("Toobar"));
    toolbar->addWidget(interactionGroupBox);
    toolbar->addSeparator();
    toolbar->addWidget(colorGroupBox);
    toolbar->addSeparator();
    toolbar->addWidget(shapeGroupBox);
    toolbar->addSeparator();
    toolbar->addWidget(styleGroupBox);

    toolbar->addSeparator();
    toolbar->addWidget(strokeSlider);

}

MainWindow::~MainWindow()
{
    delete ui;
}

/*void MainWindow::uncheckSelectIfOtherClicked()
{
    qDebug() << "was called!";
    QToolButton* selectButton = this->findChild<QToolButton*>("select");
    qDebug() << selectButton;
    qDebug() << selectButton->isChecked();
    if (selectButton && selectButton->isChecked()) {
        selectButton->setChecked(false);
        qDebug() << "here!";
    }
} */

void QWidget::closeEvent(QCloseEvent *event)
{
    QMessageBox msgBox;
    msgBox.setText("Are you sure you want to quit?");
    QAbstractButton *yesButton = msgBox.addButton(tr("Yes"), QMessageBox::ActionRole);
    QAbstractButton *noButton = msgBox.addButton(tr("No"), QMessageBox::ActionRole);
    msgBox.exec();

    if (msgBox.clickedButton() == noButton) {
        event->ignore();
    } else if (msgBox.clickedButton() == yesButton) {
        event->accept();
    }
}

void MainWindow::openFile()
{
    std::cout << "Open File" << std::endl;
    QString filename = QFileDialog::getOpenFileName(this, tr("Open File"), "C:/Users/mai/Documents/Ecole/M2_IGD_Cours", tr("Text files (*.txt)"));
    qDebug() << filename;
    QFile file(filename);
    if (file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QTextStream in(&file);
        //QString content = in.readAll();
        file.close();
    }
}

void MainWindow::saveFile()
{
    std::cout << "Save File" << std::endl;
    QString filename = QFileDialog::getSaveFileName(this, tr("Save File"), "C:/Users/mai/Documents/Ecole/M2_IGD_Cours", tr("Text files (*.txt)"));
    qDebug() << filename;
    QFile file(filename);
    if (file.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        QTextStream out(&file);
        file.close();
    }
}

void MainWindow::quitApp()
{
    std::cout << "Quit App" << std::endl;
    QMessageBox msgBox;
    msgBox.setText("Are you sure you want to quit?");
    QAbstractButton *yesButton = msgBox.addButton(tr("Yes"), QMessageBox::ActionRole);
    QAbstractButton *noButton = msgBox.addButton(tr("No"), QMessageBox::ActionRole);
    msgBox.exec();

    if (msgBox.clickedButton() == noButton) {
        msgBox.close();
    } else if (msgBox.clickedButton() == yesButton) {
        QApplication::quit();
    }

}
