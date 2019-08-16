#include "Client/App.hpp"

int main(int argc, const char * argv[]) {
    
    auto app = new App(argc, argv);
    int result = app->run();

    delete app;
    app = nullptr;

    return result;
}