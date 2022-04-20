#include "obraz.h"
#include <QScreen>
#include <QtWidgets/QMessageBox>

void Ui_Obraz::setupUi(QWidget *obraz)
{
        if (obraz->objectName().isEmpty())
            obraz->setObjectName(QStringLiteral("Obraz"));
        QSizePolicy sizePolicy(QSizePolicy::Ignored, QSizePolicy::MinimumExpanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(obraz->sizePolicy().hasHeightForWidth());
        obraz->setSizePolicy(sizePolicy);
        //Obraz->setMinimumSize(QSize(380, 230));
        obraz->setWindowTitle(QStringLiteral(""));
        verticalLayoutWidget = new QWidget(obraz);
        verticalLayoutWidget->setObjectName(QStringLiteral("verticalLayoutWidget"));
        //verticalLayoutWidget->setGeometry(QRect(30, 60, 352, 231));
        verticalLayout = new QVBoxLayout(verticalLayoutWidget);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setContentsMargins(5, 5, 5, 5);
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        horizontalSpacer_2 = new QSpacerItem(20, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_2);

        scale_label = new QLabel(verticalLayoutWidget);
        scale_label->setObjectName(QStringLiteral("scale_label"));
        QSizePolicy sizePolicy1(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(scale_label->sizePolicy().hasHeightForWidth());
        scale_label->setSizePolicy(sizePolicy1);
        scale_label->setMinimumSize(QSize(50, 20));

        horizontalLayout_2->addWidget(scale_label);

        scale_value = new QSpinBox(verticalLayoutWidget);
        scale_value->setObjectName(QStringLiteral("scale_value"));
        scale_value->setEnabled(true);
        sizePolicy1.setHeightForWidth(scale_value->sizePolicy().hasHeightForWidth());
        scale_value->setSizePolicy(sizePolicy1);
        scale_value->setMinimumSize(QSize(50, 20));

        horizontalLayout_2->addWidget(scale_value);

        pause_label = new QLabel(verticalLayoutWidget);
        pause_label->setObjectName(QStringLiteral("pause_label"));
        sizePolicy1.setHeightForWidth(pause_label->sizePolicy().hasHeightForWidth());
        pause_label->setSizePolicy(sizePolicy1);
        pause_label->setMinimumSize(QSize(150, 20));

        horizontalLayout_2->addWidget(pause_label);

        pause_factor = new QSpinBox(verticalLayoutWidget);
        pause_factor->setObjectName(QStringLiteral("pause_factor"));
        pause_factor->setEnabled(true);
        sizePolicy1.setHeightForWidth(pause_factor->sizePolicy().hasHeightForWidth());
        pause_factor->setSizePolicy(sizePolicy1);

        horizontalLayout_2->addWidget(pause_factor);


        verticalLayout->addLayout(horizontalLayout_2);

        scrollArea = new QScrollArea(verticalLayoutWidget);
        scrollArea->setObjectName(QStringLiteral("scrollArea"));
        QSizePolicy sizePolicy2(QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(scrollArea->sizePolicy().hasHeightForWidth());
        scrollArea->setSizePolicy(sizePolicy2);
        scrollArea->setWidgetResizable(true);
        all_lives = new QLabel();
        all_lives->setObjectName(QStringLiteral("all_lives"));
        all_lives->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
        
        scrollArea->setWidget(all_lives);
        all_lives->setScaledContents(false);

        verticalLayout->addWidget(scrollArea);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_3);

        pause_button = new QPushButton(verticalLayoutWidget);
        pause_button->setObjectName(QStringLiteral("pause_button"));
        QSizePolicy sizePolicy4(QSizePolicy::Maximum, QSizePolicy::Fixed);
        sizePolicy4.setHorizontalStretch(0);
        sizePolicy4.setVerticalStretch(0);
        sizePolicy4.setHeightForWidth(pause_button->sizePolicy().hasHeightForWidth());
        pause_button->setSizePolicy(sizePolicy4);

        horizontalLayout->addWidget(pause_button);

        end_button = new QPushButton(verticalLayoutWidget);
        end_button->setObjectName(QStringLiteral("end_button"));
        sizePolicy4.setHeightForWidth(end_button->sizePolicy().hasHeightForWidth());
        end_button->setSizePolicy(sizePolicy4);

        horizontalLayout->addWidget(end_button);


        verticalLayout->addLayout(horizontalLayout);

        //verticalLayoutWidget->raise();

        retranslateUi(obraz);

        QMetaObject::connectSlotsByName(obraz);
    } // setupUi

 void Ui_Obraz::retranslateUi(QWidget *obraz)
    {
        scale_label->setText(QApplication::translate("Obraz", "Skala", Q_NULLPTR));
        pause_label->setText(QApplication::translate("Obraz", "Przerwa mi\304\231dzy cyklami x100 [ms]", Q_NULLPTR));
        pause_button->setText(QApplication::translate("Obraz", "Start", Q_NULLPTR));
        end_button->setText(QApplication::translate("Obraz", "Koniec", Q_NULLPTR));
        Q_UNUSED(obraz);
    } // retranslateUi


Ui::Obraz::Obraz(const uchar *_data, NS_GoL::index _cols, NS_GoL::index _rows):Ui_Obraz()
{
  setupUi(this);
  
  timer = new QTimer();
  image = new QImage(_data, _cols, _rows, _cols / CHAR_BIT, QImage::Format_MonoLSB);
  if (image == NULL || timer == NULL)
  {
      QMessageBox msg;
      msg.setText("Insufficient memory [image or timer]");
      msg.exec();
      close();
  }
  
  QScreen *screen = QGuiApplication::primaryScreen();
  QRect  screenGeometry = screen->geometry();
  max_size.setHeight(screenGeometry.height() * 24/30);
  max_size.setWidth(screenGeometry.width() * 29/30);
  min_size.setHeight(150);
  min_size.setWidth(350);
  scale_value->setValue(1);
  scale_value->setRange(1,15);
  pause_factor->setValue(5);
  pause_factor->setRange(1,50) ;
  
  connect(timer, &QTimer::timeout, this, &Ui::Obraz::refresh);
  connect(pause_factor, SIGNAL(valueChanged(int)), this, SLOT(pause_changed(int)));
  connect(scale_value, SIGNAL(valueChanged(int)), this, SLOT(ustaw_wielkosc(void)));
  connect(pause_button, &QPushButton::clicked, this, &Ui::Obraz::run_stop);
  connect(end_button, &QPushButton::clicked, this, &Ui::Obraz::close);
  run = 0;
  window_title.clear();
  window_title = QString("%1 x %2").arg(_cols).arg(_rows);
  setWindowTitle(window_title);
  move(10,10);
  ustaw_wielkosc();
  pause_changed(pause_factor->value());
}

void Ui::Obraz::run_stop(void)
{
  if(timer->isActive())
  {
    pause_button->setText("Start");
    timer->stop();
  }
  else
  {
    pause_button->setText("Pause");
    timer->start();
  }
}

Ui::Obraz::~Obraz()
{
 if(image)
  delete image;
}

void Ui::Obraz::refresh(void)
{
  NS_GoL::next_cycle();
  all_lives->setPixmap(QPixmap::fromImage(*image).scaled(image->size() * scale_value->text().toInt(), Qt::KeepAspectRatio));
  setWindowTitle((operator+(window_title, ", krok: %1")).arg(++run));
}

void Ui::Obraz::pause_changed(int _value) 
{
  timer->setInterval(_value*100);
}

void Ui::Obraz::ustaw_wielkosc(void)
{ 
 QSize actual_size(image->width()*scale_value->text().toInt() + 10, image->height()*scale_value->text().toInt() + 25);
 all_lives->setPixmap(QPixmap::fromImage(*image).scaled(image->size() * scale_value->text().toInt(), Qt::KeepAspectRatio));
 setMaximumSize(actual_size.boundedTo(max_size));
 setMaximumSize(maximumSize().expandedTo(min_size));
 setMaximumSize(operator+(maximumSize(), QSize(25,80)));
 setMinimumSize(maximumSize());
 resize(size());
 verticalLayoutWidget->setGeometry(0, 0, width(), height() - 5);
}

