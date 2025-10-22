
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

    model3d->Load("Models/sphere.obj");

    // Shaders
    auto vs = neu::Resources().Get<neu::Shader>("Shaders/basic_lit.vert", GL_VERTEX_SHADER);
    auto fs = neu::Resources().Get<neu::Shader>("Shaders/basic_lit.frag", GL_FRAGMENT_SHADER);

    // Program
    auto program = std::make_shared<neu::Program>();
    program->AttachShader(vs);
    program->AttachShader(fs);
    program->Link();
    program->Use();

    // Texture
    neu::res_t<neu::Texture> texture = neu::Resources().Get<neu::Texture>("Textures/SpongeShrug.png");
    program->SetUniform("u_texture", 0);

    // Lighting
    program->SetUniform("u_ambient_light", glm::vec3{ 0.0f, 0.0f, 0.0f });
    neu::Transform light{ { 2, 4, 5 } };

    // Transform
    neu::Transform transform{ { 1, 0, 0 } };
    neu::Transform camera{ { 0, 0, 5 } };

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
        float dt = neu::GetEngine().GetTime().GetDeltaTime();

        if (neu::GetEngine().GetInput().GetKeyPressed(SDL_SCANCODE_ESCAPE)) quit = true;

        // Model Matrix
        transform.rotation.y = 90 * dt;
        program->SetUniform("u_model", transform.GetMatrix());
        
        // View Matrix
        float speed = 10.0f;
        if (neu::GetEngine().GetInput().GetKeyDown(SDL_SCANCODE_W)) camera.position.z -= speed * dt;
        if (neu::GetEngine().GetInput().GetKeyDown(SDL_SCANCODE_A)) camera.position.x -= speed * dt;
        if (neu::GetEngine().GetInput().GetKeyDown(SDL_SCANCODE_S)) camera.position.z += speed * dt;
        if (neu::GetEngine().GetInput().GetKeyDown(SDL_SCANCODE_D)) camera.position.x += speed * dt;
        if (neu::GetEngine().GetInput().GetKeyDown(SDL_SCANCODE_Q)) camera.position.y += speed * dt;
        if (neu::GetEngine().GetInput().GetKeyDown(SDL_SCANCODE_E)) camera.position.y -= speed * dt;

        glm::mat4 view = glm::lookAt(camera.position, camera.position + glm::vec3{ 0, 0, -1 }, glm::vec3{ 0, 1, 0 });
        program->SetUniform("u_view", view);
        program->SetUniform("u_light.position", (glm::vec3)(view * glm::vec4(light.position, 1)));
        program->SetUniform("u_light.color", glm::vec3{ 0.6f, 0.7f, 0.8f });
        light.position.x = neu::math::sin(neu::GetEngine().GetTime().GetTime() * 3);

        // Draw
        neu::GetEngine().GetRenderer().Clear();

        model3d->Draw(GL_TRIANGLES);

        neu::GetEngine().GetRenderer().Present();
    }

    neu::GetEngine().GetRenderer().Present();
    return 0;
}
