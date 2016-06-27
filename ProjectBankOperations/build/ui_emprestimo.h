/********************************************************************************
** Form generated from reading UI file 'emprestimo.ui'
**
** Created by: Qt User Interface Compiler version 5.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_EMPRESTIMO_H
#define UI_EMPRESTIMO_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDateEdit>
#include <QtWidgets/QGraphicsView>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Emprestimo
{
public:
    QPushButton *btnSair;
    QWidget *horizontalLayoutWidget;
    QHBoxLayout *horizontalLayout;
    QVBoxLayout *verticalLayout;
    QGridLayout *gridLayout;
    QPushButton *btnCarregar;
    QLabel *label;
    QDateEdit *deditDataCurva;
    QLabel *lblDownload;
    QTableWidget *tblCalculo;
    QGridLayout *gridLayout_2;
    QLabel *label_3;
    QLineEdit *txtValor;
    QPushButton *btnCalcular;
    QLabel *label_2;
    QDateEdit *deditDataInterpolacao;
    QGridLayout *gridLayout_3;
    QLabel *label_4;
    QLabel *label_5;
    QGraphicsView *graphics;

    void setupUi(QWidget *Emprestimo)
    {
        if (Emprestimo->objectName().isEmpty())
            Emprestimo->setObjectName(QStringLiteral("Emprestimo"));
        Emprestimo->resize(553, 382);
        Emprestimo->setMinimumSize(QSize(553, 382));
        Emprestimo->setMaximumSize(QSize(553, 382));
        btnSair = new QPushButton(Emprestimo);
        btnSair->setObjectName(QStringLiteral("btnSair"));
        btnSair->setGeometry(QRect(410, 350, 130, 23));
        horizontalLayoutWidget = new QWidget(Emprestimo);
        horizontalLayoutWidget->setObjectName(QStringLiteral("horizontalLayoutWidget"));
        horizontalLayoutWidget->setGeometry(QRect(10, 10, 531, 331));
        horizontalLayout = new QHBoxLayout(horizontalLayoutWidget);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(6);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        gridLayout = new QGridLayout();
        gridLayout->setSpacing(6);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        btnCarregar = new QPushButton(horizontalLayoutWidget);
        btnCarregar->setObjectName(QStringLiteral("btnCarregar"));

        gridLayout->addWidget(btnCarregar, 1, 1, 1, 1);

        label = new QLabel(horizontalLayoutWidget);
        label->setObjectName(QStringLiteral("label"));

        gridLayout->addWidget(label, 0, 0, 1, 1);

        deditDataCurva = new QDateEdit(horizontalLayoutWidget);
        deditDataCurva->setObjectName(QStringLiteral("deditDataCurva"));

        gridLayout->addWidget(deditDataCurva, 1, 0, 1, 1);


        verticalLayout->addLayout(gridLayout);

        lblDownload = new QLabel(horizontalLayoutWidget);
        lblDownload->setObjectName(QStringLiteral("lblDownload"));

        verticalLayout->addWidget(lblDownload);

        tblCalculo = new QTableWidget(horizontalLayoutWidget);
        if (tblCalculo->columnCount() < 2)
            tblCalculo->setColumnCount(2);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        tblCalculo->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        tblCalculo->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        tblCalculo->setObjectName(QStringLiteral("tblCalculo"));
        tblCalculo->setAutoFillBackground(false);
        tblCalculo->setFrameShape(QFrame::Panel);
        tblCalculo->setFrameShadow(QFrame::Plain);
        tblCalculo->setDragDropMode(QAbstractItemView::NoDragDrop);
        tblCalculo->setSelectionMode(QAbstractItemView::SingleSelection);
        tblCalculo->setColumnCount(2);

        verticalLayout->addWidget(tblCalculo);

        gridLayout_2 = new QGridLayout();
        gridLayout_2->setSpacing(6);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        label_3 = new QLabel(horizontalLayoutWidget);
        label_3->setObjectName(QStringLiteral("label_3"));

        gridLayout_2->addWidget(label_3, 2, 0, 1, 1);

        txtValor = new QLineEdit(horizontalLayoutWidget);
        txtValor->setObjectName(QStringLiteral("txtValor"));

        gridLayout_2->addWidget(txtValor, 2, 1, 1, 1);

        btnCalcular = new QPushButton(horizontalLayoutWidget);
        btnCalcular->setObjectName(QStringLiteral("btnCalcular"));

        gridLayout_2->addWidget(btnCalcular, 1, 1, 1, 1);

        label_2 = new QLabel(horizontalLayoutWidget);
        label_2->setObjectName(QStringLiteral("label_2"));

        gridLayout_2->addWidget(label_2, 0, 0, 1, 1);

        deditDataInterpolacao = new QDateEdit(horizontalLayoutWidget);
        deditDataInterpolacao->setObjectName(QStringLiteral("deditDataInterpolacao"));

        gridLayout_2->addWidget(deditDataInterpolacao, 1, 0, 1, 1);


        verticalLayout->addLayout(gridLayout_2);


        horizontalLayout->addLayout(verticalLayout);

        gridLayout_3 = new QGridLayout();
        gridLayout_3->setSpacing(6);
        gridLayout_3->setObjectName(QStringLiteral("gridLayout_3"));
        label_4 = new QLabel(horizontalLayoutWidget);
        label_4->setObjectName(QStringLiteral("label_4"));

        gridLayout_3->addWidget(label_4, 0, 0, 1, 1);

        label_5 = new QLabel(horizontalLayoutWidget);
        label_5->setObjectName(QStringLiteral("label_5"));
        label_5->setLayoutDirection(Qt::LeftToRight);

        gridLayout_3->addWidget(label_5, 1, 1, 1, 1);

        graphics = new QGraphicsView(horizontalLayoutWidget);
        graphics->setObjectName(QStringLiteral("graphics"));

        gridLayout_3->addWidget(graphics, 0, 1, 1, 1);


        horizontalLayout->addLayout(gridLayout_3);

        horizontalLayoutWidget->raise();
        btnSair->raise();

        retranslateUi(Emprestimo);
        QObject::connect(btnSair, SIGNAL(clicked()), Emprestimo, SLOT(fechar()));
        QObject::connect(btnCalcular, SIGNAL(clicked()), Emprestimo, SLOT(interpolar()));
        QObject::connect(btnCarregar, SIGNAL(clicked()), Emprestimo, SLOT(carregar()));

        QMetaObject::connectSlotsByName(Emprestimo);
    } // setupUi

    void retranslateUi(QWidget *Emprestimo)
    {
        Emprestimo->setWindowTitle(QApplication::translate("Emprestimo", "Emprestimo", 0));
        btnSair->setText(QApplication::translate("Emprestimo", "Sair", 0));
        btnCarregar->setText(QApplication::translate("Emprestimo", "Carregar", 0));
        label->setText(QApplication::translate("Emprestimo", "Data da curva:", 0));
        lblDownload->setText(QString());
        QTableWidgetItem *___qtablewidgetitem = tblCalculo->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QApplication::translate("Emprestimo", "Data", 0));
        QTableWidgetItem *___qtablewidgetitem1 = tblCalculo->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QApplication::translate("Emprestimo", "Taxa", 0));
        label_3->setText(QApplication::translate("Emprestimo", "Valor:", 0));
        btnCalcular->setText(QApplication::translate("Emprestimo", "Calcular", 0));
        label_2->setText(QApplication::translate("Emprestimo", "Inerpolar data para taxa: ", 0));
        label_4->setText(QApplication::translate("Emprestimo", "<html><head/><body><p>T</p><p>A</p><p>X</p><p>A</p></body></html>", 0));
        label_5->setText(QApplication::translate("Emprestimo", "                        N\303\272mero de dias ut\303\251is", 0));
    } // retranslateUi

};

namespace Ui {
    class Emprestimo: public Ui_Emprestimo {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_EMPRESTIMO_H
