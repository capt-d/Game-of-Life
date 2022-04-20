/********************************************************************************
** Form generated from reading UI file 'gol.ui_kopia'
**
** Created by: Qt User Interface Compiler version 5.9.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_GOL_H
#define UI_GOL_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QWidget>
#include "gol_core.h"
#include "UIntValidator.h"

QT_BEGIN_NAMESPACE

class Ui_GoLWindow: public QMainWindow
{
public:
    QWidget *centralwidget;
    QWidget *gridLayoutWidget;
    QGridLayout *gridLayout;
    QHBoxLayout *horizontalLayout_6;
    QPushButton *start;
    QPushButton *stop;
    QSpacerItem *verticalSpacer_2;
    QCheckBox *set_torus;
    QPushButton *init_board;
    QSpacerItem *horizontalSpacer;
    QFormLayout *formLayout;
    QLabel *szerokoLabel;
    QLineEdit *cols;
    QLabel *wysokoLabel;
    QLineEdit *rows;
    QSpacerItem *horizontalSpacer_2;
    QFormLayout *formLayout_3;
    QLabel *procentYwychLabel;
    QLineEdit *percent;
    QFormLayout *formLayout_2;
    QLabel *iloWTkWLabel;
    QLineEdit *threads_count;
    QSpacerItem *verticalSpacer;
    
    void setupUi(QMainWindow *GoLWindow);
    void retranslateUi(QMainWindow *GoLWindow);
};

namespace Ui {
    class Obraz;
     
    class GoLWindow: public Ui_GoLWindow {
      Q_OBJECT
           
          private: 
            class pointer {
              public: 
                const uchar *data;
                pointer(const uchar *_data);
              };
            pointer *bity = NULL;
            UIntValidator *ui_validator = NULL;
            QDoubleValidator *percent_validator = NULL;
            Obraz *obraz = NULL;
            
            void preinit_game_setup(void);
            void init_game(void);            
            void stop_game(void);
            
            void enable_init(void);
            void enter_next(void);
            void zakoncz(void);
            void show_image(void);
             
        public slots:  
             void focusChanged(QWidget*, QWidget*); 
        
        public: 
         GoLWindow();
         ~GoLWindow();   
  };
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_GOL_H
