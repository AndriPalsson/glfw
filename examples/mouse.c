//========================================================================
//
// Andri Pálsson 2013
//
// Keys:
// 1: Normal Cursor
// 2: Hidden Cursor
// 3: Disabled Cursor
// F: Toggle Fullscreen
//
//========================================================================


#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define GLFW_INCLUDE_GLU
#include <GLFW/glfw3.h>

GLFWwindow* window = NULL;
int screenMode = GL_FALSE;
int setCursor = GL_TRUE;

int openWindow(int fullscreen);


void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (action != GLFW_PRESS)
        return;

    switch (key)
    {
        case GLFW_KEY_ESCAPE:
            glfwSetWindowShouldClose(window, GL_TRUE);
            break;
        case GLFW_KEY_1:
            printf("Cursor Normal\n");
            glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
            break;
        case GLFW_KEY_2:
            printf("Cursor Hidden\n");
            glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
            break;
        case GLFW_KEY_3:
            printf("Cursor Disabled\n");
            glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
            break;
        case GLFW_KEY_F:
            screenMode = !screenMode;
            openWindow(screenMode);
            break;
        case GLFW_KEY_M:
            setCursor = !setCursor;
            break;
        default:
            break;
    }
}

int openWindow(int fullscreen)
{
    
    const GLFWvidmode *videoMode;
    GLFWmonitor  *monitor = NULL;
    double width, height;
    
    if(!fullscreen)
    {
        width = 800;
        height = 600;
    }
    else
    {
        monitor = glfwGetPrimaryMonitor();
        videoMode = glfwGetVideoMode(monitor);
        width = videoMode->width;
        height = videoMode->height;
    }
    
    if (window)
    {
        glfwDestroyWindow(window);
        //window = NULL;
    }
    
    window = glfwCreateWindow(width, height, "OSX Cursor Test", fullscreen ? monitor:NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        exit(EXIT_FAILURE);
//        return GL_FALSE;
    }
    
    glfwSetKeyCallback(window, key_callback);
    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);
    return GL_TRUE;
}

int main(int argc, char* argv[])
{
    const double posX = 100.0f;
    const double posY = 100.0f;
    
    double x, y;
    
    
    if (!glfwInit())
        exit(EXIT_FAILURE);

    if (!openWindow(screenMode))
        exit(EXIT_FAILURE);
    
    glfwSetCursorPos(window, posX, posY);
    
    
    while (!glfwWindowShouldClose(window))
    {
        
        
        glfwGetCursorPos(window, &x, &y); //Get Mouse movement
        
        //Only print if mouse moved
        if ( (abs(x-posX) >=  0.0001) || (abs(y-posY) >=  0.0001) )
        {
            printf("x: %f, y: %f\n",x,y);
        }
        
        //Reset cursor to inital position
        if (setCursor)
        {
            glfwSetCursorPos(window, posX, posY);

        }
        
        glfwPollEvents();
        
    }
    exit(EXIT_SUCCESS);
}

