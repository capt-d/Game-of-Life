/********************************************************************************
** Form generated from reading UI file 'obraz.ui'
**
** Created by: Qt User Interface Compiler version 5.9.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_OBRAZ_H
#define UI_OBRAZ_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QScrollArea>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include <QTimer>
#include "gol_core.h"
#include <QCloseEvent>

QT_BEGIN_NAMESPACE

class Ui_Obraz: public QWidget
{
Q_OBJECT
public:
    QWidget *verticalLayoutWidget;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout_2;
    QSpacerItem *horizontalSpacer_2;
    QLabel *scale_label;
    QSpinBox *scale_value;
    QLabel *pause_label;
    QSpinBox *pause_factor;
    QScrollArea *scrollArea;
    QWidget *scrollAreaWidgetContents;
    QLabel *all_lives;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer_3;
    QPushButton *pause_button;
    QPushButton *end_button;

    void setupUi(QWidget *);
    void retranslateUi(QWidget*);
  
signals: 
    virtual void closeEvent(QCloseEvent *event) = 0;
    virtual void mousePressEvent(QMouseEvent *ev) = 0;
};

namespace Ui {
    class Obraz: public Ui_Obraz {
    
    Q_OBJECT
      public:
        QImage *image = NULL;
        Obraz(const uchar *_data, const NS_GoL::index cols, const NS_GoL::index rows);
        ~Obraz();

      signals:
        void closeEvent(QCloseEvent *event);
        //void resizeEvent(QResizeEvent *event);
        void mousePressEvent(QMouseEvent *ev);

      private:
        QTimer *timer = NULL;
        void refresh(void);
        QSize max_size;
        QSize min_size;
        unsigned long long run;
        QString window_title;
      
      private slots:
        void pause_changed(int _value);
        void run_stop(void);
        void ustaw_wielkosc(void);
  };

} // namespace Ui

QT_END_NAMESPACE

#endif // UI_OBRAZ_H
