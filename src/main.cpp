#include <GL/freeglut.h>
#include <player.h>
#include <cstdio>
#include <environment.h>
#include <camera.h>
#include <constants.h>
#include <enemies/enemy_like.h>
#include <enemies/enemy_factory.h>
#include <enemies/basic_enemy_tank.h>
#include <iostream>

Camera *camera;
Player *player;
Environment *environment;
EnemyFactory *enemyFactory;

std::list<Bullet> bulletList;
std::list<Wall *> wallList;
std::list<EnemyLike *> enemyList;

int mouseX, mouseY;
auto actualTime = 0;
auto pressedKeys = new char[256];

void run(float delta) {
    std::list<Collidable *> collidables;
    collidables.insert(collidables.end(), wallList.begin(), wallList.end());
    collidables.insert(collidables.end(), enemyList.begin(), enemyList.end());

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

        if ((*enemy)->shouldBeDestroyed())
            enemy = enemyList.erase(enemy);
    }
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
    player = new Player{Vector3D{0, 0, 0}};
    environment = new Environment();
    camera = new Camera(player->getPosition());
    enemyFactory = new EnemyFactory();

    for (const auto wallPosition : WALLS_POSITIONS)
        wallList.push_back(new Wall{wallPosition});

    enemyList.push_back(new BasicEnemyTank{Vector3D{-30, 10, 0}});
    enemyList.push_back(new BasicEnemyTank{Vector3D{-45, 15, 0}});
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
