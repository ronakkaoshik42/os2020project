#include<QMessageBox>
#include<QFileDialog>
#include<QTextStream>
#include <QElapsedTimer>
#include<QGraphicsSimpleTextItem>
#include <QGraphicsTextItem>

#include "sub_window.h"
#include "ui_sub_window.h"
#include"mainwindow.h"


extern int ch;
extern int num;
extern process p[10],p1[10],temp;
extern queue<int>q1;
int time_slice=1;
float simulation_speed;
int condition=0;


sub_window::sub_window(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::sub_window)
{
    ui->setupUi(this);

    scene=new QGraphicsScene(this);
    //scene->setSceneRect(0,0,200,100);

    ui->graphicsView->setScene(scene);
    ui->QLineEdit_Process_Num_2->setPlaceholderText(">2");
    ui->lineEdit_timeslice->setPlaceholderText(">0");

    QStringList header;
    header<<"Arrival Time"<<"CPU cycles"<<"I/O cycles"<<"Priority";
    ui->tableWidget->setColumnCount(4);
    ui->tableWidget->setHorizontalHeaderLabels(header);
    ui->tableWidget->horizontalHeader()->setStyleSheet("QHeaderView::section{background:skyblue;}");
    ui->tableWidget->verticalHeader()->setStyleSheet("QHeaderView::section{background:skyblue;}");
    //ui->tableWidget_Result->horizontalHeader()->resizeSection(2,150);

}

void sub_window::on_QLineEdit_Process_Num_2_textChanged(const QString &arg1)
{
    ui->tableWidget->setRowCount(arg1.toInt());
    num=arg1.toInt();
    ui->tableWidget->horizontalHeader()->setStyleSheet("QHeaderView::section{background:skyblue;}");
    ui->tableWidget->verticalHeader()->setStyleSheet("QHeaderView::section{background:skyblue;}");
}

// Buuble sort for processes if needed (ascending)
void sub_window::shortest_job_sort(int n)
{
    int i, j;
    for (i = 2; i <= n; i++)
    {
        for (j = 1; j <= i; j++)
        {
            if (p[j].at > p[i].at)
            {
                temp = p[i];
                p[i] = p[j];
                p[j] = temp;
            }
            else if (p[j].at == p[i].at)
            {
                if (p[j].bt > p[i].bt)
                {
                    temp = p[i];
                    p[i] = p[j];
                    p[j] = temp;
                }
            }
        }
    }
}


void sub_window::displaylegend()
{
    int i;

    QStringList header;
    header<<"ID"<<"Color";
    ui->tableWidget_Result->setRowCount(num);
    ui->tableWidget_Result->setColumnCount(2);
    ui->tableWidget_Result->setHorizontalHeaderLabels(header);
    ui->tableWidget_Result->horizontalHeader()->setStyleSheet("QHeaderView::section{background:skyblue;}");
    ui->tableWidget_Result->verticalHeader()->setStyleSheet("QHeaderView::section{background:skyblue;}");
    ui->tableWidget_Result->horizontalHeader()->resizeSection(2,150);


    for (i=0 ; i<=ui->tableWidget_Result->rowCount() ; i++ )
    {

        QTableWidgetItem* item = new QTableWidgetItem();
        QString temp_string=QString::number(p[i+1].id);
        item->setText(temp_string);
        ui->tableWidget_Result->setItem(i,0,item);

        QTableWidgetItem* item_2 = new QTableWidgetItem();
        QBrush color_brush(QColor(p[i+1].color));
        item_2->setBackground(color_brush);
        ui->tableWidget_Result->setItem(i,1,item_2);
    }
}

void sub_window::displayturnwait(int n)
{
    int i;
    for(i=1;i<=num;i++)
    {
        p[i].tat=p[i].ft-p[i].at;
        p[i].wt=p[i].tat-p[i].bt;
        p[i].res_t = p[i].st - p[i].at;
        p[0].tat=p[0].tat+p[i].tat;
        p[0].wt=p[0].wt+p[i].wt;
        if (p[i].wt<0)
        {
            p[i].wt=0;
        }
    }

    p[0].tat=p[0].tat/n;
    p[0].wt=p[0].wt/n;



    QStringList header;
    header<<"ID"<<"Color"<<"Finish Time"<<"Turnaround Time"<<"Waiting Time"<<"Start time"<<"Response time";
    ui->tableWidget_Result->setRowCount(num);
    ui->tableWidget_Result->setColumnCount(7);
    ui->tableWidget_Result->setHorizontalHeaderLabels(header);
    ui->tableWidget_Result->horizontalHeader()->setStyleSheet("QHeaderView::section{background:skyblue;}");
    ui->tableWidget_Result->verticalHeader()->setStyleSheet("QHeaderView::section{background:skyblue;}");
    ui->tableWidget_Result->horizontalHeader()->resizeSection(2,150);


    for (i=0 ; i<=ui->tableWidget_Result->rowCount() ; i++ )
    {

        QTableWidgetItem* item = new QTableWidgetItem();
        QString temp_string=QString::number(p[i+1].id);
        item->setText(temp_string);
        ui->tableWidget_Result->setItem(i,0,item);
    }

    for (i=0 ; i<=ui->tableWidget_Result->rowCount() ; i++ )
    {
        QTableWidgetItem* item = new QTableWidgetItem();
        QBrush color_brush(QColor(p[i+1].color));
        item->setBackground(color_brush);
        ui->tableWidget_Result->setItem(i,1,item);
    }

    for (i=0 ; i<=ui->tableWidget_Result->rowCount() ; i++ )
    {

        QTableWidgetItem* item = new QTableWidgetItem();
        QString temp_string=QString::number(p[i+1].ft);
        item->setText(temp_string);
        ui->tableWidget_Result->setItem(i,2,item);
    }

    for (i=0 ; i<=ui->tableWidget_Result->rowCount() ; i++ )
    {
        QTableWidgetItem* item = new QTableWidgetItem();
        QString temp_string=QString::number(p[i+1].tat);
        item->setText(temp_string);
        ui->tableWidget_Result->setItem(i,3,item);
    }

    for (i=0 ; i<=ui->tableWidget_Result->rowCount() ; i++ )
    {
        QTableWidgetItem* item = new QTableWidgetItem();
        QString temp_string=QString::number(p[i+1].wt);
        item->setText(temp_string);
        ui->tableWidget_Result->setItem(i,4,item);
    }

    for (i=0 ; i<=ui->tableWidget_Result->rowCount() ; i++ )
    {
        QTableWidgetItem* item = new QTableWidgetItem();
        QString temp_string=QString::number(p[i+1].st);
        item->setText(temp_string);
        ui->tableWidget_Result->setItem(i,5,item);
    }
    for (i=0 ; i<=ui->tableWidget_Result->rowCount() ; i++ )
    {
        QTableWidgetItem* item = new QTableWidgetItem();
        QString temp_string=QString::number(p[i+1].res_t);
        item->setText(temp_string);
        ui->tableWidget_Result->setItem(i,6,item);
    }
}

sub_window::~sub_window()
{
    delete ui;
}

void sub_window::on_pushButton_clicked()
{


    int temp_data[ui->tableWidget->rowCount()][ui->tableWidget->columnCount()];

    for(int i=0;i<ui->tableWidget->rowCount();i++)
    {
        for(int j=0;j<ui->tableWidget->columnCount();j++)
        {
            temp_data[i][j]=ui->tableWidget->item(i,j)->text().toInt();
        }
    }

    ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);

    /*
    QString tableData[ui->tableWidget->rowCount()][ui->tableWidget->columnCount()];
    for(int i=0;i<ui->tableWidget->rowCount();i++)
    {
        for(int j=0;j<ui->tableWidget->columnCount();j++)
        {
            temp_data[i][j]=tableData[i][j].toInt();
        }
    }
    */

    const char *color_list[10] = {"red","green","blue","yellow","magenta","cyan","gray","darkRed","darkGreen","darkBlue"};

    for(int i=0;i<ui->tableWidget->rowCount();i++)
    {
        p[i+1].id=i+1;
        p[i+1].at=temp_data[i][0];
        p[i+1].ct=temp_data[i][1];
        p[i+1].it=temp_data[i][2];
        p[i+1].bt=p[i+1].ct+p[i+1].it;
        p[i+1].pr=temp_data[i][3];
        p[i+1].color=color_list[i]; //tableData[i][5]
    }

    simulation_speed=ui->horizontalSlider->value();
    simulation_speed = ((simulation_speed/99)*2500);
    condition=0;

    if(ui->radioButton_Sub_RR->isChecked())
    {
        QString text_tempa=ui->lineEdit_timeslice->text();
        time_slice=text_tempa.toFloat();
        if(time_slice==0)
        {
            QMessageBox::warning(this,"Warning","Please Input The Time Quantum!");
        }
        else
        {
            condition+=1;
            displaylegend();
            QMessageBox::information(this,"Success","Data Registered!");
        }
    }
    else
    {
        condition+=1;
        displaylegend();
        QMessageBox::information(this,"Success","Data Registered!");
    }
}

int height_level(int cpu_flag,int io_flag,int c)
{
    return (cpu_flag*-c)+(io_flag*c);
}

int select_process_pr(int t,process *tp)
{
    int tmp_priority,idx;
    tmp_priority = 1000;
    int c=0;
    for(int i=0;i<num;i++)
    {
        if(tp[i+1].at<=t && tp[i+1].ct+tp[i+1].it>0 && tp[i+1].pr<tmp_priority)
        {
            idx = i+1;
            tmp_priority = tp[i+1].pr;
            c=1;
        }
    }
    if(c==1)
    {
        return idx;
    }
    else
    {
        return -1;

    }
}

int select_process_srtf(int t,process *tp)
{
    int idx,rem_time;
    rem_time=1000;
    int c=0;
    for(int i=0;i<num;i++)
    {
        if(tp[i+1].at<=t && tp[i+1].ct+tp[i+1].it>0)
        {
            if(tp[i+1].ct+tp[i+1].it<rem_time)
            {
                idx = i+1;
                rem_time = tp[i+1].ct+tp[i+1].it;
                c=1;
            }
            else if(tp[i+1].ct+tp[i+1].it==rem_time)
            {
                if(tp[idx].pr>tp[i+1].pr)
                {
                    idx = i+1;
                    rem_time = tp[i+1].ct+tp[i+1].it;
                    c=1;
                }
            }
        }
    }
    if(c==1)
    {
        return idx;
    }
    else
    {
        return -1;

    }
}

int select_wc_pr(int t,process *tp,int cpu_flag,int idx)
{
    int tmp_priority = 1000;
    int c=0;
    int idx2;
    if(cpu_flag)
    {
        for(int i=0;i<num;i++)
        {
            if(tp[i+1].at<=t && idx!=i+1 && tp[i+1].it>0 && tp[i+1].pr<tmp_priority)
            {
                idx2 = i+1;
                tmp_priority=tp[i+1].pr;
                c=1;
            }
        }
    }
    else
    {
        for(int i=0;i<num;i++)
        {
            if(tp[i+1].at<=t && idx!=i+1 && tp[i+1].ct>0 && tp[i+1].pr<tmp_priority)
            {
                idx2 = i+1;
                tmp_priority=tp[i+1].pr;
                c=1;
            }
        }
    }

    if(c==1)
    {
        return idx2;
    }
    else
    {
        return -1;
    }
}

void sub_window::on_pushButton_2_clicked()
{
    if(ui->radioButton_Sub_FCFS->isChecked())
    {
        ch=1;
        condition+=1;
    }

    else if(ui->radioButton_Sub_PSJF->isChecked())
    {
        ch=2;
        condition+=1;
    }
    else if(ui->radioButton_Sub_PR->isChecked())
    {
        ch=3;
        condition+=1;
    }
    else if(ui->radioButton_Sub_RR->isChecked())
    {
        ch=4;
        condition+=1;
    }

    else if(ui->radioButton_Sub_PSJF_2->isChecked())
    {
        ch=5;
        condition+=1;
    }
    else
    {
        QMessageBox::warning(this,"Warning","Please Select An Algorithm!");
    }

    if(condition>=2)
    {
        QString _cpu_io= "CPU";
        QGraphicsTextItem *cpu_io = new QGraphicsTextItem(_cpu_io);
        cpu_io->setScale(1.25);
        cpu_io->setPos(QPointF(-170+Rectangle_Width*(-5), -17));
        cpu_io->setTextWidth(200);
        scene->addItem(cpu_io);

        _cpu_io= "I/O";
        cpu_io = new QGraphicsTextItem(_cpu_io);
        cpu_io->setScale(1.25);
        cpu_io->setPos(QPointF(-170+Rectangle_Width*(-5), 35));
        cpu_io->setTextWidth(200);
        scene->addItem(cpu_io);

        if(ch==1) //FCFS
        {
           shortest_job_sort(num);
           int i;
           for(i=1;i<=num;i++)
           {
               p1[i]=p[i];
               p1[i].cpu_count = 0;
               p1[i].io_count = 0;
               p1[i].cpu_flag=0;
               p1[i].io_flag=0;
           }
           p[1].st = p[1].at;
           for (i = 2; i <= num; i++)
           {
               p[i].st = p[i - 1].st + p[i - 1].bt;
           }

           p[1].ft=p[1].bt;

           for(i=2;i<=num;i++)
           {
               p[i].ft=p[i-1].ft+p[i].bt;
           }
           int split = 1;
           p[0].ft = 0;
           for(i=1;i<=num;i++)
           {
               for(int m=0;m<p[i].bt;m++)
               {
                   if(m==0 && p1[i].ct>0)
                   {
                       p1[i].cpu_flag=1;
                       p1[i].io_flag=0;
                       p1[i].cpu_count++;
                       p1[i].ct--;
                   }
                   else
                   {
                       if(p1[i].cpu_count<(p1[i].io_count+1)*split && p1[i].ct>0)
                       {
                           p1[i].cpu_flag=1;
                           p1[i].io_flag=0;
                           p1[i].cpu_count++;
                           p1[i].ct--;
                       }
                       else if(p1[i].it>0)
                       {
                           p1[i].cpu_flag=0;
                           p1[i].io_flag=1;
                           p1[i].io_count++;
                           p1[i].it--;
                       }
                   }
                   QBrush color_brush(QColor(p[i].color));
                   QPen blackpen(Qt::black);
                   blackpen.setWidth(1);
                   rectangle=scene->addRect(-200+Rectangle_Width*p[i-1].ft+Rectangle_Width*m,height_level(p1[i].cpu_flag,p1[i].io_flag,25),Rectangle_Width,50,blackpen,color_brush);

                   QString temp_str=QString::number(p[i-1].ft);
                   QGraphicsTextItem *txtitem = new QGraphicsTextItem(temp_str);

                   /// Rectangle labelling
                   txtitem->setPos(QPointF(-200+Rectangle_Width*p[i-1].ft, 100));
                   scene->addItem(txtitem);
                   //text=scene->addText();
                   QElapsedTimer t;
                   t.start();
                   while(t.elapsed() < simulation_speed)  /// speed variation
                   {
                       QCoreApplication::processEvents();
                   }
               }
           }

           QString temp_str=QString::number(p[num].ft);
           QGraphicsTextItem *txtitema = new QGraphicsTextItem(temp_str);
           txtitema->setPos(QPointF(-200+Rectangle_Width*p[num].ft, 100));
           scene->addItem(txtitema);
           condition=0;
           displayturnwait(num);
           QMessageBox::information(this,"Succeed","Simulation Completed!");
        }

        if(ch==2)
        {

            for(int i=1;i<=num;i++)
            {
                p1[i]=p[i];
                p1[i].cpu_count = 0;
                p1[i].io_count = 0;
                p[i].ft=-1;
                p[i].st=-1;
            }


            int idx,cpu_flag,io_flag;
            int split =2;
            int t=0;
            int loop_check = 1;
            while(loop_check!=0)
            {
                idx = select_process_srtf(t,p1);
                if(idx!=-1)
                {
                    if(p1[idx].bt==p[idx].bt && p1[idx].ct>0)
                    {
                        cpu_flag=1;
                        io_flag=0;
                        p1[idx].cpu_count++;
                        p1[idx].ct--;
                        p1[idx].bt--;
                    }
                    else
                    {
                        if(p1[idx].cpu_count<(p1[idx].io_count+1)*split && p1[idx].ct>0)
                        {
                            cpu_flag=1;
                            io_flag=0;
                            p1[idx].cpu_count++;
                            p1[idx].ct--;
                            p1[idx].bt--;
                        }
                        else
                        {
                            cpu_flag=0;
                            io_flag=1;
                            p1[idx].io_count++;
                            p1[idx].it--;
                            p1[idx].bt--;
                        }
                    }

                    QBrush color_brush(QColor(p1[idx].color));
                    QPen blackpen(Qt::black);
                    blackpen.setWidth(1);
                    rectangle=scene->addRect(-200+Rectangle_Width*t,height_level(cpu_flag,io_flag,25),Rectangle_Width,50,blackpen,color_brush);

                    QString temp_str=QString::number(t);
                    QGraphicsTextItem *txtitem = new QGraphicsTextItem(temp_str);

                    /// Rectangle labelling
                    txtitem->setPos(QPointF(-200+Rectangle_Width*t, 100));
                    scene->addItem(txtitem);
                    //text=scene->addText();
                    QElapsedTimer t1;
                    t1.start();
                    while(t1.elapsed() < simulation_speed)  /// speed variation
                    {
                        QCoreApplication::processEvents();
                    }
               }
                loop_check=0;
                for(int j=0;j<num;j++)
                {
                    loop_check+=p1[j+1].bt;
                }
                for(int k=0;k<num;k++)
                {
                    if(p1[k+1].bt==0 && p[k+1].ft==-1)
                    {
                        p[k+1].ft=t+1;
                    }
                    if(p1[k+1].bt<p[k+1].bt && p[k+1].st==-1)
                    {
                        p[k+1].st=t;
                    }
                }
                t++;
            }
            QString temp_str=QString::number(t);
            QGraphicsTextItem *txtitem = new QGraphicsTextItem(temp_str);
            txtitem->setPos(QPointF(-200+Rectangle_Width*t, 100));
            scene->addItem(txtitem);

            condition=0;

            displayturnwait(num);
            QMessageBox::information(this,"Succeed","Simulation Completed!");

        }

        if(ch==3)
        {

           int total_simulation_time=0;
           for(int i=0;i<num;i++)
           {
               total_simulation_time = total_simulation_time + p[i+1].bt;
           }

           for(int i=1;i<=num;i++)
           {
               p1[i]=p[i];
               p1[i].cpu_count = 0;
               p1[i].io_count = 0;
               p[i].ft=-1;
               p[i].st=-1;
           }


           int idx,cpu_flag,io_flag;
           int split =2;
           int t=0;
           int loop_check = 1;
           while(loop_check!=0)
           {
               idx = select_process_pr(t,p1);
               if(idx!=-1)
               {
               if(p1[idx].bt==p[idx].bt && p1[idx].ct>0)
               {
                   cpu_flag=1;
                   io_flag=0;
                   p1[idx].cpu_count++;
                   p1[idx].ct--;
                   p1[idx].bt--;
               }
               else
               {
                   if(p1[idx].cpu_count<(p1[idx].io_count+1)*split && p1[idx].ct>0)
                   {
                       cpu_flag=1;
                       io_flag=0;
                       p1[idx].cpu_count++;
                       p1[idx].ct--;
                       p1[idx].bt--;
                   }
                   else
                   {
                       cpu_flag=0;
                       io_flag=1;
                       p1[idx].io_count++;
                       p1[idx].it--;
                       p1[idx].bt--;
                   }
               }

               QBrush color_brush(QColor(p1[idx].color));
               QPen blackpen(Qt::black);
               blackpen.setWidth(1);
               rectangle=scene->addRect(-200+Rectangle_Width*t,height_level(cpu_flag,io_flag,25),Rectangle_Width,50,blackpen,color_brush);


               }
               loop_check=0;
               for(int j=0;j<num;j++)
               {
                   loop_check+=p1[j+1].bt;
               }

               QString temp_str=QString::number(t);
               QGraphicsTextItem *txtitem = new QGraphicsTextItem(temp_str);

               /// Rectangle labelling
               txtitem->setPos(QPointF(-200+Rectangle_Width*t, 100));
               scene->addItem(txtitem);
               //text=scene->addText();
               QElapsedTimer t1;
               t1.start();
               while(t1.elapsed() < simulation_speed)  /// speed variation
               {
                   QCoreApplication::processEvents();
               }
               for(int k=0;k<num;k++)
               {
                   if(p1[k+1].bt==0 && p[k+1].ft==-1)
                   {
                       p[k+1].ft=t+1;
                   }
                   if(p1[k+1].bt<p[k+1].bt && p[k+1].st==-1)
                   {
                       p[k+1].st=t;
                   }
               }
               t++;
           }

           QString temp_str=QString::number(t);
           QGraphicsTextItem *txtitem = new QGraphicsTextItem(temp_str);
           txtitem->setPos(QPointF(-200+Rectangle_Width*t, 100));
           scene->addItem(txtitem);

           condition=0;

           displayturnwait(num);
           QMessageBox::information(this,"Succeed","Simulation Completed!");


        }

        if(ch==4)
        {
            shortest_job_sort(num);

            int idx, current_time=0, completed=0;
            int burst_time[num+1], mark[num+1];

            int io_cpu_assign; //0=CPU Cycle; 1=IO Cycle

            for(int i=1;i<=num;i++)
            {
                p1[i]=p[i];
                burst_time[i]=p[i].bt;
            }

            q1.push(1);
            memset(mark,0,sizeof(mark));
            mark[1] = 1;

            while(completed != num)
            {
                idx = q1.front();
                q1.pop();

                if(p[idx].bt == burst_time[idx])
                {
                    p[idx].st = max(current_time,p[idx].at);
                    //total_idle_time += p[idx].st - current_time;
                    current_time = p[idx].st;
                }

                if(p[idx].cpu_flag)
                {
                    if(p[idx].ct!=0)
                    {
                        io_cpu_assign=0;
                        //p[idx].ct-=1;
                        p[idx].cpu_flag=0;
                    }
                    else if(p[idx].it!=0)
                    {
                        io_cpu_assign=1;
                        //p[idx].it-=1;
                        p[idx].cpu_flag=1;
                    }
                }
                else
                {
                    if(p[idx].it!=0)
                    {
                        io_cpu_assign=1;
                        //p[idx].it-=1;
                        p[idx].cpu_flag=1;
                    }
                    else if(p[idx].ct!=0)
                    {
                        io_cpu_assign=0;
                        //p[idx].ct-=1;
                        p[idx].cpu_flag=0;
                    }
                }

                if(io_cpu_assign==0) //CPU Cycle
                {
                    if(p[idx].ct-time_slice > 0)
                    {
                        QBrush color_brush(QColor(p[idx].color));
                        QPen blackpen(Qt::black);
                        blackpen.setWidth(1);
                        rectangle=scene->addRect(-200+Rectangle_Width*current_time,-25,Rectangle_Width*time_slice,50,blackpen,color_brush);
                        QString temp_str=QString::number(current_time);
                        QGraphicsTextItem *txtitem = new QGraphicsTextItem(temp_str);
                        txtitem->setPos(QPointF(-200+Rectangle_Width*current_time, 100));
                        scene->addItem(txtitem);

                        p[idx].ct -= time_slice;
                        p[idx].bt -= time_slice;
                        current_time += time_slice;
                    }
                    else
                    {
                        QBrush color_brush(QColor(p[idx].color));
                        QPen blackpen(Qt::black);
                        blackpen.setWidth(1);
                        rectangle=scene->addRect(-200+Rectangle_Width*current_time,-25,Rectangle_Width*p[idx].ct,50,blackpen,color_brush);
                        QString temp_str=QString::number(current_time);
                        QGraphicsTextItem *txtitem = new QGraphicsTextItem(temp_str);
                        txtitem->setPos(QPointF(-200+Rectangle_Width*current_time, 100));
                        scene->addItem(txtitem);

                        int time_left= time_slice-p[idx].ct;

                        current_time += p[idx].ct;
                        p[idx].bt -= p[idx].ct;
                        p[idx].ct = 0;

                        if(time_left>0 && p[idx].it>0)
                        {
                            io_cpu_assign=1;
                            p[idx].cpu_flag=1;

                            if(p[idx].it-time_left > 0)
                            {
                                QBrush color_brush(QColor(p[idx].color));
                                QPen blackpen(Qt::black);
                                blackpen.setWidth(1);
                                rectangle=scene->addRect(-200+Rectangle_Width*current_time,25,Rectangle_Width*time_left,50,blackpen,color_brush);
                                QString temp_str=QString::number(current_time);
                                QGraphicsTextItem *txtitem = new QGraphicsTextItem(temp_str);
                                txtitem->setPos(QPointF(-200+Rectangle_Width*current_time, 100));
                                scene->addItem(txtitem);

                                p[idx].it -= time_left;
                                p[idx].bt -= time_left;
                                current_time += time_left;
                            }
                            else
                            {
                                QBrush color_brush(QColor(p[idx].color));
                                QPen blackpen(Qt::black);
                                blackpen.setWidth(1);
                                rectangle=scene->addRect(-200+Rectangle_Width*current_time,25,Rectangle_Width*p[idx].it,50,blackpen,color_brush);
                                QString temp_str=QString::number(current_time);
                                QGraphicsTextItem *txtitem = new QGraphicsTextItem(temp_str);
                                txtitem->setPos(QPointF(-200+Rectangle_Width*current_time, 100));
                                scene->addItem(txtitem);

                                current_time += p[idx].it;
                                p[idx].bt -= p[idx].it;
                                p[idx].it = 0;
                            }
                        }

                        if(p[idx].bt==0)
                        {
                            completed++;

                            p[idx].ft = current_time;
                            p[idx].tat = p[idx].ft - p[idx].at;
                            p[idx].wt = p[idx].tat - burst_time[idx];
                            p[idx].rt = p[idx].st - p[idx].at;

                            //total_turnaround_time += p[idx].tat;
                            //total_waiting_time += p[idx].wt;
                            //total_response_time += p[idx].response_time;
                        }
                    }
                }

                else if(io_cpu_assign==1) //IO Cycle
                {
                    if(p[idx].it-time_slice > 0)
                    {
                        QBrush color_brush(QColor(p[idx].color));
                        QPen blackpen(Qt::black);
                        blackpen.setWidth(1);
                        rectangle=scene->addRect(-200+Rectangle_Width*current_time,25,Rectangle_Width*time_slice,50,blackpen,color_brush);
                        QString temp_str=QString::number(current_time);
                        QGraphicsTextItem *txtitem = new QGraphicsTextItem(temp_str);
                        txtitem->setPos(QPointF(-200+Rectangle_Width*current_time, 100));
                        scene->addItem(txtitem);

                        p[idx].it -= time_slice;
                        p[idx].bt -= time_slice;
                        current_time += time_slice;
                    }
                    else
                    {
                        QBrush color_brush(QColor(p[idx].color));
                        QPen blackpen(Qt::black);
                        blackpen.setWidth(1);
                        rectangle=scene->addRect(-200+Rectangle_Width*current_time,25,Rectangle_Width*p[idx].it,50,blackpen,color_brush);
                        QString temp_str=QString::number(current_time);
                        QGraphicsTextItem *txtitem = new QGraphicsTextItem(temp_str);
                        txtitem->setPos(QPointF(-200+Rectangle_Width*current_time, 100));
                        scene->addItem(txtitem);

                        int time_left= time_slice-p[idx].it;

                        current_time += p[idx].it;
                        p[idx].bt -= p[idx].it;
                        p[idx].it = 0;

                        if(time_left>0 && p[idx].ct>0)
                        {
                            io_cpu_assign=0;
                            p[idx].cpu_flag=0;

                            if(p[idx].ct-time_left > 0)
                            {
                                QBrush color_brush(QColor(p[idx].color));
                                QPen blackpen(Qt::black);
                                blackpen.setWidth(1);
                                rectangle=scene->addRect(-200+Rectangle_Width*current_time,-25,Rectangle_Width*time_left,50,blackpen,color_brush);
                                QString temp_str=QString::number(current_time);
                                QGraphicsTextItem *txtitem = new QGraphicsTextItem(temp_str);
                                txtitem->setPos(QPointF(-200+Rectangle_Width*current_time, 100));
                                scene->addItem(txtitem);

                                p[idx].ct -= time_left;
                                p[idx].bt -= time_left;
                                current_time += time_left;
                            }
                            else
                            {
                                QBrush color_brush(QColor(p[idx].color));
                                QPen blackpen(Qt::black);
                                blackpen.setWidth(1);
                                rectangle=scene->addRect(-200+Rectangle_Width*current_time,-25,Rectangle_Width*p[idx].ct,50,blackpen,color_brush);
                                QString temp_str=QString::number(current_time);
                                QGraphicsTextItem *txtitem = new QGraphicsTextItem(temp_str);
                                txtitem->setPos(QPointF(-200+Rectangle_Width*current_time, 100));
                                scene->addItem(txtitem);

                                current_time += p[idx].ct;
                                p[idx].bt -= p[idx].ct;
                                p[idx].ct = 0;
                            }
                        }

                        if(p[idx].bt == 0)
                        {
                            completed++;

                            p[idx].ft = current_time;
                            p[idx].tat = p[idx].ft - p[idx].at;
                            p[idx].wt = p[idx].tat - burst_time[idx];
                            p[idx].rt = p[idx].st - p[idx].at;

                            //total_turnaround_time += p[idx].tat;
                            //total_waiting_time += p[idx].wt;
                            //total_response_time += p[idx].response_time;
                        }
                    }
                }

                for(int i = 1; i <=num; i++)
                {
                    if(p[i].bt > 0 && p[i].at <= current_time && mark[i] == 0)
                    {
                        q1.push(i);
                        mark[i] = 1;
                    }
                }

                if(p[idx].bt > 0)
                {
                    q1.push(idx);
                }

                if(q1.empty())
                {
                    for(int i = 1; i <= num; i++)
                    {
                        if(p[i].bt > 0)
                        {
                            q1.push(i);
                            mark[i] = 1;
                            break;
                        }
                    }
                }

                //qDebug( "%d\n", completed);

                QElapsedTimer t;
                t.start();
                while(t.elapsed() < simulation_speed)
                {
                    QCoreApplication::processEvents();
                }

            }

            QString temp_str=QString::number(current_time);
            QGraphicsTextItem *txtitem = new QGraphicsTextItem(temp_str);
            txtitem->setPos(QPointF(-200+Rectangle_Width*current_time, 100));
            scene->addItem(txtitem);
            condition=0;
            displayturnwait(num);
            QMessageBox::information(this,"Success","Simulation Completed!");
        }

        if(ch==5)
        {

            for(int i=1;i<=num;i++)
            {
                p1[i]=p[i];
                p1[i].cpu_count = 0;
                p1[i].io_count = 0;
                p[i].ft=-1;
                p[i].st=-1;
            }


            int idx,cpu_flag,io_flag;
            int split =2;
            int t=0;
            int loop_check = 1;
            while(loop_check!=0)
            {
                idx = select_process_pr(t,p1);
                if(idx!=-1)
                {
                if(p1[idx].bt==p[idx].bt && p1[idx].ct>0)
                {
                    cpu_flag=1;
                    io_flag=0;
                    p1[idx].cpu_count++;
                    p1[idx].ct--;
                    p1[idx].bt--;
                }
                else
                {
                    if(p1[idx].cpu_count<(p1[idx].io_count+1)*split && p1[idx].ct>0)
                    {
                        cpu_flag=1;
                        io_flag=0;
                        p1[idx].cpu_count++;
                        p1[idx].ct--;
                        p1[idx].bt--;
                    }
                    else
                    {
                        cpu_flag=0;
                        io_flag=1;
                        p1[idx].io_count++;
                        p1[idx].it--;
                        p1[idx].bt--;
                    }
                }

                QBrush color_brush(QColor(p1[idx].color));
                QPen blackpen(Qt::black);
                blackpen.setWidth(1);
                rectangle=scene->addRect(-200+Rectangle_Width*t,height_level(cpu_flag,io_flag,25),Rectangle_Width,50,blackpen,color_brush);

                int idx2;
                idx2 = select_wc_pr(t,p1,cpu_flag,idx);
                if(idx2!=-1)
                {
                    if(cpu_flag)
                    {
                        p1[idx2].io_count++;
                        p1[idx2].it--;
                        p1[idx2].bt--;
                        QBrush color_brush(QColor(p1[idx2].color));
                        QPen blackpen(Qt::black);
                        blackpen.setWidth(1);
                        rectangle=scene->addRect(-200+Rectangle_Width*t,25,Rectangle_Width,50,blackpen,color_brush);

                    }
                    else
                    {
                        p1[idx2].cpu_count++;
                        p1[idx2].ct--;
                        p1[idx2].bt--;
                        QBrush color_brush(QColor(p1[idx2].color));
                        QPen blackpen(Qt::black);
                        blackpen.setWidth(1);
                        rectangle=scene->addRect(-200+Rectangle_Width*t,-25,Rectangle_Width,50,blackpen,color_brush);

                    }
                }

                QElapsedTimer t1;
                t1.start();
                while(t1.elapsed() < simulation_speed)  /// speed variation
                {
                    QCoreApplication::processEvents();
                }
                }

                loop_check=0;
                for(int j=0;j<num;j++)
                {
                    loop_check+=p1[j+1].bt;
                }

                QString temp_str=QString::number(t);
                QGraphicsTextItem *txtitem = new QGraphicsTextItem(temp_str);

                /// Rectangle labelling
                txtitem->setPos(QPointF(-200+Rectangle_Width*t, 100));
                scene->addItem(txtitem);
                for(int k=0;k<num;k++)
                {
                    if(p1[k+1].bt==0 && p[k+1].ft==-1)
                    {
                        p[k+1].ft=t+1;
                    }
                    if(p1[k+1].bt<p[k+1].bt && p[k+1].st==-1)
                    {
                        p[k+1].st=t;
                    }
                }

                t++;
            }

            QString temp_str=QString::number(t);
            QGraphicsTextItem *txtitem = new QGraphicsTextItem(temp_str);
            txtitem->setPos(QPointF(-200+Rectangle_Width*t, 100));
            scene->addItem(txtitem);

            condition=0;

            displayturnwait(num);
            QMessageBox::information(this,"Succeed","Simulation Completed!");

        }
    }

    else
    {
        QMessageBox::warning(this,"Warning","Data Not Registered!");
    }
}

void sub_window::on_pushButton_4_clicked()
{
    scene->clear();

    QStringList header;
    header<<"ID"<<"Color"<<"Finish Time"<<"Turnaround Time"<<"Waiting Time";
    ui->tableWidget_Result->setRowCount(num);
    ui->tableWidget_Result->setColumnCount(5);
    ui->tableWidget_Result->setHorizontalHeaderLabels(header);
    ui->tableWidget_Result->horizontalHeader()->setStyleSheet("QHeaderView::section{background:skyblue;}");
    ui->tableWidget_Result->verticalHeader()->setStyleSheet("QHeaderView::section{background:skyblue;}");
    ui->tableWidget_Result->horizontalHeader()->resizeSection(2,150);

    for(int i=0;i<ui->tableWidget->rowCount();i++)
    {
        p[i+1].id=0;
        p[i+1].at=0;
        p[i+1].ct=0;
        p[i+1].it=0;
        p[i+1].bt=0;
        p[i+1].pr=0;
        p[i+1].color="";

        p[i+1].ft=0;
        p[i+1].st=0;
        p[i+1].tat=0;
        p[i+1].wt=0;
        p[i+1].rt=0;
        p[i+1].cpu_flag=1;
    }

    ui->tableWidget->setEditTriggers(QAbstractItemView::AllEditTriggers);

    QMessageBox::information(this,"Cleared","Simulator Reset!");
}

void sub_window::on_pushButton_5_clicked()
{
    QString filter = "CSV File (*.csv)";
    QString file_name = QFileDialog::getOpenFileName(this,"Open a File","C:\\",filter);
    QFile file(file_name);

    if(!file.open(QFile::ReadOnly))
    {
        QMessageBox::warning(this,"Warning","File Not Opening!");
    }
    QTextStream in(&file);
    QString text = in.readAll();

    QStringList rowOfData;
    QStringList rowData;

    rowOfData.clear();
    rowData.clear();

    rowOfData = text.split("\n");

    rowData = rowOfData.at(0).split(",");
    if(rowData.size()!=4)
    {
        QMessageBox::warning(this,"Warning","Data Input Wrong!");
    }

    else
    {
        num=rowOfData.size();
        ui->tableWidget->setRowCount(rowOfData.size());

        for(int x=0; x<rowOfData.size(); x++)
        {
            rowData=rowOfData.at(x).split(",");

            for(int y=0; y<rowData.size(); y++)
            {
                ui->tableWidget->setItem(x,y,new QTableWidgetItem(rowData[y]));

            }
        }
    }

    file.close();
}
