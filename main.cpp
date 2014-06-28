#include <iostream>
#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MAIN
#define BOOST_TEST_MODULE ComponentSystem
#include <boost/test/unit_test.hpp>

#include <ComponentSystem/DefaultEntityManager.h>
#include <ComponentSystem/Component.h>
#include <ComponentSystem/Entity.h>
#include <ComponentSystem/EntityManagerException.h>

class TestComponent : public poison::Component {
public:
    TestComponent(const std::string* id)
        : poison::Component(id)
        , test(100)
    {

    }

    int getControlValue() { return test; }

    static const std::string* getId() {
        static std::string id = "test";
        return &id;
    }

protected:
    int test;
};

class TestComponent2 : public poison::Component {
public:
    TestComponent2(const std::string* id)
        : poison::Component(id)
        , test(101)
    {

    }

    int getControlValue() { return test; }

    static const std::string* getId() {
        static std::string id = "test2";
        return &id;
    }

protected:
    int test;
};

void initEM() {
    static poison::EntityManager* em = 0;
    if (!em) {
        ServiceContainer::sharedContainer().registerService<poison::DefaultEntityManager>();
    }
}

BOOST_AUTO_TEST_CASE( entity_manager_init )
{

    initEM();
    BOOST_CHECK( poison::EntityManager::instance() );

}

BOOST_AUTO_TEST_CASE( entity_creation )
{

    auto entity = new poison::Entity();
    BOOST_CHECK_EQUAL( entity->getId(), 1 );
    entity = new poison::Entity();
    BOOST_CHECK_EQUAL( entity->getId(), 2 );

}

BOOST_AUTO_TEST_CASE( entity_search )
{
    auto entity = poison::EntityManager::instance()->getEntity(1);
    BOOST_CHECK_EQUAL( entity->getId(), 1 );
    entity = poison::EntityManager::instance()->getEntity(2);
    BOOST_CHECK_EQUAL( entity->getId(), 2 );
}

BOOST_AUTO_TEST_CASE( components_creation )
{

    std::set<poison::Component*> createdComponents;

    auto entity = poison::EntityManager::instance()->getEntity(1).get();
    auto component = entity->addComponent<TestComponent>();
    createdComponents.insert(component);


    BOOST_CHECK_EQUAL( entity->getId(), 1 );
    BOOST_CHECK_EQUAL( component->getControlValue(), 100 );
    BOOST_CHECK_EQUAL( component->getEntityId(), 1 );

    component = entity->addComponent<TestComponent>();
    createdComponents.insert(component);
    BOOST_CHECK_EQUAL( entity->getId(), 1 );
    BOOST_CHECK_EQUAL( component->getControlValue(), 100 );
    BOOST_CHECK_EQUAL( component->getEntityId(), 1 );

    auto components = poison::EntityManager::instance()->getComponentsForEntity(entity);
    BOOST_CHECK_EQUAL( components.size(), 2 );

    for (auto component : components) {
        BOOST_CHECK( createdComponents.find(component) != createdComponents.end() );
    }

    // check whether other components doesn't intersect with components of the first entity

    createdComponents.clear();

    entity = poison::EntityManager::instance()->getEntity(2).get();

    component = entity->addComponent<TestComponent>();
    createdComponents.insert(component);

    BOOST_CHECK_EQUAL( entity->getId(), 2 );
    BOOST_CHECK_EQUAL( component->getEntityId(), 2 );

    component = entity->addComponent<TestComponent>();
    createdComponents.insert(component);

    BOOST_CHECK_EQUAL( entity->getId(), 2 );
    BOOST_CHECK_EQUAL( component->getEntityId(), 2 );

    components = poison::EntityManager::instance()->getComponentsForEntity(entity);
    BOOST_CHECK_EQUAL( components.size(), 2 );

    for (auto component : components) {
        BOOST_CHECK( createdComponents.find(component) != createdComponents.end() );
    }
}

BOOST_AUTO_TEST_CASE( components_removing )
{


    auto entity = poison::EntityManager::instance()->getEntity(1).get();
    auto components = poison::EntityManager::instance()->getComponentsForEntity(entity);


    BOOST_CHECK_EQUAL( components.size(), 2 );

    entity->removeComponent<TestComponent>();
    components = poison::EntityManager::instance()->getComponentsForEntity(entity);

    BOOST_CHECK_EQUAL( components.size(), 0 );

    entity = poison::EntityManager::instance()->getEntity(2).get();
    components = poison::EntityManager::instance()->getComponentsForEntity(entity);
    BOOST_CHECK_EQUAL( components.size(), 2 );
}

BOOST_AUTO_TEST_CASE( components_acquiring )
{
    auto entity = new poison::Entity();
    auto component1 = entity->addComponent<TestComponent>();
    auto component2 = entity->addComponent<TestComponent2>();

    BOOST_CHECK_EQUAL( component1, entity->getComponent<TestComponent>() );
    BOOST_CHECK_EQUAL( component2, entity->getComponent<TestComponent2>() );
    BOOST_CHECK_EQUAL( component1->getControlValue(), 100 );
    BOOST_CHECK_EQUAL( component2->getControlValue(), 101 );

}

BOOST_AUTO_TEST_CASE( components_removal )
{
    auto entity = poison::EntityManager::instance()->getEntity(3).get();
    entity->removeComponent<TestComponent2>();
    BOOST_CHECK( !entity->getComponent<TestComponent2>() );


}

BOOST_AUTO_TEST_CASE( entity_removal )
{
    auto entity = poison::EntityManager::instance()->getEntity(3).get();
    entity->remove();

    try {
        // should throw exception
        poison::EntityManager::instance()->getEntity(3);
        BOOST_CHECK( 0 );
    } catch (const poison::EntityManagerException& e) {

    }


    auto components = poison::EntityManager::instance()->getComponents<TestComponent>();

    for (auto component : components) {
        BOOST_CHECK( component->getEntityId() != 3 );
    }

}
