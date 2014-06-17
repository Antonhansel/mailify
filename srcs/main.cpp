#include "MainUI.hpp"

int		main(int argc, char **argv)
{
  QApplication	app(argc, argv);
  MainUI	Client;
  
  Client.show();
  return (app.exec());
}
