#pragma once
#include "GameObject.h"

class Graveyard : GameObject
{

private:

	VertexArrayObject m_vao;
	Shader m_shader;
	std::vector<Layer> m_layers;
	Direction m_direction;

public:

	Graveyard() :
		m_vao(VertexArrayObject()),
		m_shader(Shader()),
		m_direction(Direction::RIGHT)
	{
		GLfloat vertexCoords[] = { -1.0f, -1.0f, 1.0f, -1.0, 1.0f, 1.0f, -1.0f, 1.0f };
		GLfloat textureCoords[] = { 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f, 0.0f, 1.0f };
		GLuint indices[] = { 0, 1, 2, 2, 3, 0 };

		VertexBufferObject vbo1 = VertexBufferObject(vertexCoords, sizeof(vertexCoords));
		VertexBufferObject vbo2 = VertexBufferObject(textureCoords, sizeof(textureCoords));
		VertexBufferObject vbo3 = VertexBufferObject(indices, sizeof(indices), GL_ELEMENT_ARRAY_BUFFER);

		m_vao.AddBuffer(vbo1, 2);
		m_vao.AddBuffer(vbo2, 2);
		m_vao.AddBuffer(vbo3, 3, GL_ELEMENT_ARRAY_BUFFER);

		//Do not forget to create the shader here
		std::cout << "Do not forget to pass the shaders filepath here." << std::endl;	
		m_shader.CreateShader();

		//Do not forget do add the textures here
		std::cout << "Do not forget do add the textures for the graveyard." << std::endl;
 		m_layers.push_back(Layer(Texture(""), -0.01f, 0.0001f));
		m_layers.push_back(Layer(Texture(""), -0.02f, 0.0002f));
		m_layers.push_back(Layer(Texture(""), -0.03f, 0.0004f));
		m_layers.push_back(Layer(Texture(""), -0.04f, 0.0006f));
		m_layers.push_back(Layer(Texture(""), -0.05f, 0.0008f));
		m_layers.push_back(Layer(Texture(""), -0.06f, 0.001f));
		m_layers.push_back(Layer(Texture(""), -0.07f, 0.001f));
	}

	void ProcessInput(int key)
	{
		if (key == GLFW_KEY_D)
			for (int i = 0; i < m_layers.size(); i++)
				m_layers[i].ScrollRight();
		else if (key == GLFW_KEY_A)
			for (int i = 0; i < m_layers.size(); i++)
				m_layers[i].ScrollLeft();
		else
			for (int i = 0; i < m_layers.size(); i++)
				m_layers[i].HaltScrolling();
	}

	void Draw() 
	{
		glActiveTexture(GL_TEXTURE0);
		m_vao.Bind();
		m_shader.Use();

		for (int i = 0; i < m_layers.size(); i++)
		{
			m_layers[i].BindTexture();
			m_shader.SetTexture("u_Texture", 0);
			m_shader.SetFloat("u_Depth", m_layers[i].GetDepth());
			m_shader.SetFloat("u_OffsetX", m_layers[i].GetOffsetX());
			glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		}
	}

};
