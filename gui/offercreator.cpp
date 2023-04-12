#include "offercreator.h"
#include "ui_offercreator.h"

OfferCreator::OfferCreator(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::OfferCreator)
{
    ui->setupUi(this);
}

OfferCreator::~OfferCreator()
{
    delete ui;
}


//    QFrame popup;
//    popup.setFrameStyle(QFrame::Box | QFrame::Plain);
//    popup.setLineWidth(1);
//    popup.setAutoFillBackground(true);
//    popup.setStyleSheet("background-color: white");
//    popup.setWindowFlags(Qt::FramelessWindowHint);

//    QLabel label("Текст подсказки");
//    QPushButton button("Закрыть");
//    QObject::connect(&button, &QPushButton::clicked, &popup, &QWidget::hide);

//    QHBoxLayout layout(&popup);
//    layout.addWidget(&label);
//    layout.addWidget(&button);
//    layout.setMargin(2);

//    QPushButton buttonWithPopup("Нажми меня");
//    QObject::connect(&buttonWithPopup, &QPushButton::clicked, [&popup, &buttonWithPopup]()
//    {
//        QPoint pos = buttonWithPopup.mapToGlobal(QPoint(0, buttonWithPopup.height()));
//        popup.move(pos);
//        popup.show();
//    });

//    QObject::connect(&a, &QApplication::focusChanged, [&popup, &buttonWithPopup](){
//        if (!popup.underMouse() && !buttonWithPopup.underMouse() && !buttonWithPopup.hasFocus())
//        {
//            popup.hide();
//        }
//    });

//    QVBoxLayout mainLayout;
//    mainLayout.addWidget(&buttonWithPopup);
//    mainLayout.setMargin(10);

//    QWidget window;
//    window.resize(300,100);
//    window.setLayout(&mainLayout);
//    window.show();


    //---------------------------------------------------------------------------

//    QWidget mainWidget;
//    QVBoxLayout mainLayout(&mainWidget);
//    mainWidget.setLayout(&mainLayout);

//    QPushButton button("Нажми меня");
//    QLabel popup("Всплывающее окно!", &mainWidget);
//    QPushButton closePopupButton("+", &mainWidget);
//    closePopupButton.hide();

//    QFrame popupContainer(&mainWidget);
//    QHBoxLayout popupLayout(&popupContainer);
//    popupLayout.addWidget(&popup);
//    popupLayout.addWidget(&closePopupButton);
//    popupLayout.setMargin(2);
//    popupLayout.setSpacing(2);
//    popupContainer.hide();
//    popupContainer.setStyleSheet("background-color: #f5f5f5; border: 1px solid #ccc;");

//    QObject::connect(&button, &QPushButton::clicked, [&]()
//    {
//        if(!popupContainer.isVisible())
//        {
//            QPoint pos = button.mapToGlobal(QPoint(0, button.height()));
//            popupContainer.move(pos);
//            popupContainer.show();
//            popupContainer.raise();
//            closePopupButton.show();
//        }
//    });

//    QObject::connect(&closePopupButton, &QPushButton::clicked, &popupContainer, &QFrame::hide);
//    QObject::connect(qApp, &QApplication::focusChanged, [&]()
//    {
//        if (!popupContainer.underMouse() && !button.underMouse() && !button.hasFocus())
//            popupContainer.hide();
//    });

//    mainLayout.addWidget(&button);
//    mainLayout.addWidget(&popupContainer);

//    mainWidget.show();
