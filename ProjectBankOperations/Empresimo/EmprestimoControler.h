#ifndef EMPRESTIMOCONTROLER_H
#define EMPRESTIMOCONTROLER_H
#include "EmprestimoView.h"

#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QUrl>

class EmprestimoControler
{
public:
    EmprestimoControler();

    ~EmprestimoControler();
    void holidays();

private:
    EmprestimoView *m_emprestimoView;
    QNetworkAccessManager *m_manager;

private:

};

#endif // EMPRESTIMOCONTROLER_H
