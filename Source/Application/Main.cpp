
int main(int argc, char* argv[]) {
    neu::file::SetCurrentDirectory("Assets");
    LOG_INFO("current directory {}", neu::file::GetCurrentDirectory());

    // initialize Engine
    LOG_INFO("initialize engine...");
    neu::GetEngine().Initialize();

    // Initialize Scene
    SDL_Event e;
    bool quit = false;

    // Render to Texture
    auto renderTexture = std::make_shared<neu::RenderTexture>();
    renderTexture->Create(512, 512);
    neu::Resources().AddResource("renderTexture", renderTexture);


    // Scene
    auto scene = std::make_unique<neu::Scene>();
    scene->Load("Scenes/scene04.json");
    scene->Start();

    // Editor
    auto editor = std::make_unique<neu::Editor>();

    // MAIN LOOP
    while (!quit) {
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_EVENT_QUIT) {
                quit = true;
            }
            ImGui_ImplSDL3_ProcessEvent(&e);
        }

        // Update
        neu::GetEngine().Update();
        float dt = neu::GetEngine().GetTime().GetDeltaTime();

        if (neu::GetEngine().GetInput().GetKeyPressed(SDL_SCANCODE_ESCAPE)) quit = true;

        // Scene
        scene->Update(dt);

        // Editor
        editor->Begin();
        editor->UpdateGui(*scene);
        
        // Draw
        // Set ImGui
        ImGui::Begin("Editor");
        ImGui::End();

        scene->Draw(neu::GetEngine().GetRenderer());

        // Draw ImGui
        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        neu::GetEngine().GetRenderer().Present();
    }

    neu::GetEngine().GetRenderer().Present();
    return 0;
}
