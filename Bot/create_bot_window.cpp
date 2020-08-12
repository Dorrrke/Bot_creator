#include "create_bot_window.h"
#include "ui_create_bot_window.h"
#include <QtGui>
#include <QTranslator>
Create_bot_window::Create_bot_window(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Create_bot_window)
{
    ui->setupUi(this);

    QPixmap bkgnd(":/resourec/img/1579284620_32-89.jpg");
        bkgnd = bkgnd.scaled(this->size(), Qt::IgnoreAspectRatio);
        QPalette palette;
        palette.setBrush(QPalette::Background, bkgnd);
        this->setPalette(palette);
      this->setWindowFlags(Qt::FramelessWindowHint);

        // Задаём два пункта с текстом локалей в комбобоксе
            ui->comboBox_2->addItems(QStringList() << "en_US" << "ru_RU");

            // подключаем к сигналу изменения пункта комбобокса лямбда функцию,
            // в которой будет изменяться перевод приложения
            // Здесь имеется интересный момент. Поскольку QComboBox имеет перегрузку сигнатуры сигнала,
            // то нам необходимо скастовать сигнал к нужной сигнатуре.
            // В данном случае будем использовать название пункта при его изменении
            connect(ui->comboBox_2, static_cast<void (QComboBox::*)(const QString &)>(&QComboBox::currentIndexChanged),
                    [=](const QString &str){
                qtLanguageTranslator1.load("QtLanguage_" + str, ".");   // Загружаем перевод
                qApp->installTranslator(&qtLanguageTranslator1);        // Устанавливаем перевод в приложение
            });

            // Сделаем первоначальную инициализацию перевода для окна прилоежния
            qtLanguageTranslator1.load(QString("QtLanguage_") + QString("en_US"));
            qApp->installTranslator(&qtLanguageTranslator1);
}

Create_bot_window::~Create_bot_window()
{
    delete ui;
}

void Create_bot_window::on_CreateBotButton_clicked()
{
    this->close();
    emit menuW();
}

void Create_bot_window::on_comadLine_textEdited(const QString &arg1)
{
  this->com = arg1;
}

void Create_bot_window::on_messLine_textEdited(const QString &arg1)
{
    this->mes = arg1;
}

void Create_bot_window::on_checkBox_5_stateChanged(int arg1)
{
    if (arg1 == 1)
        mes_permiss = true;
    else
      mes_permiss = false;
}

void Create_bot_window::on_AddMess_clicked()
{
    Creator::Func arg;
    arg.Command = ui->comadLine->text();
    mes = ui->messLine->text();
    arg.FuncName = "Mess";
    if(ui->checkBox_5->isChecked())
      {
        arg.permissions = true;
      }
    else
      {
        arg.permissions = false;
      }
    bot.add_in_list(arg);
    bot.set_message(mes);
}



void Create_bot_window::on_AddClear_clicked()
{
    Creator::Func arg;
    arg.Command = "Clear";
    arg.FuncName = "Clear";
    if(ui->checkBox->isChecked())
      {
        arg.permissions = true;
      }
    else
      {
        arg.permissions = false;
      }
    bot.add_in_list(arg);
}

void Create_bot_window::on_checkBox_4_stateChanged(int arg1)
{
  if(arg1 == 1)
    flip_permiss = true;
  else
    flip_permiss = false;
}

void Create_bot_window::on_AddFlip_clicked()
{
  Creator::Func arg;
  arg.Command = "flip";
  arg.FuncName = "flip";
  if(ui->checkBox_4->isChecked())
    {
      arg.permissions = true;
    }
  else
    {
      arg.permissions = false;
    }
  bot.add_in_list(arg);
}

void Create_bot_window::on_checkBox_3_stateChanged(int arg1)
{
  if(arg1 == 1)
    info_permiss = true;
  else
    info_permiss = false;
}

void Create_bot_window::on_AddInfo_clicked()
{
  Creator::Func arg;
  arg.Command = "info";
  arg.FuncName = "info";
  if(ui->checkBox_3->isChecked())
    {
      arg.permissions = true;
    }
  else
    {
      arg.permissions = false;
    }
  bot.add_in_list(arg);
}

void Create_bot_window::on_checkBox_2_stateChanged(int arg1)
{
  if(arg1 == 1)
    melling_permiss = true;
  else
    melling_permiss = false;
}

void Create_bot_window::on_AddMassMelling_clicked()
{
  Creator::Func arg;
  arg.Command = "mass";
  arg.FuncName = "mass";
  if(ui->checkBox_2->isChecked())
    {
      arg.permissions = true;
    }
  else
    {
      arg.permissions = false;
    }
  bot.add_in_list(arg);
}

void Create_bot_window::on_checkBox_6_stateChanged(int arg1)
{
  if(arg1 == 1)
    game_permiss = true;
  else
    game_permiss = false;
}

void Create_bot_window::on_AddMafia_clicked()
{
  Creator::Func arg;
  arg.Command = "mafia";
  arg.FuncName = "mafia";
  if(ui->checkBox_6->isChecked())
    {
      arg.permissions = true;
    }
  else
    {
      arg.permissions = false;
    }
  bot.add_in_list(arg);
}

void Create_bot_window::on_pushButton_clicked()
{
    QString Dir = QFileDialog::getOpenFileName(0, "Select dir", "");
    ui->dirLine->insert(Dir);
}

void Create_bot_window::on_CreateButton_clicked()
{
    bot.set_info(ui->BotsName->text(), ui->Token->text(), ui->comboBox->currentText());
    bot.set_directory(ui->dirLine->text());
    bot.create_bot_file();
}

void Create_bot_window::mouseMoveEvent(QMouseEvent *e)
{
    if(myPos1.x()>=0 && e->buttons()&& Qt::LeftButton)
    {
        QPoint diff = e->pos()- myPos1;
        QPoint newpos = this->pos()+diff;
        this->move(newpos);
    }
}
void Create_bot_window::mousePressEvent(QMouseEvent *e)
{
    myPos1 = e->pos();
}
void Create_bot_window::mouseReleaseEvent(QMouseEvent *e)
{
    myPos1 = QPoint(-1,1);
}

void Create_bot_window::on_pushButton_2_clicked()
{
    close();
}



void Create_bot_window::on_Back_clicked()
{
    this->close();
    emit menuW();
}
void Create_bot_window::changeEvent(QEvent *event)
{
    // В случае получения события изменения языка приложения
    if (event->type() == QEvent::LanguageChange) {
        ui->retranslateUi(this);    // переведём окно заново
    }
}

void Create_bot_window::on_pushButton_3_clicked()
{
    showMinimized ();
}
