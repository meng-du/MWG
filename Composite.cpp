#include "Composite.h"
#include "Geometry.h"
#include "Utility.h"
#include "Agent.h"
#include <cassert>
#include <iostream>

using std::shared_ptr;
using std::string;
using std::cout; using std::endl;


void Composite::add_component(shared_ptr<Component> elem) {
    // check if the elem is a valid component
    if (is_ancestor(elem))
        throw Error(get_name() + " cannot add its ancestor as a child!");
    if (shared_from_this() == elem)
        throw Error(get_name() + " cannot add itself as a child!");
    if (children.find(elem->get_name()) != children.end())
        throw Error(elem->get_name() + " is already in group " + get_name());
    if (elem->has_parent())
        throw Error(elem->get_name() + " already has a parent!");

    children[elem->get_name()] = elem;
    elem->parent = shared_from_this();
}

void Composite::remove_component(const string& name) {
    shared_ptr<Component> to_remove = get_child(name);
    if (to_remove) {
    	to_remove->parent.reset();
    	children.erase(name);
    }
}

shared_ptr<Component> Composite::get_child(std::string name) {
    auto finding = children.find(name);
    if (finding == children.end())
    	return nullptr;		// did not find this child
    return finding->second;
}

void Composite::describe() const {
	if (children.size() == 0) {
		cout << "Group " << get_name() << endl << "   is empty" << endl;
		return;
	}
    cout << "Group " << get_name() << " has " << children.size() << " component(s):" << endl;
    for(auto& p: children)
        cout << "   " << p.second->get_name() << endl;
}

void Composite::move_to(Point destination_) {
    for(auto& p: children)
        p.second->move_to(destination_);
}

void Composite::stop() {
    for(auto& p: children)
        p.second->stop();
}

void Composite::start_working(shared_ptr<Structure> source_,
                              shared_ptr<Structure> destination_) {
    for (auto& p: children) {
        try {
            p.second->start_working(source_, destination_);
        } catch (Error& err) {
            cout << err.what() << endl;
        }
        // try and throw error if one child cannot operate this action
        // so that the process can continue to the next child
    }
}

void Composite::start_attacking(shared_ptr<Component> target_ptr) {
	Component::start_attacking(target_ptr);
    for (auto& p: children) {
        try {
            p.second->start_attacking(target_ptr);
        } catch (Error& err) {
            cout << err.what() << endl;
        }
        // try and throw error if one child cannot operate this action
        // so that the process can continue to the next child
    }
}
