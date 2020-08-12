#include<iostream>
#include<vector>
#include "creator.h"
#include<QTextStream>
using namespace std;
QTextStream out(stdout);

void Creator::set_info(const QString Name, const QString token, QString prefix)
{
  bot.set_name(Name);
  bot.set_token(token);
  bot.set_prefix(prefix);
}
void Creator::set_directory(QString dir)
{
    Creator::directory = dir;
}
void Creator::set_func_list(vector<Func> list)
{
    Creator::FuncList.reserve(list.size());
    for (unsigned int i = 0; i < list.size(); i++)
    {
        this->FuncList[i] = list[i];
    }
}
void Creator::add_in_list(Func arg)
{
  FuncList.push_back(arg);
}
void Creator::set_message(QString mess)
{
  this->message = mess;
}
QString Creator::get_directory()
{
    return Creator::directory;
}
vector<Creator::Func> Creator::get_func_list()
{
    return Creator::FuncList;
}
void Creator::create_bot_file()
{
  QFile botF(get_directory());
  if(botF.open(QIODevice::WriteOnly))
    {
      QTextStream out(&botF);
      botF.write("import discord\n");
      botF.write("from discord.ext import commands\n");
      botF.write("import random\n");
      botF.write("from random import randint\n");
      botF.write("import os\n");
      botF.write("TOKEN = "); out << bot.get_token() << endl;
      botF.write("PREFIX = "); out << "'" << bot.get_prefix() << "'" << endl;
      botF.write("client = commands.Bot( command_prefix = PREFIX )\n");
      botF.write("@client.event\n");
      botF.write("async def on_ready():\n");
      botF.write("\tprint( ' Im connected ' )\n");
      botF.write("@client.event\n");
      botF.write("async def on_command_error(ctx, error):\n");
      botF.write("\tif isinstance(error, commands.CommandNotFound ):\n");
      botF.write("\t\tawait ctx.send(embed = discord.Embed(description = f'** {ctx.author.name}, this command does not exist. Existing teams can be viewed using {PREFIX}help .**', color=discord.Color.red()))\n");
      for(unsigned int i =0; i<FuncList.size(); i++)
        {
          out << "@client.command( pass_context = True )" << endl;
          if(FuncList[i].permissions == true)
            out << "@commands.has_permissions( administrator = True )" << endl;
          out << "async def " << FuncList[i].Command;
          if(FuncList[i].FuncName == "Mess")
            {
              out <<"( ctx ):" << endl;
              out << "\tawait ctx.send( '" << this->message << "')" << endl;
            }
          if(FuncList[i].FuncName == "Clear")
            {
              out << "( ctx, amount = 100):" << endl;
              out << "\tprint(ctx.author.name + '[command]: clear')" <<endl;
              out << "\tawait ctx.channel.purge( limit = amount )" << endl;
            }
          if(FuncList[i].FuncName == "flip" )
            {
              out << "( ctx ):" << endl;
              out << "\tprint(ctx.author.name + '[command]: flip')" << endl;
              out << "\temb = discord.Embed ( title = 'Coin tossed', colour = discord.Color.gold() )" << endl;
              out << "\trandom.seed()" << endl;
              out << "\tmoney = randint(0, 1)" << endl;
              out << "\tif money == 0:" << endl;
              out << "\t\temb.set_author( name = client.user.name, icon_url = client.user.avatar_url )" << endl;
              out << "\t\temb.set_footer( text = ctx.author.name, icon_url = ctx.author.avatar_url )" << endl;
              out << "\t\temb.add_field( name = 'Coin fell eagle up', value = 'Hope you are lucky' )" << endl;
              out << "\t\temb.set_image( url = 'https://coins.tsbnk.ru/upload/iblock/573/5015-0052.png' )" << endl;
              out << "\t\tawait ctx.channel.send( embed = emb)" << endl;
              out << "\telse:" << endl;
              out << "\t\temb.set_author( name = client.user.name, icon_url = client.user.avatar_url )" << endl;
              out << "\t\temb.set_footer( text = ctx.author.name, icon_url = ctx.author.avatar_url )" << endl;
              out << "\t\temb.add_field( name = 'Coin Tails Up', value = 'Hope you are lucky' )" << endl;
              out << "\t\temb.set_image( url = 'https://cs8.pikabu.ru/post_img/big/2017/04/22/11/1492888050140348172.png' )" << endl;
              out << "\t\tawait ctx.channel.send( embed = emb)" << endl;
            }
          if(FuncList[i].FuncName == "info")
            {
              out << "( ctx ):" << endl;
              out << "\temb = discord.Embed ( title = 'My Info', colour = ctx.author.top_role.colour )" << endl;
              out << "\temb.set_author ( name = client.user.name, icon_url = client.user.avatar_url )" << endl;
              out << "\temb.add_field ( name = ctx.author.name, value = f' Composed by {str(ctx.author.guild)}  Main role {str(ctx.author.top_role)}')" << endl;
              out << "\temb.set_image ( url = ctx.author.avatar_url )" << endl;
              out << "\tawait ctx.channel.send( embed = emb )" << endl;
            }
          if(FuncList[i].FuncName == "mass")
            {
              out << "( ctx, mes : str ):" << endl;
              out << "\tprint(ctx.author.name + '[command]: mass_send ( ' + mes + ' )')" << endl;
              out << "\tfor i in client.get_channel(697822717050748979).members:" <<endl;
              out << "\t\tawait i.send(mes)" << endl;
            }
          if(FuncList[i].FuncName == "mafia")
            {
              out << "( ctx ):" << endl;
              out << "\tprint(ctx.author.name + '[command]: Mafia Game')" << endl;
              out << "\tif len(client.get_channel(714072862197022821).members) < 4:" <<endl;
              out << "\t\tawait ctx.channel.send(' Too few people to play !!! ')" <<endl;
              out << "\telse:" <<endl;
              out << "\t\ttemp = 0" <<endl;
              out << "\t\tply_roles = []" <<endl;
              out << "\t\trole_list = []" <<endl;
              out << "\t\tfor i in range(0, len(client.get_channel(714072862197022821).members)):" <<endl;
              out << "\t\t\trole_list.append(i)" <<endl;
              out << "\t\tif len(client.get_channel(714072862197022821).members) > 7:" <<endl;
              out << "\t\t\trole_list[4] = 0" <<endl;
              out << "\t\trandom.shuffle(role_list)" <<endl;
              out << "\t\trandom.shuffle(form_list)" <<endl;
              out << "\t\tfor i in client.get_channel(714072862197022821).members:" <<endl;
              out << "\t\t\tif role_list[temp] == 0:" <<endl;
              out << "\t\t\t\tply_roles.append('Mafia is ' + i.name)" <<endl;
              out << "\t\t\tif role_list[temp] == 1:" <<endl;
              out << "\t\t\t\tply_roles.append('Commissioner is ' + i.name)" <<endl;
              out << "\t\t\tif role_list[temp] == 2:" <<endl;
              out << "\t\t\t\tved = i" <<endl;
              out << "\t\t\tif len(client.get_channel(714072862197022821).members) > 5:" <<endl;
              out << "\t\t\t\tif role_list[temp] == 3:" <<endl;
              out << "\t\t\t\t\tply_roles.append('Doctor is ' + i.name)" <<endl;
              out << "\t\t\t\telse:" <<endl;
              out << "\t\t\t\t\tif role_list[temp]>3:" <<endl;
              out << "\t\t\t\t\t\tawait i.send('Peace')" <<endl;
              out << "\t\t\telse:" <<endl;
              out << "\t\t\t\tif role_list[temp] > 2:" <<endl;
              out << "\t\t\t\t\tawait i.send('Peace') " <<endl;
              out << "\t\t\ttemp+=1" <<endl;
              out << "\t\tfor i in range(len(ply_roles)):" <<endl;
              out << "\t\t\tawait ved.send(str(ply_roles[i]))" <<endl;
            }

        }
      botF.write("client.run(TOKEN)\n");
    }
  botF.close();
}
