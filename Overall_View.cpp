//#define NDEBUG
#include "Overall_View.h"
#include <iostream>
#include <limits>
#include <cassert>

using std::string;
using std::cout; using std::endl;
using std::min; using std::max;
using std::numeric_limits;

const double min_distance_c = 5.0;

const int overall_view_size_c = 25;
const double initial_overall_view_scale_c = 2.0;
const Point initial_overall_view_origin_c(-10.0, -10.0);

Overall_View::Overall_View() :
		Grid_View(overall_view_size_c,
				  initial_overall_view_scale_c,
				  initial_overall_view_origin_c),
		min_x(numeric_limits<double>::max()),
		max_x(numeric_limits<double>::min()),
		min_y(numeric_limits<double>::max()),
		max_y(numeric_limits<double>::min()) {}

void Overall_View::update_location(const std::string &name, Point location) {
    Grid_View::update_location(name, location);

    if (location.x >= min_x && location.x <= max_x &&
    	location.y >= min_y && location.y <= min_y) 	// does not need to change
    	return;

    // change borders
    min_x = min(min_x, location.x);
    max_x = max(max_x, location.x);
    min_y = min(min_y, location.y);
    max_y = max(max_y, location.y);

	double distance = max(max_y - min_y, max_x - min_x);	//TODO add comments

    distance = max(distance, min_distance_c);	//TODO add comments

    Grid_View::set_scale(distance / (overall_view_size_c - 1));	//TODO add comments

    Grid_View::set_origin(Point(min_x, min_y));
}

void Overall_View::print_info() {
    cout << "Overall View of the world:" << endl;
}
