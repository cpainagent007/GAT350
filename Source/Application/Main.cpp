
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

    // Model
    auto model3d = std::make_shared<neu::Model>();

    model3d->Load("models/sphere.obj");
    
    // Shaders
    auto vs = neu::Resources().Get<neu::Shader>("Shaders/basic.vert", GL_VERTEX_SHADER);
    auto fs = neu::Resources().Get<neu::Shader>("Shaders/basic.frag", GL_FRAGMENT_SHADER);

    // Program
    auto program = std::make_shared<neu::Program>();
    program->AttachShader(vs);
    program->AttachShader(fs);
    program->Link();
    program->Use();

    // Texture
    neu::res_t<neu::Texture> texture = neu::Resources().Get<neu::Texture>("Textures/SpongeSurprise.png");

    // Uniform
    program->SetUniform("u_texture", 0);

    // Transform
    float rotation = 0.0f;
    glm::vec3 eye{ 0, 0, 1 };

    neu::Transform transform{ { 1, 0, 0 } };
    neu::Transform view{ { 1, 0, 0 } };

    // Projection Matrix
    float aspect = (neu::GetEngine().GetRenderer().GetWidth()) / (float)(neu::GetEngine().GetRenderer().GetHeight());
    glm::mat4 projection = glm::perspective(glm::radians(90.0f), aspect, 0.01f, 100.0f);
    program->SetUniform("u_projection", projection);

    // MAIN LOOP
    while (!quit) {
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_EVENT_QUIT) {
                quit = true;
            }
        }

        // Update
        neu::GetEngine().Update();

        if (neu::GetEngine().GetInput().GetKeyPressed(SDL_SCANCODE_ESCAPE)) quit = true;

        // Model Matrix
        rotation += neu::GetEngine().GetTime().GetDeltaTime() * 90;
        glm::mat4 model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(1.5f, 0.0f, 0.0f));
        model = glm::rotate(model, glm::radians(rotation), glm::vec3(0.0f, 0.0f, 1.0f));
        model = glm::scale(model, glm::vec3(0.5f, 0.5f, 0.5f));
        program->SetUniform("u_model", model);

        // View Matrix
        eye.x += neu::GetEngine().GetInput().GetMouseDelta().x * 0.01f;
        eye.z += neu::GetEngine().GetInput().GetMouseDelta().y * 0.01f;
        glm::mat4 view = glm::lookAt(eye, eye + glm::vec3{ 0, 0, -1 }, glm::vec3{ 0, 1, 0 });
        program->SetUniform("u_view", view);

        // Draw
        neu::GetEngine().GetRenderer().Clear();

        model3d->Draw(GL_TRIANGLES);

        neu::GetEngine().GetRenderer().Present();

        neu::GetEngine().GetRenderer().Present();
    }

    neu::GetEngine().Shutdown();

    return 0;
}
