#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include<iostream>
#define button_size_x 111
#define button_size_y 31
#define line_size_x 113
#define line_size_y 24

using namespace std;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui ->pushButton_salir_lista ->setFixedSize(0, 0);
    ui ->pushButton_buscar ->setFixedSize(0, 0);
    ui ->pushButton_salir_tabla ->setFixedSize(0, 0);
    ui ->pushButton_salir_mostrar ->setFixedSize(0, 0);
    ui ->plainTextEdit_lista ->setFixedSize(0, 0);
    ui ->line_buscar ->setFixedSize(0, 0);
    ui ->tableWidget_tabla ->setColumnCount(7);
    QString str1 ="Id", str2 ="Voltaje", str3 ="X", str4 ="Y", str5 ="Red", str6 ="Green", str7 ="Blue";
    QStringList labels =(QStringList() <<str1 <<str2 <<str3 <<str4 <<str5 <<str6 <<str7);
    ui ->tableWidget_tabla ->setHorizontalHeaderLabels(labels);
    ui ->tableWidget_tabla ->setFixedSize(0, 0);
    ui ->graphicsViews_ellipses ->setFixedSize(0, 0);
    ui ->graphicsViews_ellipses ->scale(2, 2);
    ui ->pushButton_por_id ->setFixedSize(0, 0);
    ui ->pushButton_por_voltaje ->setFixedSize(0, 0);
    ui ->pushButton_graficar ->setFixedSize(0, 0);
    ui ->plainTextEdit_adyacencia ->setFixedSize(0, 0);
    ui ->line_recorrido_id ->setFixedSize(0, 0);
    ui ->pushButton_recorrido_id ->setFixedSize(0, 0);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::ocultar_todo()
{
    ui ->label_id ->setText("");
    ui ->label_voltaje ->setText("");
    ui ->label_x ->setText("");
    ui ->label_y ->setText("");
    ui ->label_r ->setText("");
    ui ->label_g ->setText("");
    ui ->label_b ->setText("");
    ui ->line_id ->setFixedSize(0, 0);
    ui ->line_voltaje ->setFixedSize(0, 0);
    ui ->line_x ->setFixedSize(0, 0);
    ui ->line_y ->setFixedSize(0, 0);
    ui ->line_red ->setFixedSize(0, 0);
    ui ->line_green ->setFixedSize(0, 0);
    ui ->line_blue ->setFixedSize(0, 0);
    ui ->pushButton_add ->setFixedSize(0, 0);
    ui ->pushButton_addf ->setFixedSize(0, 0);
    ui ->pushButton_lista ->setFixedSize(0, 0);
    ui ->pushButton_tabla ->setFixedSize(0, 0);
    ui ->pushButton_mostrar ->setFixedSize(0, 0);
    ui ->pushButton_salir ->setFixedSize(0, 0);
    ui ->pushButton_ordenar ->setFixedSize(0, 0);
}

void MainWindow::mostrar_todo()
{
    ui ->label_id ->setText("Id:");
    ui ->label_voltaje ->setText("Voltaje:");
    ui ->label_x ->setText("Posicion X:");
    ui ->label_y ->setText("Posicion Y:");
    ui ->label_r ->setText("Red:");
    ui ->label_g ->setText("Green:");
    ui ->label_b ->setText("Blue:");
    ui ->line_id ->setFixedSize(line_size_x, line_size_y);
    ui ->line_voltaje ->setFixedSize(line_size_x, line_size_y);
    ui ->line_x ->setFixedSize(line_size_x, line_size_y);
    ui ->line_y ->setFixedSize(line_size_x, line_size_y);
    ui ->line_red ->setFixedSize(line_size_x, line_size_y);
    ui ->line_green ->setFixedSize(line_size_x, line_size_y);
    ui ->line_blue ->setFixedSize(line_size_x, line_size_y);
    ui ->pushButton_add ->setFixedSize(button_size_x, button_size_y);
    ui ->pushButton_addf ->setFixedSize(button_size_x, button_size_y);
    ui ->pushButton_lista ->setFixedSize(button_size_x, button_size_y);
    ui ->pushButton_tabla ->setFixedSize(button_size_x, button_size_y);
    ui ->pushButton_mostrar ->setFixedSize(button_size_x, button_size_y);
    ui ->pushButton_salir ->setFixedSize(button_size_x, button_size_y);
    ui ->pushButton_ordenar ->setFixedSize(button_size_x, button_size_y);
}

void MainWindow::on_actionGuardar_triggered()
{
    QString filename =QFileDialog::getOpenFileName(this, tr("Open File"),"C:/Users/Ivan/Downloads", tr("Text Files(*.txt)"));
    QFile archivo(filename);
    if(!archivo.open(QFile::WriteOnly |QFile::Text)){
        QMessageBox::warning(this, "title", "No se pudo abrir el archivo...");
    }
    QTextStream out(&archivo);
    QString datos;
    if(lista.cant_neuronas() ==0){
        datos =QString("");
    }
    else{
        for(size_t i =0; i <lista.cant_neuronas(); i ++){
            datos =QString("%1;%2;%3;%4;%5;%6;%7\n").arg(lista.getid(i))
                        .arg(lista.getvoltaje(i)).arg(lista.getx(i))
                        .arg(lista.gety(i)).arg(lista.getred(i))
                        .arg(lista.getgreen(i)).arg(lista.getblue(i));
            out <<datos;
        }
    }
    archivo.close();
}

void MainWindow::on_actionCargar_triggered()
{
    QString filename =QFileDialog::getOpenFileName(this, tr("Open File"),"C:/Users/Ivan/Downloads", tr("Text Files(*.txt)"));
    QFile archivo(filename);
    if(!archivo.open(QFile::ReadOnly |QFile::Text)){
        QMessageBox::warning(this, "title", "No se pudo abrir el archivo...");
    }
    QTextStream in(&archivo);
    QString datos;
    int pyc1, pyc2;
    while(!in.atEnd()){
        datos =in.readLine();
        pyc1 =0;
        pyc2 =delimitador(pyc1 +1, datos);
        ui ->line_id ->setText(datos.sliced(pyc1, (pyc2 -pyc1)));
        pyc2 ++;
        pyc1 =delimitador(pyc2 +1, datos);
        ui ->line_voltaje ->setText(datos.sliced(pyc2, (pyc1 -pyc2)));
        pyc1 ++;
        pyc2 =delimitador(pyc1 +1, datos);
        ui ->line_x ->setText(datos.sliced(pyc1, (pyc2 -pyc1)));
        pyc2 ++;
        pyc1 =delimitador(pyc2 +1, datos);
        ui ->line_y ->setText(datos.sliced(pyc2, (pyc1 -pyc2)));
        pyc1 ++;
        pyc2 =delimitador(pyc1 +1, datos);
        ui ->line_red ->setText(datos.sliced(pyc1, (pyc2 -pyc1)));
        pyc2 ++;
        pyc1 =delimitador(pyc2 +1, datos);
        ui ->line_green ->setText(datos.sliced(pyc2, (pyc1 -pyc2)));
        pyc1 ++;
        pyc2 =delimitador(pyc1 +1, datos);
        ui ->line_blue ->setText(datos.sliced(pyc1, (pyc2 -pyc1)));
        on_pushButton_addf_clicked();
    }
    archivo.close();
}

int MainWindow::delimitador(int pyc, QString datos){
    for(; pyc <datos.length(); pyc ++){
        if(datos[pyc] ==';'){
            return pyc;
        }
    }
    return pyc;
}

void MainWindow::on_pushButton_add_clicked()
{
    QString id, voltaje, x, y, red, green, blue;
    id =ui ->line_id ->text();
    voltaje =ui ->line_voltaje ->text();
    x =ui ->line_x ->text();
    y =ui ->line_y ->text();
    red =ui ->line_red ->text();
    green =ui ->line_green ->text();
    blue =ui ->line_blue ->text();
    Neurona neurona(id.toInt(), voltaje.toFloat(), x.toInt(), y.toInt(), red.toInt(), green.toInt(), blue.toInt());
    lista.agregar_inicio(neurona);
    ui ->line_id ->setText("");
    ui ->line_voltaje ->setText("");
    ui ->line_x ->setText("");
    ui ->line_y ->setText("");
    ui ->line_red ->setText("");
    ui ->line_green ->setText("");
    ui ->line_blue ->setText("");
}

void MainWindow::on_pushButton_addf_clicked()
{
    QString id, voltaje, x, y, red, green, blue;
    id =ui ->line_id ->text();
    voltaje =ui ->line_voltaje ->text();
    x =ui ->line_x ->text();
    y =ui ->line_y ->text();
    red =ui ->line_red ->text();
    green =ui ->line_green ->text();
    blue =ui ->line_blue ->text();
    Neurona neurona(id.toInt(), voltaje.toFloat(), x.toInt(), y.toInt(), red.toInt(), green.toInt(), blue.toInt());
    lista.agregar_final(neurona);
    ui ->line_id ->setText("");
    ui ->line_voltaje ->setText("");
    ui ->line_x ->setText("");
    ui ->line_y ->setText("");
    ui ->line_red ->setText("");
    ui ->line_green ->setText("");
    ui ->line_blue ->setText("");
}

void MainWindow::on_pushButton_lista_clicked()
{
    ocultar_todo();
    ui ->pushButton_salir_lista ->setFixedSize(button_size_x, button_size_y);
    ui ->plainTextEdit_lista ->setFixedSize(251, 291);
    if(lista.cant_neuronas() ==0)
        ui ->plainTextEdit_lista ->setPlainText("No hay ninguna neurona registrada...");
    else{
        QString cadena;
        for(size_t i =0; i <lista.cant_neuronas(); i ++){
            cadena =QString("Neurona: %1\nVoltaje: %2\nPosicion: ("
                             "%3, %4)\nRGB: (%5, %6, %7)\n\n").arg(lista.getid(i))
                         .arg(lista.getvoltaje(i)).arg(lista.getx(i))
                         .arg(lista.gety(i)).arg(lista.getred(i))
                         .arg(lista.getgreen(i)).arg(lista.getblue(i));
            ui ->plainTextEdit_lista ->insertPlainText(cadena);
        }
    }
}

void MainWindow::on_pushButton_salir_lista_clicked()
{
    mostrar_todo();
    ui ->pushButton_salir_lista ->setFixedSize(0, 0);
    ui ->plainTextEdit_lista ->setPlainText("");
    ui ->plainTextEdit_lista ->setFixedSize(0, 0);
}

void MainWindow::on_pushButton_tabla_clicked()
{
    ocultar_todo();
    ui ->tableWidget_tabla ->setFixedSize(891, 291);
    ui ->line_buscar ->setFixedSize(line_size_x, line_size_y);
    ui ->pushButton_buscar ->setFixedSize(button_size_x, button_size_y);
    ui ->pushButton_salir_tabla ->setFixedSize(button_size_x, button_size_y);
    ui ->tableWidget_tabla ->setRowCount(lista.cant_neuronas());
    QString cadena;
    size_t i, j;
    QTableWidgetItem *item;
    for(i =0; i <lista.cant_neuronas(); i ++){
        j =0;
        cadena =QString("%1").arg(lista.getid(i));
        item =new QTableWidgetItem(cadena);
        ui ->tableWidget_tabla ->setItem(i, j, item);
        j ++;
        cadena =QString("%1").arg(lista.getvoltaje(i));
        item =new QTableWidgetItem(cadena);
        ui ->tableWidget_tabla ->setItem(i, j, item);
        j ++;
        cadena =QString("%1").arg(lista.getx(i));
        item =new QTableWidgetItem(cadena);
        ui ->tableWidget_tabla ->setItem(i, j, item);
        j ++;
        cadena =QString("%1").arg(lista.gety(i));
        item =new QTableWidgetItem(cadena);
        ui ->tableWidget_tabla ->setItem(i, j, item);
        j ++;
        cadena =QString("%1").arg(lista.getred(i));
        item =new QTableWidgetItem(cadena);
        ui ->tableWidget_tabla ->setItem(i, j, item);
        j ++;
        cadena =QString("%1").arg(lista.getgreen(i));
        item =new QTableWidgetItem(cadena);
        ui ->tableWidget_tabla ->setItem(i, j, item);
        j ++;
        cadena =QString("%1").arg(lista.getblue(i));
        item =new QTableWidgetItem(cadena);
        ui ->tableWidget_tabla ->setItem(i, j, item);
    }
}

void MainWindow::on_pushButton_buscar_clicked()
{
    int rows =0, j;
    ui ->tableWidget_tabla ->clearContents();
    ui ->tableWidget_tabla ->setRowCount(0);
    if(lista.cant_neuronas() !=0){
        QTableWidgetItem *item;
        QString buscado =ui ->line_buscar ->text(), cadena;
        for(size_t i =0; i <lista.cant_neuronas(); i ++){
            cadena =QString("%1").arg(lista.getid(i));
            if(buscado ==cadena){
                rows ++;
                j =0;
                ui ->tableWidget_tabla ->setRowCount(rows);
                item =new QTableWidgetItem(cadena);
                ui ->tableWidget_tabla ->setItem(rows -1, j, item);
                j ++;
                cadena =QString("%1").arg(lista.getvoltaje(i));
                item =new QTableWidgetItem(cadena);
                ui ->tableWidget_tabla ->setItem(rows -1, j, item);
                j ++;
                cadena =QString("%1").arg(lista.getx(i));
                item =new QTableWidgetItem(cadena);
                ui ->tableWidget_tabla ->setItem(rows -1, j, item);
                j ++;
                cadena =QString("%1").arg(lista.gety(i));
                item =new QTableWidgetItem(cadena);
                ui ->tableWidget_tabla ->setItem(rows -1, j, item);
                j ++;
                cadena =QString("%1").arg(lista.getred(i));
                item =new QTableWidgetItem(cadena);
                ui ->tableWidget_tabla ->setItem(rows -1, j, item);
                j ++;
                cadena =QString("%1").arg(lista.getgreen(i));
                item =new QTableWidgetItem(cadena);
                ui ->tableWidget_tabla ->setItem(rows -1, j, item);
                j ++;
                cadena =QString("%1").arg(lista.getblue(i));
                item =new QTableWidgetItem(cadena);
                ui ->tableWidget_tabla ->setItem(rows -1, j, item);
            }
        }
    }
}

void MainWindow::on_pushButton_salir_tabla_clicked()
{
    mostrar_todo();
    ui ->tableWidget_tabla ->clearContents();
    ui ->tableWidget_tabla ->setFixedSize(0, 0);
    ui ->pushButton_buscar ->setFixedSize(0, 0);
    ui ->pushButton_salir_tabla ->setFixedSize(0, 0);
    ui ->line_buscar ->setFixedSize(0, 0);
    ui ->line_buscar ->setText("");
}

void MainWindow::on_pushButton_mostrar_clicked()
{
    ocultar_todo();
    ui ->graphicsViews_ellipses ->setFixedSize(471, 291);
    ui ->plainTextEdit_adyacencia ->setFixedSize(221, 291);
    ui ->pushButton_graficar ->setFixedSize(button_size_x, button_size_y);
    ui ->pushButton_salir_mostrar ->setFixedSize(button_size_x, button_size_y);
    if(lista.cant_neuronas()){
        QGraphicsScene *scene;
        QGraphicsTextItem *text;
        QString id;
        scene =new QGraphicsScene();
        QGraphicsEllipseItem *ellipse;
        QPen pen;
        ui ->graphicsViews_ellipses ->setScene(scene);
        for(size_t i =0; i <lista.cant_neuronas(); i ++){
            QColor color(lista.getred(i), lista.getgreen(i), lista.getblue(i));
            QBrush brush(color);
            ellipse =scene ->addEllipse(lista.getx(i), lista.gety(i), 16, 16, pen, brush);
            ellipse ->setZValue(1);
            id =QString("%1").arg(lista.getid(i));
            text =new QGraphicsTextItem(id);
            text ->setPos(lista.getx(i) -2, lista.gety(i) -5);
            text ->setZValue(2);
            scene ->addItem(text);
        }
    }
}

void MainWindow::on_pushButton_graficar_clicked()
{
    float distancia, x, y, menor, razon =3;
    int peso;
    Neurona *origen =nullptr;
    Neurona *destino =nullptr;
    QGraphicsLineItem *arista;
    QGraphicsTextItem *text;
    QString peso_arista;
    ui ->pushButton_graficar ->setFixedSize(0, 0);
    ui ->line_recorrido_id ->setFixedSize(line_size_x, line_size_y);
    ui ->pushButton_recorrido_id ->setFixedSize(button_size_x, button_size_y);
    for(size_t i =0; i <lista.cant_neuronas(); i ++){
        menor =9999;
        origen =nullptr;
        destino =nullptr;
        for(size_t j =0; j <lista.cant_neuronas(); j ++){
            if(i !=j){
                x =pow(lista.getx(j) -lista.getx(i), 2);
                y =pow(lista.gety(j) -lista.gety(i), 2);
                distancia =sqrt(x +y);
                if(distancia <menor){
                    menor =distancia;
                    origen =lista.getneurona(i);
                    destino =lista.getneurona(j);
                }
            }
        }
        if(origen !=nullptr &&destino !=nullptr){
            arista =ui ->graphicsViews_ellipses ->scene() ->addLine(origen ->getnx() +8, origen ->getny() +8, destino ->getnx() +8, destino ->getny() +8);
            peso =origen->getnvoltaje() +destino->getnvoltaje();
            peso_arista =QString("%1").arg(peso);
            text =new QGraphicsTextItem(peso_arista);
            text ->setPos((destino ->getnx() +origen ->getnx()) /2 -4, (destino ->getny() +origen ->getny()) /2 -4);
            text ->setDefaultTextColor(QColor(255, 0, 0));
            ui ->graphicsViews_ellipses ->scene() ->addItem(text);
            lista.grafo ->listaAdyacencia[origen].push_back(std::make_pair(destino, peso));
            ui ->graphicsViews_ellipses ->scene() ->addRect((origen ->getnx() +razon *destino ->getnx()) /(razon +1) +7, (origen ->getny() +razon *destino ->getny()) /(razon +1) +7, 1.5, 1.5);
        }
    }
    for(size_t i =0; i <lista.cant_neuronas(); i ++){
        origen =nullptr;
        destino =nullptr;
        if((i !=0) &&(i %2 ==0) &&(i +2 <lista.cant_neuronas())){
            origen =lista.getneurona(i);
            destino =lista.getneurona(i +2);
            if(origen !=nullptr &&destino !=nullptr){
                peso =origen->getnvoltaje() +destino->getnvoltaje();
                peso_arista =QString("%1").arg(peso);
                text =new QGraphicsTextItem(peso_arista);
                text ->setPos((destino ->getnx() +origen ->getnx()) /2 -4, (destino ->getny() +origen ->getny()) /2 -4);
                text ->setDefaultTextColor(QColor(255, 0, 0));
                ui ->graphicsViews_ellipses ->scene() ->addItem(text);
                lista.grafo ->listaAdyacencia[origen].push_back(std::make_pair(destino, peso));
                arista =ui ->graphicsViews_ellipses ->scene() ->addLine(origen ->getnx() +8, origen ->getny() +8, destino ->getnx() +8, destino ->getny() +8);
                ui ->graphicsViews_ellipses ->scene() ->addRect((origen ->getnx() +razon *destino ->getnx()) /(razon +1) +7, (origen ->getny() +razon *destino ->getny()) /(razon +1) +7, 1.5, 1.5);
            }
        }
    }
}

void MainWindow::on_pushButton_salir_mostrar_clicked()
{
    mostrar_todo();
    ui ->graphicsViews_ellipses ->setFixedSize(0, 0);
    ui ->plainTextEdit_adyacencia ->setPlainText("");
    ui ->plainTextEdit_adyacencia ->setFixedSize(0, 0);
    ui ->pushButton_graficar ->setFixedSize(0, 0);
    ui ->pushButton_salir_mostrar ->setFixedSize(0, 0);
    ui ->line_recorrido_id ->setFixedSize(0, 0);
    ui ->pushButton_recorrido_id ->setFixedSize(0, 0);
    ui ->graphicsViews_ellipses ->resetCachedContent();
    lista.grafo ->vaciarListaAdyacencia();
}

void MainWindow::on_pushButton_ordenar_clicked()
{
    ocultar_todo();
    ui ->pushButton_por_id ->setFixedSize(button_size_x, button_size_y);
    ui ->pushButton_por_voltaje ->setFixedSize(button_size_x, button_size_y);
}

void MainWindow::on_pushButton_por_id_clicked()
{
    mostrar_todo();
    lista.quickSort(1);
    ui ->pushButton_por_id ->setFixedSize(0, 0);
    ui ->pushButton_por_voltaje ->setFixedSize(0, 0);
}

void MainWindow::on_pushButton_por_voltaje_clicked()
{
    mostrar_todo();
    lista.quickSort(0);
    ui ->pushButton_por_id ->setFixedSize(0, 0);
    ui ->pushButton_por_voltaje ->setFixedSize(0, 0);
}

void MainWindow::on_pushButton_salir_clicked()
{
    close();
}

void MainWindow::on_pushButton_recorrido_id_clicked()
{
    ui ->plainTextEdit_adyacencia ->setPlainText("");
    if(lista.cant_neuronas() !=0){
        int f =0;
        Neurona *neurona =nullptr;
        QString buscado =ui ->line_recorrido_id ->text(), cadena;
        ui ->line_recorrido_id ->setText("");
        for(size_t i =0; (i <lista.cant_neuronas()) &&(f ==0); i ++){
            cadena =QString("%1").arg(lista.getid(i));
            if(buscado ==cadena){
                neurona =lista.getneurona(i);
                f ++;
            }
        }
        if(f !=0){
            cadena =lista.grafo ->profundidad(neurona);
            ui ->plainTextEdit_adyacencia ->setPlainText(cadena);
        }
    }
}
//insertPlainText(cadena)

//imprimir(lista.grafo);

/*void imprimir(const Grafo& grafo){
    std::cout << "Lista de Adyacencia:\n";

    for (const auto& par : grafo.listaAdyacencia) {
        Neurona* nodo = par.first;
        const std::vector<std::pair<Neurona*, int>>& vecinos = par.second;

        std::cout << "Nodo ID " << nodo ->getnid() << " -> ";
        for (const auto& vecino : vecinos) {
            Neurona* nodoVecino = vecino.first;
            int peso = vecino.second;
            std::cout << "(ID: " << nodoVecino ->getnid() << ", Peso: " << peso << ") ";
        }
        std::cout << "\n";
    }9
}*/
