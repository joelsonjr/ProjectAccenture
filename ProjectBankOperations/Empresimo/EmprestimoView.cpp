#include "EmprestimoView.h"

#include <iostream>
#include <utility>
#include <fstream>
#include <math.h>
#include <stdlib.h>
#include <cstdio>
#include <unordered_map>
#include <QFileInfo>
#include <QFile>
#include <QMessageBox>
#include <QIODevice>
#include <QProcess>

#include <QXmlStreamReader>
#include "ui_emprestimo.h"

EmprestimoView::EmprestimoView(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Emprestimo),
    m_emprestimoDao(new EmprestimoDAO())
{
    ui->setupUi(this);
    ui->lblDownload->setText(QString("Downloading: 0 DE 0"));
    ui->deditDataCurva->setDate(QDate::currentDate());
    ui->deditDataInterpolacao->setDate(QDate::currentDate());

    m_scene = new QGraphicsScene(this);
    ui->graphics->setScene(m_scene);

    m_emprestimoDao->createDatabase();
    }

EmprestimoView::~EmprestimoView()
{
    delete ui;
}

void EmprestimoView::fechar()
{
    this->close();
}

void EmprestimoView::carregar()
{
    doDownload();
}

void EmprestimoView::loadCurve(const std::vector<EmprestimoDAO::DataCurva>& dataCurve)
{
    m_taxaDI.clear();
    {
        for(const auto & it : dataCurve)
        {
            const std::string& str = it.dataTx;
            const int32_t day = std::stol(str.substr(6,2));
            const int32_t month = std::stol(str.substr(4,2));
            const int32_t year = std::stol(str.substr(0,4));
            QDate date(year, month, day);
            m_taxaDI[date] = it.valor;
        }
    }
    ui->tblCalculo->setRowCount(m_taxaDI.size());
    {
        int i = 0;
        for( const auto &it : m_taxaDI)
        {
            const QDate& date = it.first;
            ui->tblCalculo->setItem(i,0,new QTableWidgetItem(date.toString(Qt::SystemLocaleDate)));
            ui->tblCalculo->setItem(i,1,new QTableWidgetItem(QString::number(it.second) + "%"));
            ++i;
        }
    }
    dadosCurvaJuros();
}

void EmprestimoView::doDownload()
{    
    QDate date = ui->deditDataCurva->date();
    std::string day = QString::number(date.day()).toStdString();
    std::string month = QString::number(date.month()).toStdString();
    std::string year = QString::number(date.year()).toStdString();
    if(month.size() == 1)
        month = "0" + month;
    if(day.size() == 1)
        day = "0" + day;
    m_fileDate = year.substr(2,2) + month + day;

    std::vector<EmprestimoDAO::DataCurva> dataCurve;
    m_emprestimoDao->retrievelData(m_fileDate, dataCurve);

    if(!dataCurve.empty())
    {
        loadCurve(dataCurve);
        return;
    }
    const std::string url = "http://www.bmf.com.br/ftp/ContratosPregaoFinal/BF" + m_fileDate + ".ex_";

    m_manager = new QNetworkAccessManager(this);
    QNetworkReply *response = m_manager->get(QNetworkRequest(QUrl(QString(url.c_str()))));

    connect(response,SIGNAL(downloadProgress(qint64,qint64)),
            this,SLOT(onDownloadProgress(qint64,qint64)));

    connect(m_manager, SIGNAL(finished(QNetworkReply*)),
            this, SLOT(replyFinished(QNetworkReply*)));
}

void EmprestimoView::onDownloadProgress(qint64 bytesRead,qint64 bytesTotal)
{
    ui->lblDownload->setText(QString("Downloading: ") + QString::number(bytesRead).toLatin1() +" DE "+ QString::number(bytesTotal).toLatin1());
}


void EmprestimoView::replyFinished (QNetworkReply *reply)
{
    if(reply->error())
    {
        QString msg("Problema ao carregar o arquivo \n" + reply->errorString());
        QMessageBox::information(this, "Error", msg , QMessageBox::Ok);
        return;
    }

    QUrl url = reply->url();
    QString path = url.path();
    QString basename = QFileInfo(path).fileName();

    qDebug() << basename;

    basename.replace("ex_", "exe");
    qDebug() << basename;
    QFile file(basename);
    if (!file.open(QIODevice::WriteOnly)) {
        qDebug() << "Erro ao abrir o arquivo";
        return;
    }

    file.write(reply->readAll());
    file.close();

    system(basename.toStdString().c_str());

    reply->deleteLater();

    carregandoTaxaDI();

    dadosCurvaJuros();

    std::remove(basename.toStdString().c_str());
}

void EmprestimoView::carregandoTaxaDI()
{
    mouseWait();
    std::ifstream file;
    const std::string filename = "BD_Final.txt";
    file.open(filename);

    if(!file.is_open())
    {
        qDebug() << " Error ao abrir o arquivo ";
        return;
    }

    std::string line;
    m_taxaDI.clear();
    while(getline(file, line))
    {
        if(line.find("DI1", 21, 3) != std::string::npos)
        {
            EmprestimoDAO::DataCurva datac;
            const std::string& d = line.substr(36,8);
            const int32_t day = std::stol(d.substr(6,2));
            const int32_t month = std::stol(d.substr(4,2));
            const int32_t year = std::stol(d.substr(0,4));
            QDate date(year, month, day);
            datac.dataTx = d;
            datac.cotacao = std::stol(line.substr(231,13));
            datac.diasUteis = std::stol(line.substr(388,5));

            datac.valor = (pow((10000000/datac.cotacao),(252/datac.diasUteis)) - 1);

            m_taxaDI[date] = datac.valor;

            m_emprestimoDao->insertDataCurva(datac);
        }
    }
    file.close();

    ui->tblCalculo->setRowCount(m_taxaDI.size());
    int i = 0;
    for( const auto &it : m_taxaDI)
    {
        const QDate& date = it.first;
        ui->tblCalculo->setItem(i,0,new QTableWidgetItem(date.toString(Qt::SystemLocaleDate)));
        ui->tblCalculo->setItem(i,1,new QTableWidgetItem(QString::number(it.second) + "%"));
        ++i;
    }
    m_emprestimoDao->insertData(m_fileDate);

    std::remove(filename.c_str());
    mouseRestore();
}

void EmprestimoView::holidays(const std::vector<QDate>& holyday)
{
    m_holyday = holyday;
}

int32_t EmprestimoView::calcularDiasUteis(const QDate &dateIni, const QDate& dateEnd)
{
    if(dateIni ==  dateEnd)
        return 0;

    int32_t d = 0;

    QDate date(dateIni.year(), dateIni.month(), dateIni.day());

    int i = 0;
    bool hasSaturday = false;
    bool hasSunday = false;
    while(date <= dateEnd)
    {
        if(date.dayOfWeek() ==  6)
        {
            hasSaturday = true;
        }

        if(date.dayOfWeek() == 7)
        {
            hasSunday = true;
            break;
        }
        ++i;
       date = date.addDays(1);
    }
    if(!hasSaturday){
        d = i - 1;
    }else if( (hasSaturday ==  true) && (hasSunday ==  false)){
        d = dateIni.daysTo(dateEnd) - 1;
    }else if ( (hasSaturday ==  true) && (hasSunday ==  true))
    {
        double numDiasTemp = date.daysTo(dateEnd);
        int numfds = (int)numDiasTemp / 7;
        if(numfds != 0)
        {
            d = i + date.daysTo(dateEnd) - (numfds * 2) - 2;
        }else
            d = dateIni.daysTo(dateEnd) - 2;
        if(dateEnd.dayOfWeek() ==  6)
            d -= 1;
    }
    auto itIni = std::lower_bound(m_holyday.begin(), m_holyday.end(), dateIni);
    if(itIni == m_holyday.end())
        return d;
    auto itEnd = std::upper_bound(m_holyday.begin(), m_holyday.end(), dateEnd);

    while(itIni != itEnd)
    {
        if((itIni->dayOfWeek() != 6) && (itIni->dayOfWeek() != 7))
            d -= 1;
        ++itIni;
    }
    return d;
}

void EmprestimoView::preencherGrafico()
{
    m_scene->clear();
    auto it = m_dadosCurva.rbegin();
    m_scene->clear();
    QBrush redBrush(Qt::red);
    QPen outlinePen(Qt::black);

    outlinePen.setWidth(2);
    m_scene->addLine(0, 0, it->first + 5, 0, outlinePen);
    m_scene->addLine(0, 0, 0, -250, outlinePen);

    for(const auto& itT : m_dadosCurva)
    {
        int32_t duteis = itT.first;
        double valor = itT.second * -1;
        m_scene->addEllipse(duteis, (valor - 2.5), 5, 5, outlinePen, redBrush);
    }
}

void EmprestimoView::interpolar()
{
    if(m_taxaDI.empty())
        return;

    const auto& itI = m_taxaDI.begin();
    const QDate& dateIni = itI->first;
    const auto& itE = m_taxaDI.rbegin();
    const QDate& dateEnd = itE->first;

    QDate dateInterpolacao = ui->deditDataInterpolacao->date();

    if( (dateIni > dateInterpolacao) || (dateInterpolacao > dateEnd) )
    {
        QMessageBox::information(this, "Error", QString("Data da interppolação fora do intervalo \n") , QMessageBox::Ok);
        return;
    }

    const int32_t & diasUteis = calcularDiasUteis(dateIni, dateInterpolacao);

    auto it = m_dadosCurva.upper_bound(diasUteis);
    const int32_t& dx2 = it->first;
    const double& ty2 = it->second;

    --it;
    const int32_t& dx1 = it->first;
    const double& ty1 = it->second;

    double a = ty1 - ty2;
    int32_t b = dx2 - dx1;
    double c = (dx1 * ty2) - (dx2 * ty1);
    double num = (a*diasUteis) + c;
    double num2 =  b;
    double result = (num / num2) * -1;
    ui->txtValor->setText(QString::number(result) + "%");

    m_dadosCurva[diasUteis] = result;

    preencherGrafico();
}

void EmprestimoView::dadosCurvaJuros()
{
    QDate dateInicial;
    m_dadosCurva.clear();
    for(auto it = m_taxaDI.begin() ; it != m_taxaDI.end(); ++it)
    {
        const QDate& d = it->first;
        const double & value = it->second;
        if(it == m_taxaDI.begin())
        {
            m_dadosCurva[0] = value;
            dateInicial.setDate(d.year(), d.month(), d.day());
            continue;
        }
        const int32_t & diasUteis = calcularDiasUteis(dateInicial, d);
        m_dadosCurva[diasUteis] = value;
    }
    preencherGrafico();
}

void EmprestimoView::mouseWait()
{
    QApplication::setOverrideCursor(Qt::WaitCursor);
}

void EmprestimoView::mouseRestore()
{
    QApplication::setOverrideCursor(Qt::ArrowCursor);
}



