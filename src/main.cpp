#include <GL/freeglut.h>
#include <player.h>
#include <environment.h>
#include <camera.h>
#include <constants.h>
#include <enemies/enemy_like.h>
#include <enemies/enemy_factory.h>
#include <iostream>
#include <effolkronium/random.hpp>
#include <enemies/basic_enemy_tank.h>

using Random = effolkronium::random_static;

Camera *camera;
Player *player;
Environment *environment;
EnemyFactory *enemyFactory;

std::list<Bullet> bulletList;
std::list<Wall *> wallList;
std::list<EnemyLike *> enemyList;

int mouseX, mouseY;
auto points = 0;
auto actualTime = 0;
auto pressedKeys = new char[256];

void createEnemy() {
    auto firstIndex = Random::get(0, static_cast<int>(WALLS_COORDINATES.size()) - 1);
    auto secondIndex = Random::get(0, static_cast<int>(WALLS_COORDINATES[firstIndex].size()) - 1);

    if (WALLS_COORDINATES[firstIndex][secondIndex] == 0)
        enemyList.push_back(new BasicEnemyTank{Vector3D{static_cast<float>(secondIndex * Wall::SIZE),
                                                        static_cast<float>(firstIndex * Wall::SIZE), 0}});
    else
        createEnemy();
}

void run(float delta) {
    std::list<Collidable *> collidables;
    collidables.insert(collidables.end(), wallList.begin(), wallList.end());
    collidables.insert(collidables.end(), enemyList.begin(), enemyList.end());
    collidables.push_back(player);

    environment->run(delta);

    if (pressedKeys[119] != 0)
        player->moveForward(delta, collidables);

    if (pressedKeys[115] != 0)
        player->moveBackward(delta, collidables);

    if (pressedKeys[97] != 0)
        player->rotateLeft(delta);

    if (pressedKeys[100] != 0)
        player->rotateRight(delta);

    player->rotateUpperPart(camera->getMouseRelativeCoordinates());
    player->run(delta);

    for (auto bullet = bulletList.begin(); bullet != bulletList.end(); ++bullet) {
        bullet->run(delta);

        if (bullet->shouldBeDestroyed(collidables))
            bullet = bulletList.erase(bullet);
    }

    for (auto enemy = enemyList.begin(); enemy != enemyList.end(); ++enemy) {
        (*enemy)->run(delta, collidables);

        if ((*enemy)->detectPlayer(wallList, player))
            bulletList.push_back((*enemy)->shoot());

        if ((*enemy)->shouldBeDestroyed()) {
            enemy = enemyList.erase(enemy);
            points += 1;
        }
    }

    if (!player->isAlive()) {
        std::cout << "Koniec gry! Zdobyłeś " << points << " punktów.";
        exit(0);
    }

    if (enemyList.size() * 10 < actualTime / 1000.0f)
        createEnemy();
}

void render() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    camera->run();
    player->render();
    environment->render();

    for (const auto bullet : bulletList)
        bullet.render();

    for (const auto enemy : enemyList)
        enemy->render();

    for (const auto wall : wallList)
        wall->render();

    glutSwapBuffers();
    glutPostRedisplay();
}

void display() {
    auto glutActualTime = glutGet(GLUT_ELAPSED_TIME);
    auto deltaTime = static_cast<float>((glutActualTime - actualTime) / 1e3);
    actualTime = glutActualTime;

    run(deltaTime);
    render();
}

void reshapeScreen(int width, int height) {
    glViewport(0, 0, (GLsizei) width, (GLsizei) height);
    glMatrixMode(GL_PROJECTION);
    gluPerspective(90, (GLfloat) width / (GLfloat) height, 0.1f, 100.0f);
    glMatrixMode(GL_MODELVIEW);
}

void keyDown(unsigned char key, int x, int y) {
    pressedKeys[key] = true;
}

void keyUp(unsigned char key, int x, int y) {
    pressedKeys[key] = false;
}

void mouseMotion(int x, int y) {
    camera->setMousePosition(Vector3D(x, y, 0));
}

void mousePassiveMotion(int x, int y) {
    camera->setMousePosition(Vector3D(x, y, 0));
}

void mouseButton(int button, int state, int x, int y) {
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
        bulletList.push_back(player->shoot());
}

void createInstances() {
    player = new Player{Vector3D{20, 20, 0}};
    environment = new Environment();
    camera = new Camera(player->getPosition());
    enemyFactory = new EnemyFactory();

    for (int i = 0; i < WALLS_COORDINATES.size(); ++i)
        for (int j = 0; j < WALLS_COORDINATES[i].size(); ++j)
            if (WALLS_COORDINATES[i][j] == 1)
                wallList.push_back(new Wall{Vector3D{static_cast<float>(j), static_cast<float>(i), 0} * Wall::SIZE});
}

void init(int argc, char **argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
    glutInitWindowPosition(0, 0);
    glutCreateWindow("Tanx");

    glClearColor(0, 0, 0, 0);
    glEnable(GL_DEPTH_TEST);

    for (int i = 0; i < 256; ++i)
        pressedKeys[i] = false;

    createInstances();
}

void createEventHandlers() {
    glutDisplayFunc(display);
    glutReshapeFunc(reshapeScreen);
    glutKeyboardFunc(keyDown);
    glutKeyboardUpFunc(keyUp);
    glutMotionFunc(mouseMotion);
    glutPassiveMotionFunc(mousePassiveMotion);
    glutMouseFunc(mouseButton);
}

void cleanUp() {
    delete camera;
    delete player;
    delete environment;
    delete enemyFactory;
    delete[] pressedKeys;
}

int main(int argc, char **argv) {
    init(argc, argv);
    createEventHandlers();
    glutMainLoop();
    cleanUp();
    return 0;
}
