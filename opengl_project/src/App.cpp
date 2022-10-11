#include "core/Application.h"
#include <GL/glew.h>
#include "GLFW/glfw3.h"

int main(void)
{
    Application* app = new Application("Test App");
    app->Run();
    delete app;
    return 0;
}