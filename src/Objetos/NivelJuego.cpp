#include "NivelJuego.h"

///////////////////////////
////////CONSTRUCTORES//////

NivelJuego::NivelJuego()
{
}

////////////////////////
////////METODOS/////////

bool NivelJuego::init()
{
    //if (!scene.initializeScene()) {
       // return false;
    //}

    ///////////////////////////////////////////////////////
    // NPC
    ///////////////////////////////////////////////////////

    scene.agregarEntidad(
        glm::vec2(30, 30),
        glm::vec2(22, 26),
        "shaders/sprite.vs",
        "shaders/sprite.fs",
        "assets/npc.png"
    );

    ///////////////////////////////////////////////////////
    // TERRENO
    ///////////////////////////////////////////////////////

    scene.agregarTerreno(
        glm::vec2(0, 0),
        "shaders/sprite.vs",
        "shaders/sprite.fs",
        "assets/house.png"
    );

    ///////////////////////////////////////////////////////
    // JUGADOR
    ///////////////////////////////////////////////////////

    scene.agregaJugador(
        glm::vec2(100, 100),
        glm::vec2(22, 26),
        "shaders/sprite.vs",
        "shaders/sprite.fs",
        "assets/player.png"
    );

    // 1. Inicializar OpenGL y ventana
    if (!gl.InitializeGLFW(WINDOW_WIDTH, WINDOW_HEIGHT, "Proyecto SR38", false)) return false;
    input = (new InputClass(LOGICAL_WIDTH, LOGICAL_HEIGHT));
    gl.SetInput(input);
    window = gl.GetWindow();
    // Proyección ortográfica lógica
    proyection = glm::ortho(0.0f, LOGICAL_WIDTH, LOGICAL_HEIGHT, 0.0f);
    //NOTA: PARA MANTENER RELACION DE IMAGEN
    pixelRenderer = PixelPerfectRenderer(&gl, window, LOGICAL_WIDTH, LOGICAL_HEIGHT);
    if (!pixelRenderer.Initialize()) return false;

    // cargar shaders
    ResourceManager::LoadShader("sprite", "shaders/sprite.vs", "shaders/sprite.fs", &gl);
    ResourceManager::LoadShader("color", "shaders/color.vs", "shaders/color.fs", &gl);

    // crear renderers compartidos (uno para sprites si quieres y otro para outlines)
    auto spriteShader = ResourceManager::GetShader("sprite");
    if (spriteShader) ResourceManager::GetOrCreateRenderer("spriteRenderer", spriteShader);

    auto colorShader = ResourceManager::GetShader("color");
    if (colorShader) ResourceManager::GetOrCreateRenderer("outline", colorShader);

    scene.gl = gl;

    scene.window = window;

    return true;
}

void NivelJuego::update(float dt)
{
    scene.updateAll(dt);
    scene.drawAll();
}

void NivelJuego::draw()
{
    scene.drawAll(0.0f);
}

void NivelJuego::unload()
{
    scene.liberarMemoria();
}

bool NivelJuego::isFinished() const
{
    return finished;
}

int NivelJuego::nextLevel() const
{
    return next;
}



void NivelJuego::Run() const
{
    float last = (float)glfwGetTime();

    while (!scene.gl.WindowShouldClose()) {
        float now = (float)glfwGetTime();
        float dt = now - last;
        last = now;
        scene.pixelRenderer.Begin();
        scene.drawAll(dt);
        scene.pixelRenderer.End();
        glfwSwapBuffers(scene.gl.GetWindow());
        glfwPollEvents();
    }
}