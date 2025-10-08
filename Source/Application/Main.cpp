
int main(int argc, char* argv[]) {
    neu::file::SetCurrentDirectory("Assets");
    LOG_INFO("current directory {}", neu::file::GetCurrentDirectory());

    // initialize engine
    LOG_INFO("initialize engine...");
    neu::GetEngine().Initialize();

    // initialize scene


    SDL_Event e;
    bool quit = false;

    std::vector<neu::vec3> points{ {-0.5f, -0.5f, 0}, {0, 0.5, 0}, {0.5, -0.5, 0} };
    std::vector<neu::vec3> colors{ {0.5f, 0.5f, 0}, {0, 0.5f, 0.5f}, {0.5f, 0, 0.5f} };

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
