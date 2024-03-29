#ifndef COMPOSITE_H
#define COMPOSITE_H

#include "Component.h"
#include <map>

/*
 Composite is inherent from Component, and it have a container for Component.
 ?? todo
 */
class Composite: public Component, public std::enable_shared_from_this<Composite> {
public:
    Composite(const std::string & name) : Component(name) {}

    // return true because this is a composite
    bool is_composite() override { return true; }

    // add a component to this composite
    void add_component(std::shared_ptr<Component> elem) override;

    // remove the component with the given name if it is "this" or a child of "this"
    void remove_component(const std::string& name) override;

    // return a pointer of the child if found, return a nullptr otherwise
    std::shared_ptr<Component> get_child(std::string name) override;

    // output the children of this composite
    void describe() const override;

    // tell all the children to start moving to location destination_
    void move_to(Point destination_) override;
    
    // tell all the children to stop its activity
    void stop() override;

    // tell all the children to start working/attacking
    // if one child throws an Error, the process will continue to the next child
    void start_working(std::shared_ptr<Structure>, std::shared_ptr<Structure>) override;
    void start_attacking(std::shared_ptr<Component> target_ptr) override;

private:
    std::map<std::string, std::shared_ptr<Component>> children;
};

#endif
