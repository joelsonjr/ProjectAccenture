#ifndef EMPRESTIMOVIEW_H
#define EMPRESTIMOVIEW_H

#include <QWidget>

#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsItem>
#include <QUrl>
#include <QDate>

#include "emprestimodao.h"

namespace Ui {
class Emprestimo;
}

class EmprestimoView : public QWidget
{
    Q_OBJECT

public:
    explicit EmprestimoView(QWidget *parent = 0);
    ~EmprestimoView();
    void doDownload();
    void holidays( const std::vector<QDate>& );

public slots:
    void fechar();
    void replyFinished (QNetworkReply *reply);
    void interpolar();
    void carregar();
    void onDownloadProgress(qint64,qint64);

private:
    void carregandoTaxaDI();    
    int32_t calcularDiasUteis(const QDate &dateIni, const QDate& dateEnd);
    void dadosCurvaJuros();
    void preencherGrafico();
    void loadCurve(const std::vector<EmprestimoDAO::DataCurva>&);
    void mouseWait();
    void mouseRestore();
private:
    Ui::Emprestimo *ui;
    QNetworkAccessManager *m_manager;
    std::vector <QDate> m_holyday;
    std::map<QDate,double> m_taxaDI;
    std::map<int32_t, double> m_dadosCurva;
    std::string m_fileDate;
    QGraphicsScene *m_scene;
    QGraphicsEllipseItem *m_ellipse;
    QGraphicsRectItem *m_rectangle;
    QGraphicsTextItem *m_text;
    EmprestimoDAO *m_emprestimoDao;
};

#endif // EMPRESTIMOVIEW_H
