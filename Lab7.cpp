#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFPhysics.h>
using namespace std;
using namespace sf;
using namespace sfp;

int main() {
    // Create our window and world with gravity 0, 1
    RenderWindow window(VideoMode(800, 600), "Bounce");
    World world(Vector2f(0, 1));

    // Create the ball
    PhysicsCircle ball;
    ball.setCenter(Vector2f(400, 100));
    ball.setRadius(20);
    world.AddPhysicsBody(ball);

    // Apply initial impulse
    ball.applyImpulse(Vector2f(-100, -200));

    // Create the floor
    PhysicsRectangle floor;
    floor.setSize(Vector2f(800, 20));
    floor.setCenter(Vector2f(400, 590));
    floor.setStatic(true);
    world.AddPhysicsBody(floor);

    // Create the walls and ceiling
    PhysicsRectangle leftWall, rightWall, ceiling;

    leftWall.setSize(Vector2f(20, 600));
    leftWall.setCenter(Vector2f(10, 300));
    leftWall.setStatic(true);
    world.AddPhysicsBody(leftWall);

    rightWall.setSize(Vector2f(20, 600));
    rightWall.setCenter(Vector2f(790, 300));
    rightWall.setStatic(true);
    world.AddPhysicsBody(rightWall);

    ceiling.setSize(Vector2f(800, 20));
    ceiling.setCenter(Vector2f(400, 10));
    ceiling.setStatic(true);
    world.AddPhysicsBody(ceiling);

    // Create the center obstacle
    PhysicsRectangle centerObstacle;
    centerObstacle.setSize(Vector2f(100, 20));
    centerObstacle.setCenter(Vector2f(400, 300));
    centerObstacle.setStatic(true);
    world.AddPhysicsBody(centerObstacle);

    int thudCount(0);
    floor.onCollision = [&thudCount](PhysicsBodyCollisionResult result) {
        cout << "thud " << thudCount << endl;
        thudCount++;
    };

    int bangCount(0);
    centerObstacle.onCollision = [&bangCount](PhysicsBodyCollisionResult result) {
        cout << "bang " << bangCount << endl;
        bangCount++;
        if (bangCount == 3) {
            exit(0);
        }
    };

    Clock clock;
    Time lastTime(clock.getElapsedTime());
    while (true) {
        // Calculate MS since the last frame
        Time currentTime(clock.getElapsedTime());
        Time deltaTime(currentTime - lastTime);
        int deltaTimeMS(deltaTime.asMilliseconds());
        if (deltaTimeMS > 0) {
            world.UpdatePhysics(deltaTimeMS);
            lastTime = currentTime;
        }
        window.clear(Color(0, 0, 0));
        window.draw(ball);
        window.draw(floor);
        window.draw(leftWall);
        window.draw(rightWall);
        window.draw(ceiling);
        window.draw(centerObstacle);
        window.display();
    }
}