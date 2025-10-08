
int main(int argc, char* argv[]) {
    neu::file::SetCurrentDirectory("Assets");
    LOG_INFO("current directory {}", neu::file::GetCurrentDirectory());

    // initialize engine
    LOG_INFO("initialize engine...");
    neu::GetEngine().Initialize();

    // initialize scene


    SDL_Event e;
    bool quit = false;

    // OpenGL
    std::vector<neu::vec3> points{ {-0.5f, -0.5f, 0}, {0, 0.5, 0}, {0.5, -0.5, 0} };
    std::vector<neu::vec3> colors{ {0.5f, 0.5f, 0}, {0, 0.5f, 0.5f}, {0.5f, 0, 0.5f} };

    // (Vertex Buffer Object)
    GLuint vbo;
    glGenBuffers(1, &vbo);

    // Vertex Buffer (Position)
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(neu::vec3) * points.size(), points.data(), GL_STATIC_DRAW);

    // (Vertex Array Object)
    GLuint vao;
    glGenVertexArrays(1, &vao);

    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);

    // Vertex Shader
    std::string vs_source;
    neu::file::ReadTextFile("Shaders/basic.vert", vs_source);
    const char* vs_cstr = vs_source.c_str();
    
    // (Vertex Shader)
    GLuint vs;
    vs = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vs, 1, &vs_cstr, NULL);
    glCompileShader(vs);

    // MAIN LOOP
    while (!quit) {
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_EVENT_QUIT) {
                quit = true;
            }
        }

        // update
        neu::GetEngine().Update();


        if (neu::GetEngine().GetInput().GetKeyPressed(SDL_SCANCODE_ESCAPE)) quit = true;

        float angle = neu::GetEngine().GetTime().GetTime() * 90.0f;
        float scale = neu::math::Remap(-1.0f, 1.0f, 0.3f, 1.5f, neu::math::sin(neu::GetEngine().GetTime().GetTime()));
        neu::vec2 mouse = neu::GetEngine().GetInput().GetMousePosition();
        neu::vec2 position;
        position.x = neu::math::Remap(0.0f, (float)neu::GetEngine().GetRenderer().GetWidth(), -1.0f, 1.0f, mouse.x);
        position.y = -neu::math::Remap(0.0f, (float)neu::GetEngine().GetRenderer().GetWidth(), -1.0f, 1.0f, mouse.y);


        // draw
        neu::GetEngine().GetRenderer().Clear();

        glLoadIdentity();
        glPushMatrix();

        glTranslatef(position.x, position.y, 0);
        glRotatef(angle, 0, 0, 1);
        glScalef(scale, scale, 0);

        glBegin(GL_TRIANGLES);

        for (int i = 0; i < points.size(); i++) {
            glColor3f(colors[i].r, colors[i].g, colors[i].b);
            glVertex3f(points[i].x, points[i].y, points[i].z);
        }

        glPopMatrix();

        glEnd();

        neu::GetEngine().GetRenderer().Present();
    }

    neu::GetEngine().Shutdown();

    return 0;
}
