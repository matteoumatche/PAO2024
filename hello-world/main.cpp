// Includes Qt header files
# include < QApplication >
# include < QLabel >

int main (int argc , char * argv []) {
// Defines an application object
QApplication app ( argc , argv ) ;
// A piece of text
Mainwindow hello (" Hello world !") ;
// Tells Qt to actually show the label
hello . show () ;
// Runs application
return app . exec () ;
}