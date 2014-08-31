
#include <GL/glew.h>
#include <stdio.h>
#include <stdlib.h>
#include <GL/glut.h>
#include "math_3d.h"
#include <string>
#include <iostream>
#include <fstream>
#include <assert.h>
#include "Pipeline.h"
#include "Camera.h"
#include "Texture.h"
#include "Callbacks.h"
#include "Lighting.h"
#include "GlutBackend.h"

#define W_HEIGHT 800
#define W_WIDTH 800
#define ARRAY_SIZE_IN_ELEMENTS(a) (sizeof(a)/sizeof(a[0]))

struct Vertex{
	Vector3f m_pos;
	Vector2f m_tex;
	Vector3f m_normal;

	Vertex(){}

	Vertex(Vector3f pos, Vector2f tex){
		m_pos = pos;
		m_tex = tex;
		m_normal = Vector3f(0.0f, 0.0f, 0.0f);
	}
};


class MainFuncs : public Callbacks{
public:
	MainFuncs(){
		//moveCam = NULL;
		textura = NULL;
		pEffect = NULL;
		Scale = 0.0f;
		directionalLight.Color = Vector3f(1.0f, 1.0f, 1.0f);
		directionalLight.AmbientIntensity = 0.5f;
		directionalLight.DiffuseIntensity = 1.5f;
		directionalLight.Direction = Vector3f(-1.0f, -1.0f, -1.0f);
	}

	~MainFuncs(){
		delete pEffect;
		//delete moveCam;
		delete textura;
	}

	bool Init(){

		unsigned int indices[] = {0, 3 ,1 , 1, 3, 2, 2, 3, 0, 0, 1, 2};

		vertexBinding(indices, ARRAY_SIZE_IN_ELEMENTS(indices));
		indexBinding(indices, ARRAY_SIZE_IN_ELEMENTS(indices));

		pEffect = new Lighting();
		if (!pEffect->init()){
			return false;
		}
		
		pEffect->enable();
		pEffect->setTextureUnit(0);
		textura = new Texture(GL_TEXTURE_2D, "test.bmp");
		if (!textura->load()){
			return false;
		}
		return true;
	}

	void run(){
		glutBackendRun(this);
	}

	virtual void display(){
		glClear(GL_COLOR_BUFFER_BIT);

		static float Scale = 0.0f;
		Scale += 0.5f;
	
		Pipeline p;
		p.Rotate(0.0f, Scale, 0.0f);
		p.Scale(1.0f, 1.0f, 1.0f);
		p.WorldPos(0.0f, 0.0f, 3.0f);
		p.setCamera(moveCam.getPos(), moveCam.getTarget(), moveCam.getUp());
		p.SetPerspectiveProj(60.0f, W_WIDTH, W_HEIGHT, 1.0f, 100.0f);

		pEffect->setWVP(p.getWVPTrans());
		const Matrix4f &WorldTransform = p.getWorldTrans();
		pEffect->setWorldMatrix(WorldTransform);
		pEffect->setDirLight(directionalLight);
		
		glEnableVertexAttribArray(0);
		glEnableVertexAttribArray(1);
		glEnableVertexAttribArray(2);
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const GLvoid*)12);
		glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const GLvoid*)20);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
		textura->bind(GL_TEXTURE0);
		glDrawElements(GL_TRIANGLES, 12, GL_UNSIGNED_INT, 0);
		glDisableVertexAttribArray(0);
		glDisableVertexAttribArray(1);
		glDisableVertexAttribArray(2);

		glutSwapBuffers();
	}

	virtual void idleDisp(){
		display();
	}

	virtual void specialKeyboard(int Key, int x, int y)
    {
		moveCam.onKeyboard(Key);
    }

	virtual void keyboardFunc(unsigned char key, int x, int y){
		switch(key){
		case 'q':
			exit(0);
		}
	}

private:

	void CalcNormals(const unsigned int* pIndices, unsigned int IndexCount,
                     Vertex* pVertices, unsigned int VertexCount)
    {
        // Accumulate each triangle normal into each of the triangle vertices
        for (unsigned int i = 0 ; i < IndexCount ; i += 3) {
            unsigned int Index0 = pIndices[i];
            unsigned int Index1 = pIndices[i + 1];
            unsigned int Index2 = pIndices[i + 2];
            Vector3f v1 = pVertices[Index1].m_pos - pVertices[Index0].m_pos;
            Vector3f v2 = pVertices[Index2].m_pos - pVertices[Index0].m_pos;
            Vector3f Normal = v1.Cross(v2);
            Normal.Normalize();

            pVertices[Index0].m_normal += Normal;
            pVertices[Index1].m_normal += Normal;
            pVertices[Index2].m_normal += Normal;
        }

        // Normalize all the vertex normals
        for (unsigned int i = 0 ; i < VertexCount ; i++) {
            pVertices[i].m_normal.Normalize();
        }
    }

	void vertexBinding(const unsigned int *pIndices, unsigned int iCount){
		Vertex Vertices[4];
		Vertices[0] = Vertex(Vector3f(-1.0f, -1.0f, 0.5773f), Vector2f(0.0f, 0.0f));
		Vertices[1] = Vertex(Vector3f(0.0f, -1.0f, -1.155f), Vector2f(0.5f, 0.0f));
		Vertices[2] = Vertex(Vector3f(1.0f, -1.0f, 0.577f), Vector2f(1.0f, 0.0f));
		Vertices[3] = Vertex(Vector3f(0.0f, 1.0f, 0.0f), Vector2f(0.5f, 1.0f));

		unsigned int vCount = ARRAY_SIZE_IN_ELEMENTS(Vertices);
		CalcNormals(pIndices, iCount, Vertices, vCount);

		glGenBuffers(1, &VBO);
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(Vertices), Vertices, GL_STATIC_DRAW);
	}


	void indexBinding(const unsigned int* pIndices, unsigned int szBt){

		glGenBuffers(1, &IBO);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, szBt, pIndices, GL_STATIC_DRAW);
	}

	Camera moveCam;
	Texture *textura;
	GLuint VBO, IBO;
	Lighting *pEffect;
	float Scale;
	DirectionalLight directionalLight;
};


int main(int argc, char** argv)
{
    glutBackendInit(argc, argv);

	if (!glutBackendWindow(W_WIDTH, W_HEIGHT, "RollBalls"))
		return 1;

	MainFuncs *app;
	app = new MainFuncs();
	if(!app->Init())
		return 1;

	app->run();
	
	delete app;
	getchar();
    return 0;
}