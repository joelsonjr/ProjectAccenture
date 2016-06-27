#-------------------------------------------------
#
# Project created by QtCreator 2016-06-19T07:55:37
#
#-------------------------------------------------

QT       += core network gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Empresimo
TEMPLATE = app

SOURCES += main.cpp\
        EmprestimoView.cpp \
    EmprestimoControler.cpp \
    emprestimodao.cpp

HEADERS  += EmprestimoView.h \
    EmprestimoControler.h \
    emprestimodao.h

FORMS    += emprestimo.ui


