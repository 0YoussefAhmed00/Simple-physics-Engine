#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include "Particle.h"
#include "PhysicsWorld.h"
#include "Renderer.h"

using namespace sf;
using namespace std;

int main() {
    RenderWindow window(VideoMode(800, 600), "Collision Tests");

    Renderer renderer;
	PhysicsWorld physicsWorld;
    Particle* circleA = new Particle(Vector2d(100, 100), 1.0f, 0.0f);
    Particle* circleB = new Particle(Vector2d(700, 100), 1.0f, 0.0f);
    Particle* aabbA = new Particle(Vector2d(100, 300), 1.0f, 0.0f);
    Particle* aabbB = new Particle(Vector2d(700, 300), 1.0f, 0.0f);
    Particle* satA = new Particle(Vector2d(100, 500), 1.0f, 0.0f);
    Particle* satB = new Particle(Vector2d(700, 500), 1.0f, 0.0f);
    Particle* reflA = new Particle(Vector2d(100, 200), 2.0f, 0.0f);
    Particle* reflB = new Particle(Vector2d(700, 200), 1.0f, 0.0f);

    circleA->velocity = Vector2d(80, 0);
    circleB->velocity = Vector2d(-80, 0);
    aabbA->velocity = Vector2d(100, 0);
    aabbB->velocity = Vector2d(-100, 0);
    satA->velocity = Vector2d(60, 0);
    satB->velocity = Vector2d(-60, 0);
    reflA->velocity = Vector2d(120, 0);
    reflB->velocity = Vector2d(-60, 0);

    satA->collider_sat.points = {
        Vector2d(-5, -5), Vector2d(5, -5), Vector2d(5, 5), Vector2d(-5, 5)
    };
    satB->collider_sat.points = {
        Vector2d(-16, -16), Vector2d(16, -16), Vector2d(16, 16), Vector2d(-16, 16)
    };
    satA->collider_sat.updatePosition(satA->postion);
    satB->collider_sat.updatePosition(satB->postion);

    CircleShape sCircleA(10); sCircleA.setOrigin(10, 10); sCircleA.setFillColor(Color::Red);
    CircleShape sCircleB(10); sCircleB.setOrigin(10, 10); sCircleB.setFillColor(Color::Red);
    CircleShape sAabbA(10);   sAabbA.setOrigin(10, 10);   sAabbA.setFillColor(Color::Blue);
    CircleShape sAabbB(10);   sAabbB.setOrigin(10, 10);   sAabbB.setFillColor(Color::Blue);
    CircleShape sSatA(10);    sSatA.setOrigin(10, 10);    sSatA.setFillColor(Color(200, 100, 30));
    CircleShape sSatB(10);    sSatB.setOrigin(10, 10);    sSatB.setFillColor(Color(200, 100, 30));
    CircleShape sReflA(10);   sReflA.setOrigin(10, 10);   sReflA.setFillColor(Color::Magenta);
    CircleShape sReflB(10);   sReflB.setOrigin(10, 10);   sReflB.setFillColor(Color::Magenta);

    bool circleCollided = false;
    bool aabbCollided = false;
    bool satCollided = false;
    bool reflectionCollided = false;

   
    Clock clock;

    while (window.isOpen()) {
        Event event;
        while (window.pollEvent(event)) {
            if (event.type == Event::Closed)
                window.close();
        }

        float dt = clock.restart().asSeconds();
        
        circleA->Update(dt);
        circleB->Update(dt);
        aabbA->Update(dt);
        aabbB->Update(dt);
        satA->Update(dt);
        satB->Update(dt);
        reflA->Update(dt);
        reflB->Update(dt);

        satA->collider_sat.updatePosition(satA->postion);
        satB->collider_sat.updatePosition(satB->postion);
        aabbA->collider_aabb.updatePosition(aabbA->postion);
        aabbB->collider_aabb.updatePosition(aabbB->postion);

        if (!circleCollided && circleA->collider.checkCollision(circleB->collider)) {
            circleCollided = true;
            cout << "Circle collision detected\n";
            circleA->velocity = Vector2d(0, 0);
            circleB->velocity = Vector2d(0, 0);
            sCircleA.setFillColor(Color::Green);
            sCircleB.setFillColor(Color::Green);
        }
        if (!aabbCollided && aabbA->collider_aabb.checkCollision(aabbB->collider_aabb)) {
            aabbCollided = true;
            cout << "AABB collision detected\n";
            aabbA->velocity = Vector2d(0, 0);
            aabbB->velocity = Vector2d(0, 0);
            sAabbA.setFillColor(Color::Green);
            sAabbB.setFillColor(Color::Green);
        }
        if (!satCollided && satA->collider_sat.checkCollision(satB->collider_sat)) {
            satCollided = true;
            cout << "SAT collision detected\n";
            satA->velocity = Vector2d(0, 0);
            satB->velocity = Vector2d(0, 0);
            sSatA.setFillColor(Color::Green);
            sSatB.setFillColor(Color::Green);
        }
        if (!reflectionCollided && reflA->collider.checkCollision(reflB->collider)) {
            reflectionCollided = true;
            cout << "Impulse reflection circle collision detected\n";
            PhysicsWorld::ResolveCircleCollision(reflA, reflB, 0.9f);
            sReflA.setFillColor(Color::Cyan);
            sReflB.setFillColor(Color::Cyan);
        }

        sCircleA.setPosition(circleA->postion.x, circleA->postion.y);
        sCircleB.setPosition(circleB->postion.x, circleB->postion.y);
        sAabbA.setPosition(aabbA->postion.x, aabbA->postion.y);
        sAabbB.setPosition(aabbB->postion.x, aabbB->postion.y);
        sSatA.setPosition(satA->postion.x, satA->postion.y);
        sSatB.setPosition(satB->postion.x, satB->postion.y);
        sReflA.setPosition(reflA->postion.x, reflA->postion.y);
        sReflB.setPosition(reflB->postion.x, reflB->postion.y);

        renderer.AddDrawable(&sCircleA);
        renderer.AddDrawable(&sCircleB);
        renderer.AddDrawable(&sAabbA);
        renderer.AddDrawable(&sAabbB);
        renderer.AddDrawable(&sSatA);
        renderer.AddDrawable(&sSatB);
        renderer.AddDrawable(&sReflA);
        renderer.AddDrawable(&sReflB);

        renderer.Render(&window);
    }

    delete circleA; delete circleB;
    delete aabbA; delete aabbB;
    delete satA; delete satB;
    delete reflA; delete reflB;
    return 0;
}