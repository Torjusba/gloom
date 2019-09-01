// Local headers
#include "program.hpp"
#include "gloom/gloom.hpp"
#include "gloom/shader.hpp"


void runProgram(GLFWwindow* window)
{
    // Enable depth (Z) buffer (accept "closest" fragment)
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);

    // Configure miscellaneous OpenGL settings
    glEnable(GL_CULL_FACE);

    // Set default colour after clearing the colour buffer
    glClearColor(0.3f, 0.5f, 0.8f, 1.0f);

    // Set up your scene here (create Vertex Array Objects, etc.)
	
	Gloom::Shader shader;
	shader.makeBasicShader("../../gloom/shaders/simple.vert", "../../gloom/shaders/simple.frag");

	std::vector<float> triangle_vertices{	-0.6, -0.6, 0,
											0, -0.6, 0, 
											-0.3, 0, 0,
											0.6, -0.6, 0,
											0.3, 0, 0,
											0,0.6,0, //5
											-1.0,1.0,0,
											-1.0,-0.9,0,
											-0.1,1.0,0,
											1.0,1.0,0,
											0.1,1.0,0,
											1.0,-0.9,0 //10
	};
	
	std::vector<int> triangle_indices{	0,1,2,
										1,3,4,
										2,4,5,
										6,7,8,
										9,10,11
	};

	unsigned int triangleVAOID = createTriangleVAO(triangle_vertices, triangle_indices);

	shader.activate();

    // Rendering Loop
    while (!glfwWindowShouldClose(window))
    {
        // Clear colour and depth buffers
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // Draw your scene here

		glBindVertexArray(triangleVAOID);

		glDrawElements(GL_TRIANGLES, 15, GL_UNSIGNED_INT, 0);

        // Handle other events
        glfwPollEvents();
        handleKeyboardInput(window);

        // Flip buffers
        glfwSwapBuffers(window);
    }

	// Cleanup
	shader.deactivate();
	shader.destroy();
}


void handleKeyboardInput(GLFWwindow* window)
{
    // Use escape key for terminating the GLFW window
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(window, GL_TRUE);
    }
}


//Set up a Vertex Array Object for drawing triangles
unsigned int createTriangleVAO(std::vector<float> vertices, std::vector<int> indices)
{
	unsigned int array=0;
	glGenVertexArrays(1, &array);
	glBindVertexArray(array);

	unsigned int array_buffer=0;
	glGenBuffers(1, &array_buffer);
	glBindBuffer(GL_ARRAY_BUFFER, array_buffer);

	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), vertices.data(), GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 12, 0);
	glEnableVertexAttribArray(0);

	unsigned int index_buffer=0;
	glGenBuffers(1, &index_buffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, index_buffer);

	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(int), indices.data(), GL_STATIC_DRAW);


	printGLError();

	return array;
}

